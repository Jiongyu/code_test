#include <stdio.h>
#include <stdlib.h>
#include <queue>
 
class CData
{
public:
    // 禁止隐式转换
    // explicit CData(int value)
    CData(int value)
    {
        mValue = 100;
    }
 
    ~CData()
    {
        printf("destructor\n");
        mValue = 0;
    }
 
private:
    int mValue;
};
 
int main()
{
    std::queue<CData> dataQueue;
    dataQueue.push(10);
    printf("anonymous destructor\n");
    dataQueue.push(10);
 
    printf("------ exit main ------\n");
    return 0;
}