#include <iostream>

#include "Writer.hpp"

void Writer::write(Network *network)
{
    auto graph = network->getGraph();
    std::cout << graph->getMaxFlow() << std::endl;
    std::cout << graph->m_num_vertices << std::endl;
}