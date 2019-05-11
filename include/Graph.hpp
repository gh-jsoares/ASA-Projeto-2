#pragma once

#include <vector>
#include <memory>
#include <bits/stdc++.h>

#include "utils.hpp"
#include "Node.hpp"
#include "Connection.hpp"

class Graph
{
private:
    int m_num_vertices;
    int m_num_suppliers;

    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Connection>> m_connections;
    
    std::vector<std::shared_ptr<Connection>> m_increases;

    bool push(std::shared_ptr<Node> node);
    void relabel(std::shared_ptr<Node> node);
    void preflow(std::shared_ptr<Node> origin);
    void updateReverseEdgeFlow(std::shared_ptr<Connection> connection, int flow);
    std::shared_ptr<Node> overFlowNode();

    bool calculateIncreasesRecursive(std::shared_ptr<Node> node, bool *visited);
public:
    Graph(int num_vertices, int num_suppliers);

    void addNode(std::shared_ptr<Node> node);
    void addConnection(std::shared_ptr<Node> origin, std::shared_ptr<Node> destination, int capacity);

    int getMaxFlow();
    std::shared_ptr<Node> getSource();
    std::shared_ptr<Node> getTail();
    std::shared_ptr<Node> getNode(int id);
    int getNodeIndex(std::shared_ptr<Node> node);
    bool isStorage(int node_id);

    void calculateIncreases();
    std::vector<std::shared_ptr<Connection>> getIncreases();
};