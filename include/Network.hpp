#pragma once

#include <memory>
#include <vector>

#include "Supplier.hpp"
#include "Storage.hpp"

class Network
{
private:
    int num_suppliers;
    int num_storages;
    int num_connections;

    std::vector<std::shared_ptr<Supplier>> suppliers;
    std::vector<std::shared_ptr<Storage>> storages;

public:
    Network(int num_suppliers, int num_storages, int num_connections);
    ~Network();

    int countSuppliers();
    int countStorages();
    int countConnections();

    void addSupplier(int amount);
    int nextSupplierId();
    std::vector<std::shared_ptr<Supplier>> getSuppliers();

    void addStorage(int amount);
    int nextStorageId();
    std::vector<std::shared_ptr<Storage>> getStorages();
};