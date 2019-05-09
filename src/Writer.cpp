#include <iostream>

#include "Writer.hpp"
#include "Network.hpp"

void Writer::write(Network network) {
    std::cout << "Suppliers: "   << network.countSuppliers()   << std::endl;
    std::cout << "Storages: "    << network.countStorages()    << std::endl;
    std::cout << "Connections: " << network.countConnections() << std::endl;

    std::cout << "Suppliers: " << std::endl;
    auto suppliers = network.getSuppliers();

    for(auto it = suppliers.begin(); it != suppliers.end(); ++it) {
        std::cout << "id: " << (*it)->getId() << " | amount: " << (*it)->getAmount() << std::endl;
    }

    std::cout << "Storages: " << std::endl;
    auto storages = network.getStorages();

    for(auto it = storages.begin(); it != storages.end(); ++it) {
        std::cout << "id: " << (*it)->getId() << " | amount: " << (*it)->getAmount() << std::endl;
    }
}