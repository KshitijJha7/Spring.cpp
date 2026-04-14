#include <dependency-resolver/di_graph.hpp>
#include <queue>
#include <algorithm>
#include <stdexcept>

DIGraph::DIGraph(std::unordered_map<DIKey, Injectable*, DIKeyHash>& graph) : graph(graph) {
    for (const auto& [di_key, injectable] : graph) {
        if(injectable->getCtor() != nullptr) {
            for (const auto& dep : injectable->getCtor()->getDependencyKeys()) {
                adjacencyList[dep].push_back(di_key);
                indegree[di_key]++;
            }
        }
    }
}

bool DIGraph::dfsVisit(const DIKey& node, std::unordered_map<DIKey, int, DIKeyHash>& state, std::unordered_map<DIKey, DIKey, DIKeyHash>& parent, std::vector<DIKey>& cycle) {
    state[node] = 1;

    for (const auto& neighbor : adjacencyList[node]) {
        if (state[neighbor] == 1) {
            cycle.push_back(neighbor);
            DIKey curr = node;
            while (!(curr == neighbor)) {
                cycle.push_back(curr);
                curr = parent.at(curr);
            }
            cycle.push_back(neighbor);
            std::reverse(cycle.begin(), cycle.end());
            return true;
        }
        if (state[neighbor] == 0) {
            parent.insert_or_assign(neighbor, node);
            if (dfsVisit(neighbor, state, parent, cycle)) return true;
        }
    }

    state[node] = 2;
    return false;
}

std::vector<DIKey> DIGraph::findCycle() {
    std::unordered_map<DIKey, int, DIKeyHash> state;
    std::unordered_map<DIKey, DIKey, DIKeyHash> parent;
    std::vector<DIKey> cycle;

    for (const auto& [di_key, _] : graph) {
        if (state[di_key] == 0) {
            if (dfsVisit(di_key, state, parent, cycle)) return cycle;
        }
    }

    return cycle;
}

std::vector<DIKey> DIGraph::resolveDependencies() {
    std::vector<DIKey> topoList;
    std::queue<DIKey> q;
    for (const auto& [di_key, _] : graph) {
        if (indegree[di_key] == 0) {
            q.push(di_key);
        }
    }

    while (!q.empty()) {
        DIKey current = q.front();
        q.pop();
        topoList.push_back(current);

        for (const auto& neighbor : adjacencyList[current]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (topoList.size() != graph.size()) {
        auto cycle = findCycle();
        std::string cycleStr;
        for (const auto& key : cycle) {
            cycleStr += key.type.name() + (key.qualifier.empty() ? "" : ":" + key.qualifier) + " -> ";
        }
        cycleStr = cycleStr.substr(0, cycleStr.size() - 4);
        throw std::runtime_error("Cycle detected in dependency graph: " + cycleStr);
    }

    return topoList;
}
