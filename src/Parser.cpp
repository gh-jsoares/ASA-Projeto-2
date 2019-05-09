#include <iostream>

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


Network Parser::factory() {
    std::string line;
    int num_suppliers, num_storages, num_connections;

    line = read_three_num_line(&num_suppliers, &num_storages, &num_connections);
    Network network(num_suppliers, num_storages, num_connections);

    // // get number connections
    // line = read_line();
    // connections = std::stoi(line);

    // // get all connections

    // int a, b;
    // for (int i = 0; i < connections; i++) {
    //     line = read_line();
    //     sscanf(line.c_str(), "%d %d", &a, &b);
    //     network.add_node(a, b);
    // }

    return network;
}

// std::istringstream ss(your_string_here);
// std::vector<int> vec(std::istream_iterator<int>(ss), {});