#pragma once

#include <string>

#include "Network.hpp"

class Parser
{
private:
    std::string read_line();
    std::string read_three_num_line(int *a, int *b, int *c);
public:
    Network factory();
};