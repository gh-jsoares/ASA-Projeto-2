#include <iostream>

#include "Writer.hpp"
#include "Network.hpp"
#include "Connection.hpp"

void Writer::write(Network network)
{
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

    std::cout << "Connections: " << std::endl;
    int cc = network.countConnections();
    auto connections = network.getConnections();
    for (int i = 0; i < cc; i++) {
        std::cout << i + 1 << " - ";

        for (auto it = connections[i].begin(); it != connections[i].end(); ++it) {
            Connection con = *(*it).get();
            std::cout << con.getVertexId() << "(W: " << con.getWeight() << ")" << " - ";
        }

        std::cout << "\\" << std::endl;
    }

}