// menu/menu.cpp

// 引入 Dear ImGui 的主头文件
#include "imgui.h"
// 引入菜单的自定义头文件，可能包含了 state 命名空间和 draw 函数的声明
#include "menu.h"
// 引入 C++ 标准库的 vector 和 string，用于管理标签和构建字符串
#include <vector>
#include <string>

// 定义一个名为 menu 的命名空间，用于组织所有与菜单相关的代码
namespace menu {

    /**
     * @brief 将 ImGui 的按键码 (ImGuiKey) 转换为 Windows 虚拟按键码 (Virtual-Key Code)。
     *
     * 这在需要与操作系统底层输入（如 Windows Hooks）交互时非常有用，
     * 因为 ImGui 使用自己的按键枚举，而 Windows API 使用 VK 码。
     *
     * @param key 要转换的 ImGuiKey 枚举值。
     * @return 对应的 Windows 虚拟按键码 (VK_*)，如果无对应则返回 0。
     */
    int ImGuiKeyToVirtualKey(ImGuiKey key) {
        // 使用 switch 语句处理非字母和数字的特殊按键
        switch (key) {
        case ImGuiKey_Insert:       return VK_INSERT;
        case ImGuiKey_Delete:       return VK_DELETE;
        case ImGuiKey_Home:         return VK_HOME;
        case ImGuiKey_End:          return VK_END;
        case ImGuiKey_PageUp:       return VK_PRIOR;  // VK_PRIOR 是 PageUp 的虚拟码
        case ImGuiKey_PageDown:     return VK_NEXT;   // VK_NEXT 是 PageDown 的虚拟码
        case ImGuiKey_LeftArrow:    return VK_LEFT;
        case ImGuiKey_RightArrow:   return VK_RIGHT;
        case ImGuiKey_UpArrow:      return VK_UP;
        case ImGuiKey_DownArrow:    return VK_DOWN;
        case ImGuiKey_Escape:       return VK_ESCAPE;
        case ImGuiKey_Tab:          return VK_TAB;
        case ImGuiKey_Backspace:    return VK_BACK;
        case ImGuiKey_Enter:        return VK_RETURN;
        case ImGuiKey_F1:           return VK_F1;
        case ImGuiKey_F2:           return VK_F2;
        case ImGuiKey_F3:           return VK_F3;
        case ImGuiKey_F4:           return VK_F4;
        case ImGuiKey_F5:           return VK_F5;
        case ImGuiKey_F6:           return VK_F6;
        case ImGuiKey_F7:           return VK_F7;
        case ImGuiKey_F8:           return VK_F8;
        case ImGuiKey_F9:           return VK_F9;
        case ImGuiKey_F10:          return VK_F10;
        case ImGuiKey_F11:          return VK_F11;
        case ImGuiKey_F12:          return VK_F12;
        }
        // 如果是字母 A 到 Z，通过计算偏移量得出对应的 ASCII/VK 码
        if (key >= ImGuiKey_A && key <= ImGuiKey_Z) return 'A' + (key - ImGuiKey_A);
        // 如果是数字 0 到 9，同样通过计算偏移量得出
        if (key >= ImGuiKey_0 && key <= ImGuiKey_9) return '0' + (key - ImGuiKey_0);
        // 如果没有找到对应的按键，返回 0
        return 0;
    }

    /**
     * @brief 创建一个可交互的按键绑定 ImGui 部件。
     *
     * 该部件允许用户点击一个按钮，然后按下键盘上的任意键来设置一个新的按键绑定。
     *
     * @param label 部件的标签文本。
     * @param key_to_change 一个 ImGuiKey 变量的引用，用于存储和更新绑定的按键。
     * @param is_waiting_flag 一个布尔值的引用，用于管理部件的状态（正常显示 vs 等待按键输入）。
     */
    void Keybind(const char* label, ImGuiKey& key_to_change, bool& is_waiting_flag) {
        // 如果当前不处于“等待按键”状态
        if (!is_waiting_flag) {
            // 构建按钮上显示的文本，格式为 "标签: [按键名]"
            std::string button_label = std::string(label) + "[" + ImGui::GetKeyName(key_to_change) + "]";
            // 创建一个按钮，如果被点击
            if (ImGui::Button(button_label.c_str())) {
                // 将状态标志设置为 true，进入“等待按键”状态
                is_waiting_flag = true;
            }
        }
        // 如果当前处于“等待按键”状态
        else {
            // 显示一个提示用户按键的按钮
            ImGui::Button("...Press any key...");
            // 遍历所有 ImGui 支持的命名按键
            for (int key_code = ImGuiKey_NamedKey_BEGIN; key_code < ImGuiKey_NamedKey_END; key_code++) {
                ImGuiKey key_it = static_cast<ImGuiKey>(key_code);
                // 检查当前帧是否有按键被按下（false 表示只触发一次）
                if (ImGui::IsKeyPressed(key_it, false)) {
                    // 如果按下的是 Escape 键，则将按键绑定设置为空 (None)
                    if (key_it == ImGuiKey_Escape) {
                        key_to_change = ImGuiKey_None;
                    }
                    // 否则，更新绑定的按键为用户按下的键
                    else {
                        key_to_change = key_it;
                    }
                    // 将状态标志设置回 false，退出“等待按键”状态
                    is_waiting_flag = false;
                    // 按键已捕获，跳出循环
                    break;
                }
            }
        }
    }

