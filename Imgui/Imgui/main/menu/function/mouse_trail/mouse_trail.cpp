// MouseTrail.cpp
#include "mouse_trail.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "main/menu/menu.h"

namespace menu {
    void MouseTrail::Render() {
        if (!menu::Visuals::mouse_trail::Enabled) {
            // 如果禁用了，清空轨迹点并返回
            if (!points.empty()) {
                points.clear();
            }
            return;
        }

        ImGuiIO& io = ImGui::GetIO();

        // 1. 获取当前鼠标位置并添加到队列头部
        points.push_front(io.MousePos);

        // 2. 维护队列长度，移除最旧的点
        while (points.size() > menu::Visuals::mouse_trail::MaxLength) {
            points.pop_back();
        }

        // 至少需要两个点才能画线
        if (points.size() < 2) {
            return;
        }

        // 3. 获取前景绘制列表 (Foreground Draw List)
        // 这能确保我们的拖尾绘制在所有 ImGui 窗口之上
        ImDrawList* draw_list = ImGui::GetForegroundDrawList();

        // 4. 遍历历史点并绘制渐变的线条
        for (size_t i = 0; i < points.size() - 1; ++i) {
            ImVec2 p1 = points[i];
            ImVec2 p2 = points[i + 1];

            // --- 美化效果 ---
            // 计算当前线段在整个拖尾中的位置比例 (0.0=头部, 1.0=尾部)
            float fraction = (float)i / (float)points.size();

            // a. 粗细渐变：从 StartThickness 线性递减到 1.0f
            float current_thickness = ImLerp(menu::Visuals::mouse_trail::StartThickness, 1.0f, fraction);

            // b. 颜色和透明度渐变
            // 分解头部颜色
            float r_start = (float)((menu::Visuals::mouse_trail::StartColor >> 0) & 0xFF) / 255.0f;
            float g_start = (float)((menu::Visuals::mouse_trail::StartColor >> 8) & 0xFF) / 255.0f;
            float b_start = (float)((menu::Visuals::mouse_trail::StartColor >> 16) & 0xFF) / 255.0f;
            float a_start = (float)((menu::Visuals::mouse_trail::StartColor >> 24) & 0xFF) / 255.0f;

            // 定义尾部颜色（例如，完全透明的深蓝色）
            float r_end = b_start+0.9f, g_end = g_start+0.9f, b_end = r_start+0.9f, a_end = 0.0f;

            // 使用 ImLerp (线性插值) 计算当前线段的颜色
            float r = ImLerp(r_start, r_end, fraction);
            float g = ImLerp(g_start, g_end, fraction);
            float b = ImLerp(b_start, b_end, fraction);
            float a = ImLerp(a_start, a_end, fraction);

            ImU32 current_color = ImGui::GetColorU32(ImVec4(r, g, b, a));

            // 绘制线段
            draw_list->AddLine(p1, p2, current_color, current_thickness);
        }
    }
}