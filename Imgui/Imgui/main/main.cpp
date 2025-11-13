/*// main.cpp
// --- 核心头文件 ---
#include <cstdio>
#include <iostream>
#include <stdexcept>

// --- 库头文件 ---
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#ifdef IMGUI_ENABLE_FREETYPE
#include "imgui_freetype.h" // [MERGE] 如果要加载彩色Emoji，需要包含此头文件
#endif

// --- 项目头文件 ---
#include "menu/menu.h"
#include "ThemeManager/ThemeManager.h"
#include "main.h"

// [REWRITE] 将平台特定的代码隔离到不同的代码块中，提高可读性
#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>
#endif

// ===================================================================================
//  GPU 性能偏好设置 (适用于双显卡笔记本)
// ===================================================================================
// [REWRITE] 这部分逻辑是正确的，予以保留并用注释块进行格式化。
#ifdef _WIN32
extern "C" {
    // 提示 NVIDIA 驱动程序使用独立显卡
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    // 提示 AMD 驱动程序使用独立显卡
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

// ===================================================================================
//  全局热键处理 (平台特定)
// ===================================================================================
// [REWRITE] 全局热键是一个高级功能，将其逻辑封装起来，使其与主程序逻辑解耦。
#ifdef _WIN32
HHOOK g_keyboardHook = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // 检查是否按下了我们定义的菜单切换键
            if (menu::state::toggle_key_vk != 0 && pkbhs->vkCode == menu::state::toggle_key_vk) {
                menu::state::visible = !menu::state::visible;
                // 返回 1 可以阻止按键消息继续传递，但我们通常不这样做
                //return 1;
            }
        }
    }
    // 必须调用 CallNextHookEx，否则会破坏钩子链
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

void InstallGlobalHotkey() {
    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    if (g_keyboardHook == NULL) {
        std::cerr << "错误: 无法安装全局键盘钩子 (SetWindowsHookEx failed)!" << std::endl;
    }
}

void UninstallGlobalHotkey() {
    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
    }
}
#else
// 在非 Windows 平台上提供空的实现，以保证代码可以编译通过
void InstallGlobalHotkey() {
    std::cout << "信息: 当前平台不支持全局热键。" << std::endl;
}
void UninstallGlobalHotkey() {}
#endif

// ===================================================================================
//  辅助函数
// ===================================================================================
void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW 错误 %d: %s\n", error, description);
}

GLFWwindow* g_Window = nullptr;

// ===================================================================================
//  主函数
// ===================================================================================
int main() {
    // --- 1. 初始化 GLFW ---
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "严重错误: GLFW 初始化失败。\n");
        return -1;
    }

    // --- 2. 配置窗口提示 (Hints) ---
    // [REWRITE] 创建一个更适合覆盖层的窗口：无边框、透明、浮动
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);             // 无边框
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);// 开启帧缓冲透明
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);               // 窗口置顶

    // --- 3. 创建窗口 ---
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    if (!mode) {
        fprintf(stderr, "严重错误: 无法获取主显示器的视频模式。\n");
        glfwTerminate();
        return -1;
    }
    g_Window = glfwCreateWindow(mode->width+1, mode->height+1, "ImGui Overlay", NULL, NULL);
    if (g_Window == NULL) {
        fprintf(stderr, "严重错误: 创建 GLFW 窗口失败。\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(g_Window);
    // [REWRITE] 启用垂直同步。对于UI应用，这通常是更好的选择，可以防止画面撕裂并降低GPU负载。
    // 如果需要极致的低延迟，可以设为 0。
    glfwSwapInterval(0);

    // --- 4. 初始化 GLAD ---
    // [REWRITE] 初始化 GLAD 来加载 OpenGL 函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "严重错误: 初始化 GLAD 失败。\n");
        glfwTerminate();
        return -1;
    }
    printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));

    // --- 5. 初始化 ImGui ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
     io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // 多视口功能按需开启

     ImGuiStyle& style = ImGui::GetStyle();
     style.WindowRounding = 10.0F;
     // 让背景稍微透明一点，更有覆盖层的“毛玻璃”感觉
     style.Colors[ImGuiCol_WindowBg].w = 0.85f;
     style.Colors[ImGuiCol_PopupBg].w = 0.85f;

     if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
         style.WindowRounding = 0.0f;
         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
     }

    // 初始化 ImGui 后端
    ImGui_ImplGlfw_InitForOpenGL(g_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // --- 6. 加载字体 ---
    const char* font_path = "C:/Windows/Fonts/msyhbd.ttc"; // 微软雅黑 Bold
    float font_size = 18.0f;
    if (io.Fonts->AddFontFromFileTTF(font_path, font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()) == nullptr) {
        fprintf(stderr, "警告: 中文字体加载失败，将使用默认字体。路径: %s\n", font_path);
    }
#ifdef IMGUI_ENABLE_FREETYPE // 使用宏定义来条件编译
    {
        ImFontConfig cfg;
        cfg.MergeMode = true; // 关键：设置为合并模式
        cfg.PixelSnapH = true; // 提高字体清晰度

        // 关键：告诉 FreeType 加载彩色表情符号
        // 注意：在旧版 ImGui 中可能是 FontBuilderFlags
        cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;

        // 指定要加载的字形范围，这里使用默认的，Emoji通常在这个范围内
        static const ImWchar ranges[] = { 0x1, 0x1FFFF, 0 };

        io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/seguiemj.ttf", 17.0f, &cfg, ranges);
        IM_ASSERT(io.Fonts->Fonts.back() != nullptr);
    }
#endif
    // --- 7. 初始化应用程序逻辑 ---
    menu::state::toggle_key_vk = menu::ImGuiKeyToVirtualKey(menu::state::toggle_key);
    InstallGlobalHotkey();

    // [FIX] 实例化鼠标轨迹对象
    menu::MouseTrail mouse_trail;
    
    // [REWRITE] 定义一个完全透明的清屏颜色
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    // --- 8. 主循环 ---
    while (!glfwWindowShouldClose(g_Window)) {
        // [REWRITE] 性能优化: 使用 glfwWaitEvents()。
        // 当没有窗口事件 (如鼠标移动、键盘输入) 时，程序会“睡眠”，CPU占用率会降到接近0%。
        // 这对于一个覆盖层菜单来说是理想的选择。如果菜单内有持续动画，则应换回 glfwPollEvents()。
        glfwPollEvents();
        //glfwWaitEventsTimeout(1.0 / 144.0);
        

        // 开始新的一帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- 绘制 UI ---
        // 设置一个全屏的 Dockspace
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(main_viewport->WorkPos);
        ImGui::SetNextWindowSize(main_viewport->WorkSize);
        ImGui::SetNextWindowViewport(main_viewport->ID);

        ImGuiWindowFlags host_window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground; 
        host_window_flags |= ImGuiWindowFlags_NoMouseInputs;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Dockspace Host", nullptr, host_window_flags);
        ImGui::PopStyleVar();

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::End();
        mouse_trail.Render();
        // 只有当菜单可见时，才绘制它
        if (menu::state::visible) {
            menu::draw();
            //printf("draw\n");
        }
        
        
        // --- 渲染 ---
        ImGui::Render();

        if (!menu::state::visible) {
            // 菜单隐藏时，无条件开启穿透
            glfwSetWindowAttrib(g_Window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
            //printf("on\n");
        }
        //else {
        //    // 菜单可见时，才根据鼠标是否在UI上进行判断
        //    bool is_hovering_gui = ImGui::GetIO().WantCaptureMouse;
        //    glfwSetWindowAttrib(g_Window, GLFW_MOUSE_PASSTHROUGH, is_hovering_gui ? GLFW_FALSE : GLFW_TRUE);
        //}

        int display_w, display_h;
        glfwGetFramebufferSize(g_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 多视口支持
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        glfwSwapBuffers(g_Window);
    }

    // --- 9. 清理资源 ---
    UninstallGlobalHotkey();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(g_Window);
    glfwTerminate();

    return 0;
}*/

