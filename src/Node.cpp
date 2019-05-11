#include <iostream>

#include "Node.hpp"

Node::Node(int id) : m_id(id), m_height(0), m_excess_flow(0) { }

int Node::getId()
{
    return m_id;
}

int Node::getHeight()
{
    return m_height;
}

int Node::getExcessFlow()
{
    return m_excess_flow;
}

void Node::setHeight(int height)
{
    m_height = height;
}

void Node::setExcessFlow(int excess_flow)
{
    m_excess_flow = excess_flow;
}

void Node::addExcessFlow(int excess_flow)
{
    m_excess_flow += excess_flow;
}

