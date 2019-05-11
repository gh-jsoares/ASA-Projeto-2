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
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Connection>> m_connections;

    bool push(std::shared_ptr<Node> node);
    void relabel(std::shared_ptr<Node> node);
    void preflow(std::shared_ptr<Node> origin);
    void updateReverseEdgeFlow(std::shared_ptr<Connection> connection, int flow);
    std::shared_ptr<Node> overFlowNode();
public:
    int m_num_vertices;
    Graph(int num_vertices);

    void addNode(std::shared_ptr<Node> node);
    void addConnection(std::shared_ptr<Node> origin, std::shared_ptr<Node> destination, int capacity);

    int getMaxFlow();
    std::shared_ptr<Node> getSource();
    std::shared_ptr<Node> getNode(int id);
};