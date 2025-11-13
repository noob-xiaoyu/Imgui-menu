# ImGui Menu Overlay Example

这是一个使用 C++、Dear ImGui、GLFW 和 OpenGL3 实现的菜单覆盖层（Menu Overlay）模板项目。它的主要目标是展示如何创建一个可以附加到任何应用程序或游戏上的、通过全局热键切换的、可交互的菜单界面。

## ✨ 特性

- **全局热键切换**：无论当前焦点在哪个窗口，都可以通过一个全局热键（默认为 `Insert`）来显示或隐藏菜单。
- **动态按键绑定**：用户可以在菜单的设置页面中方便地修改用于切换菜单的热键。
- **透明可穿透覆盖层**：当菜单隐藏时，窗口完全透明，并且鼠标点击可以“穿透”它，不会影响与桌面或背景应用程序的正常交互。
- **多标签页界面**：采用经典的侧边栏导航布局，易于扩展和组织不同的功能模块。
- **中文字体支持**：已配置加载中文字体，确保界面能正确显示中文字符。
- **Windows 平台特定**：利用 Windows API 的全局键盘钩子来实现核心功能。

## 🚀 开始使用

### 先决条件

- 一个支持 C++17 的编译器 (例如 Visual Studio 2019 或更高版本)
- [CMake](https://cmake.org/download/) (版本 3.15 或更高)
- [Git](https://git-scm.com/)

## 🛠️ 工作原理

本项目通过几个关键技术的组合来实现其功能：

### 1. 全局键盘钩子 (Windows Hook)

为了在任何时候都能响应菜单切换键，项目使用了 Windows 的低级别键盘钩子 (`WH_KEYBOARD_LL`)。

-   在 `main.cpp` 中，通过 `SetWindowsHookEx` API 安装了一个全局钩子。
-   回调函数 `LowLevelKeyboardProc` 会在系统范围内每次有键盘事件时被调用。
-   在该函数中，我们检查按下的键是否与 `menu::state::toggle_key_vk` 中存储的虚拟键码匹配。如果匹配，就翻转菜单的可见状态 `menu::state::visible`。
-   这就是为什么此项目当前仅适用于 Windows 平台的原因。

### 2. 透明可穿透的覆盖窗口

为了让菜单看起来像是“浮”在屏幕上，并且在隐藏时不影响其他操作，GLFW 窗口被设置为一个特殊的覆盖层。

-   **窗口设置**：在创建窗口前，通过 `glfwWindowHint` 设置了几个关键属性：
    -   `GLFW_DECORATED, GLFW_FALSE`: 移除窗口的标题栏和边框。
    -   `GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE`: 启用帧缓冲区的 Alpha 通道，使窗口背景可以透明。
-   **ImGui Dockspace**：在主循环中，我们创建了一个占据整个屏幕的 ImGui `Dockspace`。
    -   `ImGuiDockNodeFlags_PassthruCentralNode` 是实现“点击穿透”的核心。它使得 Dockspace 的中心区域对鼠标事件“透明”，允许点击操作传递到下面的窗口或桌面。
-   **渲染**：每一帧的背景都用完全透明的颜色 (`0, 0, 0, 0`) 进行清除。

### 3. 状态管理与按键绑定

-   所有菜单的共享状态（如可见性、热键等）都集中在 `menu/menu.h` 的 `menu::state` 命名空间中。
-   `Keybind` 函数是一个自定义的 ImGui 控件，它提供了一个用户友好的界面来捕获新的按键输入。
-   当用户设置新热键时，`ImGuiKeyToVirtualKey` 函数会将 ImGui 内部的 `ImGuiKey` 格式转换为 Windows API 能识别的虚拟键码 (`VK_` code)，并更新 `toggle_key_vk` 变量，以确保键盘钩子能监听到正确的按键。

## 📦 依赖项

-   [Dear ImGui](https://github.com/ocornut/imgui): 主 UI 库。

## 📜 许可证

本项目采用 [MIT 许可证](https://github.com/noob-xiaoyu/Imgui-menu)。
