#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
#include <functional>

/*
 * Generic implementation to erase elements by Callback
 * It iterates over all the elements and for every element it executes
 * the callback, if it returns the true then it will delete
 * that entry and move to next.
 */
template<typename K, typename V>
int erase_if(std::map<K, V> & mapOfElemen, bool(* functor)(V))
{
    int totalDeletedElements = 0;
    auto it = mapOfElemen.begin();
    // Iterate through the map
    while(it != mapOfElemen.end())
    {
        // Check if value of this entry matches with given value
        if(functor(it->second))
        {
            totalDeletedElements++;
            // Erase the current element, erase() will return the
            // next iterator. So, don't need to increment
            it = mapOfElemen.erase(it);
        }
        else
        {
            // Go to next entry in map
            it++;
        }
    }
    return totalDeletedElements;
}
bool isODD(int val)
{
    if(val % 2 == 1)
            return true;
        else
            return false;
}
int main() {
    // Map of string & int i.e. words as key & there
    // occurrence count as values
    std::map<std::string, int> wordMap = {
                { "is", 6 },
                { "the", 5 },
                { "hat", 9 },
                { "at", 6 }
            };
    std::cout << "Map Entries Before Deletion" << std::endl;
    // Print the map elements
    for (auto elem : wordMap)
        std::cout << elem.first << " :: " << elem.second << std::endl;
    // Erase all the elements whose value is ODD
    int deletedCount = erase_if(wordMap, &isODD);
    std::cout<<"Total elements deleted = "<<deletedCount<<std::endl;
    std::cout << "Map Entries After Deletion" << std::endl;
    // Print the map elements
    for (auto elem : wordMap)
        std::cout << elem.first << " :: " << elem.second << std::endl;
    return 0;
}
