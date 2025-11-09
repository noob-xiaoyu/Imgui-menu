// main.cpp

// 引入 Dear ImGui 核心库
#include "imgui.h"
// 引入 ImGui 的 GLFW 后端实现
#include "imgui_impl_glfw.h"
// 引入 ImGui 的 OpenGL3 后端实现
#include "imgui_impl_opengl3.h"
// 引入 GLFW 窗口管理库
#include <GLFW/glfw3.h>
// 引入我们自定义的菜单头文件
#include "menu/menu.h"
// 引入标准输入输出库，用于打印错误信息
#include <cstdio>

// 条件编译：下面的代码只在 Windows 平台上编译
#ifdef _WIN32
// 这个宏定义允许我们通过 glfw3native.h 访问底层的 Win32 API
#define GLFW_EXPOSE_NATIVE_WIN32
// 引入 GLFW 的原生平台接口头文件，用于获取 HWND
#include <GLFW/glfw3native.h>
// 引入 Windows API 主头文件，用于键盘钩子
#include <Windows.h>
#endif

// 全局变量，用于存储键盘钩子的句柄。
// 必须是全局的，以便在回调函数和 main 函数中都能访问。
HHOOK g_keyboardHook = NULL;

/**
 * @brief 低级别键盘钩子回调函数 (Low-Level Keyboard Hook Procedure)。
 *
 * 这是一个由 Windows 系统在每次键盘事件发生时调用的函数。
 * 它允许我们的程序在系统级别监听键盘输入，即使我们的窗口没有焦点。
 *
 * @param nCode 一个代码，钩子过程用它来决定如何处理消息。我们只关心 HC_ACTION。
 * @param wParam 消息类型，例如 WM_KEYDOWN (按键按下)。
 * @param lParam 指向 KBDLLHOOKSTRUCT 结构的指针，包含关于按键事件的详细信息。
 * @return LRESULT 返回值，通常是调用 CallNextHookEx 的结果。
 */
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // 如果 nCode 是 HC_ACTION，表示我们应该处理这个消息。
    if (nCode == HC_ACTION) {
        // 将 lParam 转换为指向键盘钩子结构体的指针，以获取详细信息。
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;

        // 我们只关心按键被按下的事件 (WM_KEYDOWN 或 WM_SYSKEYDOWN for Alt+key etc.)
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // ===================================================
            //  ↓ 关键逻辑：使用 menu::state::toggle_key_vk 进行判断 ↓
            // ===================================================
            // 检查我们是否设置了切换键 (不为0)，并且当前按下的键的虚拟键码 (vkCode)
            // 是否与我们存储的菜单切换键的虚拟键码相匹配。
            if (menu::state::toggle_key_vk != 0 && pkbhs->vkCode == menu::state::toggle_key_vk) {
                // 如果匹配，就翻转菜单的可见状态 (true -> false, false -> true)。
                menu::state::visible = !menu::state::visible;

                // 如果在这里返回 1 (return 1;)，这个按键消息将被“吞掉”，
                // 其他应用程序（包括游戏本身）将不会收到这个按键事件。
                // 这在某些情况下有用，但通常我们希望按键能正常传递下去。
                // return 1; 
            }
        }
    }
    // 调用 CallNextHookEx 将消息传递给钩子链中的下一个钩子。
    // 这是一个非常重要的步骤，否则会中断其他依赖键盘钩子的程序（如热键软件）。
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

