// menu/menu.h

// 预处理指令，防止头文件被多次包含。这是现代 C++ 中标准的头文件保护宏。
#pragma once

// 引入 Dear ImGui 的主头文件，这是构建 UI 的基础。
#include "imgui.h"

// 条件编译：下面的代码只在编译目标为 Windows 平台时才会被包含。
#ifdef _WIN32
// 包含 Windows API 的主头文件。
// 这是为了使用 Windows 特有的定义，例如虚拟按键码 (Virtual-Key Codes)，如 VK_INSERT。
#include <Windows.h> 
#endif

// 定义一个名为 menu 的命名空间，用于封装所有与菜单相关的代码，
// 避免与应用程序的其他部分产生命名冲突。
namespace menu {

    // 定义一个嵌套的命名空间 state，专门用于存放菜单的全局状态变量。
    // 这样做可以清晰地组织代码，将数据和操作分离开。
    namespace state {

        // C++17 的 `inline` 变量特性。
        // 这允许我们在头文件中定义并初始化全局变量，而不会在链接时产生“多重定义”错误。
        // 每个包含此头文件的编译单元都会有这个变量的副本，但链接器会确保它们都指向同一个实例。

        /**
         * @brief 控制菜单窗口是否可见。
         *
         * 当为 true 时，菜单会显示；为 false 时，菜单会隐藏。
         * 这个变量通常会作为引用传递给 ImGui::Begin() 函数的 p_open 参数。
         */
        inline bool visible = true;

        /**
         * @brief 用于切换菜单可见性的按键，使用 ImGui 的内部按键枚举 ImGuiKey。
         *
         * 默认设置为 Insert 键。这个变量由 Keybind 部件修改。
         */
        inline ImGuiKey toggle_key = ImGuiKey_Insert;

        /**
         * @brief 与 toggle_key 对应的 Windows 虚拟按键码 (VK code)。
         *
         * 这个值通常用于在游戏的主循环或 Windows 消息处理（如 WndProc）中监听全局按键事件，
         * 因为 ImGui 的按键检测通常只在 ImGui 上下文活动时才有效。
         * 当 toggle_key 改变时，这个值也需要同步更新。
         */
        inline int toggle_key_vk = VK_INSERT;

        /**
         * @brief 一个状态标志，用于 Keybind 部件。
         *
         * 当用户点击按键绑定按钮后，此标志设为 true，表示系统正在等待用户按下新的按键。
         */
        inline bool is_waiting_for_key = false;

        // 以下是菜单中其他 UI 控件的状态变量示例。

        /** @brief 一个示例复选框的状态（选中/未选中）。 */
        inline bool a_checkbox = false;

        /** @brief 一个示例滑块的当前值。 */
        inline float a_slider = 0.5f;
    }

    /**
     * @brief 绘制整个菜单界面的主函数。
     *
     * 这个函数应该在应用程序的每一帧中被调用，它会负责渲染所有菜单窗口和控件。
     */
    void draw();

    /**
     * @brief 创建一个自定义的 ImGui 按键绑定部件。
     *
     * @param label 部件的标签。
     * @param key_to_change 对要修改的 ImGuiKey 变量的引用。
     * @param is_waiting_flag 对状态标志的引用，用于管理“等待输入”的状态。
     */
    void Keybind(const char* label, ImGuiKey& key_to_change, bool& is_waiting_flag);

    /**
     * @brief 将 ImGui 的按键码 (ImGuiKey) 转换为 Windows 的虚拟按键码 (VK code)。
     *
     * @param key 要转换的 ImGuiKey。
     * @return 对应的 Windows VK 码。如果没有找到匹配项，则返回 0。
     */
    int ImGuiKeyToVirtualKey(ImGuiKey key);
}