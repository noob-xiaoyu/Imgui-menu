// MouseTrail.h
#pragma once
#include "imgui.h"
#include <vector>
#include <deque> // 使用 deque 更高效地在头部添加/删除

class MouseTrail {
public:
    MouseTrail(int max_length = 50, float thickness = 4.0f, ImU32 color = IM_COL32(255, 255, 0, 255));

    // 每帧调用此函数来更新和绘制拖尾
    void Render();
private:
    std::deque<ImVec2> points; // 存储历史点的队列
};