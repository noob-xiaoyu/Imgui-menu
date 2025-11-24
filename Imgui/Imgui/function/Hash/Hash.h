#include <cstdint>
#pragma once
extern constexpr uint64_t CompileTimeHash(const char* str);
extern uint64_t RuntimeHash(const char* str);