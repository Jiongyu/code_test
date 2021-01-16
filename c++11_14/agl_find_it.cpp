#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class Item
{
private:
    std::string  m_ItemId;
    int m_Price;
    int m_Count;
public:
    Item(std::string id, int price, int count):
        m_ItemId(id), m_Count(count), m_Price(price)
    {}
    int getCount() const {
        return m_Count;
    }
    std::string getItemId() const {
        return m_ItemId;
    }
    int getPrice() const {
        return m_Price;
    }
    bool operator==(const Item & obj2) const
    {
        if(this->getItemId().compare(obj2.getItemId()) == 0)
            return true;
        else
            return false;
    }
};
std::vector<Item> getItemList()
{
    std::vector<Item> vecOfItems ;
    vecOfItems.push_back(Item("D121",100,2));
    vecOfItems.push_back(Item("D122",12,5));
    vecOfItems.push_back(Item("D123",28,6));
    vecOfItems.push_back(Item("D124",8,10));
    vecOfItems.push_back(Item("D125",99,3));
    return vecOfItems;
}


template <typename T>
struct GenericComparator
{
    typedef  int (T::*GETTER)() const;
    GETTER m_getterFunc;
    int m_data;
    GenericComparator(GETTER getterFunc, int data)
    {
        m_getterFunc = getterFunc;
        m_data = data;
    }
    bool operator()(const T  & obj)
    {
        if((obj.*m_getterFunc)() == m_data)
            return true;
        else
            return false;
    }
};

void fun1()
{   
    std::vector<Item> vecOfItems = getItemList();
    std::vector<Item>::iterator it;
    it = std::find_if(vecOfItems.begin(), vecOfItems.end(), GenericComparator<Item>(&Item::getPrice, 99) );
    if(it != vecOfItems.end())
        std::cout<<"Item Price ::"<<it->getPrice()<<" Count :: "<<it->getCount()<<std::endl;
    else
        std::cout<<"Item not Found"<<std::endl;
}

// lambda function
void fun2()
{
    std::vector<Item> vecOfItems = getItemList();
    std::vector<Item>::iterator it;
    it = std::find_if(vecOfItems.begin(), vecOfItems.end(), [](Item const& obj){
            return obj.getPrice() == 28;
        } );
    if(it != vecOfItems.end())
        std::cout<<"Item Price ::"<<it->getPrice()<<" Count :: "<<it->getCount()<<std::endl;
    else
        std::cout<<"Item not Found"<<std::endl;
}

// bind function
bool priceComparision(Item & obj, int y)
{
    if(obj.getPrice() == y)
        return true;
    else
        return false;
}

void fun3()
{
    std::vector<Item> vecOfItems = getItemList();
    std::vector<Item>::iterator it;
    it = std::find_if(vecOfItems.begin(), vecOfItems.end(), std::bind(priceComparision,  std::placeholders::_1 , 28) );
    if(it != vecOfItems.end())
        std::cout<<"Item Price ::"<<it->getPrice()<<" Count :: "<<it->getCount()<<std::endl;
    else
        std::cout<<"Item not Found"<<std::endl;
}

int main(int argc, char const *argv[])
{
    fun1();
    fun2();
    fun3();
    return 0;
}

