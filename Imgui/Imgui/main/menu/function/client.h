#pragma once
#include "imgui.h"
#include <utility> // 用于 std::pair

namespace client {
	// 获取屏幕尺寸
    inline std::pair<int, int> screen_size() {
        ImVec2 size = ImGui::GetIO().DisplaySize;
        return { (int)size.x, (int)size.y };
    }

}