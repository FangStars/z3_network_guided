#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

struct Edge {
    std::string node1;
    std::string port1;
    std::string node2;
    std::string port2;
    Edge(const std::string& n1, const std::string& p1, const std::string& n2, const std::string& p2) : node1(n1), port1(p1), node2(n2), port2(p2) {}
};

struct NodePortPeer {
    std::string node;
    std::string port;
    NodePortPeer(const std::string& n, const std::string& p) : node(n), port(p) {}
};

struct Neighbor {
    std::string srcPort;
    std::string dstNode;
    std::string dstPort;
    Neighbor(const std::string& sp, const std::string& dn, const std::string& dp) : srcPort(sp), dstNode(dn), dstPort(dp) {}
};

class Graph {
public:
    Graph() {}

    void addNode(const std::string& node);

    void addEdge(const std::string& node1, const std::string& port1, const std::string& node2, const std::string& port2);

    bool hasNode(const std::string& node) const;

    bool hasEdge(const std::string& node1, const std::string& port1, const std::string& node2, const std::string& port2) const;

    int numNodes() const;

    int numEdges() const;

    std::vector<std::string> getNodeList() const;

    std::vector<Neighbor> getNeighborList(const std::string& node) const;

    void BFS(const std::string& startNode);

    int getDistanceToOrigin(const std::string& node) const;


private:
    std::unordered_map<std::string, std::vector<Neighbor>> adjList;

    std::unordered_map<std::string, int> distanceMap;

    //std::unordered_map<std::pair<std::string, std::string>, int> distanceMap;

    int nodesNum = 0;

    int edgesNum = 0;
};

extern Graph g_graph;
extern bool g_is_queued;