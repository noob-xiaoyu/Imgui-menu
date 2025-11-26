// main.cpp (Simplified & Refactored)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <stdint.h>
#include <tchar.h>
#include <iostream>
#include <chrono>
#include <thread> 
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "menu/menu.h"
#include "menu/Theme.h"
#include "main.h"

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
                    return 1;
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
        std::cout << u8"信息: 当前平台不支持全局热键。" << std::endl;
    }
    void UninstallGlobalHotkey() {
        if (g_keyboardHook) {
            UnhookWindowsHookEx(g_keyboardHook);
            g_keyboardHook = NULL;
            std::cout << u8"信息: 全局键盘钩子已卸载。" << std::endl;
        }
    }
#endif

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

// --- Globals ---
// D3D11 Resources
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static ID3D11Texture2D* g_renderTexture = nullptr;      // GPU-side render target
static ID3D11RenderTargetView* g_renderTargetView = nullptr;
static ID3D11Texture2D* g_stagingTexture = nullptr;     // Staging texture for CPU readback

// GDI Resources (for UpdateLayeredWindow)
static HBITMAP                  g_hBitmap = nullptr;            // GDI bitmap that holds the final image
static void* g_pBitmapPixels = nullptr;      // Pointer to the raw pixel data of g_hBitmap
static HDC                      g_hBitmapDC = nullptr;          // GDI Device Context for our bitmap

// Window state
static UINT                     g_width = screenWidth;
static UINT                     g_height = screenHeight;
static HWND                     g_hWnd = nullptr;
static bool                     g_showMenu = true;

const int                       TOGGLE_MENU_VK = VK_INSERT;

ImFont* G_DefaultFont = nullptr;
ImFont* G_HugeFont = nullptr;

// --- Forward Declarations ---
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string FormatTimeHMS(float time_in_seconds)
{
    // 确保时间不是负数
    if (time_in_seconds < 0) time_in_seconds = 0;

    // 向下取整，得到总的整数秒
    int total_seconds_int = static_cast<int>(floor(time_in_seconds));
    int hours = total_seconds_int / 3600;
    int minutes = (total_seconds_int % 3600) / 60;
    int seconds = total_seconds_int % 60;
    int centiseconds = static_cast<int>(fmodf(time_in_seconds, 1.0f) * 100);

    char buffer[32];
    // 使用 snprintf 格式化字符串，%02d 确保数字不足两位时前面补0
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d:%02d", hours, minutes, seconds, centiseconds);

    return std::string(buffer);
}

// --- Main ---
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // Register window class
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0, 0, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGuiLayered", nullptr };
    RegisterClassExW(&wc);

    // Create a layered, popup window
    g_hWnd = CreateWindowExW(WS_EX_LAYERED, wc.lpszClassName, L"Hello World",WS_POPUP | WS_VISIBLE, 100, 100, (int)g_width, (int)g_height, nullptr, nullptr, wc.hInstance, nullptr);
    if (!g_hWnd) return 1;

    //const int refreshRate = GetMonitorRefreshRate(g_hWnd);
    //std::cout << "Detected Monitor Refresh Rate: " << refreshRate << " Hz" << std::endl;
    //const int TARGET_FPS = refreshRate;
    //const auto TARGET_FRAME_DURATION = std::chrono::nanoseconds(1000000000 / TARGET_FPS);

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
    io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;
    SetSakuraPinkTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    const char* font_path = "C:/Windows/Fonts/msyhbd.ttc"; // 微软雅黑 Bold
    float font_size = 18.0f;
    if (io.Fonts->AddFontFromFileTTF(font_path, font_size, NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon()) == nullptr) {
        fprintf(stderr, "警告: 中文字体加载失败，将使用默认字体。路径: %s\n", font_path);
    }
    G_HugeFont = io.Fonts->AddFontFromFileTTF(font_path, font_size * 8.0f);
    if (G_HugeFont == nullptr) {
        printf("Error: Failed to load huge font '%s'\n", font_path);
        G_HugeFont = G_DefaultFont;
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
    menu::state::toggle_key_vk = UI::ImGuiKeyToVirtualKey(menu::state::toggle_key);
    InstallGlobalHotkey();

    // [FIX] 实例化鼠标轨迹对象
    menu::MouseTrail mouse_trail;
    
    // Main loop
    bool done = false;
    while (!done)
    {
        auto frame_start_time = std::chrono::high_resolution_clock::now();
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
        
        if (false) {
            ImGui::Begin("Info");
            ImGui::Checkbox("开关", &menu::state::visible);
            if (ImGui::Button("load hook")) {
                InstallGlobalHotkey();
            }
            if (ImGui::Button("un hook")) {
                UninstallGlobalHotkey();
            }
            ImGui::End();
        }
        mouse_trail.Render();
        if (menu::is_running)
            menu::total_seconds += ImGui::GetIO().DeltaTime;
        if (menu::state::visible) {
            ImGui::SetNextWindowSize(ImVec2(1300, 900), ImGuiCond_Once);
            menu::draw();
        }
        //menu::DrawFullscreenGrid();
            //menu::DrawMouseCrosshair();
            //ImGui::ShowDemoWindow();
            //printf("draw\n");
        
        // Rendering
        ImGui::Render();

        // Render to texture and update the layered window
        RenderAndUpdateLayeredWindow();
        //auto frame_end_time = std::chrono::high_resolution_clock::now();
        //auto frame_duration = frame_end_time - frame_start_time;

        //// 如果当前帧的执行时间小于目标帧时长，就休眠剩下的时间
        //if (frame_duration < TARGET_FRAME_DURATION)
        //{
        //    // Sleep 会让出 CPU，显著降低资源占用
        //    std::this_thread::sleep_for(TARGET_FRAME_DURATION - frame_duration);
        //}
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

int GetMonitorRefreshRate(HWND hwnd)
{
    // 1. 根据窗口句柄获取它所在的显示器句柄 (HMONITOR)
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    if (!hMonitor) {
        return 60; // 如果失败，返回默认值
    }

    // 2. 获取显示器的详细信息，主要是为了得到设备名称
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);
    if (!GetMonitorInfo(hMonitor, &monitorInfo)) {
        return 60; // 如果失败，返回默认值
    }

    // 3. 使用设备名称查询当前的显示设置
    DEVMODE devMode;
    devMode.dmSize = sizeof(DEVMODE);
    devMode.dmDriverExtra = 0;

    // ENUM_CURRENT_SETTINGS 表示获取当前的设置
    if (EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &devMode) != 0)
    {
        // 4. 从 DEVMODE 结构体中返回显示频率
        return static_cast<int>(devMode.dmDisplayFrequency);
    }

    // 如果 EnumDisplaySettings 也失败了，返回默认值
    return 999;
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