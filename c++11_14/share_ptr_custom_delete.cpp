#include <iostream>
#include <memory>
struct Sample
{
    Sample()
    {
        std::cout << "CONSTRUCTOR\n";
    }
    ~Sample()
    {
        std::cout << "DESTRUCTOR\n";
    }
};
// function that calls the delete [] on received pointer
void deleter(Sample * x)
{
    std::cout << "DELETER FUNCTION CALLED\n";
    delete[] x;
}
int main()
{
    // Creating a shared+ptr with custom deleter
    // 1.) Try not to use same raw pointer for creating more than one shared_ptr object 
    // because in that case different shared_ptr objects will not get to know that they 
    // are sharing the pointer with any other shared_ptr objects.
    // 2.) Don’t create shared_ptr object from memory from stack instead of heap.
    std::shared_ptr<Sample> p3(new Sample[12], deleter);

    return 0;
}