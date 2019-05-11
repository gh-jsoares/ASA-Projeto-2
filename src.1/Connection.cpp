#include "Connection.hpp"

Connection::Connection(int vertex_id, int capacity)
{
    this->vertex_id = vertex_id;
    this->capacity = capacity;
    this->flow = 0;
}

int Connection::getVertexId()
{
    return this->vertex_id;
}

int Connection::getCapacity()
{
    return this->capacity;
}

void Connection::setReverseConnection(std::shared_ptr<Connection> reverse)
{
    this->reverse = reverse;
}

std::weak_ptr<Connection> Connection::getReverseConnection()
{
    return this->reverse;
}
