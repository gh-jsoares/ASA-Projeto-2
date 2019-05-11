#include <iostream>
#include <sstream>

#include "Parser.hpp"

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

int Parser::cycle_line(std::string line, Network *network, int type, int num_nodes, int num_elements)
{
    char *tmp = new char[line.length() + 1];
    strcpy(tmp, line.c_str());

    int n;
    for(int i = 0; i < num_elements; i++) {
        sscanf(tmp, "%d %[^\n]", &n, tmp);
        num_nodes++;
        if(type == TYPE_SUPPLIER)
            network->addEdge(0, num_nodes , n);
        else
            network->addEdge(num_nodes, -num_nodes , n);
    }

    delete [] tmp;
    
    return num_nodes;
}

Network Parser::factory() {
    std::string line;
    int num_suppliers, num_storages, num_connections;

    line = read_three_num_line(&num_suppliers, &num_storages, &num_connections);
    Network network(num_suppliers + num_storages * 2 + 2, num_suppliers);;

    int num_nodes = 1;

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_SUPPLIER, num_nodes, num_suppliers);

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_STORAGE, num_nodes, num_storages);

    int origin_id, destination_id, capacity;
    for(int i = 0; i < num_connections; i++ ) {
        line = read_three_num_line(&origin_id, &destination_id, &capacity);

        if(network.isStorage(origin_id))
            origin_id *= -1; // storages are paths between 2 nodes with symmetrical ids

        network.addEdge(origin_id, destination_id, capacity);
    }
    
    return network;
}