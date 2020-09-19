// override 关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的虚函数，否则将无法通过编译
// final 则是为了防止类被继续继承以及终止虚函数继续重载引入的

struct Base {
    virtual void foo(int);
};
struct SubClass: Base {
    virtual void foo(int) override; // 合法
    virtual void foo(float) override; // 非法, 父类没有此虚函数
};

struct SubClass1 final: Base {
};                  // 合法

struct SubClass2 : SubClass1 {
};                  // 非法, SubClass1 已 final

struct SubClass3: Base {
        void foo(); // 非法, foo 已 final
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
