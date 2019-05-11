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

    // graph->calculateIncreases();

    // auto increases = graph->getIncreases();
    // for(unsigned int i = 0; i < increases.size(); i++) {
    //     auto connection = increases[i];
    //     auto origin = connection->getOrigin();
    //     auto destination = connection->getDestination();
        

    //     if(origin->getId() == -destination->getId()) // storage
    //         LOG(origin->getId());
    //     else // normal path
    //         LOG(std::to_string(origin->getId()) + " " + std::to_string(destination->getId()));
    // }
}