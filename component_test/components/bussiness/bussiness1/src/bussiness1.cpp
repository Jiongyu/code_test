#include "bussiness1.h"

int bussiness::bussiness1::get_data()
{
    return this->data_.take();
}

void bussiness::bussiness1::set_data(int data)
{
    this->data_.put(data);
}