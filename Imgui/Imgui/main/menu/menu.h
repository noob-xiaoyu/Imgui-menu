// menu/menu.h
#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <Windows.h> 
#endif
#include <deque>
#include <vector>
#include <chrono>

namespace menu {
    inline int active_tab = 0;
    inline const std::vector<const char*> menu_tabs = { "占位符##1", "Visuals", "占位符##2", "Time","Settings"};
    inline const char* active_tab_name = menu_tabs[0];

    inline float total_seconds = 0.0f;
    inline bool is_running = false;

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
    //void DrawFullscreenGrid();
    //void DrawMouseCrosshair();
    void Keybind(const char* label, ImGuiKey& key_to_change, bool& is_waiting_flag);
    int ImGuiKeyToVirtualKey(ImGuiKey key);
}
