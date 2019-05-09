#pragma once

#include <memory>
#include <vector>

#include "Supplier.hpp"
#include "Storage.hpp"
#include "Connection.hpp"

class Network
{
private:
    int num_suppliers;
    int num_storages;
    int num_connections;

    std::vector<std::shared_ptr<Supplier>> suppliers;
    std::vector<std::shared_ptr<Storage>> storages;

    std::vector<std::shared_ptr<Connection>> *connections;

public:
    Network(int num_suppliers, int num_storages);
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

    void addConnection(int origin_id, int destiny_id, int weight);
    std::vector<std::shared_ptr<Connection>> *getConnections();
};