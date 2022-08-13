#include "bussiness1.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    bussiness::bussiness1 demo;
    int i = 0;
    while(i < 10)
    {
        demo.set_data(i++);
        std::cout << demo.get_data() << " ";
    }
    std::cout << std::endl;
    return 0;
}
