#include <memory>
#include <iostream>
#include <vector>
#include <list>

#include "Network.hpp"
#include "Supplier.hpp"

Network::Network(int num_suppliers, int num_storages)
{
    this->num_suppliers   = num_suppliers;
    this->num_storages    = num_storages;
    this->num_connections = num_suppliers + num_storages + 1; // 1 is the final destination

    this->connections = new std::vector<std::shared_ptr<Connection>>[this->num_connections];
}

Network::~Network()
{
    for (int i = 0; i < this->num_connections; i++)
        this->connections[i].clear();

    delete [] this->connections;
}

int Network::countSuppliers()
{
    return this->num_suppliers;
}

int Network::countStorages()
{
    return this->num_storages;
}

int Network::countConnections()
{
    return this->num_connections;
}

void Network::addSupplier(int amount)
{
    int id = this->nextSupplierId();

    auto supplier = std::make_shared<Supplier>(id, amount);
    this->suppliers.push_back(supplier);
}

int Network::nextSupplierId()
{
    return getSuppliers().size() + 2; // Os números de 2 a f+1 representam fornecedores
}

std::vector<std::shared_ptr<Supplier>> Network::getSuppliers()
{
    return this->suppliers;
}

void Network::addStorage(int amount)
{
    int id = this->nextStorageId();

    auto supplier = std::make_shared<Storage>(id, amount);
    this->storages.push_back(supplier);
}

int Network::nextStorageId()
{
    return getStorages().size() + countSuppliers() + 2 ; // Os restantes números representam estações de abastecimento e controlo
}

std::vector<std::shared_ptr<Storage>> Network::getStorages()
{
    return this->storages;
}

void Network::addConnection(int origin_id, int destiny_id, int capacity)
{
    int u = origin_id - 1; // index is id - 1 (should start at 0)
    int v = destiny_id - 1; // index is id - 1 (should start at 0)

    auto connection1 = std::make_shared<Connection>(destiny_id, capacity);
    auto connection2 = std::make_shared<Connection>(origin_id, 0);

    connection1->setReverseConnection(connection2);
    connection2->setReverseConnection(connection1);

    this->connections[u].push_back(connection1);
    this->connections[v].push_back(connection2);
}

std::vector<std::shared_ptr<Connection>> *Network::getConnections()
{
    return this->connections;
}

bool Network::bfs(int source_id, int target_id)
{
    int s = source_id - 1; // index is id - 1 (should start at 0)

    std::list<int> queue;
    queue.push_back(s);
    while(!queue.empty()) {
        int u = queue.front();
        queue.pop_front();

        auto connections = getConnections()[u];
        for (auto it = connections.begin(); it < connections.end(); ++it) {
            Connection *connection = (*it).get();
        }
        
    }
}