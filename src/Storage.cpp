#include "Storage.hpp"

Storage::Storage(int id, int amount) {
    this->id = id;
    this->amount = amount;
}

Storage::~Storage() { }

int Storage::getId()
{
    return this->id;
}

int Storage::getAmount()
{
    return this->amount;
}
