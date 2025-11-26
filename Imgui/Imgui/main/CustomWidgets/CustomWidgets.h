// CustomWidgets.h
#pragma once
#include "imgui.h"
namespace ImGui {
    
    // 声明我们翻译后的函数
    void ShowTranslatedStyleEditor(ImGuiStyle* ref = nullptr);
    
}
namespace CustomWidgets {
    bool CheckboxFloat(const char* label, float* v);
    inline int WindowBorderSize_ = 0;
    inline bool WindowBorderSize = false;
}