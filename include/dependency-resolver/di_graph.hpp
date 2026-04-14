#pragma once
#include <vector>
#include <unordered_map>
#include <injectable.hpp>
#include <di_key.hpp>

class DIGraph{
    private:
        std::unordered_map<DIKey, Injectable*,DIKeyHash> &graph;
        std::unordered_map<DIKey, std::vector<DIKey>,DIKeyHash> adjacencyList;
        std::unordered_map<DIKey, int,DIKeyHash> indegree;
        std::vector<DIKey> sortedList;
    public:
        DIGraph(std::unordered_map<DIKey, Injectable*,DIKeyHash> &graph) : graph(graph) {
            for (const auto& pair : graph) {
                const DIKey& key = pair.first;  
                adjacencyList[key] = std::vector<DIKey>();
            }
        } 

};