#pragma once

class Connection
{
private:
    int vertex_id;
    int weight;
public:
    Connection(int vertex_id, int weight);
    ~Connection();

    int getVertexId();
    int getWeight();
};