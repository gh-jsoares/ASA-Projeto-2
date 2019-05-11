#include <iostream>

#include "Node.hpp"

Node::Node(int id, int amount): id(id), amount(amount), level(-1) { }

Node::~Node() { }

int Node::getId()
{
    return this->id;
}

int Node::getAmount()
{
    return this->amount;
}

int Node::getLevel()
{
    return this->level;
}

void Node::setLevel(int new_level)
{
    this->level = new_level;
}
