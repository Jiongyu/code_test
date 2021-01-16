#include <tuple>
#include <iostream>

auto get_student(int id)
{
    // 返回类型被推断为 std::tuple<double, char, std::string>

    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果只写 0 会出现推断错误, 编译失败
}

int main(int argc, char const *argv[])
{
    auto student = get_student(1);
    std::cout   << "id: "
                << std::get<0>(student)
                << " "
                << "class: "
                << std::get<1>(student)
                << " "
                << "name: "
                << std::get<2>(student)
                << "\n";
    double id;
    char class_;
    std::string name;
    std::tie(id, class_, name) = get_student(2);
    std::cout   << "id: "
                << id
                << " "
                << "class: "
                << class_
                << " "
                << "name: "
                << name
                << "\n";
    

    return 0;
}
