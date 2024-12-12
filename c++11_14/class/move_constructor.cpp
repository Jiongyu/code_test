#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

/*
移动构造函数首先将传递参数的内存地址空间接管，然后将内部所有指针设置为nullptr，并
且在原地址上进行新对象的构造，最后调用原对象的的析构函数，这样做既不会产生额外的拷
贝开销，也不会给新对象分配内存空间。
*/

class Str{
    public:
        char *str;
        Str(char value[])
        {
            cout<<"普通构造函数..."<<endl;
            str = NULL;
            int len = strlen(value);
            str = (char *)malloc(len + 1);
            memset(str,0,len + 1);
            strcpy(str,value);
        }
        Str(const Str &s)
        {
            cout<<"拷贝构造函数..."<<endl;
            str = NULL;
            int len = strlen(s.str);
            str = (char *)malloc(len + 1);
            memset(str,0,len + 1);
            strcpy(str,s.str);
        }
        Str(Str &&s)
        {
            cout<<"移动构造函数..."<<endl;
            str = NULL;
            str = s.str;
            s.str = NULL;
        }

        Str& operator=(Str &&s) noexcept
        {
            if(this != &s)
            {
                cout << "移动赋值" << std::endl;
                str = NULL;
                str = s.str;
                s.str = NULL;
            }
            return *this;
        }

        ~Str()
        {
            cout<<"析构函数"<<endl;
            if(str != NULL)
            {
                free(str);
                str = NULL;
            }
        }
};

Str getStr()
{
    return Str("test data");
}

int main()
{
    std::cout << "1--------\n";
    char value[] = "hello copy";
    Str s(value);
    vector<Str> vs;
    vs.push_back(s);    /*拷贝构造*/

    cout<<vs[0].str<<endl;
    if(s.str != NULL)
        cout<<s.str<<endl;

    std::cout << "2--------\n";
    //vs.push_back(move(s)); /*移动构造*/
    vs.emplace_back(move(s)); /*移动构造*/
    if(s.str != NULL)
        cout<<s.str<<endl;
    std::cout << "3--------\n";
    Str a = getStr();   /*移动构造*/
    if(a.str != NULL)
        cout<<a.str<<endl;
    std::cout << "4--------\n";

    Str tmp("hello");
    Str data = std::move(tmp); /*移动构造*/
    std::cout << "5--------\n";
    tmp = std::move(data); /*移动赋值*/
    std::cout << "6--------\n";
    return 0;
}
