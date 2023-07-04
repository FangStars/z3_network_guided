// ADD_BEGIN
#include "graph.h"
#include "z3_exception.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


Graph g_graph;
bool g_is_queued = false;
bool g_is_init = false;

void Graph::addNode(const std::string& node) {
    if (!hasNode(node)) {
        adjList[node] = std::vector<Neighbor>();
        nodesNum++;
    }
}

void Graph::addEdge(const std::string& node1, const std::string& port1, const std::string& node2, const std::string& port2) {
    addNode(node1);
    if (!hasEdge(node1, port1, node2, port2)) {
        adjList[node1].push_back(Neighbor(port1, node2, port2));
        edgesNum++;
    }
}

bool Graph::hasNode(const std::string& node) const {
    return adjList.count(node) > 0;
}

bool Graph::hasEdge(const std::string& node1, const std::string& port1, const std::string& node2, const std::string& port2) const {
    if (!hasNode(node1)) {
        return false;
    }

    for (const auto& neighbor : adjList.at(node1)) {
        if (neighbor.srcPort == port1 && neighbor.dstNode == node2 && neighbor.dstPort == port2) {
            return true;
        }
    }

    return false;
}

int Graph::numNodes() const {
    return nodesNum;
}

int Graph::numEdges() const {
    return edgesNum;
}

std::vector<std::string> Graph::getNodeList() const {
    std::vector<std::string> nodes;
    for (const auto& entry : adjList) {
        nodes.push_back(entry.first);
    }
    return nodes;
}

std::vector<Neighbor> Graph::getNeighborList(const std::string& node) const {
    std::vector<Neighbor> neighbors;
    if (hasNode(node)) {
        for (const auto& neighbor : adjList.at(node)) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

void Graph::init(const std::string& topologyPath)
{
    std::ifstream file(topologyPath);
    if (!file) {
        throw default_exception("Error opening topology file: " + topologyPath);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, '@')) {
            tokens.push_back(token);
        }
        if (tokens.size() < 4) {
            std::cerr << "Invalid line: " << line << '\n';
            continue;
        }

        addEdge(tokens[0], tokens[1], tokens[2], tokens[3]);
    }
    //std::cout << g_graph.numEdges() << std::endl;
}

void Graph::BFS(const std::string& startNode) {
    std::queue <std::string> q;
    std::vector<std::string> visited;

    q.push(startNode);
    distanceMap[startNode] = 0;
    int distance = 0;

    while (!q.empty()) {
        std::string currNode = q.front();
        q.pop();

        for (const auto& neighbor : adjList[currNode]) {
            auto nextNode = neighbor.dstNode;
            
            if (std::find(visited.begin(), visited.end(), nextNode) == visited.end()) {
                q.push(nextNode);
                visited.push_back(currNode);
                distanceMap[nextNode] = distanceMap[currNode] + 1;
            }
        }
    }
}

int Graph::getDistanceToOrigin(const std::string& node, const std::string litera) const {
    //if (distanceMap.find(node) == distanceMap.end())
    //{
    //    return 100;
    //}
    int res;
    try {
        res = distanceMap.at(node);
    }
    catch (std::out_of_range& exc) {
        int size = distanceMap.size();
        throw default_exception("Exception at distanceMap: "+ node + litera);
    }
    return res ;
}

// ADD_END