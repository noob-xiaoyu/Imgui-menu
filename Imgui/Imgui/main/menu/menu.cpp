// menu/menu.cpp
#include "imgui.h"
#include "menu.h"
#include <vector>
#include <string>
#include <main/ThemeManager/ThemeManager.h>

#include "../CustomWidgets/CustomWidgets.h"
#include "Theme.h"
#include <GLFW/glfw3.h>
#include <main/main.h>
namespace menu {
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
    void Keybind(const char* label, ImGuiKey& key_to_change, bool& is_waiting_flag) {
        // 如果当前不处于“等待按键”状态
        if (!is_waiting_flag) {
            // 构建按钮上显示的文本，格式为 "标签: [按键名]"
            std::string button_label = std::string(label)+"[" + ImGui::GetKeyName(key_to_change) + "]";
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
    //static ImGuiWindowFlags demo_window_flags = ImGuiWindowFlags_MenuBar;
    void draw() {
        static const std::vector<const char*> menu_tabs = { "a", "Visuals", "c", "d","Settings"};
        static int active_tab = 0;
        //auto& app = ImGuiFramework::Application::Get();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Menu", &state::visible, window_flags); {
            ImGui::BeginChild("NavigationBar", ImVec2(120, 0), true); {
                for (int i = 0; i < menu_tabs.size(); ++i) {
                    bool is_active = (active_tab == i);
                    if (is_active) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
                    }
                    if (ImGui::Button(menu_tabs[i], ImVec2(-1, 50))) {
                        active_tab = i;
                    }
                    if (is_active) {
                        ImGui::PopStyleColor();
                    }
                }
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("ContentArea", ImVec2(0, 0), true); {
                switch (active_tab) {
                    case 0: {
                        ImGui::Text("This is the a Page.");
                        
                        
                        ImGui::Text(u8"这里是一些中文字符: 你好, ImGui!");
                        break;
                    }
                    case 1: {
                        ImGui::TableNextColumn();
                        ImGui::Text("这是外层第 2 列");
                        ImGui::SeparatorText(u8"鼠标拖尾");

                        ImGui::Checkbox(u8"启用拖尾", &menu::Visuals::mouse_trail::Enabled);
                        if (menu::Visuals::mouse_trail::Enabled)
                        {
                            // 使用 DragInt 和 DragFloat 来调整参数
                            ImGui::DragInt(u8"拖尾长度", &menu::Visuals::mouse_trail::MaxLength, 1.0f, 10, 2000);
                            ImGui::DragFloat(u8"初始粗细", &menu::Visuals::mouse_trail::StartThickness, 0.1f, 1.0f, 10.0f);

                            // 使用 ColorEdit4 来调整颜色
                            ImVec4 color_vec = ImGui::ColorConvertU32ToFloat4(menu::Visuals::mouse_trail::StartColor);
                            if (ImGui::ColorEdit4(u8"拖尾颜色", &color_vec.x)) {
                                menu::Visuals::mouse_trail::StartColor = ImGui::ColorConvertFloat4ToU32(color_vec);
                            }
                        }
                       
                        break;
                    }
                    case 2: {
                        ImGui::Text("This is the c Page.");
                        ImGui::SliderFloat("A slider", &state::a_slider, 0.0f, 1.0f);
                        break;
                    }
                    case 3: {
                        ImGui::Text("This is the d Page.");
                        ImGui::TextWrapped("This is some long text that will wrap to the next line.");
                        ImGui::TextWrapped(u8"这是一段较长的文本，将自动换行。");
                        break;
                    }
                    case 4: { // Settings Page
                        ImGui::Text("Settings");
                        ImGui::Separator();

                        ImGui::Text("Theme Selector");

                        // ImGui::RadioButton 返回 true 当它被点击时
                        // 这样我们只在主题被切换时才调用样式函数，效率更高
                        static_assert(IM_ARRAYSIZE(theme_names) == static_cast<int>(menu::Theme::COUNT), "Theme names array size does not match Theme enum count!");
                        const char* current_theme_name = theme_names[static_cast<int>(menu::Theme::COUNT)];
                        int current_theme_idx = static_cast<int>(Settings::current_theme);

                        // 添加一个安全检查，防止索引越界。如果 current_theme 未初始化，这很重要。
                        if (current_theme_idx < 0 || current_theme_idx >= IM_ARRAYSIZE(theme_names)) {
                            current_theme_idx = 0; // 如果索引无效，就默认选中第一个
                        }
                        const char* preview_value = theme_names[current_theme_idx];
                        if (ImGui::BeginCombo(u8"主题", preview_value))
                        {
                            // 4. 遍历所有主题选项
                            for (int i = 0; i < static_cast<int>(menu::Theme::COUNT); ++i)
                            {
                                // 判断当前遍历到的选项是否是已经被选中的
                                const bool is_selected = (static_cast<int>(Settings::current_theme) == i);

                                // 使用 Selectable 创建一个可选择的行
                                if (ImGui::Selectable(theme_names[i], is_selected))
                                {
                                    // 如果用户点击了这个选项，就更新当前主题
                                    Settings::current_theme = static_cast<menu::Theme>(i);
                                    // 5. 根据新的选择，应用对应的主题
                                    switch (Settings::current_theme)
                                    {
                                    case menu::Theme::Dark:
                                        ImGui::StyleColorsDark();
                                        break;
                                    case menu::Theme::Light:
                                        ImGui::StyleColorsLight();
                                        break;
                                    case menu::Theme::SakuraPink:
                                        SetSakuraPinkTheme();
                                        break;
                                    case menu::Theme::NeonPinkDark:
                                        SetNeonPinkDarkTheme();
                                        break;
                                    case menu::Theme::ApplyCustomStyle:
                                        ApplyCustomStyle();
                                        break;
                                        
                                    }
                                }

                                // 如果这个选项是被选中的，则默认将焦点设置到它上面，
                                // 这样下次打开下拉框时，列表会自动滚动到选中项
                                if (is_selected)
                                {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }

                            // 6. 结束下拉框
                            ImGui::EndCombo();
                        }

                        ImGui::Text(u8"主题管理");
                        ImGui::Separator();

                        // 1. 样式编辑器
                        static bool show_style_editor = false;
                        ImGui::Checkbox(u8"显示实时样式编辑器", &show_style_editor);
                        if (show_style_editor) {
                            ImGui::Begin(u8"样式编辑器", &show_style_editor, ImGuiWindowFlags_NoCollapse);
                            ImGui::ShowTranslatedStyleEditor(); 
                            ImGui::End();
                           /* ImGui::Begin(u8"样式编辑器原版", &show_style_editor);
                            ImGui::ShowStyleEditor();
                            ImGui::End();*/
                        }

                        ImGui::Spacing();

                        // 2. 保存当前主题
                        static char theme_filename[128];
                        

                        ImGui::Separator();

                        // 3. 加载已有主题
                        ImGui::Text(u8"加载主题");
                        static std::vector<std::string> themes = ThemeManager::GetAvailableThemes();
                        static int selected_theme = -1;

                        // 用于 ImGui::ListBox 的 C 风格字符串数组
                        std::vector<const char*> theme_cstrs;
                        for (const auto& theme : themes) {
                            theme_cstrs.push_back(theme.c_str());
                        }

                        if (ImGui::Button(u8"刷新列表")) {
                            themes = ThemeManager::GetAvailableThemes();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button(u8"保存当前主题")) {
                            ThemeManager::SaveTheme(theme_filename);
                            themes = ThemeManager::GetAvailableThemes();
                        }
                        ImGui::InputText(u8"文件名", theme_filename, sizeof(theme_filename));
                        if (!themes.empty()) {
                            std::vector<const char*> theme_cstrs;
                            for (const auto& theme : themes) {
                                theme_cstrs.push_back(theme.c_str());
                            }
                            if (ImGui::ListBox("##ThemesList", &selected_theme, theme_cstrs.data(), static_cast<int>(theme_cstrs.size())))
                            {
                                // 当 ListBox 返回 true 时，意味着 selected_theme 刚刚被用户改变了
                                // 我们就在这里更新文件名输入框的内容
                                if (selected_theme >= 0 && selected_theme < themes.size()) {
                                    // 安全地将 std::string 复制到 C 风格的 char 数组中
                                    const std::string& selected_name = themes[selected_theme];
                                    strncpy_s(theme_filename, selected_name.c_str(), sizeof(theme_filename) - 1);
                                    theme_filename[sizeof(theme_filename) - 1] = '\0'; // 确保字符串以空字符结尾
                                }
                            }

                            // --- 加载按钮 ---
                            ImGui::SameLine();
                            // 检查选中项是否有效
                            bool is_selection_valid = (selected_theme >= 0 && selected_theme < themes.size());

                            // 如果没有有效选项，则禁用按钮
                            ImGui::BeginDisabled(!is_selection_valid);
                            if (ImGui::Button(u8"加载选中项")) {
                                ThemeManager::LoadTheme(themes[selected_theme]);
                            }
                            ImGui::EndDisabled();
                        }
                        
                        else {
                            ImGui::Text(u8"在 'themes' 文件夹中未找到任何主题。");
                        }
                        
                        ImGui::Separator();
                        ImGui::Text("Menu Toggle Key:");
                        ImGui::SameLine();
                        ImGuiKey old_key = state::toggle_key;

                        Keybind(" ", state::toggle_key, state::is_waiting_for_key);
                        if (old_key != state::toggle_key) {
                            state::toggle_key_vk = ImGuiKeyToVirtualKey(state::toggle_key);
                        }
                        ImGui::Separator();
                        ImGui::Text(u8"帧率: %.1f FPS", ImGui::GetIO().Framerate);
                        
                        if (!menu::quit::show_exit_confirmation)
                        {
                            if (ImGui::Button(u8"退出"))
                            {
                                // 当点击时，我们不直接退出，而是改变状态，让确认对话框显示出来
                                menu::quit::show_exit_confirmation = true;
                            }
                        }

                        // 2. 根据状态变量，决定是否绘制确认对话框
                        if (menu::quit::show_exit_confirmation)
                        {
                            ImGui::Text(u8"您确定要退出吗？"); // 提示信息

                            // 绘制“确定”按钮
                            if (ImGui::Button(u8"确定"))
                            {
                                // 在这里执行真正的退出操作
                                std::exit(EXIT_SUCCESS);

                                // 并且关闭确认对话框（以防万一退出操作不是立即的）
                                menu::quit::show_exit_confirmation = false;
                            }

                            ImGui::SameLine(); // 让下一个控件和上一个在同一行

                            // 绘制“取消”按钮
                            if (ImGui::Button(u8"取消"))
                            {
                                // 如果用户取消，我们只需改变状态，隐藏确认对话框
                                menu::quit::show_exit_confirmation = false;
                            }
                        }

                        break;
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }
}