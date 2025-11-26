#include <cstdint> // for uint64_t

// C++14 constexpr 版本，更简洁
// 这个函数可以在编译时计算字符串字面量的哈希值
constexpr uint64_t CompileTimeHash(const char* str) {
    uint64_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str++);
    }
    return hash;
}

// 运行时版本，用于计算变量字符串的哈希值
// 逻辑和上面完全一样
uint64_t RuntimeHash(const char* str) {
    uint64_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (*str++);
    }
    return hash;
}