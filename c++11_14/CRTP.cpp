/**
 * @file CRTP.cpp
 * @author your name (you@domain.com)
 * @brief CRTP全称是curious recurring template pattern，是一种c++的设计模式，精巧地
 *        结合了继承和模板编程的技术。可以用来给c++的class提供额外功能、实现静态多态等。
 *        基类可以调用派生类的方法，而不需要使用虚函数或运行时多态。
 * @version 0.1
 * @date 
 * @compile g++ CRTP.cpp -o CRTP -std=c++14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <type_traits>

template <typename T>
struct Base
{
    void foo()
    {
        // 编译时进行类型检查和静态断言，确保派生类实现某些特定的方法或属性
        static_assert(std::is_same<std::decay_t<decltype(T::value)>, int>::value, 
            "Derived class must define 'value' as an int.");
        static_cast<T*>(this)->op();
    }
};

struct Derived : Base<Derived>
{
    static constexpr int value = 42;
    void op()
    {
        std::cout << "Derived::op()" << std::endl;
    }
};

struct Derived2 : Base<Derived2>
{
    static constexpr float value = 42.0;
    void op()
    {
        std::cout << "Derived2::op()" << std::endl;
    }
};


template <typename Derived>
class LoggingMixin {
public:
    void log(const std::string& message) {
        std::cout << "Logging: " << message << std::endl;
    }

    void performAction() {
        log("Action started");
        static_cast<Derived*>(this)->action();
        log("Action finished");
    }
};

class Task : public LoggingMixin<Task> {
public:
    void action() {
        std::cout << "Performing task..." << std::endl;
    }
};

template <typename Strategy>
class Processor {
public:
    void process() {
        static_cast<Strategy*>(this)->execute();
    }
};

class StrategyA : public Processor<StrategyA> {
public:
    void execute() {
        std::cout << "Executing Strategy A" << std::endl;
    }
};

class StrategyB : public Processor<StrategyB> {
public:
    void execute() {
        std::cout << "Executing Strategy B" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Derived d;
    d.foo();
    // Derived2 d2; // 编译无法通过
    // d2.foo();

    // 混入类，即在不改变现有类层次结构的情况下，为类添加新的功能。通过 CRTP，
    // 在基类中定义一些通用的功能，然后通过派生类将其应用到不同的类中。
    Task task;
    task.performAction();

    // CRTP 与策略模式结合使用，一种静态多态的解决方案。
    StrategyA a;
    StrategyB b;
    a.process();
    b.process();

    return 0;
}
