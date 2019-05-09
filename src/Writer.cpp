#include <iostream>

#include "Writer.hpp"
#include "Network.hpp"

void Writer::write(Network network) {
    std::cout << "Suppliers: "   << network.countSuppliers()   << std::endl;
    std::cout << "Storages: "    << network.countStorages()    << std::endl;
    std::cout << "Connections: " << network.countConnections() << std::endl;
}

// std::istringstream ss(your_string_here);
// std::vector<int> vec(std::istream_iterator<int>(ss), {});