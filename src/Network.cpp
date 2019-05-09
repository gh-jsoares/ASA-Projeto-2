#include <memory>

#include "Network.hpp"
#include "Supplier.hpp"

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

void Network::addSupplier(int amount)
{
    int id = this->nextSupplierId();

    std::shared_ptr<Supplier> supplier = std::make_shared<Supplier>(id, amount);
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

    std::shared_ptr<Storage> supplier = std::make_shared<Storage>(id, amount);
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
