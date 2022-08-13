#include "BlockingQueue.h"

namespace bussiness
{
    
class bussiness1
{
private:
    /* data */
    basic::BlockingQueue<int>data_;
public:
    bussiness1(/* args */);

    int get_data();
    void set_data(int data);
    
    ~bussiness1();
};

bussiness1::bussiness1(/* args */)
{
}

bussiness1::~bussiness1()
{
}

} // namespace bussiness

