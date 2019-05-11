#pragma once

#include <memory>

#include "Graph.hpp"

class Network
{
private:
    int m_num_suppliers;
    int m_num_storages;

    std::shared_ptr<Graph> m_graph;
public:
    Network(int num_suppliers, int num_storages);

    int countSuppliers();
    int countStorages();

    std::shared_ptr<Graph> getGraph();
    
    bool isStorage(int node_id);
};