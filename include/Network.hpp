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

    std::shared_ptr<Node> origin;
    std::weak_ptr<Edge> relative;

    Edge(int flow, int capacity, std::shared_ptr<Node> node, std::shared_ptr<Node> origin);
    Edge(int flow, int capacity, std::shared_ptr<Node> node, std::shared_ptr<Node> origin, std::shared_ptr<Edge> relative);
};

class Network
{
private:
    int m_num_nodes;
    int m_f; // num suppliers

    std::vector<std::shared_ptr<Edge>> *m_adj;
    std::vector<std::shared_ptr<Edge>> *m_adj_bkp;
    std::shared_ptr<Node> *m_nodes; // available nodes
    std::vector<std::shared_ptr<Edge>> m_increases; // what should change

    std::shared_ptr<Edge> addEdge(int origin_id, int destination_id, int flow, int capacity);
    std::shared_ptr<Edge> addEdge(int origin_id, int destination_id, int flow, int capacity, std::shared_ptr<Edge> relative);

    int getNodeIndex(std::shared_ptr<Node> node);
    int getNodeIndex(int id);

    int getNodeId(int index);

    bool isStorage(std::shared_ptr<Node> node);

    std::shared_ptr<Node> getNode(int id);

    // relabel
    std::shared_ptr<Node> overFlowNode();
    void preflow(std::shared_ptr<Node> origin);
    void updateReverseEdgeFlow(int origin_id, int destination_id, int flow, std::shared_ptr<Edge> edge);
    bool push(std::shared_ptr<Node> node);
    void relabel(std::shared_ptr<Node> node);

    // dfs
    void DFSUtil(int index, bool *visited);

    void debug();
public:
    Network(int num_nodes, int f);
    ~Network();

    void addEdge(int origin_id, int destination_id, int capacity);

    bool isStorage(int id);

    int getMaxFlow();

    void DFS();
};