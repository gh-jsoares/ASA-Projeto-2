#pragma once

class Node 
{
private:
    int m_id;

    int m_height;
    int m_excess_flow;
public:
    Node(int id);

    int getId();
    int getHeight();
    int getExcessFlow();

    void setHeight(int height);
    void setExcessFlow(int excess_flow);
    void addExcessFlow(int excess_flow);
};