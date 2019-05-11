#pragma once

#include <memory>

#include "Set.hpp"

class Network
{
private:
    int m_num_suppliers;
    int m_num_storages;

    std::shared_ptr<Set> m_graph;
public:
    Network(int num_suppliers, int num_storages);

    int countSuppliers();
    int countStorages();

    std::shared_ptr<Set> getGraph();
};