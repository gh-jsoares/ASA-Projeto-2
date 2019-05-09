#include <iostream>
#include <sstream>

#include "Parser.hpp"
#include "Network.hpp"

std::string Parser::read_line() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string Parser::read_three_num_line(int *a, int *b, int *c)
{
    std::string line = read_line();
    sscanf(line.c_str(), "%d %d %d", a, b, c);
    return line;
}

void Parser::cycle_line(std::string line, Network *network, int type)
{
    std::istringstream sstream(line);
    int n;
    while(sstream >> n) {
        switch (type) {
        case TYPE_SUPPLIER:
            network->addSupplier(n);
            break;

        case TYPE_STORAGE:
            network->addStorage(n);
            break;

        default:
            break;
        }
    }
}

Network Parser::factory() {
    std::string line;
    int num_suppliers, num_storages, num_connections;

    line = read_three_num_line(&num_suppliers, &num_storages, &num_connections);
    Network network(num_suppliers, num_storages, num_connections);

    line = read_line();
    cycle_line(line, &network, TYPE_SUPPLIER);

    line = read_line();
    cycle_line(line, &network, TYPE_STORAGE);
    
    return network;
}