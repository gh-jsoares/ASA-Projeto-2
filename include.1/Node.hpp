#pragma once

class Node 
{
private:
    int id;
    int amount;
    int level;
public:
    Node(int id, int amount);
    ~Node();

    int getId();
    int getAmount();

    int getLevel();
    void setLevel(int new_level);
};