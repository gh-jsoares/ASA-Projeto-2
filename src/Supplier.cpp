#include "Supplier.hpp"

Supplier::Supplier(int id, int amount) {
    this->id = id;
    this->amount = amount;
}

Supplier::~Supplier() {

}

int Supplier::getId()
{
    return this->id;
}

int Supplier::getAmount()
{
    return this->amount;
}
