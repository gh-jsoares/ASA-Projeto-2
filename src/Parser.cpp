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

int Parser::cycle_line(std::string line, Network *network, int type, int num_nodes)
{
    auto graph = network->getGraph();

    std::istringstream sstream(line);
    int n;
    while(sstream >> n) {
        if(type == TYPE_SUPPLIER) {
            auto supplier = std::make_shared<Node>(++num_nodes);
            graph->addNode(supplier);
            graph->addConnection(graph->getSource(), supplier, n);
        } else {
            auto storage_start = std::make_shared<Node>(++num_nodes);
            auto storage_end = std::make_shared<Node>(-num_nodes);
            graph->addNode(storage_start);
            graph->addNode(storage_end);
            graph->addConnection(storage_start, storage_end, n);
        }
    }
    return num_nodes;
}

Network Parser::factory() {
    std::string line;
    int num_suppliers, num_storages, num_connections;

    line = read_three_num_line(&num_suppliers, &num_storages, &num_connections);
    Network network(num_suppliers, num_storages);

    int num_nodes = 1;

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_SUPPLIER, num_nodes);

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_STORAGE, num_nodes);

    auto graph = network.getGraph();
    
    auto tail = std::make_shared<Node>(1);
    graph->addNode(tail);

    int i = 0;
    int origin_id, destination_id, capacity;
    while(i < num_connections) {
        line = read_three_num_line(&origin_id, &destination_id, &capacity);
        auto origin = graph->getNode(origin_id);
        auto destination = graph->getNode(destination_id);
        graph->addConnection(origin, destination, capacity);
        i++;
    }
    
    return network;
}