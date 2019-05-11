#pragma once

#include <string>

#include "Network.hpp"

#define TYPE_SUPPLIER 0
#define TYPE_STORAGE 1

class Parser
{
private:
    std::string read_line();
    std::string read_three_num_line(int *a, int *b, int *c);
    int cycle_line(std::string line, Network *network, int type, int num_nodes);
public:
    Network factory();
};