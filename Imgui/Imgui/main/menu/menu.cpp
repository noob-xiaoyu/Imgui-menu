// menu/menu.cpp
#include "imgui.h"
#include "menu.h"
#include <vector>
#include <string>
#include <main/ThemeManager/ThemeManager.h>
#include <filesystem>
#include <Shlobj.h>
#include "../CustomWidgets/CustomWidgets.h"
#include "Theme.h"
#include <GLFW/glfw3.h>
#include <main/main.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <renderer.h>
#include <ui.h>
#include <client.h>

#pragma comment(lib, "shell32.lib")


namespace UI {
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
        // 1. 先绘制左侧的标签文本
        ImGui::Text("%s", label);

        // 2. 保持在同一行
        ImGui::SameLine();

        // ----------------- 自动右对齐计算 -----------------

        // 预判按钮显示的文字内容
        std::string button_text;
        if (is_waiting_flag) {
            button_text = "..."; // 等待时显示省略号，节省空间
        }
        else {
            // 格式: [KeyName]
            button_text = std::string("[") + ImGui::GetKeyName(key_to_change) + "]";
        }

        // 计算按钮所需的宽度
        // 按钮宽 = 文字宽 + 左右内边距(FramePadding.x * 2)
        float button_width = ImGui::CalcTextSize(button_text.c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f;

        // 获取当前窗口内容区域的最右边坐标
        float right_edge = ImGui::GetWindowContentRegionMax().x;

        // 获取当前光标位置（即标签文字结束的位置）
        float cursor_pos = ImGui::GetCursorPosX();

        // 如果还有足够空间，就将光标移动到最右边
        // 注意：加一点缓冲距离，防止跟边框贴得太死
        if (right_edge - button_width > cursor_pos) {
            ImGui::SetCursorPosX(right_edge - button_width);
        }

        // --------------------------------------------------

        // 3. 绘制按钮
        // 使用 PushID 确保按钮 ID 唯一，防止同名标签冲突
        ImGui::PushID(label);

        if (is_waiting_flag) {
            // 显示等待状态的按钮
            // 注意：这里用 button_text 变量，即 "..."
            if (ImGui::Button(button_text.c_str(), ImVec2(button_width, 0))) {
                // 如果再次点击等待中的按钮，取消等待（可选功能，防止用户卡住）
                is_waiting_flag = false;
            }

            // --- 按键监听逻辑 ---
            for (int key_code = ImGuiKey_NamedKey_BEGIN; key_code < ImGuiKey_NamedKey_END; key_code++) {
                ImGuiKey key_it = static_cast<ImGuiKey>(key_code);
                if (ImGui::IsKeyPressed(key_it, false)) {
                    if (key_it == ImGuiKey_Escape) {
                        key_to_change = ImGuiKey_None;
                    }
                    else {
                        key_to_change = key_it;
                    }
                    is_waiting_flag = false;
                    std::cout << "热键更新:" << ImGui::GetKeyName(key_to_change) << std::endl;
                    break;
                }
            }
        }
        else {
            // 显示当前按键
            if (ImGui::Button(button_text.c_str(), ImVec2(button_width, 0))) {
                is_waiting_flag = true;
            }
        }

        ImGui::PopID();
    }
    class Stopwatch
    {
    public:
        Stopwatch() : is_running(false), elapsed_ms(0) {}

        void Reset()
        {
            is_running = false;
            elapsed_ms = 0;
            start_time = std::chrono::steady_clock::now();
        }

        void Start()
        {
            if (!is_running)
            {
                is_running = true;
                start_time = std::chrono::steady_clock::now();
            }
        }

        void Pause()
        {
            if (is_running)
            {
                auto now = std::chrono::steady_clock::now();
                elapsed_ms += std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
                is_running = false;
            }
        }

        void Toggle()
        {
            if (is_running)
                Pause();
            else
                Start();
        }

