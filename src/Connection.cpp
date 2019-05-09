#include "Connection.hpp"

Connection::Connection(int vertex_id, int weight)
{
    this->vertex_id = vertex_id;
    this->weight = weight;
}

Connection::~Connection() { }

int Connection::getVertexId()
{
    return this->vertex_id;
}

int Connection::getWeight()
{
    return this->weight;
}