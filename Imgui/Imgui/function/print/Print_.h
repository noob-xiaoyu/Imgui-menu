// ConsolePrint.h

#ifndef CONSOLE_PRINT_H
#define CONSOLE_PRINT_H

#include <iostream>
#include <string>

// 声明一个特殊的 'manipulator' 用于换行，模仿 std::endl
namespace Console {
    // 定义一个函数指针类型，用于处理像 endl 这样的特殊操作
    using Manipulator = std::ostream& (*)(std::ostream&);
}

// 基础的 print 函数，使用模板来接受任何可以被 std::cout 输出的类型
template<typename T>
void print(const T& value);

// 函数重载，用于处理换行符 (endl)
void print(Console::Manipulator manip);

#endif // CONSOLE_PRINT_H