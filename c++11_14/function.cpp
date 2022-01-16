#include <iostream>
#include <functional>
#include <map>
#include <string>

int add(int a, int b)
{
    return a+b;
}

struct devide{
    int operator()(int de, int di){return de / di;};
};

int main(int argc, char const *argv[])
{
    std::function<int(int,int)>fun_add = add;
    
    std::function<int(int,int)>fun_devide = devide();
    
    std::function<int(int,int)>fun_muti = [](int a, int b) ->int {return a * b;};

    std::cout <<fun_add(1,2) << std::endl;

    std::cout <<fun_devide(10,2) << std::endl;    

    std::cout <<fun_muti(14,2) << std::endl;

    std::map<std::string, std::function<int(int,int)>> ops = {
        {"add", fun_add},
        {"devide", fun_devide},
        {"muti", fun_muti},
    };

    for(auto it = ops.begin(); it != ops.end(); it++)
    {
        std::cout << it->first << ":" << it->second(10,5) << std::endl;
    }

    std::cout << ops["add"](10,5) << std::endl;

    return 0;
}
