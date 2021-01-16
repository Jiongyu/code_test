#include <iostream>
#include <map>

void example1()
{

    std::cout << "example1\n";
    // Map of string & int i.e. words as key & there
    // occurrence count as values
    std::map<std::string, int> wordMap = {
                                { "is", 6 },
                                { "the", 5 }
                            };
    // As there is no element with key 'Hello'
    // So, operator [] will create a new element in map
    // with key as 'Hello' and default value, which in this case
    // will be 0.
    int & value1 = wordMap["Hello"];
    // Display the value
    std::cout<<"value of 'Hello' = "<<value1<<std::endl;
    // Fetch the value for key 'is'
    // As key already exist therefore will not create new entry
    // Will just return the reference of value
    int & value2 = wordMap["is"];
    // Display the value
    std::cout<<"value of 'is' = "<<value2<<std::endl;
    // As [] returns the value by reference, therefore
    // it will override the new value.
    wordMap["is"] = 4;
    int & value3 = wordMap["is"];
    // Display the value
    std::cout<<"value of 'is' = "<<value3<<std::endl;
    // Override the value of element with key 'is'
    wordMap["is"] = 4;
    // Will create a new wntry with Key 'Thanks' and override its
    // default value 0 with 10.
    wordMap["Thanks"] = 10;
    std::cout<< "***********Map Entries***********" <<std::endl;
    // Print the map elements
    for (auto elem : wordMap)
        std::cout << elem.first << " :: " << elem.second << std::endl;
}

// user defined value
struct Occurance
{
    int count;
    // Default Constructor
    // Un Comment it to compile the code
    
    Occurance()
    {
        this->count = 0;
    }
    
    // Parametrized constructor
    Occurance(int count)
    {
        this->count = count;
    }
};


void example2()
{
    std::cout << "example2\n";
    // Map of string & int i.e. words as key & there
    // occurrence count as values
    std::map<std::string, Occurance> wordMap = {
                    { "is", Occurance(6) },
                    { "the", Occurance(5) }
                };
    // As key is not in map, so operator[] will create new entry
    // With default value of value field. Therefore, Will compile
    // only if Occurance sruct has default constructor.
    Occurance occur = wordMap["Hello"];
    for (auto elem : wordMap)
        std::cout << elem.first << " :: " << elem.second.count << std::endl;
}

int main(int argc, char const *argv[])
{
    example1();
    example2();
    return 0;
}