        std::string GetElapsedTimeHMS() const
        {
            int total_ms = elapsed_ms;
            if (is_running)
            {
                auto now = std::chrono::steady_clock::now();
                total_ms += std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
            }

            int total_cs = total_ms / 10; // 百分秒
            int hours = total_cs / (100 * 3600);
            int minutes = (total_cs / (100 * 60)) % 60;
            int seconds = (total_cs / 100) % 60;
            int centiseconds = total_cs % 100;

            std::ostringstream oss;
            oss << std::setfill('0') << std::setw(2) << hours << ":"
                << std::setfill('0') << std::setw(2) << minutes << ":"
                << std::setfill('0') << std::setw(2) << seconds << ":"
                << std::setfill('0') << std::setw(2) << centiseconds;
            return oss.str();
        }

        bool IsRunning() const { return is_running; }

    private:
        bool is_running;
        long long elapsed_ms; // 毫秒
        std::chrono::steady_clock::time_point start_time;
    };
    Stopwatch timer;

    namespace Visuals {
        void Visuals_MouseTrail() {
            ImGui::TableNextColumn();
            ImGui::SeparatorText(u8"鼠标拖尾");

            ui::checkbox("启用拖尾", &menu::Visuals::mouse_trail::Enabled);
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
        }
    }
    namespace Time {
        void Time() {
            
            time_t now = time(0);
            tm ltm;
            localtime_s(&ltm, &now);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &ltm);

