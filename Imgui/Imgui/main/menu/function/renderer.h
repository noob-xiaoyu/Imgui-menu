#pragma once
#include "imgui.h"
#include <imgui_internal.h>
struct BlurData {
    float x, y, w, h;
    float strength;
    float alpha;
};

extern void BlurCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd);
void BlurCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    // 获取参数
    BlurData* data = (BlurData*)cmd->UserCallbackData;

    // 如果你还没有写 DirectX/OpenGL 的 Shader 代码，
    // 这里暂时什么都不做，或者只是把数据释放掉。

    // --- 这里是未来写显卡模糊逻辑的地方 ---

    // 释放内存 (因为我们在 renderer::blur 里用了 ImGui::MemAlloc)
    if (data) {
        ImGui::MemFree(data);
    }
}
namespace renderer {
    inline ImDrawList* get_drawlist() {
        return ImGui::GetBackgroundDrawList();
    }
	// 线条
    void line(float x1, float y1, float x2, float y2, int r, int g, int b, int a, float thickness = 1.0f) {
        get_drawlist()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), IM_COL32(r, g, b, a), thickness);
    }
	// 文字
    void text(float x, float y, int r, int g, int b, int a, const char* content, bool centered = false) {
        if (centered) {
            ImVec2 textSize = ImGui::CalcTextSize(content);
            x -= textSize.x / 2.0f;
            // y -= textSize.y / 2.0f; // 如果需要垂直居中
        }
        get_drawlist()->AddText(ImVec2(x, y), IM_COL32(r, g, b, a), content);
    }
    // 空心矩形
    void rectangle(float x, float y, float w, float h, int r, int g, int b, int a) {
        // ImGui 使用 p_min, p_max，所以 p_max = x+w, y+h
        get_drawlist()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), IM_COL32(r, g, b, a));
    }
    // 实心矩形
    void filled_rectangle(float x, float y, float w, float h, int r, int g, int b, int a, float rounding = 0.0f) {
        get_drawlist()->AddRectFilled(ImVec2(x, y),ImVec2(x + w, y + h),IM_COL32(r, g, b, a),rounding);
    }
    // 三角形
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b, int a) {
        get_drawlist()->AddTriangleFilled(ImVec2(x1, y1),ImVec2(x2, y2),ImVec2(x3, y3),IM_COL32(r, g, b, a));
    }
	// 空心三角形
    void triangle_outline(float x1, float y1, float x2, float y2, float x3, float y3, int r, int g, int b, int a, float thickness = 1.0f) {
        get_drawlist()->AddTriangle(ImVec2(x1, y1),ImVec2(x2, y2),ImVec2(x3, y3),IM_COL32(r, g, b, a),thickness);
    }
    // 渐变
    void gradient(float x, float y, float w, float h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2, bool horizontal = false) {
        ImU32 col1 = IM_COL32(r1, g1, b1, a1);
        ImU32 col2 = IM_COL32(r2, g2, b2, a2);

        // ImGui 的 MultiColor 支持左上、右上、右下、左下四个颜色
        if (horizontal) {
            // 水平渐变：左边是 col1，右边是 col2
            get_drawlist()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), col1, col2, col2, col1);
        }
        else {
            // 垂直渐变：上面是 col1，下面是 col2
            get_drawlist()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), col1, col1, col2, col2);
        }
    }
	//空心圆
    void circle(float x, float y, int r, int g, int b, int a, float radius) {
        get_drawlist()->AddCircle(ImVec2(x, y), radius, IM_COL32(r, g, b, a));
    }
    // 实心圆
    void filled_circle(float x, float y, int r, int g, int b, int a, float radius, int segments = 0) {
        // segments = 0 时，ImGui 会根据半径自动计算圆的平滑度
        get_drawlist()->AddCircleFilled(ImVec2(x, y), radius, IM_COL32(r, g, b, a), segments);
    }
	// 空心圆环
    void circle_outline(float x, float y, int r, int g, int b, int a, float radius, float start_deg, float percentage, float thickness) {
        ImDrawList* draw_list = get_drawlist();

        // GameSense 使用角度，ImGui 使用弧度，需要转换
        // 转换公式: rad = deg * (PI / 180)
        float min = start_deg * (IM_PI / 180.0f);
        float max = (start_deg + 360.0f * percentage) * (IM_PI / 180.0f);

        // ImGui 绘图路径 API
        draw_list->PathArcTo(ImVec2(x, y), radius, min, max);
        draw_list->PathStroke(IM_COL32(r, g, b, a), 0, thickness);
    }
	// glow 发光
    void outline_glow(float x, float y, float w, float h, float radius, int r, int g, int b, int a) {
        float rounding = 4.0f;
        float rad = rounding + 2.0f;

        // Lua代码解释：
        // renderer.rectangle(...) 用 width=1 或 height=1 画线。
        // 在 C++ 中，我们用 filled_rectangle 来画这 1px 的实心线，比画空心矩形更稳定。

        // 1. 左边竖线
        // renderer.rectangle(x+2, y+radius+rad, 1, h-rad*2-radius*2, ...)
        filled_rectangle(x + 2, y + radius + rad, 1.0f, h - rad * 2 - radius * 2, r, g, b, a);

        // 2. 右边竖线
        // renderer.rectangle(x+w-3, y+radius+rad, 1, h-rad*2-radius*2, ...)
        filled_rectangle(x + w - 3, y + radius + rad, 1.0f, h - rad * 2 - radius * 2, r, g, b, a);

        // 3. 顶部横线
        // renderer.rectangle(x+radius+rad, y+2, w-rad*2-radius*2, 1, ...)
        filled_rectangle(x + radius + rad, y + 2, w - rad * 2 - radius * 2, 1.0f, r, g, b, a);

        // 4. 底部横线
        // renderer.rectangle(x+radius+rad, y+h-3, w-rad*2-radius*2, 1, ...)
        filled_rectangle(x + radius + rad, y + h - 3, w - rad * 2 - radius * 2, 1.0f, r, g, b, a);

        // 计算圆弧半径
        float arc_radius = radius + rounding;
        float thickness = 1.0f; // Lua代码未指定宽度，通常默认为1
        float percent = 0.25f;  // 1/4 圆

        // 5. 左上角 (180度起始)
        circle_outline(x + radius + rad, y + radius + rad, r, g, b, a, arc_radius, 180.0f, percent, thickness);

        // 6. 右上角 (270度起始)
        circle_outline(x + w - radius - rad, y + radius + rad, r, g, b, a, arc_radius, 270.0f, percent, thickness);

        // 7. 左下角 (90度起始)
        circle_outline(x + radius + rad, y + h - radius - rad, r, g, b, a, arc_radius, 90.0f, percent, thickness);

        // 8. 右下角 (0度起始)
        circle_outline(x + w - radius - rad, y + h - radius - rad, r, g, b, a, arc_radius, 0.0f, percent, thickness);
    }
	// 模糊

    void blur(float x, float y, float w, float h, int a = 255, float strength = 1.0f) {
        ImDrawList* draw_list = get_drawlist();
        // 1. 分配一块内存来存储模糊参数 (ImGui 会自动管理这块内存的生命周期)
        // 注意：如果你是在多线程环境下，这里可能需要注意内存对齐，但通常在主渲染线程没问题
        BlurData* data = (BlurData*)ImGui::MemAlloc(sizeof(BlurData));
        data->x = x;
        data->y = y;
        data->w = w;
        data->h = h;
        data->strength = strength;
        data->alpha = (float)a / 255.0f;
        // 2. 添加回调函数
        // 当 ImGui 渲染到这一步时，会调用 BlurCallback，并把 data 传进去
        draw_list->AddCallback(BlurCallback, data);
        // 注意：AddCallback 会打断合批(Batching)，稍微影响性能，不要滥用。
    }
    
	// 假模糊（半透明背景+边框）
    void blur_fake(float x, float y, int w, int h, int a = 255) {
        ImDrawList* draw_list = get_drawlist();

        // 画一个半透明黑色背景
        draw_list->AddRectFilled(
            ImVec2(x, y),
            ImVec2(x + w, y + h),
            IM_COL32(20, 20, 20, a * 0.6) // 稍微暗一点
        );

        // 画一个边框让它看起来像个面板
        draw_list->AddRect(
            ImVec2(x, y),
            ImVec2(x + w, y + h),
            IM_COL32(255, 255, 255, 30) // 淡淡的白边
        );
    }
} 