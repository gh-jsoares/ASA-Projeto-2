#include "Network.hpp"

Network::Network(int num_suppliers, int num_storages) : m_num_suppliers(num_suppliers), m_num_storages(num_storages)
{
    m_graph = std::make_shared<Graph>(0, num_suppliers);
}

int Network::countSuppliers()
{
    return m_num_suppliers;
}

int Network::countStorages()
{
    return m_num_storages;
}

std::shared_ptr<Graph> Network::getGraph()
{
    return m_graph;
}

bool Network::isStorage(int node_id)
{
    return node_id > m_num_suppliers + 1;
}