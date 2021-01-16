#include <iostream>
#include <vector>
class Item {
public:
    static int m_ConstructorCalledCount;
    static int m_DestCalledCount;
    static int m_CopyConstructorCalledCount;
    Item()     {
        m_ConstructorCalledCount++;
    }
    ~Item()    {
        m_DestCalledCount++;
    }
    Item(const Item& obj) {
        m_CopyConstructorCalledCount++;
    }
};
int Item::m_ConstructorCalledCount = 0;
int Item::m_CopyConstructorCalledCount = 0;
int Item::m_DestCalledCount = 0;
class ItemFactory
{
public:
    static std::vector<Item> getItemObjects(int count)
    {
        std::vector<Item> vecOfItems;
        vecOfItems.reserve(count);
        for (int var = 0; var < count; ++var) {
            vecOfItems.push_back(Item());
        }
        return vecOfItems;
    }
};
class ItemFactoryImproved
{
public:
    static void getItemObjects_1(std::vector<Item> & vecItems, int count)
    {
        vecItems.assign(count, Item());
    }
    static std::vector<Item> getItemObjects_2( int count)
    {
        std::vector<Item> vecOfItems;
        vecOfItems.assign(count, Item());
        return vecOfItems;
    }
};
int main()
{
    int count = 10000;
    std::vector<Item> vecOfItems;
    vecOfItems = ItemFactory::getItemObjects(count);
    std::cout<<"Total Item Objects constructed = "<<(Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount)<<std::endl;
    std::cout<<"Constructor called  "<<Item::m_ConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Copy Constructor called  "<<Item::m_CopyConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Total Item Objects destructed = "<<Item::m_DestCalledCount<<std::endl<<std::endl;
    Item::m_ConstructorCalledCount = 0;
    Item::m_CopyConstructorCalledCount = 0;
    Item::m_DestCalledCount = 0;
    std::vector<Item> vecOfItems_2 = ItemFactory::getItemObjects(count);
    std::cout<<"Total Item Objects constructed = "<<(Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount)<<std::endl;
    std::cout<<"Constructor called  "<<Item::m_ConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Copy Constructor called  "<<Item::m_CopyConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Total Item Objects destructed = "<<Item::m_DestCalledCount<<std::endl<<std::endl;
    Item::m_ConstructorCalledCount = 0;
    Item::m_CopyConstructorCalledCount = 0;
    Item::m_DestCalledCount = 0;
    std::vector<Item> vecOfItems_3 = ItemFactoryImproved::getItemObjects_2(count);
    std::cout<<"Total Item Objects constructed = "<<(Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount)<<std::endl;
    std::cout<<"Constructor called  "<<Item::m_ConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Copy Constructor called  "<<Item::m_CopyConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Total Item Objects destructed = "<<Item::m_DestCalledCount<<std::endl<<std::endl;
    Item::m_ConstructorCalledCount = 0;
    Item::m_CopyConstructorCalledCount = 0;
    Item::m_DestCalledCount = 0;
    std::vector<Item> vecOfItems_4;
    ItemFactoryImproved::getItemObjects_1(vecOfItems_4, count);
    std::cout<<"Total Item Objects constructed = "<<(Item::m_ConstructorCalledCount + Item::m_CopyConstructorCalledCount)<<std::endl;
    std::cout<<"Constructor called  "<<Item::m_ConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Copy Constructor called  "<<Item::m_CopyConstructorCalledCount <<" times"<<std::endl;
    std::cout<<"Total Item Objects destructed = "<<Item::m_DestCalledCount<<std::endl<<std::endl;
}