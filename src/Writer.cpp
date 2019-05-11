#include <iostream>

#include "Writer.hpp"

Writer::Writer()
{
    std::ios::sync_with_stdio(false); // faster cout
}

void Writer::write(Network *network)
{
    printf("%d\n", network->getMaxFlow());

    network->DFS();
}