// main.cpp (Simplified & Refactored)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <stdint.h>
#include <tchar.h>

// Dear ImGui
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "menu/menu.h"
#include <iostream>

// Link libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "gdi32.lib")
#ifdef _WIN32
extern "C" {
    // 提示 NVIDIA 驱动程序使用独立显卡
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    // 提示 AMD 驱动程序使用独立显卡
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif
#ifdef _WIN32
HHOOK g_keyboardHook = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // 检查是否按下了我们定义的菜单切换键
            if (menu::state::toggle_key_vk != 0 && pkbhs->vkCode == menu::state::toggle_key_vk) {
                menu::state::visible = !menu::state::visible;
                // 返回 1 可以阻止按键消息继续传递，但我们通常不这样做
                //return 1;
            }
        }
    }
    // 必须调用 CallNextHookEx，否则会破坏钩子链
    return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

void InstallGlobalHotkey() {
    g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    if (g_keyboardHook == NULL) {
        std::cerr << "错误: 无法安装全局键盘钩子 (SetWindowsHookEx failed)!" << std::endl;
    }
    else {
        std::cout << "信息: 全局键盘钩子安装成功。按 'Insert' 键显示/隐藏菜单。" << std::endl;
    }
}

void UninstallGlobalHotkey() {
    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
    }
}
#else
// 在非 Windows 平台上提供空的实现，以保证代码可以编译通过
void InstallGlobalHotkey() {
    std::cout << "信息: 当前平台不支持全局热键。" << std::endl;
}
void UninstallGlobalHotkey() {
    if (g_keyboardHook) {
        UnhookWindowsHookEx(g_keyboardHook);
        g_keyboardHook = NULL;
        std::cout << "信息: 全局键盘钩子已卸载。" << std::endl;
    }
}
#endif

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
// --- Globals ---
// D3D11 Resources
static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
static ID3D11Texture2D*         g_renderTexture = nullptr;      // GPU-side render target
static ID3D11RenderTargetView*  g_renderTargetView = nullptr;
static ID3D11Texture2D*         g_stagingTexture = nullptr;     // Staging texture for CPU readback

