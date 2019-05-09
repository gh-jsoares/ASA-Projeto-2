#pragma once

class Storage
{
private:
    int id;
    int amount;
public:
    Storage(int id, int amount);
    ~Storage();

    int getId();
    int getAmount();
};