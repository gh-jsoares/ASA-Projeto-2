#include "Network.hpp"

Network::Network(int num_suppliers, int num_storages, int num_connections)
{
    this->num_suppliers   = num_suppliers;
    this->num_storages    = num_storages;
    this->num_connections = num_connections;
}

Network::~Network() {

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