// GDI Resources (for UpdateLayeredWindow)
static HBITMAP                  g_hBitmap = nullptr;            // GDI bitmap that holds the final image
static void*                    g_pBitmapPixels = nullptr;      // Pointer to the raw pixel data of g_hBitmap
static HDC                      g_hBitmapDC = nullptr;          // GDI Device Context for our bitmap

// Window state
static UINT                     g_width = screenWidth;
static UINT                     g_height = screenHeight;
static HWND                     g_hWnd = nullptr;
static bool                     g_showMenu = true;

const int                       TOGGLE_MENU_VK = VK_INSERT;
// --- Forward Declarations ---
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CreateDeviceD3D();
void CleanupDeviceD3D();
bool CreateRenderResources(UINT w, UINT h);
void CleanupRenderResources();
void RenderAndUpdateLayeredWindow();

// --- Main ---
int main()
{
    // Register window class
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGuiLayered", nullptr };
    RegisterClassExW(&wc);

    // Create a layered, popup window
    g_hWnd = CreateWindowExW(
        WS_EX_LAYERED, wc.lpszClassName, L"ImGui Layered (DX11 -> UpdateLayeredWindow)",
        WS_POPUP | WS_VISIBLE, 100, 100, (int)g_width, (int)g_height, nullptr, nullptr, wc.hInstance, nullptr);
    if (!g_hWnd) return 1;

    // Initialize D3D
    if (!CreateDeviceD3D())
    {
        CleanupDeviceD3D();
        DestroyWindow(g_hWnd);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Create D3D and GDI resources for rendering
    if (!CreateRenderResources(g_width, g_height))
    {
        CleanupDeviceD3D();
        DestroyWindow(g_hWnd);
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    const char* font_path = "C:/Windows/Fonts/msyhbd.ttc"; // 微软雅黑 Bold
    float font_size = 18.0f;
    if (io.Fonts->AddFontFromFileTTF(font_path, font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()) == nullptr) {
        fprintf(stderr, "警告: 中文字体加载失败，将使用默认字体。路径: %s\n", font_path);
    }
#ifdef IMGUI_ENABLE_FREETYPE // 使用宏定义来条件编译
    {
        ImFontConfig cfg;
        cfg.MergeMode = true; // 关键：设置为合并模式
        cfg.PixelSnapH = true; // 提高字体清晰度

        // 关键：告诉 FreeType 加载彩色表情符号
        // 注意：在旧版 ImGui 中可能是 FontBuilderFlags
        cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;

        // 指定要加载的字形范围，这里使用默认的，Emoji通常在这个范围内
        static const ImWchar ranges[] = { 0x1, 0x1FFFF, 0 };

        io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/seguiemj.ttf", 17.0f, &cfg, ranges);
        IM_ASSERT(io.Fonts->Fonts.back() != nullptr);
    }
#endif
    menu::state::toggle_key_vk = menu::ImGuiKeyToVirtualKey(menu::state::toggle_key);
    InstallGlobalHotkey();

    // [FIX] 实例化鼠标轨迹对象
    menu::MouseTrail mouse_trail;
    // Main loop
    bool done = false;
    while (!done)
    {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;
        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // --- Your UI here ---
        //ImGui::ShowDemoWindow();
        if (false) {
            ImGui::Begin("Info");
            ImGui::Checkbox(u8"开关", &menu::state::visible);
            if (ImGui::Button("load hook")) {
                InstallGlobalHotkey();
            }
            if (ImGui::Button("un hook")) {
                UninstallGlobalHotkey();
            }
            ImGui::End();
        }
        mouse_trail.Render();

        if (menu::state::visible) {
            menu::draw();
            //printf("draw\n");
        }

        // Rendering
        ImGui::Render();

        // Render to texture and update the layered window
        RenderAndUpdateLayeredWindow();
    }

    // Cleanup
    
    UninstallGlobalHotkey();
    glfwTerminate();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupRenderResources();
    CleanupDeviceD3D();

    DestroyWindow(g_hWnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    
    return 0;
}

bool CreateDeviceD3D()
{
    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (FAILED(hr))
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    return SUCCEEDED(hr);
}
void CleanupDeviceD3D()
{
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}
bool CreateRenderResources(UINT w, UINT h)
{
    if (!g_pd3dDevice) return false;

    // Release existing resources first
    CleanupRenderResources();

    // --- Create D3D11 Render Target ---
    D3D11_TEXTURE2D_DESC tex_desc = {};
    tex_desc.Width = w;
    tex_desc.Height = h;
    tex_desc.MipLevels = 1;
    tex_desc.ArraySize = 1;
    tex_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // Must be BGRA for GDI compatibility
    tex_desc.SampleDesc.Count = 1;
    tex_desc.Usage = D3D11_USAGE_DEFAULT;
    tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET;

    if (FAILED(g_pd3dDevice->CreateTexture2D(&tex_desc, nullptr, &g_renderTexture))) return false;
    if (FAILED(g_pd3dDevice->CreateRenderTargetView(g_renderTexture, nullptr, &g_renderTargetView))) return false;

    // --- Create D3D11 Staging Texture (for CPU access) ---
    tex_desc.Usage = D3D11_USAGE_STAGING;
    tex_desc.BindFlags = 0;
    tex_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    if (FAILED(g_pd3dDevice->CreateTexture2D(&tex_desc, nullptr, &g_stagingTexture))) return false;
    
    // --- Create GDI Bitmap (the final destination for pixels) ---
    g_hBitmapDC = CreateCompatibleDC(nullptr);
    if (!g_hBitmapDC) return false;

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = (LONG)w;
    bmi.bmiHeader.biHeight = -(LONG)h; // Negative height indicates a top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    g_hBitmap = CreateDIBSection(g_hBitmapDC, &bmi, DIB_RGB_COLORS, &g_pBitmapPixels, nullptr, 0);
    if (!g_hBitmap) return false;

    SelectObject(g_hBitmapDC, g_hBitmap);
    
    g_width = w; g_height = h;
    return true;
}
void CleanupRenderResources()
{
    // GDI resources
    if (g_hBitmap) { DeleteObject(g_hBitmap); g_hBitmap = nullptr; }
    if (g_hBitmapDC) { DeleteDC(g_hBitmapDC); g_hBitmapDC = nullptr; }
    g_pBitmapPixels = nullptr;

    // D3D11 resources
    if (g_stagingTexture) { g_stagingTexture->Release(); g_stagingTexture = nullptr; }
    if (g_renderTargetView) { g_renderTargetView->Release(); g_renderTargetView = nullptr; }
    if (g_renderTexture) { g_renderTexture->Release(); g_renderTexture = nullptr; }
}
void RenderAndUpdateLayeredWindow()
{
    // Ensure all resources are valid
    if (!g_pd3dDeviceContext || !g_renderTargetView || !g_stagingTexture || !g_hBitmapDC || !g_pBitmapPixels) return;

    // 1. Render ImGui UI to our D3D11 texture
    const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // Transparent black
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_renderTargetView, nullptr);
    g_pd3dDeviceContext->ClearRenderTargetView(g_renderTargetView, clear_color);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // 2. Copy the rendered image from the GPU render texture to the CPU-accessible staging texture
    g_pd3dDeviceContext->CopyResource(g_stagingTexture, g_renderTexture);

    // 3. Map the staging texture to access its pixel data on the CPU
    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    if (FAILED(g_pd3dDeviceContext->Map(g_stagingTexture, 0, D3D11_MAP_READ, 0, &mapped_resource))) return;

    // 4. Copy the pixel data from the staging texture to our GDI bitmap
    uint8_t* src_pixels = (uint8_t*)mapped_resource.pData;
    uint8_t* dst_pixels = (uint8_t*)g_pBitmapPixels;
    UINT row_pitch = mapped_resource.RowPitch;
    UINT bitmap_stride = g_width * 4;

    for (UINT y = 0; y < g_height; ++y)
    {
        memcpy(dst_pixels + y * bitmap_stride, src_pixels + y * row_pitch, bitmap_stride);
    }

    g_pd3dDeviceContext->Unmap(g_stagingTexture, 0);

    // 5. Use UpdateLayeredWindow to present the GDI bitmap to the screen
    SIZE size = { (LONG)g_width, (LONG)g_height };
    POINT src_pos = { 0, 0 };
    POINT win_pos = { 0, 0 }; // We are updating the whole window, so this is relative to the window itself
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    UpdateLayeredWindow(g_hWnd, nullptr, &win_pos, &size, g_hBitmapDC, &src_pos, 0, &blend, ULW_ALPHA);
}
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
        {
            // Recreate all size-dependent resources
            CreateRenderResources(LOWORD(lParam), HIWORD(lParam));
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}