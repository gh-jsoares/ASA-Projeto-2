#pragma once

#include <memory>

class Connection
{
private:
    int vertex_id;
    int capacity;
    int flow;
    
    std::weak_ptr<Connection> reverse; // for easier tracking
public:
    Connection(int vertex_id, int capacity);

    int getVertexId();
    int getCapacity();
    int getFlow();

    void setReverseConnection(std::shared_ptr<Connection> reverse);
    std::weak_ptr<Connection> getReverseConnection();
};