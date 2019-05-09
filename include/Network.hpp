#pragma once

#include <memory>
#include <vector>

#include "Supplier.hpp"

class Network
{
private:
    int num_suppliers;
    int num_storages;
    int num_connections;

    std::vector<std::shared_ptr<Supplier>> suppliers;

public:
    Network(int num_suppliers, int num_storages, int num_connections);
    ~Network();

    int countSuppliers();
    int countStorages();
    int countConnections();
};