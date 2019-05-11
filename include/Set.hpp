#pragma once

#include <vector>
#include <memory>
#include <bits/stdc++.h>

#include "utils.hpp"

struct Node
{
    int id;
    int excess_flow = 0;
    int height = 0;

    Node(int id);
};

struct Edge
{
    int flow;
    int capacity;
    std::shared_ptr<Node> node;

    Edge(int flow, int capacity, std::shared_ptr<Node> node);
};

class Set
{
private:
    int m_num_nodes;
    int m_f; // num suppliers

    std::vector<std::shared_ptr<Edge>> *m_adj;
    std::shared_ptr<Node> *m_nodes; // available nodes

    void addEdge(int origin_id, int destination_id, int flow, int capacity);

    int getNodeIndex(std::shared_ptr<Node> node);
    int getNodeIndex(int id);

    int getNodeId(int index);

    bool isStorage(std::shared_ptr<Node> node);

    std::shared_ptr<Node> getNode(int id);
    std::shared_ptr<Node> createNode(int id);

    // relabel
    std::shared_ptr<Node> overFlowNode();
    void preflow(std::shared_ptr<Node> origin);
    void updateReverseEdgeFlow(int origin_id, int destination_id, int flow);
    bool push(std::shared_ptr<Node> node);
    void relabel(std::shared_ptr<Node> node);

public:
    Set(int num_nodes, int f);
    ~Set();

    void addEdge(int origin_id, int destination_id, int capacity);

    bool isStorage(int id);

    int getMaxFlow();
};