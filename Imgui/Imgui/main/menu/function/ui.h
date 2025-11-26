#pragma once
#include "imgui.h"
#include <vector>
#include <string>

namespace ui {

    // ---------------------------------------------------------
    // 基础控件 (Widgets)
    // ---------------------------------------------------------
    // 文字标签
    inline void label(const char* text) {
        ImGui::Text("%s", text);
    }
	// 复选框
    inline bool checkbox(const char* text, bool* v) {
        // 1. 绘制左侧文字
        ImGui::Text("%s", text);

        // 2. 保持同行
        ImGui::SameLine();

        // 3. 计算右对齐位置 (复制你之前的逻辑)
        float window_width = ImGui::GetContentRegionAvail().x;
        float cursor_pos = ImGui::GetCursorPosX();
        float check_box_width = ImGui::GetFrameHeight();
        if (window_width + ImGui::GetStyle().WindowPadding.x - check_box_width > cursor_pos) {
            ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - check_box_width);
        }

        // 4. 使用 PushID 防止不同 checkbox 冲突
        ImGui::PushID(text);

        // 5. 【关键修复】这里不能传 ""，要传 "##hidden"
        // "##" 表示隐藏标签，后面的 "hidden" 参与 ID 计算但不会显示
        bool result = ImGui::Checkbox("##hidden", v);

        ImGui::PopID();

        return result;
    }
	// 整数滑块
    inline bool slider(const char* label, int* v, int v_min, int v_max, const char* format = "%d") {
        // GameSense 的滑块通常宽度填满
        ImGui::SetNextItemWidth(-1);
        return ImGui::SliderInt(label, v, v_min, v_max, format);
    }
	// 浮点数滑块
    inline bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format = "%.2f") {
        ImGui::SetNextItemWidth(-1);
        return ImGui::SliderFloat(label, v, v_min, v_max, format);
    }
	// 按钮
    inline bool button(const char* label, const ImVec2& size = ImVec2(0, 0)) {
        return ImGui::Button(label, size);
    }
	
	// 下拉框
    inline bool combobox(const char* label, int* current_item, const std::vector<const char*>& items) {
        ImGui::SetNextItemWidth(-1);
        // ImGui 的 Combo 需要数组，这里用 vector 转换一下
        return ImGui::Combo(label, current_item, items.data(), items.size());
    }
	// 颜色选择器
    inline bool color_picker(const char* label, float col[4], bool alpha = true) {
        int flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview;
        if (!alpha) flags |= ImGuiColorEditFlags_NoAlpha;

        // 绘制颜色块
        bool result = ImGui::ColorEdit4(label, col, flags);

        // 如果需要文字标签显示在旁边
        if (label[0] != '#' && label[1] != '#') {
            ImGui::SameLine();
            ImGui::Text("%s", label);
        }
        return result;
    }
	// 文本输入框
    inline bool input_text(const char* label, char* buf, size_t buf_size) {
        ImGui::SetNextItemWidth(-1);
        return ImGui::InputText(label, buf, buf_size);
    }

    // ---------------------------------------------------------
    // 布局与分组 (Layout)
    // ---------------------------------------------------------

	// 开始一个带标题栏的分组
    inline void begin_group(const char* name, float height = 0.0f, float w = 0.0f) {
        ImGui::BeginChild(name, ImVec2(w, height), true, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            ImGui::TextUnformatted(name);
            ImGui::EndMenuBar();
        }
        // 稍微加点内边距
        ImGui::Dummy(ImVec2(0, 2.0f));
        ImGui::Indent(5.0f);
    }
	// 结束分组
    inline void end_group() {
        ImGui::Unindent(5.0f);
        ImGui::EndChild();
    }
}