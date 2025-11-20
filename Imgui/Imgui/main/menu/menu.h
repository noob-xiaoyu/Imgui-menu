// menu/menu.h

// 预处理指令，防止头文件被多次包含。这是现代 C++ 中标准的头文件保护宏。
#pragma once

// 引入 Dear ImGui 的主头文件，这是构建 UI 的基础。
#include "imgui.h"
#include <GLFW/glfw3.h>
// 条件编译：下面的代码只在编译目标为 Windows 平台时才会被包含。
#ifdef _WIN32
// 包含 Windows API 的主头文件。
// 这是为了使用 Windows 特有的定义，例如虚拟按键码 (Virtual-Key Codes)，如 VK_INSERT。
#include <Windows.h> 
#endif
#include <deque>

// 定义一个名为 menu 的命名空间，用于封装所有与菜单相关的代码，
// 避免与应用程序的其他部分产生命名冲突。
namespace menu {
    inline const char* theme_names[] = {
        "Dark",
        "Light",
        "Sakura Pink",
        "Neon Pink Dark",
        "ApplyCustomStyle"
    };
    enum class Theme {
        Dark,
        Light,
        SakuraPink,
        NeonPinkDark,
        ApplyCustomStyle,

        COUNT
    };
    extern Theme current_theme;

    namespace state {
        inline bool visible = true;
        inline ImGuiKey toggle_key = ImGuiKey_Insert;
        inline int toggle_key_vk = VK_INSERT;
        inline bool is_waiting_for_key = false;
        inline bool a_checkbox = false;
        inline float a_slider = 0.5f;
    }
    namespace Settings {
        inline Theme current_theme = Theme::Dark;
        inline bool lock_window_size = true;
    }
    namespace Visuals {
        namespace mouse_trail {
            inline bool Enabled;
            inline int MaxLength = 70;
            inline float  StartThickness = 5.0f;
            inline ImU32 StartColor = IM_COL32(255, 0, 255, 255);
        }
    }
    namespace quit {
        inline bool show_exit_confirmation = false;
    }
    class MouseTrail {
    public:
        // 构造函数不再需要参数
        MouseTrail() = default;

        // Render 函数现在直接从全局配置读取参数
        void Render();

    private:
        std::deque<ImVec2> points; // 只保留轨迹点
    };
    void draw();
    void Keybind(const char* label, ImGuiKey& key_to_change, bool& is_waiting_flag);
    int ImGuiKeyToVirtualKey(ImGuiKey key);
}
