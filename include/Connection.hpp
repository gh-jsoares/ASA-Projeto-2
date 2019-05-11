#pragma once

#include <memory>
#include "Node.hpp"

class Connection
{
private:
    int m_capacity;
    int m_flow;

    std::shared_ptr<Node> m_origin;
    std::shared_ptr<Node> m_destination;
public:
    Connection(int flow, int capacity, std::shared_ptr<Node> origin, std::shared_ptr<Node> destination);

    std::shared_ptr<Node> getOrigin();
    std::shared_ptr<Node> getDestination();

    int getCapacity();
    int getFlow();

    void setCapacity(int capacity);
    void addFlow(int flow);
};