int main() {
    // 初始化 GLFW 库
    if (!glfwInit()) return -1;

    // 获取主显示器信息，用于创建全屏覆盖窗口
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (primaryMonitor == NULL) {
        fprintf(stderr, "错误: 无法获取主显示器。\n");
        glfwTerminate();
        return -1;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    if (mode == NULL) {
        fprintf(stderr, "错误: 无法获取显示器的视频模式。\n");
        glfwTerminate();
        return -1;
    }

    // 设置窗口提示，用于创建一个无边框、透明的覆盖层窗口
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);           // 禁止调整大小
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);           // 隐藏标题栏和边框
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // 启用帧缓冲透明
    glfwWindowHint(GLFW_ICONIFIED, GLFW_TRUE);             // 初始时最小化，这是一个小技巧，有时能帮助覆盖层正确显示

    // 创建一个极小的窗口 (1x1)，因为我们实际上只关心 ImGui 的渲染内容。
    // ImGui 的 Dockspace 功能会将其扩展到全屏。
    GLFWwindow* window = glfwCreateWindow(1, 1, "Imgui Menu Example", NULL, NULL);
    if (window == NULL) {
        printf("创建窗口失败\n");
        glfwTerminate();
        return -1;
    }

    // 将窗口的 OpenGL 上下文设置为当前线程的当前上下文
    glfwMakeContextCurrent(window);
    // 启用垂直同步 (V-Sync)，限制帧率与显示器刷新率同步
    glfwSwapInterval(1);

    // --- ImGui 初始化 ---
    IMGUI_CHECKVERSION(); // 检查 ImGui 版本是否匹配
    ImGui::CreateContext(); // 创建 ImGui 上下文
    ImGuiIO& io = ImGui::GetIO(); (void)io; // 获取 IO 对象引用
    // 启用 ImGui 功能
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘导航
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // 启用 Docking 功能
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // 启用多视口功能 (允许将窗口拖出主窗口)

    // 初始化 ImGui 的 GLFW 和 OpenGL3 后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 设置背景清除颜色为完全透明 (R, G, B, Alpha)
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    // --- 字体加载 ---
    const char* font_path = "C:/Windows/Fonts/msyhbd.ttc"; // 微软雅黑粗体字体路径
    float font_size = 18.0f;
    // 从文件加载字体，并指定包含简体中文字形的范围，以便正确显示中文
    ImFont* main_font = io.Fonts->AddFontFromFileTTF(font_path, font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    if (main_font == nullptr) {
        fprintf(stderr, "警告: 中文字体加载失败！路径: %s\n", font_path);
        fprintf(stderr, "程序将使用 ImGui 默认字体。\n");
    }

    // 在程序启动时，根据默认的 ImGuiKey 初始化一次虚拟键码
    menu::state::toggle_key_vk = menu::ImGuiKeyToVirtualKey(menu::state::toggle_key);

    // --- Windows 平台特定代码：安装键盘钩子 ---
#ifdef _WIN32
    // 设置一个低级别键盘钩子，WH_KEYBOARD_LL 表示监听系统范围的键盘输入事件。
    // LowLevelKeyboardProc 是我们的回调函数。
    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    if (g_keyboardHook == NULL) {
        fprintf(stderr, "错误: SetWindowsHookEx 失败！\n");
    }
#endif

    // --- 主循环 ---
    while (!glfwWindowShouldClose(window)) {
        // 处理事件，如键盘、鼠标输入
        glfwPollEvents();

        // 开始新的一帧 ImGui 渲染
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- 创建一个全屏、透明、无交互的宿主窗口来容纳 Dockspace ---
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(main_viewport->WorkPos); // 设置位置为视口工作区左上角
        ImGui::SetNextWindowSize(main_viewport->WorkSize); // 设置大小为整个视口工作区
        ImGui::SetNextWindowViewport(main_viewport->ID); // 绑定到主视口

        // 设置窗口标志，使其成为一个不可见的背景层
        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoBackground; // 完全透明背景

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // 无圆角
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // 无边框
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // 无内边距
        ImGui::Begin("Dockspace Host", nullptr, host_window_flags); // 开始宿主窗口
        ImGui::PopStyleVar(3); // 恢复样式

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        // 创建一个 Dockspace，它将填充整个宿主窗口。
        // ImGuiDockNodeFlags_PassthruCentralNode 标志非常重要，它使得鼠标点击可以“穿透”Dockspace的中心节点，
        // 这样当菜单不可见时，用户仍然可以与下面的游戏或桌面进行交互。
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::End(); // 结束宿主窗口

        // 如果菜单的可见状态为 true，则调用 menu::draw() 来绘制菜单内容
        if (menu::state::visible) {
            menu::draw();
        }

        // --- 渲染 ---
        // 生成 ImGui 的绘图数据
        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h); // 获取帧缓冲大小
        glViewport(0, 0, display_w, display_h); // 设置 OpenGL 视口
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w); // 设置清除颜色
        glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区

        // 使用 OpenGL 渲染 ImGui 的绘图数据
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 如果启用了多视口，则更新并渲染额外的平台窗口
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // 交换前后缓冲区，将渲染结果显示在屏幕上
        glfwSwapBuffers(window);
    }

    // --- 清理和退出 ---
#ifdef _WIN32
    // 在程序退出前，必须卸载已安装的钩子
    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
    }
#endif
    // 关闭 ImGui 后端和上下文
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // 销毁 GLFW 窗口并终止 GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}