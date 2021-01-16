#include <iostream>
#include <map>
#include <string>

// map排序规则定义
struct WordGreaterComparator{
    bool operator()(const std::string &left, const std::string &right)const
    {
        return left > right;
    }
};

int main(int argc, char const *argv[])
{

    std::cout<<"Default sorting criteria for keys i.e. operator < for std::string"<<std::endl;
    // Default sorting criteria for keys i.e. operator < for std::string
    std::map<std::string, int > mapOfWords;
    mapOfWords.insert(std::make_pair("earth", 1));
    mapOfWords.insert(std::make_pair("moon", 2));
    mapOfWords.insert(std::make_pair("sun", 3));
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    for( ; it != mapOfWords.end(); it++)
        std::cout<<it->first<<" :: "<<it->second<<std::endl;

    std::cout<<"External sorting criteria for keys "<<std::endl;
    std::map<std::string, int, WordGreaterComparator > mapOfWord;
    mapOfWord.insert(std::make_pair("day", 10));
    mapOfWord.insert(std::make_pair("earth", 1));
    mapOfWord.insert(std::make_pair("moon", 2));
    mapOfWord.insert(std::make_pair("sun", 3));
    for(std::map<std::string, int>::iterator it = mapOfWord.begin(); it != mapOfWord.end(); it++)
    std::cout<<it->first<<" :: "<<it->second<<std::endl;

    return 0;

}