            ImGui::Text("Current Time:"); ImGui::SameLine(); ImGui::Text("%s", buffer);
            ImGui::Text("Time: "); ImGui::PushFont(G_HugeFont);
            ImGui::Text("%s", timer.GetElapsedTimeHMS().c_str());
            ImGui::PopFont(); ImGui::Separator();
            if (ImGui::Button(timer.IsRunning() ? "Pause" : "Start", ImVec2(100, 30)))
            {
                timer.Toggle();
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset", ImVec2(100, 30))) {
                timer.Reset();
            }
        }
    }
    namespace Settings {
        void Settings_() {
            float window_width = ImGui::GetContentRegionAvail().x;
            ui::begin_group("Setting", -1, window_width/2);{
                ImGui::Text("Theme Selector");
                static_assert(IM_ARRAYSIZE(menu::theme_names) == static_cast<int>(menu::Theme::COUNT), "Theme names array size does not match Theme enum count!");
                const char* current_theme_name = menu::theme_names[static_cast<int>(menu::Theme::COUNT)];
                int current_theme_idx = static_cast<int>(menu::Settings::current_theme);

                // 添加一个安全检查，防止索引越界。如果 current_theme 未初始化，这很重要。
                if (current_theme_idx < 0 || current_theme_idx >= IM_ARRAYSIZE(menu::theme_names)) {
                        current_theme_idx = 0; // 如果索引无效，就默认选中第一个
                    }
                const char* preview_value = menu::theme_names[current_theme_idx];
                if (ImGui::BeginCombo(u8"主题", preview_value))
                {
                    // 4. 遍历所有主题选项
                    for (int i = 0; i < static_cast<int>(menu::Theme::COUNT); ++i)
                        {
                            // 判断当前遍历到的选项是否是已经被选中的
                            const bool is_selected = (static_cast<int>(menu::Settings::current_theme) == i);

                            // 使用 Selectable 创建一个可选择的行
                            if (ImGui::Selectable(menu::theme_names[i], is_selected))
                            {
                                // 如果用户点击了这个选项，就更新当前主题
                                menu::Settings::current_theme = static_cast<menu::Theme>(i);
                                // 5. 根据新的选择，应用对应的主题
                                switch (menu::Settings::current_theme)
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
                ui::checkbox(u8"显示实时样式编辑器", &show_style_editor);
                if (show_style_editor) {
                    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
                    ImGui::Begin(u8"样式编辑器", &show_style_editor, ImGuiWindowFlags_NoCollapse);
                    ImGui::ShowStyleEditor();
                    ImGui::End();
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
                        // --- 新增代码开始 ---
                        // 为了方便处理字符串，我们先将 C 风格的 char 数组转换为 std::string
                        std::string filename_str(theme_filename);

                        // 1. 检查文件名是否为空
                        if (!filename_str.empty()) {
                            const std::string extension = ".ini";
                            bool needs_extension = true;

                            // 2. 检查文件名长度是否足够，并且是否已经以 ".ini" 结尾
                            if (filename_str.length() >= extension.length()) {
                                // 比较字符串的最后几个字符
                                if (filename_str.substr(filename_str.length() - extension.length()) == extension) {
                                    needs_extension = false;
                                }
                            }

                            // 3. 如果需要，就添加扩展名
                            if (needs_extension) {
                                filename_str += extension;
                                // 将修改后的字符串复制回原来的 char 数组
                                // 这样 InputText 和 SaveTheme 函数都能获取到正确的文件名
                                strncpy_s(theme_filename, filename_str.c_str(), sizeof(theme_filename));
                            }
                        }
                        // --- 新增代码结束 ---

                        // 使用可能已经被修改过的 theme_filename 来保存主题
                        ThemeManager::SaveTheme(theme_filename);
                        themes = ThemeManager::GetAvailableThemes(); // 保存后刷新列表
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
                            bool success = ThemeManager::LoadTheme(themes[selected_theme]);
                            if (!success) {
                                // 可以在这里处理加载失败的情况，比如弹出一个错误提示窗口
                                // ImGui::OpenPopup("Load Error");
                            }
                        }
                        ImGui::EndDisabled();
                    }

                else {
                    ImGui::Text(u8"在 'themes' 文件夹中未找到任何主题。");
                }
            }ui::end_group();
            ImGui::SameLine();
            ui::begin_group("Menu", -1, 0); {
                ui::checkbox(u8"锁定菜单布局", &menu::Settings::lock_window_size);

                ImGui::Text("Menu Toggle Key:");
                ImGui::SameLine();
                ImGuiKey old_key = menu::state::toggle_key;
                Keybind("", menu::state::toggle_key, menu::state::is_waiting_for_key);
                if (old_key != menu::state::toggle_key) {
                    menu::state::toggle_key_vk = ImGuiKeyToVirtualKey(menu::state::toggle_key);
                }
                ImGui::Separator();
                if (!menu::quit::show_exit_confirmation)
                {
                    float window_width = ImGui::GetContentRegionAvail().x;
                    if (ImGui::Button(u8"退出",ImVec2(window_width, 0)))
                    {
                        // 当点击时，我们不直接退出，而是改变状态，让确认对话框显示出来
                        menu::quit::show_exit_confirmation = true;
                    }
                }

                // 2. 根据状态变量，决定是否绘制确认对话框
                if (menu::quit::show_exit_confirmation)
                {
                    ui::begin_group("Quit?", 100, 130);
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
                    ui::end_group();
                }
            }ui::end_group();

        }
    }
    namespace Configs {
        namespace ConfigSystem {
            // 使用 static 确保只在当前文件可见，防止与其他文件变量冲突
            static int selected_index = -1;
            static char input_buffer[64] = "";

            // 初始数据
            static std::vector<std::string> config_files = {
                "Legit_Global",
                "HvH_Scout",
                "HvH_Auto",
                "Visuals_Only"
            };

            void RealSaveToFile(const std::string& filename) {
                // 这里写你真正的文件写入逻辑 (例如 ThemeManager::SaveTheme)
                std::cout << "[Disk] Saving file: " << filename << ".cfg" << std::endl;
            }

            void SaveOrCreate() {
                std::string input_name = input_buffer;

                // 情况 1: 输入框不为空
                if (!input_name.empty()) {

                    // 检查这个名字是否已经存在于列表中
                    bool found = false;
                    for (int i = 0; i < config_files.size(); i++) {
                        if (config_files[i] == input_name) {
                            // 找到了！直接选中它，准备覆盖保存
                            selected_index = i;
                            found = true;
                            break;
                        }
                    }

                    // 如果没找到 -> 说明是新配置 -> 创建它
                    if (!found) {
                        config_files.push_back(input_name);
                        selected_index = (int)config_files.size() - 1; // 选中这个新的
                        std::cout << "[List] Created new config: " << input_name << std::endl;
                    }
                }

                // 情况 2: 执行保存逻辑
                if (selected_index >= 0 && selected_index < config_files.size()) {
                    // 调用真正的保存函数
                    RealSaveToFile(config_files[selected_index]);

                    // 可选：保存后清空输入框，提升体验
                    // memset(input_buffer, 0, sizeof(input_buffer));
                }
                else {
                    std::cout << "[Error] No config selected or created to save!" << std::endl;
                }
            }

            void DeleteConfig() {
                if (selected_index >= 0 && selected_index < config_files.size()) {
                    config_files.erase(config_files.begin() + selected_index);
                    // 删除后重置选中项，防止越界访问崩溃
                    selected_index = -1;
                }
            }
        }
        // 渲染函数
        void RenderConfigList() {
            float window_width = ImGui::GetContentRegionAvail().x;
            if (false)
            {
                std::cout << window_width / 2 << std::endl;
                std::cout << window_width << std::endl;
            }
            ui::begin_group("Setting", -1, window_width / 2); {
                // -------------------------------------------------
                // 1. 顶部输入框 (用于创建新配置)
                // -------------------------------------------------
                

                // 稍微留点空隙
                ImGui::Dummy(ImVec2(0, 3));

                // -------------------------------------------------
                // 2. 列表区域 (使用 BeginChild 模拟 ListBox)
                // -------------------------------------------------
                // 高度设置为 200px (或者根据剩余空间计算)
                // true 表示显示边框
                if (ImGui::BeginChild("##ConfigList", ImVec2(0, 200), true)) {

                    for (int i = 0; i < ConfigSystem::config_files.size(); ++i) {
                        // 检查是否被选中
                        const bool is_selected = (ConfigSystem::selected_index == i);

                        // 绘制可选项
                        // GameSense 的选中项通常是高亮的
                        if (ImGui::Selectable(ConfigSystem::config_files[i].c_str(), is_selected)) {
                            ConfigSystem::selected_index = i;

                            // 可选：点击时自动把名字填入输入框，方便修改
                            strcpy_s(ConfigSystem::input_buffer, sizeof(ConfigSystem::input_buffer), ConfigSystem::config_files[i].c_str());
                        }

                        // 确保刚打开菜单时，滚动条在选中项位置
                        if (is_selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndChild();
                }

                // 稍微留点空隙
                ImGui::Dummy(ImVec2(0, 3)); float btn_w = ImGui::GetContentRegionAvail().x;

                ImGui::PushItemWidth(-1);
                ImGui::InputText("##ConfigInput", ConfigSystem::input_buffer, sizeof(ConfigSystem::input_buffer));
                ImGui::PopItemWidth();

                if (ImGui::Button("加载", ImVec2(btn_w, 0))) {
                    if (ConfigSystem::selected_index != -1) {
                        // 这里调用你的 LoadConfig 逻辑
                        printf("Loading: %s\n", ConfigSystem::config_files[ConfigSystem::selected_index].c_str());
                    }
                }

                if (ImGui::Button("保存", ImVec2(btn_w, 0))) {
                    ConfigSystem::SaveOrCreate();
                }

                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("保存选定的配置。\n如果名称不同，则创建新的配置.");
                }
                if (ImGui::Button("删除", ImVec2(btn_w, 0))) {
                    ConfigSystem::DeleteConfig();
                }
                if (ImGui::Button("重置 占位符", ImVec2(btn_w, 0))) {
                    //重置
                }
                if (ImGui::Button("从剪贴板导入 占位符", ImVec2(btn_w, 0))) {
                    //从剪贴板导入
                }
                if (ImGui::Button("导出至剪贴板 占位符", ImVec2(btn_w, 0))) {
                    //导出至剪贴板
                }
                ImGui::Dummy(ImVec2(0, 3));
            }ui::end_group();
            ImGui::SameLine();
            ui::begin_group("lua", -1, 0); {

            }ui::end_group();
        }
    }
}
namespace menu {
    void draw() {
        auto [w, h] = client::screen_size();
        renderer::blur_fake(0, 0, w, h);
        if (is_running) {
            total_seconds += ImGui::GetIO().DeltaTime;
        }
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
        if (menu::Settings::lock_window_size) {
            window_flags |= ImGuiWindowFlags_NoResize;
        }
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
            ImGui::Separator();
            ImGui::Text(u8"帧率: %.1f FPS", ImGui::GetIO().Framerate);
            ImGui::Separator();
            ImGui::EndChild();ImGui::SameLine();
            ImGui::BeginChild("ContentArea", ImVec2(0, 0), true); {
                switch (active_tab) {
                    case 0: {
                        ImGui::Text("This is the a Page.");
                        
                        
                        ImGui::Text(u8"这里是一些中文字符: 你好, ImGui!");
                        break;
                    }
                    case 1: {
                        UI::Visuals::Visuals_MouseTrail();
                        break;
                    }
                    case 2: {
                        ImGui::Text("This is the c Page.");
                        ImGui::SliderFloat("A slider", &state::a_slider, 0.0f, 1.0f);
                        break;
                    }
                    case 3: {
                        UI::Time::Time();
                        break;
                    }
                    case 4: {
                        char buf[64];
                        sprintf_s(buf, "帧率: %.1f FPS", ImGui::GetIO().Framerate);
                        renderer::text(100, 100, 255, 255, 255, 255, buf, true);
                        UI::Settings::Settings_();
                        break;
                    }
                    case 5: {
                        UI::Configs::RenderConfigList();
                        break;
                    }
                }
            }
            ImGui::EndChild();
            
        }
        ImGui::End();
    }

    struct Config {
        bool aimbot_enabled = false;
        int fov = 10;
        int hitchance = 50;
        int target_selection = 0; // 0: Cycle, 1: Distance
        float esp_color[4] = { 1.f, 0.f, 0.f, 1.f };
    } config;
    void DrawMenu() {
        // 设置一下窗口风格让它看起来像 GameSense (可选)
        // ImGui::PushStyleVar... (略)

        if (ImGui::Begin("GameSense Clone", nullptr, ImGuiWindowFlags_NoCollapse)) {

            // ----------------- 左侧栏 -----------------
            ImGui::BeginGroup();
            {

                ui::begin_group("Aimbot", 300,550); // 高度300
                {
                    ui::checkbox("Enabled", &config.aimbot_enabled);

                    // 如果勾选才显示后面的
                    if (config.aimbot_enabled) {
                        ui::slider("Field of View", &config.fov, 1, 180, "%d deg");
                        ui::slider("Hitchance", &config.hitchance, 0, 100, "%d %%");

                        // 下拉菜单
                        std::vector<const char*> targets = { "Cycle", "Distance", "Health" };
                        ui::combobox("Target Selection", &config.target_selection, targets);
                    }
                }
                ui::end_group();
            }
            ImGui::EndGroup();

            ImGui::SameLine(); // 切换到右侧

            // ----------------- 右侧栏 -----------------
            ImGui::BeginGroup();
            {
                ui::begin_group("Visuals", 300);
                {
                    ui::label("Player ESP");
                    ui::color_picker("Box Color", config.esp_color);

                    ui::button("Save Config", ImVec2(-1, 20)); // -1 表示宽占满
                    ui::button("Load Config", ImVec2(-1, 20));
                }
                ui::end_group();
            }
            ImGui::EndGroup();
        }
        ImGui::End();
    }
}

