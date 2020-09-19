#include <iostream>
#include <regex>
#include <string>

using namespace std;

string fnames[] = {"foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt"};

void regex_test1(){
    regex txt_regex("[a-z+A-Z+0-9]+\\.txt");
    for(const auto &fname : fnames){
        cout << fname << ": " <<  regex_match(fname,txt_regex) << endl;
    }
}

void regex_test2(){

    std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;
    for(const auto &fname: fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // sub_match 的第一个元素匹配整个字符串
            // sub_match 的第二个元素匹配了第一个括号表达式
            if (base_match.size() == 2) {
                std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
                std::cout << fname << " sub-match[1]: " << base_match[1].str() << std::endl;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    regex_test1();
    regex_test2();
    return 0;
}
