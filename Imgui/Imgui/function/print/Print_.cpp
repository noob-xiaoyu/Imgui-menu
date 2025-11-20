// ConsolePrint.cpp

#include "Print_.h"

// 实现模板函数：打印各种类型的值
template<typename T>
void print(const T& value) {
    std::cout << value;
}

// 实现重载函数：处理换行符
void print(Console::Manipulator manip) {
    // 调用传入的操作符函数，把它应用到 std::cout 上
    manip(std::cout);
}

// --- 显式实例化常用的模板类型 ---
// 这是为了避免链接错误。因为模板的定义在.cpp文件中，
// 其他文件在编译时看不到模板的实现，会导致链接失败。
// 通过显式实例化，我们告诉编译器为这些特定类型生成代码。
template void print<int>(const int&);
template void print<double>(const double&);
template void print<float>(const float&);
template void print<char>(const char&);
template void print<const char*>(const char* const&);
template void print<std::string>(const std::string&);