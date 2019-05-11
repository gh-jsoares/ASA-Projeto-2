#include "Connection.hpp"

Connection::Connection(int flow, int capacity, std::shared_ptr<Node> origin, std::shared_ptr<Node> destination)
    : m_capacity(capacity), m_flow(flow), m_origin(origin), m_destination(destination) { }

std::shared_ptr<Node> Connection::getOrigin()
{
    return m_origin;
}

std::shared_ptr<Node> Connection::getDestination()
{
    return m_destination;
}

int Connection::getCapacity()
{
    return m_capacity;
}

int Connection::getFlow()
{
    return m_flow;
}

void Connection::setCapacity(int capacity)
{
    m_capacity = capacity;
}

void Connection::addFlow(int flow)
{
    m_flow += flow;
}