    /**
     * @brief 绘制整个菜单界面的主函数。
     */
    void draw() {
        // 定义菜单的标签页，使用 static const 确保只初始化一次
        static const std::vector<const char*> menu_tabs = { "a", "b", "c", "d" };
        // 定义当前活动的标签页索引，使用 static 确保在函数调用之间保持其值
        static int active_tab = 0;

        // 开始绘制一个名为 "Menu" 的窗口。
        // &state::visible 是一个指向布尔值的指针，当用户点击窗口关闭按钮时，ImGui 会将其设为 false。
        // ImGuiWindowFlags_NoCollapse 标志禁止用户折叠窗口。
        ImGui::Begin("Menu", &state::visible, ImGuiWindowFlags_NoCollapse); {

            // 左侧导航栏区域
            // BeginChild 创建一个子窗口，用于容纳导航按钮。
            // ImVec2(120, 0) 表示宽度为 120 像素，高度自动填充。true 表示带边框。
            ImGui::BeginChild("NavigationBar", ImVec2(120, 0), true); {
                // 遍历所有标签页
                for (int i = 0; i < menu_tabs.size(); ++i) {
                    bool is_active = (active_tab == i);
                    // 如果当前标签是活动标签
                    if (is_active) {
                        // 临时改变按钮的颜色以高亮显示
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
                    }
                    // 创建一个按钮，ImVec2(-1, 50) 表示宽度撑满子窗口，高度为 50 像素
                    if (ImGui::Button(menu_tabs[i], ImVec2(-1, 50))) {
                        // 如果按钮被点击，则更新活动标签的索引
                        active_tab = i;
                    }
                    // 如果之前改变了颜色，现在恢复它，以避免影响后续的控件
                    if (is_active) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::EndChild(); // 结束导航栏子窗口

            // 将下一个控件放在与上一个控件（导航栏）同一行
            ImGui::SameLine();

            // 右侧内容区域
            // 创建另一个子窗口来显示标签页的内容。
            // ImVec2(0, 0) 表示自动填充剩余的父窗口空间。
            ImGui::BeginChild("ContentArea", ImVec2(0, 0), true); {
                // 使用 switch 语句根据当前活动的标签页来决定绘制什么内容
                switch (active_tab) {
                case 0: { // 第一个标签页
                    ImGui::Text("This is the a Page.");

                    ImGui::Text("Menu Toggle Key:");
                    ImGui::SameLine(); // 将按键绑定控件放在同一行
                    ImGuiKey old_key = state::toggle_key; // 保存旧的按键值，用于检测变化
                    // 调用 Keybind 函数创建一个按键绑定控件
                    Keybind(" ", state::toggle_key, state::is_waiting_for_key);
                    // 如果按键值发生了变化
                    if (old_key != state::toggle_key) {
                        // 立即更新对应的 Windows 虚拟按键码 (VK)
                        state::toggle_key_vk = ImGuiKeyToVirtualKey(state::toggle_key);
                    }
                    ImGui::Separator(); // 绘制一条分割线

                    // 显示包含中文字符的文本。u8 前缀确保字符串是 UTF-8 编码，ImGui 可以正确处理。
                    ImGui::Text(u8"这里是一些中文字符: 你好, ImGui!");
                    break;
                }
                case 1: { // 第二个标签页
                    ImGui::Text("This is the b Page.");
                    // 创建一个复选框，并将其状态与 state::a_checkbox 变量绑定
                    ImGui::Checkbox("A checkbox", &state::a_checkbox);
                    break;
                }
                case 2: { // 第三个标签页
                    ImGui::Text("This is the c Page.");
                    // 创建一个浮点数滑块，范围 0.0 到 1.0，并与 state::a_slider 变量绑定
                    ImGui::SliderFloat("A slider", &state::a_slider, 0.0f, 1.0f);
                    break;
                }
                case 3: { // 第四个标签页
                    ImGui::Text("This is the d Page.");
                    // 显示一段长文本，它会自动换行以适应窗口宽度
                    ImGui::TextWrapped("This is some long text that will wrap to the next line.");
                    ImGui::TextWrapped(u8"这是一段较长的文本，将自动换行。");
                    break;
                }
                }
            }
            ImGui::EndChild(); // 结束内容区域子窗口
        }
        ImGui::End(); // 结束 "Menu" 主窗口
    }
}