#include <iostream>
#include <algorithm>
#include <vector>

// 1.
// [=](int &x) {
//         // All outer scope elements has been passed by value
//     }

// 2.
//   [&](int &x) {
//         // All outer scope elements has been passed by reference
//     }

void cout_data(int data){
    std::cout << data << " ";
}

void display_test_1(){
    std::cout << __FUNCTION__ << ":" << std::endl;
    std::vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    std::for_each(data.begin(), data.end(), &cout_data);
    std::cout << std::endl << std::endl;
}



void lambda_test_2(){
    std::cout << __FUNCTION__ << ":" << std::endl;
    std::vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    // lambda express 
    std::for_each(data.begin(), data.end(), [&](int &x){
        // Can modify the mul inside this lambda function because
        // all outer scope elements has write access here.
        std::cout << x << " ";
        x+=1;
    });
    std::cout << std::endl << std::endl;
    std::for_each(data.begin(), data.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl << std::endl;
}


void lambda_test_3(){
    std::cout << __FUNCTION__ << ":" << std::endl;
    std::vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    // lambda express 
    std::for_each(data.begin(), data.end(), [=](int &x){
        // Can not modify the mul inside this lambda function because
        // all outer scope elements has read only access here.
        std::cout << x << " ";
        x+=1;
    });
    std::cout << std::endl << std::endl;
    std::for_each(data.begin(), data.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl << std::endl;
}

void lambda_test_1(){
    std::cout << __FUNCTION__ << ":" << std::endl;
    std::vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    // lambda express 
    std::for_each(data.begin(), data.end(), [](int x){
        std::cout << x << " ";
        x+=1;
    });
    std::cout << std::endl << std::endl;
    std::for_each(data.begin(), data.end(), [](int x){
        std::cout << x << " ";
    });
    std::cout << std::endl << std::endl;
}

int main(int argc, char const *argv[])
{
    display_test_1();
    lambda_test_1();
    lambda_test_2();
    lambda_test_3();

    return 0;
}
