// 设置一个柔和、干净的樱花粉亮色主题
#include <imgui.h>
void SetSakuraPinkTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- 核心色板 ---
    // 柔和的粉色，灵感来自樱花
    ImVec4 accent_color = ImVec4(0.95f, 0.67f, 0.72f, 1.00f);
    // 悬停时更亮
    ImVec4 accent_hovered = ImVec4(1.00f, 0.75f, 0.80f, 1.00f);
    // 激活时颜色更深、更饱和
    ImVec4 accent_active = ImVec4(0.90f, 0.60f, 0.65f, 1.00f);

    // 浅色背景和深色文本
    ImVec4 text_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // 深炭色文本
    ImVec4 bg_color = ImVec4(0.98f, 0.97f, 0.97f, 1.00f); // 带有极淡粉色的灰白背景
    ImVec4 frame_bg_color = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // 纯白控件背景，形成对比
    ImVec4 border_color = ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // 柔和的灰色边框

    // --- 颜色设置 ---
    colors[ImGuiCol_Text] = text_color;
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.71f, 0.71f, 0.71f, 1.00f);

    colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg] = frame_bg_color;
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = accent_color;
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);

    colors[ImGuiCol_CheckMark] = accent_color;
    colors[ImGuiCol_SliderGrab] = accent_color;
    colors[ImGuiCol_SliderGrabActive] = accent_active;

    colors[ImGuiCol_Button] = accent_color;
    colors[ImGuiCol_ButtonHovered] = accent_hovered;
    colors[ImGuiCol_ButtonActive] = accent_active;

    colors[ImGuiCol_Header] = accent_color;
    colors[ImGuiCol_HeaderHovered] = accent_hovered;
    colors[ImGuiCol_HeaderActive] = accent_active;

    colors[ImGuiCol_Separator] = border_color;
    colors[ImGuiCol_SeparatorHovered] = accent_hovered;
    colors[ImGuiCol_SeparatorActive] = accent_active;

    colors[ImGuiCol_ResizeGrip] = accent_color;
    colors[ImGuiCol_ResizeGripHovered] = accent_hovered;
    colors[ImGuiCol_ResizeGripActive] = accent_active;

    colors[ImGuiCol_Tab] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TabHovered] = accent_hovered;
    colors[ImGuiCol_TabActive] = accent_color;
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = bg_color;

    colors[ImGuiCol_DockingPreview] = ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.7f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.35f);

    // ... 其他颜色可以保持默认或根据需要微调

    // --- 布局和圆角 ---
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.ItemSpacing = ImVec2(7.0f, 5.0f);
    style.WindowRounding = 8.0f;
    style.FrameRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.PopupRounding = 8.0f;
    style.GrabRounding = 8.0f;
}
// 设置一个高对比度的霓虹粉暗色主题
void SetNeonPinkDarkTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- 核心色板 ---
    // 高饱和度的亮粉色
    ImVec4 accent_color = ImVec4(1.00f, 0.08f, 0.58f, 1.00f); // Hot Pink
    ImVec4 accent_hovered = ImVec4(1.00f, 0.30f, 0.68f, 1.00f);
    ImVec4 accent_active = ImVec4(0.90f, 0.00f, 0.50f, 1.00f);

    // 深色背景和亮色文本
    ImVec4 text_color = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 bg_color = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    ImVec4 frame_bg_color = ImVec4(0.16f, 0.16f, 0.18f, 1.00f);

    // --- 颜色设置 ---
    // (这里的结构与之前的暗色主题类似，只是替换了主色)
    colors[ImGuiCol_Text] = text_color;
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = bg_color;
    colors[ImGuiCol_ChildBg] = bg_color;
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_FrameBg] = frame_bg_color;
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = accent_active;
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_CheckMark] = accent_color;
    colors[ImGuiCol_SliderGrab] = accent_color;
    colors[ImGuiCol_SliderGrabActive] = accent_active;
    colors[ImGuiCol_Button] = accent_color;
    colors[ImGuiCol_ButtonHovered] = accent_hovered;
    colors[ImGuiCol_ButtonActive] = accent_active;
    colors[ImGuiCol_Header] = accent_color;
    colors[ImGuiCol_HeaderHovered] = accent_hovered;
    colors[ImGuiCol_HeaderActive] = accent_active;
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_ResizeGrip] = accent_color;
    colors[ImGuiCol_Tab] = frame_bg_color;
    colors[ImGuiCol_TabHovered] = accent_hovered;
    colors[ImGuiCol_TabActive] = accent_color;
    colors[ImGuiCol_DockingPreview] = ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.7f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(accent_color.x, accent_color.y, accent_color.z, 0.35f);

    // --- 布局和圆角 ---
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
}

void ApplyCustomStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // 颜色
    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.54f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.67f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.30f, 0.30f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.35f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);

    // 尺寸和圆角
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 3.00f);
    style.CellPadding = ImVec2(4.00f, 2.00f);
    style.ItemSpacing = ImVec2(4.00f, 4.00f);
    style.ItemInnerSpacing = ImVec2(4.00f, 4.00f);
    style.WindowRounding = 4.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;
}