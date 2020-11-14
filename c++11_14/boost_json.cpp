#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/date_time.hpp>
#include <boost/foreach.hpp>

#include <iostream>

using namespace boost;

// g++ boost_json.cpp -o boost_json -lboost_system -lboost_thread -std=c++11

int main(int argc, char const *argv[])
{
    std::string s = "{ \"a\": 100, \"b\": [1, 2, 3, 4] }";
    std::stringstream ss(s);


    property_tree::ptree tree;
    property_tree::read_json(ss, tree);  

    // 存储json文件
    std::cout << tree.get_child("a").data() << std::endl;  
    property_tree::write_json("./temp.json", tree); 

    // 读取json 文件
    tree.clear();
    property_tree::read_json("./temp.json", tree);
    property_tree::write_json(std::cout, tree);

    // 遍历数组
    property_tree::ptree subTree = tree.get_child("b");
    // property_tree::write_json(std::cout, subTree);

    // 判断子键是否存在
    if( ! subTree.empty() ){
        for (auto it: subTree) {
                std::cout << it.second.data() << " ";
        }
    }

    if(tree.get_child_optional("b")){
        for (auto it: subTree) {
                std::cout << it.second.data() << " ";
        }
    }

    return 0;
}
