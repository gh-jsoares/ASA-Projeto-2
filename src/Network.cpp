#include "Network.hpp"

Network::Network(int num_suppliers, int num_storages) : m_num_suppliers(num_suppliers), m_num_storages(num_storages)
{
    m_graph = std::make_shared<Set>(num_suppliers + num_storages * 2 + 2, num_suppliers);
}

int Network::countSuppliers()
{
    return m_num_suppliers;
}

int Network::countStorages()
{
    return m_num_storages;
}

std::shared_ptr<Set> Network::getGraph()
{
    return m_graph;
}
