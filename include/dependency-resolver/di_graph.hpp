#pragma once
#include <vector>
#include <unordered_map>
#include "core/injectable.hpp"
#include "core/di_key.hpp"

class DIGraph{
    private:
        std::unordered_map<DIKey, Injectable*,DIKeyHash> &graph;
        std::unordered_map<DIKey, std::vector<DIKey>,DIKeyHash> adjacencyList;
        std::unordered_map<DIKey, int,DIKeyHash> indegree;
        bool dfsVisit(const DIKey& node, std::unordered_map<DIKey, int, DIKeyHash>& state, std::unordered_map<DIKey, DIKey, DIKeyHash>& parent, std::vector<DIKey>& cycle);
    public:
        DIGraph(std::unordered_map<DIKey, Injectable*,DIKeyHash> &graph);
        std::vector<DIKey> findCycle();
        std::vector<DIKey> resolveDependencies();
};