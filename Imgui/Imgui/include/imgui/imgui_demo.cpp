// dear imgui, v1.92.3 WIP
// (demo code)

// Help:
// - Read FAQ at http://dearimgui.com/faq
// - Call and read ImGui::ShowDemoWindow() in imgui_demo.cpp. All applications in examples/ are doing that.
// - Need help integrating Dear ImGui in your codebase?
//   - Read Getting Started https://github.com/ocornut/imgui/wiki/Getting-Started
//   - Read 'Programmer guide' in imgui.cpp for notes on how to setup Dear ImGui in your codebase.
// Read top of imgui.cpp and imgui.h for many details, documentation, comments, links.
// Get the latest version at https://github.com/ocornut/imgui

// How to easily locate code?
// - Use Tools->Item Picker to debug break in code by clicking any widgets: https://github.com/ocornut/imgui/wiki/Debug-Tools
// - Browse an online version the demo with code linked to hovered widgets: https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
// - Find a visible string and search for it in the code!

//---------------------------------------------------
// PLEASE DO NOT REMOVE THIS FILE FROM YOUR PROJECT!
//---------------------------------------------------
// Message to the person tempted to delete this file when integrating Dear ImGui into their codebase:
// Think again! It is the most useful reference code that you and other coders will want to refer to and call.
// Have the ImGui::ShowDemoWindow() function wired in an always-available debug menu of your game/app!
// Also include Metrics! ItemPicker! DebugLog! and other debug features.
// Removing this file from your project is hindering access to documentation for everyone in your team,
// likely leading you to poorer usage of the library.
// Everything in this file will be stripped out by the linker if you don't call ImGui::ShowDemoWindow().
// If you want to link core Dear ImGui in your shipped builds but want a thorough guarantee that the demo will not be
// linked, you can setup your imconfig.h with #define IMGUI_DISABLE_DEMO_WINDOWS and those functions will be empty.
// In another situation, whenever you have Dear ImGui available you probably want this to be available for reference.
// Thank you,
// -Your beloved friend, imgui_demo.cpp (which you won't delete)

//--------------------------------------------
// ABOUT THE MEANING OF THE 'static' KEYWORD:
//--------------------------------------------
// In this demo code, we frequently use 'static' variables inside functions.
// A static variable persists across calls. It is essentially a global variable but declared inside the scope of the function.
// Think of "static int n = 0;" as "global int n = 0;" !
// We do this IN THE DEMO because we want:
// - to gather code and data in the same place.
// - to make the demo source code faster to read, faster to change, smaller in size.
// - it is also a convenient way of storing simple UI related information as long as your function
//   doesn't need to be reentrant or used in multiple threads.
// This might be a pattern you will want to use in your code, but most of the data you would be working
// with in a complex codebase is likely going to be stored outside your functions.

//-----------------------------------------
// ABOUT THE CODING STYLE OF OUR DEMO CODE
//-----------------------------------------
// The Demo code in this file is designed to be easy to copy-and-paste into your application!
// Because of this:
// - We never omit the ImGui:: prefix when calling functions, even though most code here is in the same namespace.
// - We try to declare static variables in the local scope, as close as possible to the code using them.
// - We never use any of the helpers/facilities used internally by Dear ImGui, unless available in the public API.
// - We never use maths operators on ImVec2/ImVec4. For our other sources files we use them, and they are provided
//   by imgui.h using the IMGUI_DEFINE_MATH_OPERATORS define. For your own sources file they are optional
//   and require you either enable those, either provide your own via IM_VEC2_CLASS_EXTRA in imconfig.h.
//   Because we can't assume anything about your support of maths operators, we cannot use them in imgui_demo.cpp.

// Navigating this file:
// - In Visual Studio: CTRL+comma ("Edit.GoToAll") can follow symbols inside comments, whereas CTRL+F12 ("Edit.GoToImplementation") cannot.
// - In Visual Studio w/ Visual Assist installed: ALT+G ("VAssistX.GoToImplementation") can also follow symbols inside comments.
// - In VS Code, CLion, etc.: CTRL+click can follow symbols inside comments.
// - You can search/grep for all sections listed in the index to find the section.

/*

Index of this file:

// [SECTION] Forward Declarations
// [SECTION] Helpers
// [SECTION] Demo Window / ShowDemoWindow()
// [SECTION] DemoWindowMenuBar()
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor & Multi-Select demos)
// [SECTION] DemoWindowWidgetsBasic()
// [SECTION] DemoWindowWidgetsBullets()
// [SECTION] DemoWindowWidgetsCollapsingHeaders()
// [SECTION] DemoWindowWidgetsComboBoxes()
// [SECTION] DemoWindowWidgetsColorAndPickers()
// [SECTION] DemoWindowWidgetsDataTypes()
// [SECTION] DemoWindowWidgetsDisableBlocks()
// [SECTION] DemoWindowWidgetsDragAndDrop()
// [SECTION] DemoWindowWidgetsDragsAndSliders()
// [SECTION] DemoWindowWidgetsFonts()
// [SECTION] DemoWindowWidgetsImages()
// [SECTION] DemoWindowWidgetsListBoxes()
// [SECTION] DemoWindowWidgetsMultiComponents()
// [SECTION] DemoWindowWidgetsPlotting()
// [SECTION] DemoWindowWidgetsProgressBars()
// [SECTION] DemoWindowWidgetsQueryingStatuses()
// [SECTION] DemoWindowWidgetsSelectables()
// [SECTION] DemoWindowWidgetsSelectionAndMultiSelect()
// [SECTION] DemoWindowWidgetsTabs()
// [SECTION] DemoWindowWidgetsText()
// [SECTION] DemoWindowWidgetsTextFilter()
// [SECTION] DemoWindowWidgetsTextInput()
// [SECTION] DemoWindowWidgetsTooltips()
// [SECTION] DemoWindowWidgetsTreeNodes()
// [SECTION] DemoWindowWidgetsVerticalSliders()
// [SECTION] DemoWindowWidgets()
// [SECTION] DemoWindowLayout()
// [SECTION] DemoWindowPopups()
// [SECTION] DemoWindowTables()
// [SECTION] DemoWindowInputs()
// [SECTION] About Window / ShowAboutWindow()
// [SECTION] Style Editor / ShowStyleEditor()
// [SECTION] User Guide / ShowUserGuide()
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
// [SECTION] Example App: Long Text / ShowExampleAppLongText()
// [SECTION] Example App: Auto Resize / ShowExampleAppAutoResize()
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
// [SECTION] Example App: Simple overlay / ShowExampleAppSimpleOverlay()
// [SECTION] Example App: Fullscreen window / ShowExampleAppFullscreen()
// [SECTION] Example App: Manipulating window titles / ShowExampleAppWindowTitles()
// [SECTION] Example App: Custom Rendering using ImDrawList API / ShowExampleAppCustomRendering()
// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()
// [SECTION] Example App: Assets Browser / ShowExampleAppAssetsBrowser()

*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#ifndef IMGUI_DISABLE

// System includes
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#include <stdint.h>         // intptr_t
#if !defined(_MSC_VER) || _MSC_VER >= 1800
#include <inttypes.h>       // PRId64/PRIu64, not avail in some MinGW headers.
#endif
#ifdef __EMSCRIPTEN__
#include <emscripten/version.h>     // __EMSCRIPTEN_major__ etc.
#endif

// Visual Studio warnings
#ifdef _MSC_VER
#pragma warning (disable: 4127)     // condition expression is constant
#pragma warning (disable: 4996)     // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#pragma warning (disable: 26451)    // [Static Analyzer] Arithmetic overflow : Using operator 'xxx' on a 4 byte value and then casting the result to an 8 byte value. Cast the value to the wider type before calling operator 'xxx' to avoid overflow(io.2).
#endif

// Clang/GCC warnings with -Weverything
#if defined(__clang__)
#if __has_warning("-Wunknown-warning-option")
#pragma clang diagnostic ignored "-Wunknown-warning-option"         // warning: unknown warning group 'xxx'                     // not all warnings are known by all Clang versions and they tend to be rename-happy.. so ignoring warnings triggers new warnings on some configuration. Great!
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"                // warning: unknown warning group 'xxx'
#pragma clang diagnostic ignored "-Wold-style-cast"                 // warning: use of old-style cast                           // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"        // warning: 'xx' is deprecated: The POSIX name for this..   // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"       // warning: cast to 'void *' from smaller integer type
#pragma clang diagnostic ignored "-Wformat"                         // warning: format specifies type 'int' but the argument has type 'unsigned int'
#pragma clang diagnostic ignored "-Wformat-security"                // warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"          // warning: declaration requires an exit-time destructor    // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#pragma clang diagnostic ignored "-Wunused-macros"                  // warning: macro is not used                               // we define snprintf/vsnprintf on Windows so they are available, but not always used.
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"  // warning: zero as null pointer constant                   // some standard header variations use #define NULL 0
#pragma clang diagnostic ignored "-Wdouble-promotion"               // warning: implicit conversion from 'float' to 'double' when passing argument to function  // using printf() is a misery with this as C++ va_arg ellipsis changes float to double.
#pragma clang diagnostic ignored "-Wreserved-id-macro"              // warning: macro name is a reserved identifier
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"  // warning: implicit conversion from 'xxx' to 'float' may lose precision
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"            // warning: 'xxx' is an unsafe pointer used for buffer access
#pragma clang diagnostic ignored "-Wswitch-default"                 // warning: 'switch' missing 'default' label
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpragmas"                          // warning: unknown option after '#pragma GCC diagnostic' kind
#pragma GCC diagnostic ignored "-Wfloat-equal"                      // warning: comparing floating-point with '==' or '!=' is unsafe
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"              // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat"                           // warning: format '%p' expects argument of type 'int'/'void*', but argument X has type 'unsigned int'/'ImGuiWindow*'
#pragma GCC diagnostic ignored "-Wformat-security"                  // warning: format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"                 // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"                       // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#pragma GCC diagnostic ignored "-Wmisleading-indentation"           // [__GNUC__ >= 6] warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#pragma GCC diagnostic ignored "-Wstrict-overflow"                  // warning: assuming signed overflow does not occur when simplifying division / ..when changing X +- C1 cmp C2 to X cmp C2 -+ C1
#pragma GCC diagnostic ignored "-Wcast-qual"                        // warning: cast from type 'const xxxx *' to type 'xxxx *' casts away qualifiers
#endif

// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

// Helpers
#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif

// Format specifiers for 64-bit values (hasn't been decently standardized before VS2013)
#if !defined(PRId64) && defined(_MSC_VER)
#define PRId64 "I64d"
#define PRIu64 "I64u"
#elif !defined(PRId64)
#define PRId64 "lld"
#define PRIu64 "llu"
#endif

// Helpers macros
// We normally try to not use many helpers in imgui_demo.cpp in order to make code easier to copy and paste,
// but making an exception here as those are largely simplifying code...
// In other imgui sources we can use nicer internal functions from imgui_internal.h (ImMin/ImMax) but not in the demo.
#define IM_MIN(A, B)            (((A) < (B)) ? (A) : (B))
#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))
#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))

// Enforce cdecl calling convention for functions called by the standard library,
// in case compilation settings changed the default to e.g. __vectorcall
#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif

//-----------------------------------------------------------------------------
// [SECTION] Forward Declarations
//-----------------------------------------------------------------------------

#if !defined(IMGUI_DISABLE_DEMO_WINDOWS)

// Forward Declarations
struct ImGuiDemoWindowData;
static void ShowExampleAppMainMenuBar();
static void ShowExampleAppAssetsBrowser(bool* p_open);
static void ShowExampleAppConsole(bool* p_open);
static void ShowExampleAppCustomRendering(bool* p_open);
static void ShowExampleAppDockSpace(bool* p_open);
static void ShowExampleAppDocuments(bool* p_open);
static void ShowExampleAppLog(bool* p_open);
static void ShowExampleAppLayout(bool* p_open);
static void ShowExampleAppPropertyEditor(bool* p_open, ImGuiDemoWindowData* demo_data);
static void ShowExampleAppSimpleOverlay(bool* p_open);
static void ShowExampleAppAutoResize(bool* p_open);
static void ShowExampleAppConstrainedResize(bool* p_open);
static void ShowExampleAppFullscreen(bool* p_open);
static void ShowExampleAppLongText(bool* p_open);
static void ShowExampleAppWindowTitles(bool* p_open);
static void ShowExampleMenuFile();

// We split the contents of the big ShowDemoWindow() function into smaller functions
// (because the link time of very large functions tends to grow non-linearly)
static void DemoWindowMenuBar(ImGuiDemoWindowData* demo_data);
static void DemoWindowWidgets(ImGuiDemoWindowData* demo_data);
static void DemoWindowLayout();
static void DemoWindowPopups();
static void DemoWindowTables();
static void DemoWindowColumns();
static void DemoWindowInputs();

// Helper tree functions used by Property Editor & Multi-Select demos
struct ExampleTreeNode;
static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent);
static void             ExampleTree_DestroyNode(ExampleTreeNode* node);

//-----------------------------------------------------------------------------
// [SECTION] Helpers
//-----------------------------------------------------------------------------

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

static void ShowDockingDisabledMessage()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text(u8"错误：未启用停靠功能!请查看 演示 > 配置.");
    ImGui::Text(u8"请在您的代码中设置 io.ConfigFlags |= ImGuiConfigFlags_DockingEnable，或者 ");
    ImGui::SameLine(0.0f, 0.0f);
    if (ImGui::SmallButton(u8"点击这里"))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

// Helper to wire demo markers located in code to an interactive browser
typedef void (*ImGuiDemoMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiDemoMarkerCallback      GImGuiDemoMarkerCallback;
extern void* GImGuiDemoMarkerCallbackUserData;
ImGuiDemoMarkerCallback             GImGuiDemoMarkerCallback = NULL;
void* GImGuiDemoMarkerCallbackUserData = NULL;
#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)

//-----------------------------------------------------------------------------
// [SECTION] Demo Window / ShowDemoWindow()
//-----------------------------------------------------------------------------

// Data to be shared across different functions of the demo.
struct ImGuiDemoWindowData
{
    // Examples Apps (accessible from the "Examples" menu)
    bool ShowMainMenuBar = false;
    bool ShowAppAssetsBrowser = false;
    bool ShowAppConsole = false;
    bool ShowAppCustomRendering = false;
    bool ShowAppDocuments = false;
    bool ShowAppDockSpace = false;
    bool ShowAppLog = false;
    bool ShowAppLayout = false;
    bool ShowAppPropertyEditor = false;
    bool ShowAppSimpleOverlay = false;
    bool ShowAppAutoResize = false;
    bool ShowAppConstrainedResize = false;
    bool ShowAppFullscreen = false;
    bool ShowAppLongText = false;
    bool ShowAppWindowTitles = false;

    // Dear ImGui Tools (accessible from the "Tools" menu)
    bool ShowMetrics = false;
    bool ShowDebugLog = false;
    bool ShowIDStackTool = false;
    bool ShowStyleEditor = false;
    bool ShowAbout = false;

    // Other data
    bool DisableSections = false;
    ExampleTreeNode* DemoTree = NULL;

    ~ImGuiDemoWindowData() { if (DemoTree) ExampleTree_DestroyNode(DemoTree); }
};

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does.
// You may then search for keywords in the code when you are interested by a specific feature.
void ImGui::ShowDemoWindow(bool* p_open)
{
    // Exceptionally add an extra assert here for people confused about initial Dear ImGui setup
    // Most functions would normally just assert/crash if the context is missing.
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && u8"缺少亲爱的 ImGui 上下文.参考示例应用程序!");

    // Verify ABI compatibility between caller code and compiled version of Dear ImGui. This helps detects some build issues.
    IMGUI_CHECKVERSION();

    // Stored data
    static ImGuiDemoWindowData demo_data;

    // Examples Apps (accessible from the "Examples" menu)
    if (demo_data.ShowMainMenuBar) { ShowExampleAppMainMenuBar(); }
    if (demo_data.ShowAppDockSpace) { ShowExampleAppDockSpace(&demo_data.ShowAppDockSpace); } // Important: Process the Docking app first, as explicit DockSpace() nodes needs to be submitted early (read comments near the DockSpace function)
    if (demo_data.ShowAppDocuments) { ShowExampleAppDocuments(&demo_data.ShowAppDocuments); } // ...process the Document app next, as it may also use a DockSpace()
    if (demo_data.ShowAppAssetsBrowser) { ShowExampleAppAssetsBrowser(&demo_data.ShowAppAssetsBrowser); }
    if (demo_data.ShowAppConsole) { ShowExampleAppConsole(&demo_data.ShowAppConsole); }
    if (demo_data.ShowAppCustomRendering) { ShowExampleAppCustomRendering(&demo_data.ShowAppCustomRendering); }
    if (demo_data.ShowAppLog) { ShowExampleAppLog(&demo_data.ShowAppLog); }
    if (demo_data.ShowAppLayout) { ShowExampleAppLayout(&demo_data.ShowAppLayout); }
    if (demo_data.ShowAppPropertyEditor) { ShowExampleAppPropertyEditor(&demo_data.ShowAppPropertyEditor, &demo_data); }
    if (demo_data.ShowAppSimpleOverlay) { ShowExampleAppSimpleOverlay(&demo_data.ShowAppSimpleOverlay); }
    if (demo_data.ShowAppAutoResize) { ShowExampleAppAutoResize(&demo_data.ShowAppAutoResize); }
    if (demo_data.ShowAppConstrainedResize) { ShowExampleAppConstrainedResize(&demo_data.ShowAppConstrainedResize); }
    if (demo_data.ShowAppFullscreen) { ShowExampleAppFullscreen(&demo_data.ShowAppFullscreen); }
    if (demo_data.ShowAppLongText) { ShowExampleAppLongText(&demo_data.ShowAppLongText); }
    if (demo_data.ShowAppWindowTitles) { ShowExampleAppWindowTitles(&demo_data.ShowAppWindowTitles); }

    // Dear ImGui Tools (accessible from the "Tools" menu)
    if (demo_data.ShowMetrics) { ImGui::ShowMetricsWindow(&demo_data.ShowMetrics); }
    if (demo_data.ShowDebugLog) { ImGui::ShowDebugLogWindow(&demo_data.ShowDebugLog); }
    if (demo_data.ShowIDStackTool) { ImGui::ShowIDStackToolWindow(&demo_data.ShowIDStackTool); }
    if (demo_data.ShowAbout) { ImGui::ShowAboutWindow(&demo_data.ShowAbout); }
    if (demo_data.ShowStyleEditor)
    {
        ImGui::Begin(u8"亲爱的 ImGui 风格编辑器", &demo_data.ShowStyleEditor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    // Demonstrate the various window flags. Typically you would just use the default!
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool no_docking = false;
    static bool unsaved_document = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
    if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    // Main body of the Demo window starts here.
    if (!ImGui::Begin("Dear ImGui Demo", p_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    // Most framed widgets share a common width settings. Remaining width is used for the label.
    // The width of the frame may be changed with PushItemWidth() or SetNextItemWidth().
    // - Positive value for absolute size, negative value for right-alignment.
    // - The default value is about GetWindowWidth() * 0.65f.
    // - See 'Demo->Layout->Widgets Width' for details.
    // Here we change the frame width based on how much width we want to give to the label.
    const float label_width_base = ImGui::GetFontSize() * 12;               // Some amount of width for label, based on font size.
    const float label_width_max = ImGui::GetContentRegionAvail().x * 0.40f; // ...but always leave some room for framed widgets.
    const float label_width = IM_MIN(label_width_base, label_width_max);
    ImGui::PushItemWidth(-label_width);                                     // Right-align: framed items will leave 'label_width' available for the label.
    //ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.40f);       // e.g. Use 40% width for framed widgets, leaving 60% width for labels.
    //ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.40f);      // e.g. Use 40% width for labels, leaving 60% width for framed widgets.
    //ImGui::PushItemWidth(ImGui::GetFontSize() * -12);                     // e.g. Use XXX width for labels, leaving the rest for framed widgets.

    // Menu Bar
    DemoWindowMenuBar(&demo_data);

    ImGui::Text(u8"dear imgui 向你问好!(%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ImGui::Spacing();

    IMGUI_DEMO_MARKER(u8"帮助");
    if (ImGui::CollapsingHeader(u8"帮助"))
    {
        ImGui::SeparatorText(u8"关于本演示：");
        ImGui::BulletText(u8"以下部分展示了库的许多方面.");
        ImGui::BulletText(u8"上方的\"示例\"菜单可查看更多演示内容.");
        ImGui::BulletText(u8"上方的\"工具\"菜单可访问：关于框、样式编辑器、\n"
            "和指标/调试器（通用 Dear ImGui 调试工具）.");

        ImGui::SeparatorText(u8"程序员指南：");
        ImGui::BulletText(u8"参见 imgui_demo.cpp 中的 ShowDemoWindow() 代码.<- 你在这里!");
        ImGui::BulletText(u8"参见 imgui.cpp 中的注释.");
        ImGui::BulletText(u8"参见 examples/ 文件夹中的示例应用程序.");
        ImGui::BulletText(u8"阅读常见问题解答：");
        ImGui::SameLine(0, 0);
        ImGui::TextLinkOpenURL(u8"https://www.dearimgui.com/faq/");
        ImGui::BulletText(u8"设置 'io.ConfigFlags |= NavEnableKeyboard' 启用键盘控制.");
        ImGui::BulletText(u8"设置 'io.ConfigFlags |= NavEnableGamepad' 启用游戏手柄控制.");

        ImGui::SeparatorText(u8"用户指南：");
        ImGui::ShowUserGuide();
    }

    IMGUI_DEMO_MARKER(u8"配置");
    if (ImGui::CollapsingHeader(u8"配置"))
    {
        ImGuiIO& io = ImGui::GetIO();

        if (ImGui::TreeNode(u8"配置##2"))
        {
            ImGui::SeparatorText(u8"常规");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 启用键盘导航", &io.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard);
            ImGui::SameLine(); HelpMarker(u8"启用键盘控制.");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 启用游戏手柄导航", &io.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
            ImGui::SameLine(); HelpMarker(u8"启用游戏手柄控制.需要后端设置 io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\n详情请参阅 imgui.cpp 中的说明.");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 无鼠标", &io.ConfigFlags, ImGuiConfigFlags_NoMouse);
            ImGui::SameLine(); HelpMarker(u8"指示 dear imgui 禁用鼠标输入和交互.");

            // "无鼠标"选项可能导致鼠标被禁用!让我们提供一种替代方法来解决它：
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)
            {
                if (fmodf((float)ImGui::GetTime(), 0.40f) < 0.20f)
                {
                    ImGui::SameLine();
                    ImGui::Text(u8"<<按空格键禁用>>");
                }
                // 防止两者都被选中
                if (ImGui::IsKeyPressed(ImGuiKey_Space) || (io.ConfigFlags & ImGuiConfigFlags_NoKeyboard))
                    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }

            ImGui::CheckboxFlags(u8"io.ConfigFlags: 无鼠标光标变化", &io.ConfigFlags, ImGuiConfigFlags_NoMouseCursorChange);
            ImGui::SameLine(); HelpMarker(u8"指示后端不要更改鼠标光标形状和可见性.");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 无键盘", &io.ConfigFlags, ImGuiConfigFlags_NoKeyboard);
            ImGui::SameLine(); HelpMarker(u8"指示 dear imgui 禁用键盘输入和交互.");

            ImGui::Checkbox(u8"io.ConfigInputTrickleEventQueue", &io.ConfigInputTrickleEventQueue);
            ImGui::SameLine(); HelpMarker(u8"启用输入队列细流：同一帧中提交的某些类型事件（例如按钮按下 + 释放）将分散到多个帧中，改善低帧率下的交互.");
            ImGui::Checkbox(u8"io.MouseDrawCursor", &io.MouseDrawCursor);
            ImGui::SameLine(); HelpMarker(u8"指示 Dear ImGui 自行渲染鼠标光标.请注意，通过应用程序 GPU 渲染路径渲染的鼠标光标会比硬件光标更滞后，但会与其他视觉效果更同步.\n\n某些桌面应用程序可能同时使用两种光标（例如仅在调整大小/拖动时启用软件光标）.");

            ImGui::SeparatorText(u8"键盘/游戏手柄导航");
            ImGui::Checkbox(u8"io.ConfigNavSwapGamepadButtons", &io.ConfigNavSwapGamepadButtons);
            ImGui::Checkbox(u8"io.ConfigNavMoveSetMousePos", &io.ConfigNavMoveSetMousePos);
            ImGui::SameLine(); HelpMarker(u8"方向/制表导航会传送鼠标光标.在难以移动虚拟鼠标的电视/游戏机系统上可能有用");
            ImGui::Checkbox(u8"io.ConfigNavCaptureKeyboard", &io.ConfigNavCaptureKeyboard);
            ImGui::Checkbox(u8"io.ConfigNavEscapeClearFocusItem", &io.ConfigNavEscapeClearFocusItem);
            ImGui::SameLine(); HelpMarker(u8"按 Escape 清除焦点项.");
            ImGui::Checkbox(u8"io.ConfigNavEscapeClearFocusWindow", &io.ConfigNavEscapeClearFocusWindow);
            ImGui::SameLine(); HelpMarker(u8"按 Escape 清除焦点窗口.");
            ImGui::Checkbox(u8"io.ConfigNavCursorVisibleAuto", &io.ConfigNavCursorVisibleAuto);
            ImGui::SameLine(); HelpMarker(u8"使用方向导航键使光标可见.鼠标点击隐藏光标.");
            ImGui::Checkbox(u8"io.ConfigNavCursorVisibleAlways", &io.ConfigNavCursorVisibleAlways);
            ImGui::SameLine(); HelpMarker(u8"导航光标始终可见.");

            ImGui::SeparatorText(u8"停靠");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 启用停靠", &io.ConfigFlags, ImGuiConfigFlags_DockingEnable);
            ImGui::SameLine();
            if (io.ConfigDockingWithShift)
                HelpMarker(u8"从窗口标题栏或其选项卡拖动以停靠/取消停靠.按住 SHIFT 启用停靠.\n\n从窗口菜单按钮（左上角按钮）拖动以取消停靠整个节点（所有窗口）.");
            else
                HelpMarker(u8"从窗口标题栏或其选项卡拖动以停靠/取消停靠.按住 SHIFT 禁用停靠.\n\n从窗口菜单按钮（左上角按钮）拖动以取消停靠整个节点（所有窗口）.");
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGui::Indent();
                ImGui::Checkbox(u8"io.ConfigDockingNoSplit", &io.ConfigDockingNoSplit);
                ImGui::SameLine(); HelpMarker(u8"简化停靠模式：禁用窗口分割，因此停靠仅限于将多个窗口合并到选项卡栏中.");
                ImGui::Checkbox(u8"io.ConfigDockingWithShift", &io.ConfigDockingWithShift);
                ImGui::SameLine(); HelpMarker(u8"仅当按住 Shift 时启用停靠（允许在更宽的空间中放置，减少视觉噪音）");
                ImGui::Checkbox(u8"io.ConfigDockingAlwaysTabBar", &io.ConfigDockingAlwaysTabBar);
                ImGui::SameLine(); HelpMarker(u8"在单个浮动窗口上创建停靠节点和选项卡栏.");
                ImGui::Checkbox(u8"io.ConfigDockingTransparentPayload", &io.ConfigDockingTransparentPayload);
                ImGui::SameLine(); HelpMarker(u8"停靠时使窗口或视口透明，并仅在目标视口上显示停靠框.在无法同步多个视口渲染时有用.最好与 ConfigViewportsNoAutoMerge 一起使用.");
                ImGui::Unindent();
            }

            ImGui::SeparatorText(u8"多视口");
            ImGui::CheckboxFlags(u8"io.ConfigFlags: 启用视口", &io.ConfigFlags, ImGuiConfigFlags_ViewportsEnable);
            ImGui::SameLine(); HelpMarker(u8"[测试版] 启用测试版多视口支持.详情请参阅 ImGuiPlatformIO.");
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                ImGui::Indent();
                ImGui::Checkbox(u8"io.ConfigViewportsNoAutoMerge", &io.ConfigViewportsNoAutoMerge);
                ImGui::SameLine(); HelpMarker(u8"设置使所有浮动 imgui 窗口始终创建自己的视口.否则，当重叠主宿主视口时，它们会合并到主宿主视口中.");
                ImGui::Checkbox(u8"io.ConfigViewportsNoTaskBarIcon", &io.ConfigViewportsNoTaskBarIcon);
                ImGui::SameLine(); HelpMarker(u8"运行时切换此选项通常不受支持（大多数平台后端不会立即刷新任务栏图标状态）.");
                ImGui::Checkbox(u8"io.ConfigViewportsNoDecoration", &io.ConfigViewportsNoDecoration);
                ImGui::SameLine(); HelpMarker(u8"运行时切换此选项通常不受支持（大多数平台后端不会立即刷新装饰）.");
                ImGui::Checkbox(u8"io.ConfigViewportsNoDefaultParent", &io.ConfigViewportsNoDefaultParent);
                ImGui::SameLine(); HelpMarker(u8"运行时切换此选项通常不受支持（大多数平台后端不会立即刷新父级关系）.");
                /*ImGui::Checkbox(u8"io.ConfigViewportPlatformFocusSetsImGuiFocus", &io.ConfigViewportPlatformFocusSetsImGuiFocus);
                ImGui::SameLine(); HelpMarker(u8"当平台窗口获得焦点时（例如使用 Alt+Tab，点击平台标题栏），对 imgui 窗口应用相应的焦点（可能会清除其他平台窗口中 imgui 窗口位置的焦点/活动 ID）.原则上最好启用此选项，但我们提供了选择退出，因为某些 Linux 窗口管理器倾向于急切地聚焦窗口（例如鼠标悬停时，甚至简单的窗口位置/大小更改）.");*/
                ImGui::Unindent();
            }

            //ImGui::SeparatorText(u8"DPI/缩放");
            //ImGui::Checkbox(u8"io.ConfigDpiScaleFonts", &io.ConfigDpiScaleFonts);
            //ImGui::SameLine(); HelpMarker(u8"实验性：监视器 DPI 更改时自动更新 style.FontScaleDpi.这将缩放字体但暂时不会缩放样式大小/填充.");
            //ImGui::Checkbox(u8"io.ConfigDpiScaleViewports", &io.ConfigDpiScaleViewports);
            //ImGui::SameLine(); HelpMarker(u8"实验性：监视器 DPI 更改时缩放 Dear ImGui 和平台窗口.");

            ImGui::SeparatorText(u8"窗口");
            ImGui::Checkbox(u8"io.ConfigWindowsResizeFromEdges", &io.ConfigWindowsResizeFromEdges);
            ImGui::SameLine(); HelpMarker(u8"启用从边缘和左下角调整窗口大小.\n这需要 ImGuiBackendFlags_HasMouseCursors 以获得更好的鼠标光标反馈.");
            ImGui::Checkbox(u8"io.ConfigWindowsMoveFromTitleBarOnly", &io.ConfigWindowsMoveFromTitleBarOnly);
            ImGui::Checkbox(u8"io.ConfigWindowsCopyContentsWithCtrlC", &io.ConfigWindowsCopyContentsWithCtrlC); // [实验性]
            ImGui::SameLine(); HelpMarker(u8"*实验性* CTRL+C 将焦点窗口的内容复制到剪贴板.\n\n实验性原因：\n- (1) 已知存在嵌套 Begin/End 对的问题.\n- (2) 文本输出质量各不相同.\n- (3) 文本输出按提交顺序而非空间顺序.");
            ImGui::Checkbox(u8"io.ConfigScrollbarScrollByPage", &io.ConfigScrollbarScrollByPage);
            ImGui::SameLine(); HelpMarker(u8"启用点击滚动条抓取外部时按页滚动.\n禁用时，始终滚动到点击位置.\n启用时，Shift+点击滚动到点击位置.");

            ImGui::SeparatorText(u8"控件");
            ImGui::Checkbox(u8"io.ConfigInputTextCursorBlink", &io.ConfigInputTextCursorBlink);
            ImGui::SameLine(); HelpMarker(u8"启用闪烁光标（可选，因为某些用户认为这会分散注意力）.");
            ImGui::Checkbox(u8"io.ConfigInputTextEnterKeepActive", &io.ConfigInputTextEnterKeepActive);
            ImGui::SameLine(); HelpMarker(u8"按 Enter 将保持项目活动并选择内容（仅单行）.");
            ImGui::Checkbox(u8"io.ConfigDragClickToInputText", &io.ConfigDragClickToInputText);
            ImGui::SameLine(); HelpMarker(u8"启用通过简单的鼠标点击释放（无需移动）将 DragXXX 控件转换为文本输入.");
            ImGui::Checkbox(u8"io.ConfigMacOSXBehaviors", &io.ConfigMacOSXBehaviors);
            ImGui::SameLine(); HelpMarker(u8"交换 Cmd<>Ctrl 键，启用各种 MacOS 样式行为.");
            ImGui::Text(u8"另请参阅 样式->渲染 以获取渲染选项.");

            // 另请阅读：https://github.com/ocornut/imgui/wiki/Error-Handling
            ImGui::SeparatorText(u8"错误处理");

            ImGui::Checkbox(u8"io.ConfigErrorRecovery", &io.ConfigErrorRecovery);
            ImGui::SameLine(); HelpMarker(
                u8"配置如何处理可恢复错误的选项.\n"
                u8"- 错误恢复不完美也不保证!这是一个便于开发的功能.\n"
                u8"- 你不应该在正常应用程序运行过程中依赖它.\n"
                u8"- 可能的用法：促进从脚本语言触发的错误或特定异常处理程序后的恢复.\n"
                u8"- 始终确保在程序员座位上，在进行直接 imgui API 调用时至少启用了断言或工具提示! "
                u8"否则将严重阻碍你捕获和纠正错误的能力!");
            ImGui::Checkbox(u8"io.ConfigErrorRecoveryEnableAssert", &io.ConfigErrorRecoveryEnableAssert);
            ImGui::Checkbox(u8"io.ConfigErrorRecoveryEnableDebugLog", &io.ConfigErrorRecoveryEnableDebugLog);
            ImGui::Checkbox(u8"io.ConfigErrorRecoveryEnableTooltip", &io.ConfigErrorRecoveryEnableTooltip);
            if (!io.ConfigErrorRecoveryEnableAssert && !io.ConfigErrorRecoveryEnableDebugLog && !io.ConfigErrorRecoveryEnableTooltip)
                io.ConfigErrorRecoveryEnableAssert = io.ConfigErrorRecoveryEnableDebugLog = io.ConfigErrorRecoveryEnableTooltip = true;

            // 另请阅读：https://github.com/ocornut/imgui/wiki/Debug-Tools
            ImGui::SeparatorText(u8"调试");
            ImGui::Checkbox(u8"io.ConfigDebugIsDebuggerPresent", &io.ConfigDebugIsDebuggerPresent);
            ImGui::SameLine(); HelpMarker(u8"启用各种调用 IM_DEBUG_BREAK() 的工具.\n\n需要附加调试器，否则 IM_DEBUG_BREAK() 选项似乎会使应用程序崩溃.");
            ImGui::Checkbox(u8"io.ConfigDebugHighlightIdConflicts", &io.ConfigDebugHighlightIdConflicts);
            ImGui::SameLine(); HelpMarker(u8"当多个项目有冲突的标识符时高亮并显示错误消息.");
            ImGui::BeginDisabled();
            ImGui::Checkbox(u8"io.ConfigDebugBeginReturnValueOnce", &io.ConfigDebugBeginReturnValueOnce);
            ImGui::EndDisabled();
            ImGui::SameLine(); HelpMarker(u8"对 Begin()/BeginChild() 的首次调用将返回 false.\n\n此选项已禁用，因为它需要在应用程序启动时设置才有意义.显示禁用的选项是一种使此功能更易于发现的方式.");
            ImGui::Checkbox(u8"io.ConfigDebugBeginReturnValueLoop", &io.ConfigDebugBeginReturnValueLoop);
            ImGui::SameLine(); HelpMarker(u8"某些对 Begin()/BeginChild() 的调用将返回 false.\n\n将循环遍历窗口深度然后重复.运行时窗口应闪烁.");
            ImGui::Checkbox(u8"io.ConfigDebugIgnoreFocusLoss", &io.ConfigDebugIgnoreFocusLoss);
            ImGui::SameLine(); HelpMarker(u8"停用 io.AddFocusEvent(false) 处理的选项.当焦点丢失导致清除输入数据时，可能有助于与调试器交互.");
            ImGui::Checkbox(u8"io.ConfigDebugIniSettings", &io.ConfigDebugIniSettings);
            ImGui::SameLine(); HelpMarker(u8"使用额外注释保存 .ini 数据的选项（对停靠特别有帮助，但会使保存变慢）.");

            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER(u8"配置/后端标志");
        if (ImGui::TreeNode(u8"后端标志"))
        {
            HelpMarker(
                u8"这些标志由后端（imgui_impl_xxx 文件）设置以指定其功能.\n"
                u8"这里我们将它们公开为只读字段，以避免与您的后端交互中断.");

            // 创建本地副本以避免修改实际的后端标志.
            // 修复：也许我们需要一个 BeginReadonly() 等效项来保持标签明亮?
            ImGui::BeginDisabled();
            ImGui::CheckboxFlags(u8"io.BackendFlags: 有游戏手柄", &io.BackendFlags, ImGuiBackendFlags_HasGamepad);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 有鼠标光标", &io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 可设置鼠标位置", &io.BackendFlags, ImGuiBackendFlags_HasSetMousePos);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 平台有视口", &io.BackendFlags, ImGuiBackendFlags_PlatformHasViewports);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 有鼠标悬停视口", &io.BackendFlags, ImGuiBackendFlags_HasMouseHoveredViewport);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 渲染器有顶点偏移", &io.BackendFlags, ImGuiBackendFlags_RendererHasVtxOffset);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 渲染器有纹理", &io.BackendFlags, ImGuiBackendFlags_RendererHasTextures);
            ImGui::CheckboxFlags(u8"io.BackendFlags: 渲染器有视口", &io.BackendFlags, ImGuiBackendFlags_RendererHasViewports);
            ImGui::EndDisabled();

            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER(u8"配置/样式, 字体");
        if (ImGui::TreeNode(u8"样式, 字体"))
        {
            ImGui::Checkbox(u8"样式编辑器", &demo_data.ShowStyleEditor);
            ImGui::SameLine();
            HelpMarker(u8"相同内容可在“工具->样式编辑器”中访问，或通过调用 ShowStyleEditor() 函数.");
            ImGui::TreePop();
            ImGui::Spacing();
        }

        IMGUI_DEMO_MARKER(u8"配置/捕获, 日志");
        if (ImGui::TreeNode(u8"捕获/日志"))
        {
            HelpMarker(
                u8"日志 API 重定向所有文本输出，因此您可以轻松捕获 "
                u8"窗口或块的内容.树节点可以自动展开.\n"
                u8"尝试在此窗口中打开以下任何内容，然后单击其中一个“记录到”按钮.");
            ImGui::LogButtons();

            HelpMarker(u8"您也可以调用 ImGui::LogText() 直接输出到日志而无需视觉输出.");
            if (ImGui::Button(u8"复制 \"Hello, world!\" 到剪贴板"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::TreePop();
        }
    }

    IMGUI_DEMO_MARKER(u8"窗口选项");
    if (ImGui::CollapsingHeader(u8"窗口选项"))
    {
        if (ImGui::BeginTable("split", 3))
        {
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无标题栏", &no_titlebar);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无滚动条", &no_scrollbar);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无菜单", &no_menu);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"不可移动", &no_move);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"不可调整大小", &no_resize);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"不可折叠", &no_collapse);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无关闭按钮", &no_close);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无导航", &no_nav);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无背景", &no_background);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"不置顶", &no_bring_to_front);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"无停靠", &no_docking);
            ImGui::TableNextColumn(); ImGui::Checkbox(u8"未保存文档", &unsaved_document);
            ImGui::EndTable();
        }
    }

    // All demo contents
    DemoWindowWidgets(&demo_data);
    DemoWindowLayout();
    DemoWindowPopups();
    DemoWindowTables();
    DemoWindowInputs();

    // End of ShowDemoWindow()
    ImGui::PopItemWidth();
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowMenuBar()
//-----------------------------------------------------------------------------

static void DemoWindowMenuBar(ImGuiDemoWindowData* demo_data)
{
    IMGUI_DEMO_MARKER(u8"菜单");
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(u8"菜单"))
        {
            IMGUI_DEMO_MARKER(u8"菜单/文件");
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"示例"))
        {
            IMGUI_DEMO_MARKER(u8"菜单/示例");
            ImGui::MenuItem(u8"主菜单栏", NULL, &demo_data->ShowMainMenuBar);

            ImGui::SeparatorText(u8"小型应用");
            ImGui::MenuItem(u8"资源浏览器", NULL, &demo_data->ShowAppAssetsBrowser);
            ImGui::MenuItem(u8"控制台", NULL, &demo_data->ShowAppConsole);
            ImGui::MenuItem(u8"自定义渲染", NULL, &demo_data->ShowAppCustomRendering);
            ImGui::MenuItem(u8"文档", NULL, &demo_data->ShowAppDocuments);
            ImGui::MenuItem(u8"停靠空间", NULL, &demo_data->ShowAppDockSpace);
            ImGui::MenuItem(u8"日志", NULL, &demo_data->ShowAppLog);
            ImGui::MenuItem(u8"属性编辑器", NULL, &demo_data->ShowAppPropertyEditor);
            ImGui::MenuItem(u8"简单布局", NULL, &demo_data->ShowAppLayout);
            ImGui::MenuItem(u8"简单覆盖层", NULL, &demo_data->ShowAppSimpleOverlay);

            ImGui::SeparatorText(u8"概念");
            ImGui::MenuItem(u8"自动调整窗口大小", NULL, &demo_data->ShowAppAutoResize);
            ImGui::MenuItem(u8"约束调整窗口大小", NULL, &demo_data->ShowAppConstrainedResize);
            ImGui::MenuItem(u8"全屏窗口", NULL, &demo_data->ShowAppFullscreen);
            ImGui::MenuItem(u8"长文本显示", NULL, &demo_data->ShowAppLongText);
            ImGui::MenuItem(u8"操作窗口标题", NULL, &demo_data->ShowAppWindowTitles);

            ImGui::EndMenu();
        }
        //if (ImGui::MenuItem(u8"菜单项")) {} // 你也可以在菜单栏中使用 MenuItem()!
        if (ImGui::BeginMenu(u8"工具"))
        {
            IMGUI_DEMO_MARKER(u8"菜单/工具");
            ImGuiIO& io = ImGui::GetIO();
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
            const bool has_debug_tools = true;
#else
            const bool has_debug_tools = false;
#endif
            ImGui::MenuItem(u8"指标/调试器", NULL, &demo_data->ShowMetrics, has_debug_tools);
            if (ImGui::BeginMenu(u8"调试选项"))
            {
                ImGui::BeginDisabled(!has_debug_tools);
                ImGui::Checkbox(u8"高亮ID冲突", &io.ConfigDebugHighlightIdConflicts);
                ImGui::EndDisabled();
                ImGui::Checkbox(u8"错误恢复时断言", &io.ConfigErrorRecoveryEnableAssert);
                ImGui::TextDisabled(u8"(详情及更多选项请参见 演示->配置)");
                ImGui::EndMenu();
            }
            ImGui::MenuItem(u8"调试日志", NULL, &demo_data->ShowDebugLog, has_debug_tools);
            ImGui::MenuItem(u8"ID堆栈工具", NULL, &demo_data->ShowIDStackTool, has_debug_tools);
            bool is_debugger_present = io.ConfigDebugIsDebuggerPresent;
            if (ImGui::MenuItem(u8"项目选择器", NULL, false, has_debug_tools))// && is_debugger_present))
                ImGui::DebugStartItemPicker();
            if (!is_debugger_present)
                ImGui::SetItemTooltip(u8"需要设置 io.ConfigDebugIsDebuggerPresent=true.\n\n我们否则会禁用一些额外功能，以避免普通用户使应用程序崩溃.");
            ImGui::MenuItem(u8"样式编辑器", NULL, &demo_data->ShowStyleEditor);
            ImGui::MenuItem(u8"关于 Dear ImGui", NULL, &demo_data->ShowAbout);

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor & Multi-Select demos)
//-----------------------------------------------------------------------------

// Simple representation for a tree
// (this is designed to be simple to understand for our demos, not to be fancy or efficient etc.)
struct ExampleTreeNode
{
    // Tree structure
    char                        Name[28] = "";
    int                         UID = 0;
    ExampleTreeNode* Parent = NULL;
    ImVector<ExampleTreeNode*>  Childs;
    unsigned short              IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

    // Leaf Data
    bool                        HasData = false;    // All leaves have data
    bool                        DataMyBool = true;
    int                         DataMyInt = 128;
    ImVec2                      DataMyVec2 = ImVec2(0.0f, 3.141592f);
};

// Simple representation of struct metadata/serialization data.
// (this is a minimal version of what a typical advanced application may provide)
struct ExampleMemberInfo
{
    const char* Name;       // Member name
    ImGuiDataType   DataType;   // Member type
    int             DataCount;  // Member count (1 when scalar)
    int             Offset;     // Offset inside parent structure
};

// Metadata description of ExampleTreeNode struct.
static const ExampleMemberInfo ExampleTreeNodeMemberInfos[]
{
{ u8"我的名称",     ImGuiDataType_String,  1, offsetof(ExampleTreeNode, Name) },
{ u8"我的布尔值",   ImGuiDataType_Bool,    1, offsetof(ExampleTreeNode, DataMyBool) },
{ u8"我的整数",     ImGuiDataType_S32,     1, offsetof(ExampleTreeNode, DataMyInt) },
{ u8"我的向量2",    ImGuiDataType_Float,   2, offsetof(ExampleTreeNode, DataMyVec2) },
};

static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent)
{
    ExampleTreeNode* node = IM_NEW(ExampleTreeNode);
    snprintf(node->Name, IM_ARRAYSIZE(node->Name), "%s", name);
    node->UID = uid;
    node->Parent = parent;
    node->IndexInParent = parent ? (unsigned short)parent->Childs.Size : 0;
    if (parent)
        parent->Childs.push_back(node);
    return node;
}

static void ExampleTree_DestroyNode(ExampleTreeNode* node)
{
    for (ExampleTreeNode* child_node : node->Childs)
        ExampleTree_DestroyNode(child_node);
    IM_DELETE(node);
}

// Create example tree data
// (this allocates _many_ more times than most other code in either Dear ImGui or others demo)
static ExampleTreeNode* ExampleTree_CreateDemoTree()
{
    static const char* root_names[] = { u8"苹果", u8"香蕉", u8"樱桃", u8"猕猴桃", u8"芒果", u8"橙子", u8"梨", u8"菠萝", u8"草莓", u8"西瓜" };
    const size_t NAME_MAX_LEN = sizeof(ExampleTreeNode::Name);
    char name_buf[NAME_MAX_LEN];
    int uid = 0;
    ExampleTreeNode* node_L0 = ExampleTree_CreateNode(u8"<根节点>", ++uid, NULL);
    const int root_items_multiplier = 2;
    for (int idx_L0 = 0; idx_L0 < IM_ARRAYSIZE(root_names) * root_items_multiplier; idx_L0++)
    {
        snprintf(name_buf, IM_ARRAYSIZE(name_buf), u8"%s %d", root_names[idx_L0 / root_items_multiplier], idx_L0 % root_items_multiplier);
        ExampleTreeNode* node_L1 = ExampleTree_CreateNode(name_buf, ++uid, node_L0);
        const int number_of_childs = (int)strlen(node_L1->Name);
        for (int idx_L1 = 0; idx_L1 < number_of_childs; idx_L1++)
        {
            snprintf(name_buf, IM_ARRAYSIZE(name_buf), u8"子节点 %d", idx_L1);
            ExampleTreeNode* node_L2 = ExampleTree_CreateNode(name_buf, ++uid, node_L1);
            node_L2->HasData = true;
            if (idx_L1 == 0)
            {
                snprintf(name_buf, IM_ARRAYSIZE(name_buf), u8"孙节点 %d", 0);
                ExampleTreeNode* node_L3 = ExampleTree_CreateNode(name_buf, ++uid, node_L2);
                node_L3->HasData = true;
            }
        }
    }
    return node_L0;
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsBasic()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsBasic()
{
    IMGUI_DEMO_MARKER(u8"控件/基础");
    if (ImGui::TreeNode(u8"基础"))
    {
        ImGui::SeparatorText(u8"常规");

        IMGUI_DEMO_MARKER(u8"控件/基础/按钮");
        static int clicked = 0;
        if (ImGui::Button(u8"按钮"))
            clicked++;
        if (clicked & 1)
        {
            ImGui::SameLine();
            ImGui::Text(u8"感谢点击我!");
        }

        IMGUI_DEMO_MARKER(u8"控件/基础/复选框");
        static bool check = true;
        ImGui::Checkbox(u8"复选框", &check);

        IMGUI_DEMO_MARKER(u8"控件/基础/单选按钮");
        static int e = 0;
        ImGui::RadioButton(u8"单选 a", &e, 0); ImGui::SameLine();
        ImGui::RadioButton(u8"单选 b", &e, 1); ImGui::SameLine();
        ImGui::RadioButton(u8"单选 c", &e, 2);

        ImGui::AlignTextToFramePadding();
        ImGui::TextLinkOpenURL(u8"超链接", "https://github.com/ocornut/imgui/wiki/Error-Handling");

        // 颜色按钮，演示使用 PushID() 在 ID 堆栈中添加唯一标识符，以及更改样式.
        IMGUI_DEMO_MARKER(u8"控件/基础/按钮（彩色）");
        for (int i = 0; i < 7; i++)
        {
            if (i > 0)
                ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
            ImGui::Button(u8"点击");
            ImGui::PopStyleColor(3);
            ImGui::PopID();
        }

        // 使用 AlignTextToFramePadding() 将文本基线与框架控件的基线对齐
        // （否则 Text+SameLine+Button 序列默认会使文本稍微偏高!）
        // 详情请参见“演示->布局->文本基线对齐”.
        ImGui::AlignTextToFramePadding();
        ImGui::Text(u8"按住重复：");
        ImGui::SameLine();

        // 带重复器的箭头按钮
        IMGUI_DEMO_MARKER(u8"控件/基础/按钮（重复）");
        static int counter = 0;
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
        ImGui::SameLine(0.0f, spacing);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
        ImGui::PopItemFlag();
        ImGui::SameLine();
        ImGui::Text("%d", counter);

        ImGui::Button(u8"工具提示");
        ImGui::SetItemTooltip(u8"我是一个工具提示");

        ImGui::LabelText(u8"标签", u8"值");

        ImGui::SeparatorText(u8"输入");

        {
            // 要将 InputText() 与 std::string 或任何其他自定义字符串类型连接，
            // 请参见本演示的“文本输入 > 调整大小回调”部分，以及 misc/cpp/imgui_stdlib.h 文件.
            IMGUI_DEMO_MARKER(u8"控件/基础/输入文本");
            static char str0[128] = "Hello, world!";
            ImGui::InputText(u8"输入文本", str0, IM_ARRAYSIZE(str0));
            ImGui::SameLine(); HelpMarker(
                u8"用户：\n"
                u8"按住 SHIFT 或使用鼠标选择文本.\n"
                u8"CTRL+左/右 进行单词跳转.\n"
                u8"CTRL+A 或双击选择全部.\n"
                u8"CTRL+X,CTRL+C,CTRL+V 用于剪贴板操作.\n"
                u8"CTRL+Z 撤销，CTRL+Y/CTRL+SHIFT+Z 重做.\n"
                u8"ESC 恢复.\n\n"
                u8"程序员：\n"
                u8"如果您需要将 InputText() 连接到动态字符串类型，可以使用 ImGuiInputTextFlags_CallbackResize 功能.\n"
                u8"参见 misc/cpp/imgui_stdlib.h 中的示例（此示例未在 imgui_demo.cpp 中演示）.");

            static char str1[128] = "";
            ImGui::InputTextWithHint(u8"输入文本（带提示）", u8"在此输入文本", str1, IM_ARRAYSIZE(str1));

            IMGUI_DEMO_MARKER(u8"控件/基础/输入整数, 输入浮点数");
            static int i0 = 123;
            ImGui::InputInt(u8"输入整数", &i0);

            static float f0 = 0.001f;
            ImGui::InputFloat(u8"输入浮点数", &f0, 0.01f, 1.0f, "%.3f");

            static double d0 = 999999.00000001;
            ImGui::InputDouble(u8"输入双精度数", &d0, 0.01f, 1.0f, "%.8f");

            static float f1 = 1.e10f;
            ImGui::InputFloat(u8"输入科学计数法", &f1, 0.0f, 0.0f, "%e");
            ImGui::SameLine(); HelpMarker(
                u8"您可以使用科学计数法输入值，\n"
                u8"例如 \"1e+8\" 变为 \"100000000\".");

            static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            ImGui::InputFloat3(u8"输入浮点向量3", vec4a);
        }

        ImGui::SeparatorText(u8"拖动");

        {
            IMGUI_DEMO_MARKER(u8"控件/基础/拖动整数, 拖动浮点数");
            static int i1 = 50, i2 = 42, i3 = 128;
            ImGui::DragInt(u8"拖动整数", &i1, 1);
            ImGui::SameLine(); HelpMarker(
                u8"点击并拖动以编辑值.\n"
                u8"按住 SHIFT/ALT 进行更快/更慢的编辑.\n"
                u8"双击或 CTRL+点击以输入值.");
            ImGui::DragInt(u8"拖动整数 0..100", &i2, 1, 0, 100, u8"%d%%", ImGuiSliderFlags_AlwaysClamp);
            ImGui::DragInt(u8"拖动整数 环绕 100..200", &i3, 1, 100, 200, "%d", ImGuiSliderFlags_WrapAround);

            static float f1 = 1.00f, f2 = 0.0067f;
            ImGui::DragFloat(u8"拖动浮点数", &f1, 0.005f);
            ImGui::DragFloat(u8"拖动小浮点数", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
            //ImGui::DragFloat(u8"拖动环绕 -1..1", &f3, 0.005f, -1.0f, 1.0f, NULL, ImGuiSliderFlags_WrapAround);
        }

        ImGui::SeparatorText(u8"滑块");

        {
            IMGUI_DEMO_MARKER(u8"控件/基础/滑块整数, 滑块浮点数");
            static int i1 = 0;
            ImGui::SliderInt(u8"滑块整数", &i1, -1, 3);
            ImGui::SameLine(); HelpMarker(u8"CTRL+点击以输入值.");

            static float f1 = 0.123f, f2 = 0.0f;
            ImGui::SliderFloat(u8"滑块浮点数", &f1, 0.0f, 1.0f, u8"比率 = %.3f");
            ImGui::SliderFloat(u8"滑块浮点数（对数）", &f2, -10.0f, 10.0f, "%.4f", ImGuiSliderFlags_Logarithmic);

            IMGUI_DEMO_MARKER(u8"控件/基础/滑块角度");
            static float angle = 0.0f;
            ImGui::SliderAngle(u8"滑块角度", &angle);

            // 使用格式字符串显示名称而不是整数.
            // 这里我们完全从格式字符串中省略了 '%d'，因此它只会显示一个名称.
            // 此技术也可用于 DragInt().
            IMGUI_DEMO_MARKER(u8"控件/基础/滑块（枚举）");
            enum Element { Element_Fire, Element_Earth, Element_Air, Element_Water, Element_COUNT };
            static int elem = Element_Fire;
            const char* elems_names[Element_COUNT] = { u8"火", u8"土", u8"气", u8"水" };
            const char* elem_name = (elem >= 0 && elem < Element_COUNT) ? elems_names[elem] : u8"未知";
            ImGui::SliderInt(u8"滑块枚举", &elem, 0, Element_COUNT - 1, elem_name); // 使用 ImGuiSliderFlags_NoInput 标志禁用此处的 CTRL+Click.
            ImGui::SameLine(); HelpMarker(u8"使用格式字符串参数显示名称而不是底层整数.");
        }

        ImGui::SeparatorText(u8"选择器/拾取器");

        {
            IMGUI_DEMO_MARKER(u8"控件/基础/颜色编辑3, 颜色编辑4");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ImGui::ColorEdit3(u8"颜色 1", col1);
            ImGui::SameLine(); HelpMarker(
                u8"点击颜色方块打开颜色选择器.\n"
                u8"点击并按住使用拖放.\n"
                u8"右键点击颜色方块显示选项.\n"
                u8"CTRL+点击单个组件以输入值.\n");

            ImGui::ColorEdit4(u8"颜色 2", col2);
        }

        {
            // 在此使用简化的一行式 Combo() API
            // 有关如何使用更灵活的 BeginCombo()/EndCombo() API 的示例，请参见“组合框”部分.
            IMGUI_DEMO_MARKER(u8"控件/基础/组合框");
            const char* items[] = { u8"AAAA", u8"BBBB", u8"CCCC", u8"DDDD", u8"EEEE", u8"FFFF", u8"GGGG", u8"HHHH", u8"IIIIIII", u8"JJJJ", u8"KKKKKKK" };
            static int item_current = 0;
            ImGui::Combo(u8"组合框", &item_current, items, IM_ARRAYSIZE(items));
            ImGui::SameLine(); HelpMarker(
                u8"在此使用简化的一行式组合框 API.\n"
                u8"有关如何使用更灵活和通用的 BeginCombo/EndCombo API 的说明，请参见下面的“组合框”部分.");
        }

        {
            // 在此使用简化的一行式 ListBox() API
            // 有关如何使用更灵活的 BeginListBox()/EndListBox() API 的示例，请参见“列表框”部分.
            IMGUI_DEMO_MARKER(u8"控件/基础/列表框");
            const char* items[] = { u8"苹果", u8"香蕉", u8"樱桃", u8"猕猴桃", u8"芒果", u8"橙子", u8"菠萝", u8"草莓", u8"西瓜" };
            static int item_current = 1;
            ImGui::ListBox(u8"列表框", &item_current, items, IM_ARRAYSIZE(items), 4);
            ImGui::SameLine(); HelpMarker(
                u8"在此使用简化的一行式列表框 API.\n"
                u8"有关如何使用更灵活和通用的 BeginListBox/EndListBox API 的说明，请参见下面的“列表框”部分.");
        }
        // Testing ImGuiOnceUponAFrame helper.
        //static ImGuiOnceUponAFrame once;
        //for (int i = 0; i < 5; i++)
        //    if (once)
        //        ImGui::Text("This will be displayed only once.");

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsBullets()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsBullets()
{
    IMGUI_DEMO_MARKER(u8"控件/项目符号");
    if (ImGui::TreeNode(u8"项目符号"))
    {
        ImGui::BulletText(u8"项目符号点 1");
        ImGui::BulletText(u8"项目符号点 2\n多行显示");
        if (ImGui::TreeNode(u8"树节点"))
        {
            ImGui::BulletText(u8"另一个项目符号点");
            ImGui::TreePop();
        }
        ImGui::Bullet(); ImGui::Text(u8"项目符号点 3 (两次调用)");
        ImGui::Bullet(); ImGui::SmallButton(u8"按钮");
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsCollapsingHeaders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsCollapsingHeaders()
{
    IMGUI_DEMO_MARKER(u8"控件/折叠标题");
    if (ImGui::TreeNode(u8"折叠标题"))
    {
        static bool closable_group = true;
        ImGui::Checkbox(u8"显示第二个标题", &closable_group);
        if (ImGui::CollapsingHeader(u8"标题", ImGuiTreeNodeFlags_None))
        {
            ImGui::Text(u8"IsItemHovered: %d", ImGui::IsItemHovered());
            for (int i = 0; i < 5; i++)
                ImGui::Text(u8"一些内容 %d", i);
        }
        if (ImGui::CollapsingHeader(u8"带关闭按钮的标题", &closable_group))
        {
            ImGui::Text(u8"IsItemHovered: %d", ImGui::IsItemHovered());
            for (int i = 0; i < 5; i++)
                ImGui::Text(u8"更多内容 %d", i);
        }
        /*
        if (ImGui::CollapsingHeader(u8"带项目符号的标题", ImGuiTreeNodeFlags_Bullet))
            ImGui::Text(u8"IsItemHovered: %d", ImGui::IsItemHovered());
        */
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsColorAndPickers()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsColorAndPickers()
{
    IMGUI_DEMO_MARKER(u8"控件/颜色");
    if (ImGui::TreeNode(u8"颜色/选择器控件"))
    {
        static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
        static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

        ImGui::SeparatorText(u8"选项");
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_NoAlpha", &base_flags, ImGuiColorEditFlags_NoAlpha);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_AlphaOpaque", &base_flags, ImGuiColorEditFlags_AlphaOpaque);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_AlphaNoBg", &base_flags, ImGuiColorEditFlags_AlphaNoBg);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_AlphaPreviewHalf", &base_flags, ImGuiColorEditFlags_AlphaPreviewHalf);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_NoDragDrop", &base_flags, ImGuiColorEditFlags_NoDragDrop);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_NoOptions", &base_flags, ImGuiColorEditFlags_NoOptions); ImGui::SameLine(); HelpMarker(u8"右键单击单个颜色控件以显示选项.");
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_HDR", &base_flags, ImGuiColorEditFlags_HDR); ImGui::SameLine(); HelpMarker(u8"目前这所做的只是取消拖动控件的 0..1 限制.");

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色编辑");
        ImGui::SeparatorText(u8"内联颜色编辑器");
        ImGui::Text(u8"颜色控件：");
        ImGui::SameLine(); HelpMarker(
            u8"点击颜色方块打开颜色选择器.\n"
            u8"CTRL+点击单个组件以输入值.\n");
        ImGui::ColorEdit3(u8"我的颜色##1", (float*)&color, base_flags);

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色编辑 (HSV, 带 Alpha)");
        ImGui::Text(u8"带 Alpha 的 HSV 颜色控件：");
        ImGui::ColorEdit4(u8"我的颜色##2", (float*)&color, ImGuiColorEditFlags_DisplayHSV | base_flags);

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色编辑 (浮点显示)");
        ImGui::Text(u8"浮点显示颜色控件：");
        ImGui::ColorEdit4(u8"我的颜色##2f", (float*)&color, ImGuiColorEditFlags_Float | base_flags);

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色按钮 (带选择器)");
        ImGui::Text(u8"带选择器的颜色按钮：");
        ImGui::SameLine(); HelpMarker(
            u8"使用 ImGuiColorEditFlags_NoInputs 标志可以隐藏所有滑块/文本输入.\n"
            u8"使用 ImGuiColorEditFlags_NoLabel 标志可以传递非空标签，该标签仅用于工具提示和选择器弹出窗口.");
        ImGui::ColorEdit4(u8"我的颜色##3", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | base_flags);

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色按钮 (带自定义选择器弹出窗口)");
        ImGui::Text(u8"带自定义选择器弹出窗口的颜色按钮：");

        // 生成默认调色板.调色板将持久存在并可编辑.
        static bool saved_palette_init = true;
        static ImVec4 saved_palette[32] = {};
        if (saved_palette_init)
        {
            for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
            {
                ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f,
                    saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                saved_palette[n].w = 1.0f; // Alpha
            }
            saved_palette_init = false;
        }

        static ImVec4 backup_color;
        bool open_popup = ImGui::ColorButton(u8"我的颜色##3b", color, base_flags);
        ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
        open_popup |= ImGui::Button(u8"调色板");
        if (open_popup)
        {
            ImGui::OpenPopup(u8"我的选择器");
            backup_color = color;
        }
        if (ImGui::BeginPopup(u8"我的选择器"))
        {
            ImGui::Text(u8"我的自定义颜色选择器，带有惊人的调色板!");
            ImGui::Separator();
            ImGui::ColorPicker4(u8"##选择器", (float*)&color, base_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            ImGui::SameLine();

            ImGui::BeginGroup(); // 锁定 X 位置
            ImGui::Text(u8"当前");
            ImGui::ColorButton(u8"##当前", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
            ImGui::Text(u8"上一个");
            if (ImGui::ColorButton(u8"##上一个", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
                color = backup_color;
            ImGui::Separator();
            ImGui::Text(u8"调色板");
            for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
            {
                ImGui::PushID(n);
                if ((n % 8) != 0)
                    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

                ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
                if (ImGui::ColorButton(u8"##调色板", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
                    color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // 保留 alpha!

                // 允许用户将颜色拖放到每个调色板条目中.请注意，ColorButton() 默认已经是拖放源，除非指定 ImGuiColorEditFlags_NoDragDrop 标志.
                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                        memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                    ImGui::EndDragDropTarget();
                }

                ImGui::PopID();
            }
            ImGui::EndGroup();
            ImGui::EndPopup();
        }

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色按钮 (简单)");
        ImGui::Text(u8"仅颜色按钮：");
        static bool no_border = false;
        ImGui::Checkbox(u8"ImGuiColorEditFlags_NoBorder", &no_border);
        ImGui::ColorButton(u8"我的颜色##3c", *(ImVec4*)&color, base_flags | (no_border ? ImGuiColorEditFlags_NoBorder : 0), ImVec2(80, 80));

        IMGUI_DEMO_MARKER(u8"控件/颜色/颜色选择器");
        ImGui::SeparatorText(u8"颜色选择器");

        static bool ref_color = false;
        static ImVec4 ref_color_v(1.0f, 0.0f, 1.0f, 0.5f);
        static int picker_mode = 0;
        static int display_mode = 0;
        static ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_AlphaBar;

        ImGui::PushID(u8"颜色选择器");
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_NoAlpha", &color_picker_flags, ImGuiColorEditFlags_NoAlpha);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_AlphaBar", &color_picker_flags, ImGuiColorEditFlags_AlphaBar);
        ImGui::CheckboxFlags(u8"ImGuiColorEditFlags_NoSidePreview", &color_picker_flags, ImGuiColorEditFlags_NoSidePreview);
        if (color_picker_flags & ImGuiColorEditFlags_NoSidePreview)
        {
            ImGui::SameLine();
            ImGui::Checkbox(u8"使用参考颜色", &ref_color);
            if (ref_color)
            {
                ImGui::SameLine();
                ImGui::ColorEdit4(u8"##参考颜色", &ref_color_v.x, ImGuiColorEditFlags_NoInputs | base_flags);
            }
        }

        ImGui::Combo(u8"选择器模式", &picker_mode, u8"自动/当前\0ImGuiColorEditFlags_PickerHueBar\0ImGuiColorEditFlags_PickerHueWheel\0");
        ImGui::SameLine(); HelpMarker(u8"未明确指定时，用户可以右键单击选择器以更改模式.");

        ImGui::Combo(u8"显示模式", &display_mode, u8"自动/当前\0ImGuiColorEditFlags_NoInputs\0ImGuiColorEditFlags_DisplayRGB\0ImGuiColorEditFlags_DisplayHSV\0ImGuiColorEditFlags_DisplayHex\0");
        ImGui::SameLine(); HelpMarker(
            u8"如果您未指定显示模式，ColorEdit 默认显示 RGB 输入，"
            u8"但用户可以通过右键单击这些输入来更改它.\n\n如果您未指定显示模式，ColorPicker 默认显示 RGB+HSV+Hex."
            u8"\n\n您可以使用 SetColorEditOptions() 更改默认值.");

        ImGuiColorEditFlags flags = base_flags | color_picker_flags;
        if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
        if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
        if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // 禁用所有 RGB/HSV/Hex 显示
        if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // 覆盖显示模式
        if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
        if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
        ImGui::ColorPicker4(u8"我的颜色##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

        ImGui::Text(u8"在代码中设置默认值：");
        ImGui::SameLine(); HelpMarker(
            u8"SetColorEditOptions() 旨在允许您设置启动时默认值.\n"
            u8"我们没有 Push/Pop 函数，因为您可以在需要时强制每个控件的选项，"
            u8"并且用户可以通过选项菜单更改非强制选项.\n我们没有 getter 以避免"
            u8"鼓励您持久保存不向前兼容的值.");
        if (ImGui::Button(u8"默认：Uint8 + HSV + 色相条"))
            ImGui::SetColorEditOptions(ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_PickerHueBar);
        if (ImGui::Button(u8"默认：Float + HDR + 色相轮"))
            ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

        // 始终显示两种选择器的小版本
        // （这是为了让快速浏览演示的人更容易看到）
        ImGui::Text(u8"两种类型：");
        float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.40f;
        ImGui::SetNextItemWidth(w);
        ImGui::ColorPicker3(u8"##我的颜色##5", (float*)&color, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(w);
        ImGui::ColorPicker3(u8"##我的颜色##6", (float*)&color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
        ImGui::PopID();

        // HSV 编码支持（避免 RGB<>HSV 往返以及在 S==0 或 V==0 时的奇点）
        static ImVec4 color_hsv(0.23f, 1.0f, 1.0f, 1.0f); // 存储为 HSV!
        ImGui::Spacing();
        ImGui::Text(u8"HSV 编码颜色");
        ImGui::SameLine(); HelpMarker(
            u8"默认情况下，颜色以 RGB 形式提供给 ColorEdit 和 ColorPicker，但 ImGuiColorEditFlags_InputHSV "
            u8"允许您将颜色存储为 HSV 并将其作为 HSV 传递给 ColorEdit 和 ColorPicker.这带来的额外好处是，即使饱和度或值为零，您也可以使用选择器操作色相值.");
        ImGui::Text(u8"带 InputHSV 的颜色控件：");
        ImGui::ColorEdit4(u8"HSV 显示为 RGB##1", (float*)&color_hsv, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        ImGui::ColorEdit4(u8"HSV 显示为 HSV##1", (float*)&color_hsv, ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        ImGui::DragFloat4(u8"原始 HSV 值", (float*)&color_hsv, 0.01f, 0.0f, 1.0f);

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsComboBoxes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsComboBoxes()
{
    IMGUI_DEMO_MARKER(u8"控件/组合框");
    if (ImGui::TreeNode(u8"组合框"))
    {
        // 组合框在其他系统中也称为"下拉框"
        // 将标志公开为演示的复选框
        static ImGuiComboFlags flags = 0;
        ImGui::CheckboxFlags(u8"ImGuiComboFlags_PopupAlignLeft", &flags, ImGuiComboFlags_PopupAlignLeft);
        ImGui::SameLine(); HelpMarker(u8"仅当弹出窗口大于组合框时才有所不同");
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_NoArrowButton", &flags, ImGuiComboFlags_NoArrowButton))
            flags &= ~ImGuiComboFlags_NoPreview;     // 清除不兼容的标志
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_NoPreview", &flags, ImGuiComboFlags_NoPreview))
            flags &= ~(ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview); // 清除不兼容的标志
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_WidthFitPreview", &flags, ImGuiComboFlags_WidthFitPreview))
            flags &= ~ImGuiComboFlags_NoPreview;

        // 覆盖默认弹出窗口高度
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_HeightSmall", &flags, ImGuiComboFlags_HeightSmall))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightSmall);
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_HeightRegular", &flags, ImGuiComboFlags_HeightRegular))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightRegular);
        if (ImGui::CheckboxFlags(u8"ImGuiComboFlags_HeightLargest", &flags, ImGuiComboFlags_HeightLargest))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightLargest);

        // 使用通用的 BeginCombo() API，您可以完全控制如何显示组合框内容.
        // （您的选择数据可以是索引、对象的指针、对象的 ID、对象本身中侵入式存储的标志等）
        const char* items[] = { u8"AAAA", u8"BBBB", u8"CCCC", u8"DDDD", u8"EEEE", u8"FFFF", u8"GGGG", u8"HHHH", u8"IIII", u8"JJJJ", u8"KKKK", u8"LLLLLLL", u8"MMMM", u8"OOOOOOO" };
        static int item_selected_idx = 0; // 这里我们将选择数据存储为索引.

        // 传入打开组合框前可见的预览值（它在技术上可以是不同的内容，或者不是从 items[] 中提取的）
        const char* combo_preview_value = items[item_selected_idx];
        if (ImGui::BeginCombo(u8"组合框 1", combo_preview_value, flags))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                    item_selected_idx = n;

                // 打开组合框时设置初始焦点（滚动 + 键盘导航焦点）
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        // 展示使用简单技巧嵌入过滤器：在组合框内容中显示过滤器.
        // 有关高级/深奥的替代方案，请参见 https://github.com/ocornut/imgui/issues/718.
        if (ImGui::BeginCombo(u8"组合框 2 (带过滤器)", combo_preview_value, flags))
        {
            static ImGuiTextFilter filter;
            if (ImGui::IsWindowAppearing())
            {
                ImGui::SetKeyboardFocusHere();
                filter.Clear();
            }
            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
            filter.Draw(u8"##过滤器", -FLT_MIN);

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (filter.PassFilter(items[n]))
                    if (ImGui::Selectable(items[n], is_selected))
                        item_selected_idx = n;
            }
            ImGui::EndCombo();
        }

        ImGui::Spacing();
        ImGui::SeparatorText(u8"单行变体");
        HelpMarker(u8"Combo() 函数除了您希望将所有选项嵌入单个字符串的情况外，不是很有用.\n上面的标志不适用于此部分.");

        // 简化的一行式 Combo() API，使用打包在单个常量字符串中的值
        // 当选择集很小且在编译时已知时，这很方便.
        static int item_current_2 = 0;
        ImGui::Combo(u8"组合框 3 (单行)", &item_current_2, u8"aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");

        // 简化的一行式 Combo() 使用 const char* 数组
        // 这不是很有用（可能过时）：更喜欢使用 BeginCombo()/EndCombo() 进行完全控制.
        static int item_current_3 = -1; // 如果选择不在 0..count 范围内，Combo 将不会显示预览
        ImGui::Combo(u8"组合框 4 (数组)", &item_current_3, items, IM_ARRAYSIZE(items));

        // 简化的一行式 Combo() 使用访问器函数
        static int item_current_4 = 0;
        ImGui::Combo(u8"组合框 5 (函数)", &item_current_4, [](void* data, int n) { return ((const char**)data)[n]; }, items, IM_ARRAYSIZE(items));

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDataTypes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDataTypes()
{
    IMGUI_DEMO_MARKER(u8"控件/数据类型");
    if (ImGui::TreeNode(u8"数据类型"))
    {
        // DragScalar/InputScalar/SliderScalar functions allow various data types
        // - signed/unsigned
        // - 8/16/32/64-bits
        // - integer/float/double
        // To avoid polluting the public API with all possible combinations, we use the ImGuiDataType enum
        // to pass the type, and passing all arguments by pointer.
        // This is the reason the test code below creates local variables to hold "zero" "one" etc. for each type.
        // In practice, if you frequently use a given type that is not covered by the normal API entry points,
        // you can wrap it yourself inside a 1 line function which can take typed argument as value instead of void*,
        // and then pass their address to the generic function. For example:
        //   bool MySliderU64(const char *label, u64* value, u64 min = 0, u64 max = 0, const char* format = "%lld")
        //   {
        //      return SliderScalar(label, ImGuiDataType_U64, value, &min, &max, format);
        //   }

        // Setup limits (as helper variables so we can take their address, as explained above)
        // Note: SliderScalar() functions have a maximum usable range of half the natural type maximum, hence the /2.
#ifndef LLONG_MIN
        ImS64 LLONG_MIN = -9223372036854775807LL - 1;
        ImS64 LLONG_MAX = 9223372036854775807LL;
        ImU64 ULLONG_MAX = (2ULL * 9223372036854775807LL + 1);
#endif
        const char    s8_zero = 0, s8_one = 1, s8_fifty = 50, s8_min = -128, s8_max = 127;
        const ImU8    u8_zero = 0, u8_one = 1, u8_fifty = 50, u8_min = 0, u8_max = 255;
        const short   s16_zero = 0, s16_one = 1, s16_fifty = 50, s16_min = -32768, s16_max = 32767;
        const ImU16   u16_zero = 0, u16_one = 1, u16_fifty = 50, u16_min = 0, u16_max = 65535;
        const ImS32   s32_zero = 0, s32_one = 1, s32_fifty = 50, s32_min = INT_MIN / 2, s32_max = INT_MAX / 2, s32_hi_a = INT_MAX / 2 - 100, s32_hi_b = INT_MAX / 2;
        const ImU32   u32_zero = 0, u32_one = 1, u32_fifty = 50, u32_min = 0, u32_max = UINT_MAX / 2, u32_hi_a = UINT_MAX / 2 - 100, u32_hi_b = UINT_MAX / 2;
        const ImS64   s64_zero = 0, s64_one = 1, s64_fifty = 50, s64_min = LLONG_MIN / 2, s64_max = LLONG_MAX / 2, s64_hi_a = LLONG_MAX / 2 - 100, s64_hi_b = LLONG_MAX / 2;
        const ImU64   u64_zero = 0, u64_one = 1, u64_fifty = 50, u64_min = 0, u64_max = ULLONG_MAX / 2, u64_hi_a = ULLONG_MAX / 2 - 100, u64_hi_b = ULLONG_MAX / 2;
        const float   f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
        const double  f64_zero = 0., f64_one = 1., f64_lo_a = -1000000000000000.0, f64_hi_a = +1000000000000000.0;

        // State
        static char   s8_v = 127;
        static ImU8   u8_v = 255;
        static short  s16_v = 32767;
        static ImU16  u16_v = 65535;
        static ImS32  s32_v = -1;
        static ImU32  u32_v = (ImU32)-1;
        static ImS64  s64_v = -1;
        static ImU64  u64_v = (ImU64)-1;
        static float  f32_v = 0.123f;
        static double f64_v = 90000.01234567890123456789;

        const float drag_speed = 0.2f;
        static bool drag_clamp = false;
        IMGUI_DEMO_MARKER(u8"控件/数据类型/拖动");
        ImGui::SeparatorText(u8"拖动");
        ImGui::Checkbox(u8"将整数限制在 0..50", &drag_clamp);
        ImGui::SameLine(); HelpMarker(
            u8"与 dear imgui 中的每个控件一样，除非有用户交互，否则我们从不修改值.\n"
            u8"您可以使用 CTRL+点击输入值来覆盖限制限制.");
        ImGui::DragScalar(u8"拖动 s8", ImGuiDataType_S8, &s8_v, drag_speed, drag_clamp ? &s8_zero : NULL, drag_clamp ? &s8_fifty : NULL);
        ImGui::DragScalar(u8"拖动 u8", ImGuiDataType_U8, &u8_v, drag_speed, drag_clamp ? &u8_zero : NULL, drag_clamp ? &u8_fifty : NULL, "%u ms");
        ImGui::DragScalar(u8"拖动 s16", ImGuiDataType_S16, &s16_v, drag_speed, drag_clamp ? &s16_zero : NULL, drag_clamp ? &s16_fifty : NULL);
        ImGui::DragScalar(u8"拖动 u16", ImGuiDataType_U16, &u16_v, drag_speed, drag_clamp ? &u16_zero : NULL, drag_clamp ? &u16_fifty : NULL, "%u ms");
        ImGui::DragScalar(u8"拖动 s32", ImGuiDataType_S32, &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL);
        ImGui::DragScalar(u8"拖动 s32 十六进制", ImGuiDataType_S32, &s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL, "0x%08X");
        ImGui::DragScalar(u8"拖动 u32", ImGuiDataType_U32, &u32_v, drag_speed, drag_clamp ? &u32_zero : NULL, drag_clamp ? &u32_fifty : NULL, "%u ms");
        ImGui::DragScalar(u8"拖动 s64", ImGuiDataType_S64, &s64_v, drag_speed, drag_clamp ? &s64_zero : NULL, drag_clamp ? &s64_fifty : NULL);
        ImGui::DragScalar(u8"拖动 u64", ImGuiDataType_U64, &u64_v, drag_speed, drag_clamp ? &u64_zero : NULL, drag_clamp ? &u64_fifty : NULL);
        ImGui::DragScalar(u8"拖动 float", ImGuiDataType_Float, &f32_v, 0.005f, &f32_zero, &f32_one, "%f");
        ImGui::DragScalar(u8"拖动 float 对数", ImGuiDataType_Float, &f32_v, 0.005f, &f32_zero, &f32_one, "%f", ImGuiSliderFlags_Logarithmic);
        ImGui::DragScalar(u8"拖动 double", ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, NULL, "%.10f grams");
        ImGui::DragScalar(u8"拖动 double 对数", ImGuiDataType_Double, &f64_v, 0.0005f, &f64_zero, &f64_one, "0 < %.10f < 1", ImGuiSliderFlags_Logarithmic);

        IMGUI_DEMO_MARKER(u8"控件/数据类型/滑块");
        ImGui::SeparatorText(u8"滑块");
        ImGui::SliderScalar(u8"滑块 s8 全范围", ImGuiDataType_S8, &s8_v, &s8_min, &s8_max, "%d");
        ImGui::SliderScalar(u8"滑块 u8 全范围", ImGuiDataType_U8, &u8_v, &u8_min, &u8_max, "%u");
        ImGui::SliderScalar(u8"滑块 s16 全范围", ImGuiDataType_S16, &s16_v, &s16_min, &s16_max, "%d");
        ImGui::SliderScalar(u8"滑块 u16 全范围", ImGuiDataType_U16, &u16_v, &u16_min, &u16_max, "%u");
        ImGui::SliderScalar(u8"滑块 s32 低范围", ImGuiDataType_S32, &s32_v, &s32_zero, &s32_fifty, "%d");
        ImGui::SliderScalar(u8"滑块 s32 高范围", ImGuiDataType_S32, &s32_v, &s32_hi_a, &s32_hi_b, "%d");
        ImGui::SliderScalar(u8"滑块 s32 全范围", ImGuiDataType_S32, &s32_v, &s32_min, &s32_max, "%d");
        ImGui::SliderScalar(u8"滑块 s32 十六进制", ImGuiDataType_S32, &s32_v, &s32_zero, &s32_fifty, "0x%04X");
        ImGui::SliderScalar(u8"滑块 u32 低范围", ImGuiDataType_U32, &u32_v, &u32_zero, &u32_fifty, "%u");
        ImGui::SliderScalar(u8"滑块 u32 高范围", ImGuiDataType_U32, &u32_v, &u32_hi_a, &u32_hi_b, "%u");
        ImGui::SliderScalar(u8"滑块 u32 全范围", ImGuiDataType_U32, &u32_v, &u32_min, &u32_max, "%u");
        ImGui::SliderScalar(u8"滑块 s64 低范围", ImGuiDataType_S64, &s64_v, &s64_zero, &s64_fifty, "%" PRId64);
        ImGui::SliderScalar(u8"滑块 s64 高范围", ImGuiDataType_S64, &s64_v, &s64_hi_a, &s64_hi_b, "%" PRId64);
        ImGui::SliderScalar(u8"滑块 s64 全范围", ImGuiDataType_S64, &s64_v, &s64_min, &s64_max, "%" PRId64);
        ImGui::SliderScalar(u8"滑块 u64 低范围", ImGuiDataType_U64, &u64_v, &u64_zero, &u64_fifty, "%" PRIu64 " ms");
        ImGui::SliderScalar(u8"滑块 u64 高范围", ImGuiDataType_U64, &u64_v, &u64_hi_a, &u64_hi_b, "%" PRIu64 " ms");
        ImGui::SliderScalar(u8"滑块 u64 全范围", ImGuiDataType_U64, &u64_v, &u64_min, &u64_max, "%" PRIu64 " ms");
        ImGui::SliderScalar(u8"滑块 float 低范围", ImGuiDataType_Float, &f32_v, &f32_zero, &f32_one);
        ImGui::SliderScalar(u8"滑块 float 低范围 对数", ImGuiDataType_Float, &f32_v, &f32_zero, &f32_one, "%.10f", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderScalar(u8"滑块 float 高范围", ImGuiDataType_Float, &f32_v, &f32_lo_a, &f32_hi_a, "%e");
        ImGui::SliderScalar(u8"滑块 double 低范围", ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one, "%.10f grams");
        ImGui::SliderScalar(u8"滑块 double 低范围 对数", ImGuiDataType_Double, &f64_v, &f64_zero, &f64_one, "%.10f", ImGuiSliderFlags_Logarithmic);
        ImGui::SliderScalar(u8"滑块 double 高范围", ImGuiDataType_Double, &f64_v, &f64_lo_a, &f64_hi_a, "%e grams");

        ImGui::SeparatorText(u8"滑块 (反向)");
        ImGui::SliderScalar(u8"滑块 s8 反向", ImGuiDataType_S8, &s8_v, &s8_max, &s8_min, "%d");
        ImGui::SliderScalar(u8"滑块 u8 反向", ImGuiDataType_U8, &u8_v, &u8_max, &u8_min, "%u");
        ImGui::SliderScalar(u8"滑块 s32 反向", ImGuiDataType_S32, &s32_v, &s32_fifty, &s32_zero, "%d");
        ImGui::SliderScalar(u8"滑块 u32 反向", ImGuiDataType_U32, &u32_v, &u32_fifty, &u32_zero, "%u");
        ImGui::SliderScalar(u8"滑块 s64 反向", ImGuiDataType_S64, &s64_v, &s64_fifty, &s64_zero, "%" PRId64);
        ImGui::SliderScalar(u8"滑块 u64 反向", ImGuiDataType_U64, &u64_v, &u64_fifty, &u64_zero, "%" PRIu64 " ms");

        IMGUI_DEMO_MARKER(u8"控件/数据类型/输入");
        static bool inputs_step = true;
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
        ImGui::SeparatorText(u8"输入");
        ImGui::Checkbox(u8"显示步进按钮", &inputs_step);
        ImGui::CheckboxFlags(u8"ImGuiInputTextFlags_ReadOnly", &flags, ImGuiInputTextFlags_ReadOnly);
        ImGui::CheckboxFlags(u8"ImGuiInputTextFlags_ParseEmptyRefVal", &flags, ImGuiInputTextFlags_ParseEmptyRefVal);
        ImGui::CheckboxFlags(u8"ImGuiInputTextFlags_DisplayEmptyRefVal", &flags, ImGuiInputTextFlags_DisplayEmptyRefVal);
        ImGui::InputScalar(u8"输入 s8", ImGuiDataType_S8, &s8_v, inputs_step ? &s8_one : NULL, NULL, "%d", flags);
        ImGui::InputScalar(u8"输入 u8", ImGuiDataType_U8, &u8_v, inputs_step ? &u8_one : NULL, NULL, "%u", flags);
        ImGui::InputScalar(u8"输入 s16", ImGuiDataType_S16, &s16_v, inputs_step ? &s16_one : NULL, NULL, "%d", flags);
        ImGui::InputScalar(u8"输入 u16", ImGuiDataType_U16, &u16_v, inputs_step ? &u16_one : NULL, NULL, "%u", flags);
        ImGui::InputScalar(u8"输入 s32", ImGuiDataType_S32, &s32_v, inputs_step ? &s32_one : NULL, NULL, "%d", flags);
        ImGui::InputScalar(u8"输入 s32 十六进制", ImGuiDataType_S32, &s32_v, inputs_step ? &s32_one : NULL, NULL, "%04X", flags);
        ImGui::InputScalar(u8"输入 u32", ImGuiDataType_U32, &u32_v, inputs_step ? &u32_one : NULL, NULL, "%u", flags);
        ImGui::InputScalar(u8"输入 u32 十六进制", ImGuiDataType_U32, &u32_v, inputs_step ? &u32_one : NULL, NULL, "%08X", flags);
        ImGui::InputScalar(u8"输入 s64", ImGuiDataType_S64, &s64_v, inputs_step ? &s64_one : NULL, NULL, NULL, flags);
        ImGui::InputScalar(u8"输入 u64", ImGuiDataType_U64, &u64_v, inputs_step ? &u64_one : NULL, NULL, NULL, flags);
        ImGui::InputScalar(u8"输入 float", ImGuiDataType_Float, &f32_v, inputs_step ? &f32_one : NULL, NULL, NULL, flags);
        ImGui::InputScalar(u8"输入 double", ImGuiDataType_Double, &f64_v, inputs_step ? &f64_one : NULL, NULL, NULL, flags);

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDisableBlocks()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDisableBlocks(ImGuiDemoWindowData* demo_data)
{
    IMGUI_DEMO_MARKER(u8"控件/禁用块");
    if (ImGui::TreeNode(u8"禁用块"))
    {
        ImGui::Checkbox(u8"禁用上方整个部分", &demo_data->DisableSections);
        ImGui::SameLine(); HelpMarker(u8"演示在其他部分使用 BeginDisabled()/EndDisabled().");
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragAndDrop()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragAndDrop()
{
    IMGUI_DEMO_MARKER(u8"控件/拖放");
    if (ImGui::TreeNode(u8"拖放"))
    {
        IMGUI_DEMO_MARKER(u8"控件/拖放/标准控件");
        if (ImGui::TreeNode(u8"标准控件中的拖放"))
        {
            // ColorEdit 控件自动充当拖放源和拖放目标.
            // 它们使用标准化的有效负载字符串 IMGUI_PAYLOAD_TYPE_COLOR_3F 和 IMGUI_PAYLOAD_TYPE_COLOR_4F
            // 以允许您自己的控件在其拖放交互中使用颜色.
            // 另请参见“演示->控件->颜色/选择器控件->调色板”演示.
            HelpMarker(u8"您可以从颜色方块拖动.");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ImGui::ColorEdit3(u8"颜色 1", col1);
            ImGui::ColorEdit4(u8"颜色 2", col2);
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/拖放/复制交换项目");
        if (ImGui::TreeNode(u8"拖放以复制/交换项目"))
        {
            enum Mode
            {
                Mode_Copy,
                Mode_Move,
                Mode_Swap
            };
            static int mode = 0;
            if (ImGui::RadioButton(u8"复制", mode == Mode_Copy)) { mode = Mode_Copy; } ImGui::SameLine();
            if (ImGui::RadioButton(u8"移动", mode == Mode_Move)) { mode = Mode_Move; } ImGui::SameLine();
            if (ImGui::RadioButton(u8"交换", mode == Mode_Swap)) { mode = Mode_Swap; }
            static const char* names[9] =
            {
                u8"Bobby", u8"Beatrice", u8"Betty",
                u8"Brianna", u8"Barry", u8"Bernard",
                u8"Bibi", u8"Blaine", u8"Bryn"
            };
            for (int n = 0; n < IM_ARRAYSIZE(names); n++)
            {
                ImGui::PushID(n);
                if ((n % 3) != 0)
                    ImGui::SameLine();
                ImGui::Button(names[n], ImVec2(60, 60));

                // 我们的按钮在这里既是拖放源又是拖放目标!
                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
                {
                    // 设置有效负载以携带项目的索引（可以是任何东西）
                    ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(int));

                    // 显示预览（可以是任何东西，例如在拖动图像时，我们可以决定显示
                    // 文件名和图像的小预览等）
                    if (mode == Mode_Copy) { ImGui::Text(u8"复制 %s", names[n]); }
                    if (mode == Mode_Move) { ImGui::Text(u8"移动 %s", names[n]); }
                    if (mode == Mode_Swap) { ImGui::Text(u8"交换 %s", names[n]); }
                    ImGui::EndDragDropSource();
                }
                if (ImGui::BeginDragDropTarget())
                {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
                    {
                        IM_ASSERT(payload->DataSize == sizeof(int));
                        int payload_n = *(const int*)payload->Data;
                        if (mode == Mode_Copy)
                        {
                            names[n] = names[payload_n];
                        }
                        if (mode == Mode_Move)
                        {
                            names[n] = names[payload_n];
                            names[payload_n] = "";
                        }
                        if (mode == Mode_Swap)
                        {
                            const char* tmp = names[n];
                            names[n] = names[payload_n];
                            names[payload_n] = tmp;
                        }
                    }
                    ImGui::EndDragDropTarget();
                }
                ImGui::PopID();
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/拖放/拖放以重新排序项目 (简单)");
        if (ImGui::TreeNode(u8"拖放以重新排序项目 (简单)"))
        {
            // 修复：重新排序期间存在临时（通常为单帧）ID 冲突，因为同一项目可能被提交两次.
            // 这段代码一直有些问题，但方式不容易察觉.
            // 在我们修复此问题之前，启用 ImGuiItemFlags_AllowDuplicateId 以禁用检测该问题.
            ImGui::PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true);

            // 简单重新排序
            HelpMarker(
                u8"我们这里根本不使用拖放 API! "
                u8"相反，我们查询项目被按住但未悬停的时间，并相应地排序项目.");
            static const char* item_names[] = { u8"项目一", u8"项目二", u8"项目三", u8"项目四", u8"项目五" };
            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
            {
                const char* item = item_names[n];
                ImGui::Selectable(item);

                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
                {
                    int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
                    {
                        item_names[n] = item_names[n_next];
                        item_names[n_next] = item;
                        ImGui::ResetMouseDragDelta();
                    }
                }
            }

            ImGui::PopItemFlag();
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/拖放/目标位置的工具提示");
        if (ImGui::TreeNode(u8"目标位置的工具提示"))
        {
            for (int n = 0; n < 2; n++)
            {
                // 拖放目标
                ImGui::Button(n ? u8"拖放到这里##1" : u8"拖放到这里##0");
                if (ImGui::BeginDragDropTarget())
                {
                    ImGuiDragDropFlags drop_target_flags = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoPreviewTooltip;
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F, drop_target_flags))
                    {
                        IM_UNUSED(payload);
                        ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
                        ImGui::SetTooltip(u8"不能拖放到这里!");
                    }
                    ImGui::EndDragDropTarget();
                }

                // 拖放源
                static ImVec4 col4 = { 1.0f, 0.0f, 0.2f, 1.0f };
                if (n == 0)
                    ImGui::ColorButton(u8"拖动我", col4);

            }
            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragsAndSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragsAndSliders()
{
    IMGUI_DEMO_MARKER(u8"控件/拖动和滑块标志");
    if (ImGui::TreeNode(u8"拖动/滑块标志"))
    {
        // 演示对 DragXXX 和 SliderXXX 函数使用高级标志.请注意，标志是相同的!
        static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_AlwaysClamp", &flags, ImGuiSliderFlags_AlwaysClamp);
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_ClampOnInput", &flags, ImGuiSliderFlags_ClampOnInput);
        ImGui::SameLine(); HelpMarker(u8"使用 CTRL+点击手动输入时，将值限制在最小/最大范围内.默认情况下，CTRL+点击允许超出范围.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_ClampZeroRange", &flags, ImGuiSliderFlags_ClampZeroRange);
        ImGui::SameLine(); HelpMarker(u8"即使 min==max==0.0f 也限制.否则 DragXXX 函数不限制.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_Logarithmic", &flags, ImGuiSliderFlags_Logarithmic);
        ImGui::SameLine(); HelpMarker(u8"启用对数编辑（对小值更精确）.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_NoRoundToFormat", &flags, ImGuiSliderFlags_NoRoundToFormat);
        ImGui::SameLine(); HelpMarker(u8"禁用将基础值舍入以匹配格式字符串的精度（例如，%.3f 值舍入到那 3 位数字）.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_NoInput", &flags, ImGuiSliderFlags_NoInput);
        ImGui::SameLine(); HelpMarker(u8"禁用 CTRL+点击或 Enter 键允许直接在小部件中输入文本.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_NoSpeedTweaks", &flags, ImGuiSliderFlags_NoSpeedTweaks);
        ImGui::SameLine(); HelpMarker(u8"禁用键盘修饰符更改调整速度.如果您想根据自己的逻辑自行更改调整速度，这很有用.");
        ImGui::CheckboxFlags(u8"ImGuiSliderFlags_WrapAround", &flags, ImGuiSliderFlags_WrapAround);
        ImGui::SameLine(); HelpMarker(u8"启用从最大到最小和从最小到最大的环绕（仅由 DragXXX() 函数支持）");

        // 拖动
        static float drag_f = 0.5f;
        static int drag_i = 50;
        ImGui::Text(u8"基础浮点值: %f", drag_f);
        ImGui::DragFloat(u8"DragFloat (0 -> 1)", &drag_f, 0.005f, 0.0f, 1.0f, "%.3f", flags);
        ImGui::DragFloat(u8"DragFloat (0 -> +inf)", &drag_f, 0.005f, 0.0f, FLT_MAX, "%.3f", flags);
        ImGui::DragFloat(u8"DragFloat (-inf -> 1)", &drag_f, 0.005f, -FLT_MAX, 1.0f, "%.3f", flags);
        ImGui::DragFloat(u8"DragFloat (-inf -> +inf)", &drag_f, 0.005f, -FLT_MAX, +FLT_MAX, "%.3f", flags);
        //ImGui::DragFloat(u8"DragFloat (0 -> 0)", &drag_f, 0.005f, 0.0f, 0.0f, "%.3f", flags);           // 测试 ClampZeroRange
        //ImGui::DragFloat(u8"DragFloat (100 -> 100)", &drag_f, 0.005f, 100.0f, 100.0f, "%.3f", flags);
        ImGui::DragInt(u8"DragInt (0 -> 100)", &drag_i, 0.5f, 0, 100, "%d", flags);

        // 滑块
        static float slider_f = 0.5f;
        static int slider_i = 50;
        const ImGuiSliderFlags flags_for_sliders = flags & ~ImGuiSliderFlags_WrapAround;
        ImGui::Text(u8"基础浮点值: %f", slider_f);
        ImGui::SliderFloat(u8"SliderFloat (0 -> 1)", &slider_f, 0.0f, 1.0f, "%.3f", flags_for_sliders);
        ImGui::SliderInt(u8"SliderInt (0 -> 100)", &slider_i, 0, 100, "%d", flags_for_sliders);

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsFonts()
//-----------------------------------------------------------------------------

// 前向声明 ShowFontAtlas()，目前还不值得放入公共 API
namespace ImGui { IMGUI_API void ShowFontAtlas(ImFontAtlas* atlas); }

static void DemoWindowWidgetsFonts()
{
    IMGUI_DEMO_MARKER(u8"控件/字体");
    if (ImGui::TreeNode(u8"字体"))
    {
        ImFontAtlas* atlas = ImGui::GetIO().Fonts;
        ImGui::ShowFontAtlas(atlas);
        // 修复-NEWATLAS：提供一个演示来添加/创建程序字体?
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsImages()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsImages()
{
    IMGUI_DEMO_MARKER(u8"控件/图像");
    if (ImGui::TreeNode(u8"图像"))
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::TextWrapped(
            u8"下面我们显示字体纹理（这是我们在本演示中唯一可以访问的纹理）. "
            u8"使用 'ImTextureID' 类型作为存储来传递指针或标识符到您自己的纹理数据. "
            u8"悬停纹理以查看缩放视图!");
        // Below we are displaying the font texture because it is the only texture we have access to inside the demo!
        // Read description about ImTextureID/ImTextureRef and FAQ for details about texture identifiers.
        // If you use one of the default imgui_impl_XXXX.cpp rendering backend, they all have comments at the top
        // of their respective source file to specify what they are using as texture identifier, for example:
        // - The imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer.
        // - The imgui_impl_opengl3.cpp renderer expect a GLuint OpenGL texture identifier, etc.
        // So with the DirectX11 backend, you call ImGui::Image() with a 'ID3D11ShaderResourceView*' cast to ImTextureID.
        // - If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers
        //   to ImGui::Image(), and gather width/height through your own functions, etc.
        // - You can use ShowMetricsWindow() to inspect the draw data that are being passed to your renderer,
        //   it will help you debug issues if you are confused about it.
        // - Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
        // - Read https://github.com/ocornut/imgui/blob/master/docs/FAQ.md
        // - Read https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples

        // Grab the current texture identifier used by the font atlas.
        ImTextureRef my_tex_id = io.Fonts->TexRef;

        // Regular user code should never have to care about TexData-> fields, but since we want to display the entire texture here, we pull Width/Height from it.
        float my_tex_w = (float)io.Fonts->TexData->Width;
        float my_tex_h = (float)io.Fonts->TexData->Height;

        {
            ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec2 uv_min = ImVec2(0.0f, 0.0f); // Top-left
            ImVec2 uv_max = ImVec2(1.0f, 1.0f); // Lower-right
            ImGui::PushStyleVar(ImGuiStyleVar_ImageBorderSize, IM_MAX(1.0f, ImGui::GetStyle().ImageBorderSize));
            ImGui::ImageWithBg(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
            if (ImGui::BeginItemTooltip())
            {
                float region_sz = 32.0f;
                float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
                float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
                float zoom = 4.0f;
                if (region_x < 0.0f) { region_x = 0.0f; }
                else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
                if (region_y < 0.0f) { region_y = 0.0f; }
                else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
                ImGui::Text(u8"最小值: (%.2f, %.2f)", region_x, region_y);
                ImGui::Text(u8"最大值: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
                ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
                ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
                ImGui::ImageWithBg(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                ImGui::EndTooltip();
            }
            ImGui::PopStyleVar();
        }

        IMGUI_DEMO_MARKER(u8"控件/图像/纹理按钮");
        ImGui::TextWrapped(u8"现在是一些带纹理的按钮..");
        static int pressed_count = 0;
        for (int i = 0; i < 8; i++)
        {
            // UV 坐标通常是 (0.0f, 0.0f) 和 (1.0f, 1.0f) 来显示整个纹理.
            // 这里我们尝试只显示纹理的 32x32 像素区域，因此有 UV 计算.
            // 在此阅读有关 UV 坐标的信息：https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
            ImGui::PushID(i);
            if (i > 0)
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(i - 1.0f, i - 1.0f));
            ImVec2 size = ImVec2(32.0f, 32.0f);                         // 我们想要显示的图像大小
            ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // 左下角的 UV 坐标
            ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);    // 纹理中 (32,32) 的 UV 坐标
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // 黑色背景
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // 无着色
            if (ImGui::ImageButton("", my_tex_id, size, uv0, uv1, bg_col, tint_col))
                pressed_count += 1;
            if (i > 0)
                ImGui::PopStyleVar();
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::Text(u8"按下了 %d 次.", pressed_count);
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsListBoxes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsListBoxes()
{
    IMGUI_DEMO_MARKER(u8"控件/列表框");
    if (ImGui::TreeNode(u8"列表框"))
    {
        // BeginListBox() 本质上是使用 BeginChild()/EndChild() 的薄包装
        // 使用 ImGuiChildFlags_FrameStyle 标志进行样式更改 + 显示标签.
        // 您可能想直接使用 BeginChild().但请注意 BeginChild() 需要始终调用 EndChild()
        // （与 BeginListBox()/EndListBox() 不一致）.

        // 使用通用的 BeginListBox() API，您可以完全控制如何显示组合框内容.
        // （您的选择数据可以是索引、对象的指针、对象的 ID、对象本身中侵入式存储的标志等）
        const char* items[] = { u8"AAAA", u8"BBBB", u8"CCCC", u8"DDDD", u8"EEEE", u8"FFFF", u8"GGGG", u8"HHHH", u8"IIII", u8"JJJJ", u8"KKKK", u8"LLLLLLL", u8"MMMM", u8"OOOOOOO" };
        static int item_selected_idx = 0; // 这里我们将选定的数据存储为索引.

        static bool item_highlight = false;
        int item_highlighted_idx = -1; // 这里我们将高亮的数据存储为索引.
        ImGui::Checkbox(u8"在第二个列表框中高亮悬停的项目", &item_highlight);

        if (ImGui::BeginListBox(u8"列表框 1"))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                const bool is_selected = (item_selected_idx == n);
                if (ImGui::Selectable(items[n], is_selected))
                    item_selected_idx = n;

                if (item_highlight && ImGui::IsItemHovered())
                    item_highlighted_idx = n;

                // 打开组合框时设置初始焦点（滚动 + 键盘导航焦点）
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::SameLine(); HelpMarker(u8"这里我们在两个框之间共享选择状态.");

        // 自定义大小：使用全部宽度，5 个项目高
        ImGui::Text(u8"全宽：");
        if (ImGui::BeginListBox(u8"##列表框 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (item_selected_idx == n);
                ImGuiSelectableFlags flags = (item_highlighted_idx == n) ? ImGuiSelectableFlags_Highlight : 0;
                if (ImGui::Selectable(items[n], is_selected, flags))
                    item_selected_idx = n;

                // 打开组合框时设置初始焦点（滚动 + 键盘导航焦点）
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsMultiComponents()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsMultiComponents()
{
    IMGUI_DEMO_MARKER(u8"控件/多组件控件");
    if (ImGui::TreeNode(u8"多组件控件"))
    {
        static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
        static int vec4i[4] = { 1, 5, 100, 255 };

        ImGui::SeparatorText(u8"2 宽");
        ImGui::InputFloat2(u8"输入 float2", vec4f);
        ImGui::DragFloat2(u8"拖动 float2", vec4f, 0.01f, 0.0f, 1.0f);
        ImGui::SliderFloat2(u8"滑块 float2", vec4f, 0.0f, 1.0f);
        ImGui::InputInt2(u8"输入 int2", vec4i);
        ImGui::DragInt2(u8"拖动 int2", vec4i, 1, 0, 255);
        ImGui::SliderInt2(u8"滑块 int2", vec4i, 0, 255);

        ImGui::SeparatorText(u8"3 宽");
        ImGui::InputFloat3(u8"输入 float3", vec4f);
        ImGui::DragFloat3(u8"拖动 float3", vec4f, 0.01f, 0.0f, 1.0f);
        ImGui::SliderFloat3(u8"滑块 float3", vec4f, 0.0f, 1.0f);
        ImGui::InputInt3(u8"输入 int3", vec4i);
        ImGui::DragInt3(u8"拖动 int3", vec4i, 1, 0, 255);
        ImGui::SliderInt3(u8"滑块 int3", vec4i, 0, 255);

        ImGui::SeparatorText(u8"4 宽");
        ImGui::InputFloat4(u8"输入 float4", vec4f);
        ImGui::DragFloat4(u8"拖动 float4", vec4f, 0.01f, 0.0f, 1.0f);
        ImGui::SliderFloat4(u8"滑块 float4", vec4f, 0.0f, 1.0f);
        ImGui::InputInt4(u8"输入 int4", vec4i);
        ImGui::DragInt4(u8"拖动 int4", vec4i, 1, 0, 255);
        ImGui::SliderInt4(u8"滑块 int4", vec4i, 0, 255);

        ImGui::SeparatorText(u8"范围");
        static float begin = 10, end = 90;
        static int begin_i = 100, end_i = 1000;
        ImGui::DragFloatRange2(u8"范围 float", &begin, &end, 0.25f, 0.0f, 100.0f, u8"最小值: %.1f %%", u8"最大值: %.1f %%", ImGuiSliderFlags_AlwaysClamp);
        ImGui::DragIntRange2(u8"范围 int", &begin_i, &end_i, 5, 0, 1000, u8"最小值: %d 单位", u8"最大值: %d 单位");
        ImGui::DragIntRange2(u8"范围 int (无边界)", &begin_i, &end_i, 5, 0, 0, u8"最小值: %d 单位", u8"最大值: %d 单位");

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsPlotting()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsPlotting()
{
    // 绘图/图表控件不是很好.
    // 考虑使用第三方库，如 ImPlot：https://github.com/epezent/implot
    // （参见其他 https://github.com/ocornut/imgui/wiki/Useful-Extensions）
    IMGUI_DEMO_MARKER(u8"控件/绘图");
    if (ImGui::TreeNode(u8"绘图"))
    {
        ImGui::Text(u8"需要更好的绘图和图表?考虑使用 ImPlot：");
        ImGui::TextLinkOpenURL(u8"https://github.com/epezent/implot");
        ImGui::Separator();

        static bool animate = true;
        ImGui::Checkbox(u8"动画", &animate);

        // 绘制为线条和绘制为直方图
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        ImGui::PlotLines(u8"帧时间", arr, IM_ARRAYSIZE(arr));
        ImGui::PlotHistogram(u8"直方图", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));
        //ImGui::SameLine(); HelpMarker(u8"考虑使用 ImPlot 代替!");

        // 填充连续的浮点值数组以绘制
        // 提示：如果您的浮点数不是连续的而是结构的一部分，您可以传递指向第一个浮点数的指针
        // 以及结构的 sizeof() 作为"步幅"参数.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // 为演示创建固定 60 Hz 速率的数据
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // 绘图可以显示覆盖文本
        // （在此示例中，我们将显示平均值）
        {
            float average = 0.0f;
            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
                average += values[n];
            average /= (float)IM_ARRAYSIZE(values);
            char overlay[32];
            sprintf(overlay, u8"平均值 %f", average);
            ImGui::PlotLines(u8"线条", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));
        }

        // 使用函数生成输出
        // 修复：这实际上非常尴尬，因为当前的绘图 API 只传递索引.
        // 我们可能想要一个传递浮点数的 API，用户提供采样率/计数.
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };
        static int func_type = 0, display_count = 70;
        ImGui::SeparatorText(u8"函数");
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::Combo(u8"函数", &func_type, u8"正弦\0锯齿\0");
        ImGui::SameLine();
        ImGui::SliderInt(u8"采样计数", &display_count, 1, 400);
        float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
        ImGui::PlotLines(u8"线条##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
        ImGui::PlotHistogram(u8"直方图##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsProgressBars()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsProgressBars()
{
    IMGUI_DEMO_MARKER(u8"控件/进度条");
    if (ImGui::TreeNode(u8"进度条"))
    {
        // 动画一个简单的进度条
        static float progress = 0.0f, progress_dir = 1.0f;
        progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
        if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
        if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }

        // 通常我们会使用 ImVec2(-1.0f,0.0f) 或 ImVec2(-FLT_MIN,0.0f) 来使用所有可用宽度，
        // 或 ImVec2(width,0.0f) 用于指定宽度.ImVec2(0.0f,0.0f) 使用 ItemWidth.
        ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::Text(u8"进度条");

        float progress_saturated = IM_CLAMP(progress, 0.0f, 1.0f);
        char buf[32];
        sprintf(buf, u8"%d/%d", (int)(progress_saturated * 1753), 1753);
        ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);

        // 传递一个动画的负值，例如 -1.0f * (float)ImGui::GetTime() 是推荐值.
        // 如果您想调整动画速度，请调整因子.
        ImGui::ProgressBar(-1.0f * (float)ImGui::GetTime(), ImVec2(0.0f, 0.0f), u8"搜索中..");
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::Text(u8"不确定");

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsQueryingStatuses()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsQueryingStatuses()
{
    IMGUI_DEMO_MARKER(u8"控件/查询项目状态 (已编辑,活动,悬停等)");
    if (ImGui::TreeNode(u8"查询项目状态 (已编辑/活动/悬停等)"))
    {
        // 选择一个项目类型
        const char* item_names[] =
        {
            u8"文本", u8"按钮", u8"按钮 (带重复)", u8"复选框", u8"滑块浮点数", u8"输入文本", u8"输入多行文本", u8"输入浮点数",
            u8"输入浮点数3", u8"颜色编辑4", u8"可选", u8"菜单项", u8"树节点", u8"树节点 (带双击)", u8"组合框", u8"列表框"
        };
        static int item_type = 4;
        static bool item_disabled = false;
        ImGui::Combo(u8"项目类型", &item_type, item_names, IM_ARRAYSIZE(item_names), IM_ARRAYSIZE(item_names));
        ImGui::SameLine();
        HelpMarker(u8"测试各种类型的项目如何与 IsItemXXX 函数交互.请注意，大多数 ImGui 函数的布尔返回值通常等同于调用 ImGui::IsItemHovered().");
        ImGui::Checkbox(u8"项目禁用", &item_disabled);

        // 提交选定的项目，以便我们可以在后面的代码中查询它们的状态.
        bool ret = false;
        static bool b = false;
        static float col4f[4] = { 1.0f, 0.5, 0.0f, 1.0f };
        static char str[16] = {};
        if (item_disabled)
            ImGui::BeginDisabled(true);
        if (item_type == 0) { ImGui::Text(u8"项目: 文本"); }                                              // 测试没有标识符/交互的文本项目
        if (item_type == 1) { ret = ImGui::Button(u8"项目: 按钮"); }                                    // 测试按钮
        if (item_type == 2) { ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true); ret = ImGui::Button(u8"项目: 按钮"); ImGui::PopItemFlag(); } // 测试按钮 (带重复器)
        if (item_type == 3) { ret = ImGui::Checkbox(u8"项目: 复选框", &b); }                            // 测试复选框
        if (item_type == 4) { ret = ImGui::SliderFloat(u8"项目: 滑块浮点数", &col4f[0], 0.0f, 1.0f); }   // 测试基本项目
        if (item_type == 5) { ret = ImGui::InputText(u8"项目: 输入文本", &str[0], IM_ARRAYSIZE(str)); }  // 测试输入文本 (处理制表符)
        if (item_type == 6) { ret = ImGui::InputTextMultiline(u8"项目: 输入多行文本", &str[0], IM_ARRAYSIZE(str)); } // 测试输入文本 (使用子窗口)
        if (item_type == 7) { ret = ImGui::InputFloat(u8"项目: 输入浮点数", col4f, 1.0f); }               // 测试标量输入上的 +/- 按钮
        if (item_type == 8) { ret = ImGui::InputFloat3(u8"项目: 输入浮点数3", col4f); }                   // 测试多组件项目 (IsItemXXX 标志报告为合并)
        if (item_type == 9) { ret = ImGui::ColorEdit4(u8"项目: 颜色编辑4", col4f); }                     // 测试多组件项目 (IsItemXXX 标志报告为合并)
        if (item_type == 10) { ret = ImGui::Selectable(u8"项目: 可选"); }                            // 测试可选项目
        if (item_type == 11) { ret = ImGui::MenuItem(u8"项目: 菜单项"); }                                // 测试菜单项 (它们使用 ImGuiButtonFlags_PressedOnRelease 按钮策略)
        if (item_type == 12) { ret = ImGui::TreeNode(u8"项目: 树节点"); if (ret) ImGui::TreePop(); }     // 测试树节点
        if (item_type == 13) { ret = ImGui::TreeNodeEx(u8"项目: 带 ImGuiTreeNodeFlags_OpenOnDoubleClick 的树节点", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen); } // 测试带 ImGuiButtonFlags_PressedOnDoubleClick 按钮策略的树节点.
        if (item_type == 14) { const char* items[] = { u8"苹果", u8"香蕉", u8"樱桃", u8"猕猴桃" }; static int current = 1; ret = ImGui::Combo(u8"项目: 组合框", &current, items, IM_ARRAYSIZE(items)); }
        if (item_type == 15) { const char* items[] = { u8"苹果", u8"香蕉", u8"樱桃", u8"猕猴桃" }; static int current = 1; ret = ImGui::ListBox(u8"项目: 列表框", &current, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items)); }

        bool hovered_delay_none = ImGui::IsItemHovered();
        bool hovered_delay_stationary = ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary);
        bool hovered_delay_short = ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort);
        bool hovered_delay_normal = ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal);
        bool hovered_delay_tooltip = ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip); // = Normal + Stationary

        // 显示 IsItemHovered() 和其他常见项目状态函数的值.
        // 请注意，ImGuiHoveredFlags_XXX 标志可以组合.
        // 因为 BulletText 本身就是一个项目，这会影响 IsItemXXX 函数的输出，
        // 我们在一次调用中查询每个状态以避免存储它们并简化代码.
        ImGui::BulletText(
            u8"返回值 = %d\n"
            "IsItemFocused() = %d\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByWindow) = %d\n"
            "IsItemHovered(_AllowWhenDisabled) = %d\n"
            "IsItemHovered(_RectOnly) = %d\n"
            "IsItemActive() = %d\n"
            "IsItemEdited() = %d\n"
            "IsItemActivated() = %d\n"
            "IsItemDeactivated() = %d\n"
            "IsItemDeactivatedAfterEdit() = %d\n"
            "IsItemVisible() = %d\n"
            "IsItemClicked() = %d\n"
            "IsItemToggledOpen() = %d\n"
            "GetItemRectMin() = (%.1f, %.1f)\n"
            "GetItemRectMax() = (%.1f, %.1f)\n"
            "GetItemRectSize() = (%.1f, %.1f)",
            ret,
            ImGui::IsItemFocused(),
            ImGui::IsItemHovered(),
            ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlappedByItem),
            ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlappedByWindow),
            ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled),
            ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly),
            ImGui::IsItemActive(),
            ImGui::IsItemEdited(),
            ImGui::IsItemActivated(),
            ImGui::IsItemDeactivated(),
            ImGui::IsItemDeactivatedAfterEdit(),
            ImGui::IsItemVisible(),
            ImGui::IsItemClicked(),
            ImGui::IsItemToggledOpen(),
            ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y,
            ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y,
            ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y
        );
        ImGui::BulletText(
            u8"带悬停延迟或静止测试:\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_Stationary) = %d\n"
            "IsItemHovered(_DelayShort) = %d\n"
            "IsItemHovered(_DelayNormal) = %d\n"
            "IsItemHovered(_Tooltip) = %d",
            hovered_delay_none, hovered_delay_stationary, hovered_delay_short, hovered_delay_normal, hovered_delay_tooltip);

        if (item_disabled)
            ImGui::EndDisabled();

        char buf[1] = "";
        ImGui::InputText(u8"未使用", buf, IM_ARRAYSIZE(buf), ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();
        HelpMarker(u8"此控件仅用于能够从上面的控件中跳出并查看例如 Deactivated() 状态.");

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"控件/查询窗口状态 (聚焦,悬停等)");
    if (ImGui::TreeNode(u8"查询窗口状态 (聚焦/悬停等)"))
    {
        static bool embed_all_inside_a_child_window = false;
        ImGui::Checkbox(u8"将所有内容嵌入子窗口中以测试 _RootWindow 标志.", &embed_all_inside_a_child_window);
        if (embed_all_inside_a_child_window)
            ImGui::BeginChild(u8"外部子窗口", ImVec2(0, ImGui::GetFontSize() * 20.0f), ImGuiChildFlags_Borders);

        // 测试 IsWindowFocused() 函数及其各种标志.
        ImGui::BulletText(
            "IsWindowFocused() = %d\n"
            "IsWindowFocused(_ChildWindows) = %d\n"
            "IsWindowFocused(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_DockHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowFocused(_RootWindow) = %d\n"
            "IsWindowFocused(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowFocused(_AnyWindow) = %d\n",
            ImGui::IsWindowFocused(),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_NoPopupHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_DockHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_NoPopupHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_DockHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_NoPopupHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_DockHierarchy),
            ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow));

        // 测试 IsWindowHovered() 函数及其各种标志.
        ImGui::BulletText(
            "IsWindowHovered() = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsWindowHovered(_ChildWindows) = %d\n"
            "IsWindowHovered(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_DockHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowHovered(_RootWindow) = %d\n"
            "IsWindowHovered(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_RootWindow|_DockHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AnyWindow) = %d\n"
            "IsWindowHovered(_Stationary) = %d\n",
            ImGui::IsWindowHovered(),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_NoPopupHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_DockHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_NoPopupHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_DockHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_NoPopupHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_DockHierarchy),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow),
            ImGui::IsWindowHovered(ImGuiHoveredFlags_Stationary));

        ImGui::BeginChild(u8"子窗口", ImVec2(0, 50), ImGuiChildFlags_Borders);
        ImGui::Text(u8"这是另一个用于测试 _ChildWindows 标志的子窗口.");
        ImGui::EndChild();
        if (embed_all_inside_a_child_window)
            ImGui::EndChild();

        // 在 begin 之后调用 IsItemHovered() 返回标题栏的悬停状态.
        // 这特别有用，如果您想创建与窗口标题栏关联的上下文菜单.
        // 当停靠到选项卡中时，这也会起作用（选项卡替换标题栏并保证相同的属性）.
        static bool test_window = false;
        ImGui::Checkbox(u8"Begin() 之后的悬停/活动测试用于标题栏测试", &test_window);
        if (test_window)
        {
            // 修复-停靠：此窗口无法停靠在 ImGui 演示窗口内，这将导致反馈循环并使它们卡住.
            // 我们可以通过 ImGuiWindowClass 功能或 API 调用来标记我们的父级为"不要跳过项目"来修复此问题吗?
            ImGui::Begin(u8"标题栏悬停/活动测试", &test_window);
            if (ImGui::BeginPopupContextItem()) // <-- 这使用 IsItemHovered()
            {
                if (ImGui::MenuItem(u8"关闭")) { test_window = false; }
                ImGui::EndPopup();
            }
            ImGui::Text(
                u8"begin 之后的 IsItemHovered() = %d (== 标题栏悬停)\n"
                u8"begin 之后的 IsItemActive() = %d (== 窗口被点击/移动)\n",
                ImGui::IsItemHovered(), ImGui::IsItemActive());
            ImGui::End();
        }

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectables()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsSelectables()
{
    IMGUI_DEMO_MARKER(u8"控件/可选项目");
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode(u8"可选项目"))
    {
        // Selectable() 有 2 个重载：
        // - 一个接受 "bool selected" 作为只读选择信息.
        //   当 Selectable() 被点击时返回 true，您可以相应地更改选择状态.
        // - 一个接受 "bool* p_selected" 作为读写选择信息（在某些情况下很方便）
        // 前者更灵活，因为在真实应用程序中，您的选择可能以多种不同方式存储
        // 不一定在布尔值内（例如在对象中的标志中，作为外部列表等）.
        IMGUI_DEMO_MARKER(u8"控件/可选项目/基础");
        if (ImGui::TreeNode(u8"基础"))
        {
            static bool selection[5] = { false, true, false, false };
            ImGui::Selectable(u8"1. 我是可选的", &selection[0]);
            ImGui::Selectable(u8"2. 我是可选的", &selection[1]);
            ImGui::Selectable(u8"3. 我是可选的", &selection[2]);
            if (ImGui::Selectable(u8"4. 我可双击", selection[3], ImGuiSelectableFlags_AllowDoubleClick))
                if (ImGui::IsMouseDoubleClicked(0))
                    selection[3] = !selection[3];
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/可选项目/在同一行渲染更多项目");
        if (ImGui::TreeNode(u8"在同一行渲染更多项目"))
        {
            // (1) 使用 SetNextItemAllowOverlap()
            // (2) 使用接受 "bool* p_selected" 参数的 Selectable() 重载，布尔值会自动切换.
            static bool selected[3] = { false, false, false };
            ImGui::SetNextItemAllowOverlap(); ImGui::Selectable(u8"main.c", &selected[0]); ImGui::SameLine(); ImGui::SmallButton(u8"链接 1");
            ImGui::SetNextItemAllowOverlap(); ImGui::Selectable(u8"Hello.cpp", &selected[1]); ImGui::SameLine(); ImGui::SmallButton(u8"链接 2");
            ImGui::SetNextItemAllowOverlap(); ImGui::Selectable(u8"Hello.h", &selected[2]); ImGui::SameLine(); ImGui::SmallButton(u8"链接 3");
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/可选项目/在表格中");
        if (ImGui::TreeNode(u8"在表格中"))
        {
            static bool selected[10] = {};

            if (ImGui::BeginTable("split1", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
            {
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, u8"项目 %d", i);
                    ImGui::TableNextColumn();
                    ImGui::Selectable(label, &selected[i]); // 修复-表格：选择重叠
                }
                ImGui::EndTable();
            }
            ImGui::Spacing();
            if (ImGui::BeginTable("split2", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders))
            {
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, u8"项目 %d", i);
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Selectable(label, &selected[i], ImGuiSelectableFlags_SpanAllColumns);
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"其他一些内容");
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"123456");
                }
                ImGui::EndTable();
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/可选项目/网格");
        if (ImGui::TreeNode(u8"网格"))
        {
            static char selected[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

            // 添加一些有趣的元素...
            const float time = (float)ImGui::GetTime();
            const bool winning_state = memchr(selected, 0, sizeof(selected)) == NULL; // 如果所有单元格都被选中...
            if (winning_state)
                ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f + 0.5f * cosf(time * 2.0f), 0.5f + 0.5f * sinf(time * 3.0f)));

            for (int y = 0; y < 4; y++)
                for (int x = 0; x < 4; x++)
                {
                    if (x > 0)
                        ImGui::SameLine();
                    ImGui::PushID(y * 4 + x);
                    if (ImGui::Selectable(u8"水手", selected[y][x] != 0, 0, ImVec2(50, 50)))
                    {
                        // 切换点击的单元格 + 切换邻居
                        selected[y][x] ^= 1;
                        if (x > 0) { selected[y][x - 1] ^= 1; }
                        if (x < 3) { selected[y][x + 1] ^= 1; }
                        if (y > 0) { selected[y - 1][x] ^= 1; }
                        if (y < 3) { selected[y + 1][x] ^= 1; }
                    }
                    ImGui::PopID();
                }

            if (winning_state)
                ImGui::PopStyleVar();
            ImGui::TreePop();
        }
        IMGUI_DEMO_MARKER(u8"控件/可选项目/对齐");
        if (ImGui::TreeNode(u8"对齐"))
        {
            HelpMarker(
                u8"默认情况下，Selectables 使用 style.SelectableTextAlign，但可以使用 PushStyleVar() 在每个项目的基础上覆盖它."
                u8"您可能希望始终保持默认情况为左对齐，否则很难在同一行上布局多个项目");
            static bool selected[3 * 3] = { true, false, true, false, true, false, true, false, true };
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    ImVec2 alignment = ImVec2((float)x / 2.0f, (float)y / 2.0f);
                    char name[32];
                    sprintf(name, u8"(%.1f,%.1f)", alignment.x, alignment.y);
                    if (x > 0) ImGui::SameLine();
                    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, alignment);
                    ImGui::Selectable(name, &selected[3 * y + x], ImGuiSelectableFlags_None, ImVec2(80, 80));
                    ImGui::PopStyleVar();
                }
            }
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectionAndMultiSelect()
//-----------------------------------------------------------------------------
// 多选演示
// 另请阅读：https://github.com/ocornut/imgui/wiki/Multi-Select
//-----------------------------------------------------------------------------

static const char* ExampleNames[] =
{
    u8"洋蓟", u8"芝麻菜", u8"芦笋", u8"牛油果", u8"竹笋", u8"豆芽", u8"豆类", u8"甜菜", u8"比利时菊苣", u8"甜椒",
    u8"苦瓜", u8"小白菜", u8"西兰花", u8"球芽甘蓝", u8"牛蒡根", u8"卷心菜", u8"葫芦", u8"刺山柑", u8"胡萝卜", u8"木薯",
    u8"花椰菜", u8"芹菜", u8"芹菜根", u8"生菜", u8"佛手瓜", u8"芥蓝", u8"玉米", u8"黄瓜"
};

// Extra functions to add deletion support to ImGuiSelectionBasicStorage
struct ExampleSelectionWithDeletion : ImGuiSelectionBasicStorage
{
    // Find which item should be Focused after deletion.
    // Call _before_ item submission. Return an index in the before-deletion item list, your item loop should call SetKeyboardFocusHere() on it.
    // The subsequent ApplyDeletionPostLoop() code will use it to apply Selection.
    // - We cannot provide this logic in core Dear ImGui because we don't have access to selection data.
    // - We don't actually manipulate the ImVector<> here, only in ApplyDeletionPostLoop(), but using similar API for consistency and flexibility.
    // - Important: Deletion only works if the underlying ImGuiID for your items are stable: aka not depend on their index, but on e.g. item id/ptr.
    // FIXME-MULTISELECT: Doesn't take account of the possibility focus target will be moved during deletion. Need refocus or scroll offset.
    int ApplyDeletionPreLoop(ImGuiMultiSelectIO* ms_io, int items_count)
    {
        if (Size == 0)
            return -1;

        // If focused item is not selected...
        const int focused_idx = (int)ms_io->NavIdItem;  // Index of currently focused item
        if (ms_io->NavIdSelected == false)  // This is merely a shortcut, == Contains(adapter->IndexToStorage(items, focused_idx))
        {
            ms_io->RangeSrcReset = true;    // Request to recover RangeSrc from NavId next frame. Would be ok to reset even when NavIdSelected==true, but it would take an extra frame to recover RangeSrc when deleting a selected item.
            return focused_idx;             // Request to focus same item after deletion.
        }

        // If focused item is selected: land on first unselected item after focused item.
        for (int idx = focused_idx + 1; idx < items_count; idx++)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        // If focused item is selected: otherwise return last unselected item before focused item.
        for (int idx = IM_MIN(focused_idx, items_count) - 1; idx >= 0; idx--)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        return -1;
    }

    // Rewrite item list (delete items) + update selection.
    // - Call after EndMultiSelect()
    // - We cannot provide this logic in core Dear ImGui because we don't have access to your items, nor to selection data.
    template<typename ITEM_TYPE>
    void ApplyDeletionPostLoop(ImGuiMultiSelectIO* ms_io, ImVector<ITEM_TYPE>& items, int item_curr_idx_to_select)
    {
        // Rewrite item list (delete items) + convert old selection index (before deletion) to new selection index (after selection).
        // If NavId was not part of selection, we will stay on same item.
        ImVector<ITEM_TYPE> new_items;
        new_items.reserve(items.Size - Size);
        int item_next_idx_to_select = -1;
        for (int idx = 0; idx < items.Size; idx++)
        {
            if (!Contains(GetStorageIdFromIndex(idx)))
                new_items.push_back(items[idx]);
            if (item_curr_idx_to_select == idx)
                item_next_idx_to_select = new_items.Size - 1;
        }
        items.swap(new_items);

        // Update selection
        Clear();
        if (item_next_idx_to_select != -1 && ms_io->NavIdSelected)
            SetItemSelected(GetStorageIdFromIndex(item_next_idx_to_select), true);
    }
};

// Example: Implement dual list box storage and interface
struct ExampleDualListBox
{
    ImVector<ImGuiID>           Items[2];               // ID is index into ExampleName[]
    ImGuiSelectionBasicStorage  Selections[2];          // Store ExampleItemId into selection
    bool                        OptKeepSorted = true;

    void MoveAll(int src, int dst)
    {
        IM_ASSERT((src == 0 && dst == 1) || (src == 1 && dst == 0));
        for (ImGuiID item_id : Items[src])
            Items[dst].push_back(item_id);
        Items[src].clear();
        SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void MoveSelected(int src, int dst)
    {
        for (int src_n = 0; src_n < Items[src].Size; src_n++)
        {
            ImGuiID item_id = Items[src][src_n];
            if (!Selections[src].Contains(item_id))
                continue;
            Items[src].erase(&Items[src][src_n]); // FIXME-OPT: Could be implemented more optimally (rebuild src items and swap)
            Items[dst].push_back(item_id);
            src_n--;
        }
        if (OptKeepSorted)
            SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void ApplySelectionRequests(ImGuiMultiSelectIO* ms_io, int side)
    {
        // In this example we store item id in selection (instead of item index)
        Selections[side].UserData = Items[side].Data;
        Selections[side].AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { ImGuiID* items = (ImGuiID*)self->UserData; return items[idx]; };
        Selections[side].ApplyRequests(ms_io);
    }
    static int IMGUI_CDECL CompareItemsByValue(const void* lhs, const void* rhs)
    {
        const int* a = (const int*)lhs;
        const int* b = (const int*)rhs;
        return (*a - *b);
    }
    void SortItems(int n)
    {
        qsort(Items[n].Data, (size_t)Items[n].Size, sizeof(Items[n][0]), CompareItemsByValue);
    }
    void Show()
    {
        //if (ImGui::Checkbox("Sorted", &OptKeepSorted) && OptKeepSorted) { SortItems(0); SortItems(1); }
        if (ImGui::BeginTable(u8"分裂", 3, ImGuiTableFlags_None))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);    // Left side
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);      // Buttons
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);    // Right side
            ImGui::TableNextRow();

            int request_move_selected = -1;
            int request_move_all = -1;
            float child_height_0 = 0.0f;
            for (int side = 0; side < 2; side++)
            {
                // FIXME-MULTISELECT: Dual List Box: Add context menus
                // FIXME-NAV: Using ImGuiWindowFlags_NavFlattened exhibit many issues.
                ImVector<ImGuiID>& items = Items[side];
                ImGuiSelectionBasicStorage& selection = Selections[side];

                ImGui::TableSetColumnIndex((side == 0) ? 0 : 2);
                ImGui::Text("%s (%d)", (side == 0) ? u8"可用" : u8"篮子", items.Size);

                // Submit scrolling range to avoid glitches on moving/deletion
                const float items_height = ImGui::GetTextLineHeightWithSpacing();
                ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));

                bool child_visible;
                if (side == 0)
                {
                    // Left child is resizable
                    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetFrameHeightWithSpacing() * 4), ImVec2(FLT_MAX, FLT_MAX));
                    child_visible = ImGui::BeginChild("0", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY);
                    child_height_0 = ImGui::GetWindowSize().y;
                }
                else
                {
                    // Right child use same height as left one
                    child_visible = ImGui::BeginChild("1", ImVec2(-FLT_MIN, child_height_0), ImGuiChildFlags_FrameStyle);
                }
                if (child_visible)
                {
                    ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_None;
                    ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                    ApplySelectionRequests(ms_io, side);

                    for (int item_n = 0; item_n < items.Size; item_n++)
                    {
                        ImGuiID item_id = items[item_n];
                        bool item_is_selected = selection.Contains(item_id);
                        ImGui::SetNextItemSelectionUserData(item_n);
                        ImGui::Selectable(ExampleNames[item_id], item_is_selected, ImGuiSelectableFlags_AllowDoubleClick);
                        if (ImGui::IsItemFocused())
                        {
                            // FIXME-MULTISELECT: Dual List Box: Transfer focus
                            if (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter))
                                request_move_selected = side;
                            if (ImGui::IsMouseDoubleClicked(0)) // FIXME-MULTISELECT: Double-click on multi-selection?
                                request_move_selected = side;
                        }
                    }

                    ms_io = ImGui::EndMultiSelect();
                    ApplySelectionRequests(ms_io, side);
                }
                ImGui::EndChild();
            }

            // Buttons columns
            ImGui::TableSetColumnIndex(1);
            ImGui::NewLine();
            //ImVec2 button_sz = { ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f, ImGui::GetFrameHeight() + padding.y * 2.0f };
            ImVec2 button_sz = { ImGui::GetFrameHeight(), ImGui::GetFrameHeight() };

            // (Using BeginDisabled()/EndDisabled() works but feels distracting given how it is currently visualized)
            if (ImGui::Button(">>", button_sz))
                request_move_all = 0;
            if (ImGui::Button(">", button_sz))
                request_move_selected = 0;
            if (ImGui::Button("<", button_sz))
                request_move_selected = 1;
            if (ImGui::Button("<<", button_sz))
                request_move_all = 1;

            // Process requests
            if (request_move_all != -1)
                MoveAll(request_move_all, request_move_all ^ 1);
            if (request_move_selected != -1)
                MoveSelected(request_move_selected, request_move_selected ^ 1);

            // FIXME-MULTISELECT: Support action from outside
            /*
            if (OptKeepSorted == false)
            {
                ImGui::NewLine();
                if (ImGui::ArrowButton("MoveUp", ImGuiDir_Up)) {}
                if (ImGui::ArrowButton("MoveDown", ImGuiDir_Down)) {}
            }
            */

            ImGui::EndTable();
        }
    }
};

static void DemoWindowWidgetsSelectionAndMultiSelect(ImGuiDemoWindowData* demo_data)
{
    IMGUI_DEMO_MARKER(u8"控件/选择状态和多选");
    if (ImGui::TreeNode(u8"选择状态和多选"))
    {
        HelpMarker(u8"可以使用 Selectable()、TreeNode() 或其他控件构建选择.选择状态由应用程序代码/数据拥有.");

        // 无需任何花哨的 API：自己管理单选.
        IMGUI_DEMO_MARKER(u8"控件/选择状态/单选");
        if (ImGui::TreeNode(u8"单选"))
        {
            static int selected = -1;
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, u8"对象 %d", n);
                if (ImGui::Selectable(buf, selected == n))
                    selected = n;
            }
            ImGui::TreePop();
        }

        // 演示手动实现最基本形式的多选
        // 这不支持需要 BeginMultiSelect() 的 SHIFT 修饰符!
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (手动/简化, 无 BeginMultiSelect)");
        if (ImGui::TreeNode(u8"多选 (手动/简化, 无 BeginMultiSelect)"))
        {
            HelpMarker(u8"按住 CTRL 并点击以选择多个项目.");
            static bool selection[5] = { false, false, false, false, false };
            for (int n = 0; n < 5; n++)
            {
                char buf[32];
                sprintf(buf, u8"对象 %d", n);
                if (ImGui::Selectable(buf, selection[n]))
                {
                    if (!ImGui::GetIO().KeyCtrl) // 当未按住 CTRL 时清除选择
                        memset(selection, 0, sizeof(selection));
                    selection[n] ^= 1; // 切换当前项目
                }
            }
            ImGui::TreePop();
        }

        // 演示使用 BeginMultiSelect/EndMultiSelect API 处理正确的多选.
        // 支持 SHIFT+点击 w/ CTRL 和其他标准功能.
        // 我们使用 ImGuiSelectionBasicStorage 辅助器，您可以自由重新实现.
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选");
        if (ImGui::TreeNode(u8"多选"))
        {
            ImGui::Text(u8"支持的功能：");
            ImGui::BulletText(u8"键盘导航 (方向键, 上/下页, 首页/尾页, 空格键).");
            ImGui::BulletText(u8"Ctrl 修饰符用于保留和切换选择.");
            ImGui::BulletText(u8"Shift 修饰符用于范围选择.");
            ImGui::BulletText(u8"CTRL+A 选择全部.");
            ImGui::BulletText(u8"Escape 清除选择.");
            ImGui::BulletText(u8"点击并拖动进行框选.");
            ImGui::Text(u8"提示：使用 '演示->工具->调试日志->选择' 查看选择请求的发生情况.");

            // 使用默认选择.Adapter：将索引传递给 SetNextItemSelectionUserData()，将索引存储在 Selection 中
            const int ITEMS_COUNT = 50;
            static ImGuiSelectionBasicStorage selection;
            ImGui::Text(u8"选择: %d/%d", selection.Size, ITEMS_COUNT);

            // BeginChild() 对选择逻辑没有目的，只是提供一个滚动区域.
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, u8"对象 %05d: %s", n, ExampleNames[n % IM_ARRAYSIZE(ExampleNames)]);
                    bool item_is_selected = selection.Contains((ImGuiID)n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // 演示将裁剪器与 BeginMultiSelect()/EndMultiSelect() 一起使用
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (带裁剪器)");
        if (ImGui::TreeNode(u8"多选 (带裁剪器)"))
        {
            // 使用默认选择.Adapter：将索引传递给 SetNextItemSelectionUserData()，将索引存储在 Selection 中
            static ImGuiSelectionBasicStorage selection;

            ImGui::Text(u8"新增功能：");
            ImGui::BulletText(u8"使用 ImGuiListClipper.");

            const int ITEMS_COUNT = 10000;
            ImGui::Text(u8"选择: %d/%d", selection.Size, ITEMS_COUNT);
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                ImGuiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // 确保 RangeSrc 项目不被裁剪.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        char label[64];
                        sprintf(label, u8"对象 %05d: %s", n, ExampleNames[n % IM_ARRAYSIZE(ExampleNames)]);
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        ImGui::SetNextItemSelectionUserData(n);
                        ImGui::Selectable(label, item_is_selected);
                    }
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // 演示使用 BeginMultiSelect/EndMultiSelect API 的动态项目列表 + 删除支持.
        // 为了支持删除而没有任何故障，您需要：
        // - (1) 如果项目在其自己的滚动区域中提交，请提前提交内容大小 SetNextWindowContentSize() 以防止滚动的一帧调整.
        // - (2) 项目需要具有持久的 ID 堆栈标识符 = ID 不能依赖于它们的索引.PushID(index) = 错误.PushID(item_id) = 正确.这是为了在选择后可靠地聚焦项目.
        // - (3) BeginXXXX 过程
        // - (4) 聚焦过程
        // - (5) EndXXXX 过程
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (带删除)");
        if (ImGui::TreeNode(u8"多选 (带删除)"))
        {
            // 将项目数据与选择数据分开存储.
            // （如果您不需要对相同项目的多个视图，您可以决定将选择数据存储在您的项目中（也称为侵入式存储））
            // 使用自定义选择.Adapter：将项目标识符存储在 Selection 中（而不是索引）
            static ImVector<ImGuiID> items;
            static ExampleSelectionWithDeletion selection;
            selection.UserData = (void*)&items;
            selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { ImVector<ImGuiID>* p_items = (ImVector<ImGuiID>*)self->UserData; return (*p_items)[idx]; }; // 索引 -> ID

            ImGui::Text(u8"新增功能：");
            ImGui::BulletText(u8"支持 Delete 键的动态列表.");
            ImGui::Text(u8"选择大小: %d/%d", selection.Size, items.Size);

            // 使用 50 个项目初始化默认列表 + 添加/删除项目的按钮.
            static ImGuiID items_next_id = 0;
            if (items_next_id == 0)
                for (ImGuiID n = 0; n < 50; n++)
                    items.push_back(items_next_id++);
            if (ImGui::SmallButton(u8"添加 20 个项目")) { for (int n = 0; n < 20; n++) { items.push_back(items_next_id++); } }
            ImGui::SameLine();
            if (ImGui::SmallButton(u8"移除 20 个项目")) { for (int n = IM_MIN(20, items.Size); n > 0; n--) { selection.SetItemSelected(items.back(), false); items.pop_back(); } }

            // (1) 支持删除的额外内容：提交滚动范围以避免删除时的故障
            const float items_height = ImGui::GetTextLineHeightWithSpacing();
            ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));

            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (selection.Size > 0);
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;

                for (int n = 0; n < items.Size; n++)
                {
                    const ImGuiID item_id = items[n];
                    char label[64];
                    sprintf(label, u8"对象 %05u: %s", item_id, ExampleNames[item_id % IM_ARRAYSIZE(ExampleNames)]);

                    bool item_is_selected = selection.Contains(item_id);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                    if (item_curr_idx_to_focus == n)
                        ImGui::SetKeyboardFocusHere(-1);
                }

                // 应用多选请求
                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // 实现双列表框 (#6648)
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (双列表框)");
        if (ImGui::TreeNode(u8"多选 (双列表框)"))
        {
            // 初始化默认状态
            static ExampleDualListBox dlb;
            if (dlb.Items[0].Size == 0 && dlb.Items[1].Size == 0)
                for (int item_id = 0; item_id < IM_ARRAYSIZE(ExampleNames); item_id++)
                    dlb.Items[0].push_back((ImGuiID)item_id);

            // 显示
            dlb.Show();

            ImGui::TreePop();
        }

        // 演示将裁剪器与 BeginMultiSelect()/EndMultiSelect() 一起使用
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (在表格中)");
        if (ImGui::TreeNode(u8"多选 (在表格中)"))
        {
            static ImGuiSelectionBasicStorage selection;

            const int ITEMS_COUNT = 10000;
            ImGui::Text(u8"选择: %d/%d", selection.Size, ITEMS_COUNT);
            if (ImGui::BeginTable("##Basket", 2, ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter))
            {
                ImGui::TableSetupColumn(u8"对象");
                ImGui::TableSetupColumn(u8"操作");
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableHeadersRow();

                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                ImGuiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // 确保 RangeSrc 项目不被裁剪.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        char label[64];
                        sprintf(label, u8"对象 %05d: %s", n, ExampleNames[n % IM_ARRAYSIZE(ExampleNames)]);
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        ImGui::SetNextItemSelectionUserData(n);
                        ImGui::Selectable(label, item_is_selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap);
                        ImGui::TableNextColumn();
                        ImGui::SmallButton(u8"你好");
                    }
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                ImGui::EndTable();
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (复选框)");
        if (ImGui::TreeNode(u8"多选 (复选框)"))
        {
            ImGui::Text(u8"在复选框列表中（非可选）：");
            ImGui::BulletText(u8"使用 _NoAutoSelect + _NoAutoClear 标志.");
            ImGui::BulletText(u8"Shift+点击以选中多个复选框.");
            ImGui::BulletText(u8"Shift+键盘以将当前值复制到其他复选框.");

            // 如果您有一个复选框数组，您可能希望使用 NoAutoSelect + NoAutoClear 和 ImGuiSelectionExternalStorage 辅助器.
            static bool items[20] = {};
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_NoAutoSelect | ImGuiMultiSelectFlags_NoAutoClear | ImGuiMultiSelectFlags_ClearOnEscape;
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoSelect", &flags, ImGuiMultiSelectFlags_NoAutoSelect);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClear", &flags, ImGuiMultiSelectFlags_NoAutoClear);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect2d", &flags, ImGuiMultiSelectFlags_BoxSelect2d); // 不能使用 ImGuiMultiSelectFlags_BoxSelect1d，因为复选框宽度不同.

            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, -1, IM_ARRAYSIZE(items));
                ImGuiSelectionExternalStorage storage_wrapper;
                storage_wrapper.UserData = (void*)items;
                storage_wrapper.AdapterSetItemSelected = [](ImGuiSelectionExternalStorage* self, int n, bool selected) { bool* array = (bool*)self->UserData; array[n] = selected; };
                storage_wrapper.ApplyRequests(ms_io);
                for (int n = 0; n < 20; n++)
                {
                    char label[32];
                    sprintf(label, u8"项目 %d", n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Checkbox(label, &items[n]);
                }
                ms_io = ImGui::EndMultiSelect();
                storage_wrapper.ApplyRequests(ms_io);
            }
            ImGui::EndChild();

            ImGui::TreePop();
        }

        // 演示同一窗口中的单独选择范围
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (多个范围)");
        if (ImGui::TreeNode(u8"多选 (多个范围)"))
        {
            // 使用默认选择：将索引传递给 SetNextItemSelectionUserData()，将索引存储在 Selection 中
            const int SCOPES_COUNT = 3;
            const int ITEMS_COUNT = 8; // 每个范围
            static ImGuiSelectionBasicStorage selections_data[SCOPES_COUNT];

            // 使用 ImGuiMultiSelectFlags_ScopeRect 不影响同一窗口中的其他选择.
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ScopeRect | ImGuiMultiSelectFlags_ClearOnEscape;// | ImGuiMultiSelectFlags_ClearOnClickVoid;
            if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeWindow", &flags, ImGuiMultiSelectFlags_ScopeWindow) && (flags & ImGuiMultiSelectFlags_ScopeWindow))
                flags &= ~ImGuiMultiSelectFlags_ScopeRect;
            if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeRect", &flags, ImGuiMultiSelectFlags_ScopeRect) && (flags & ImGuiMultiSelectFlags_ScopeRect))
                flags &= ~ImGuiMultiSelectFlags_ScopeWindow;
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnClickVoid", &flags, ImGuiMultiSelectFlags_ClearOnClickVoid);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect1d", &flags, ImGuiMultiSelectFlags_BoxSelect1d);

            for (int selection_scope_n = 0; selection_scope_n < SCOPES_COUNT; selection_scope_n++)
            {
                ImGui::PushID(selection_scope_n);
                ImGuiSelectionBasicStorage* selection = &selections_data[selection_scope_n];
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection->Size, ITEMS_COUNT);
                selection->ApplyRequests(ms_io);

                ImGui::SeparatorText(u8"选择范围");
                ImGui::Text(u8"选择大小: %d/%d", selection->Size, ITEMS_COUNT);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, u8"对象 %05d: %s", n, ExampleNames[n % IM_ARRAYSIZE(ExampleNames)]);
                    bool item_is_selected = selection->Contains((ImGuiID)n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                }

                // 应用多选请求
                ms_io = ImGui::EndMultiSelect();
                selection->ApplyRequests(ms_io);
                ImGui::PopID();
            }
            ImGui::TreePop();
        }

        // 参见 ShowExampleAppAssetsBrowser()
        if (ImGui::TreeNode(u8"多选 (平铺资源浏览器)"))
        {
            ImGui::Checkbox(u8"资源浏览器", &demo_data->ShowAppAssetsBrowser);
            ImGui::Text(u8"(也可从菜单中的 '示例->资源浏览器' 访问)");
            ImGui::TreePop();
        }

        // 演示在树中支持多选.
        // - 我们不使用线性索引作为选择用户数据，而是直接使用我们的 ExampleTreeNode* 指针!
        //   这展示了 SetNextItemSelectionUserData() 从不假设索引!
        // - 这里的困难是从 RangeSrcItem 到 RangeDstItem 在 SetAll/SetRange 请求中"插值".
        //   我们希望这种插值匹配用户看到的：按可见顺序，跳过关闭的节点.
        //   这是由我们的 TreeGetNextNodeInVisibleOrder() 用户空间辅助器实现的.
        // - 重要：在旨在实现具有自定义过滤器的全功能可选树的真实代码库中，您
        //   更可能构建一个将顺序索引映射到可见树节点的数组，因为您的
        //   过滤/搜索 + 裁剪过程将从中受益.拥有这个将使这种插值更容易.
        // - 将此视为原型：我们正在努力简化其中的一些.
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (树)");
        if (ImGui::TreeNode(u8"多选 (树)"))
        {
            HelpMarker(
                u8"这相当高级和实验性.如果您刚开始使用多选，"
                u8"请不要从查看如何将其用于树开始!\n\n"
                u8"未来版本将尝试简化并形式化其中一些内容.");

            struct ExampleTreeFuncs
            {
                static void DrawNode(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection)
                {
                    ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                    tree_node_flags |= ImGuiTreeNodeFlags_NavLeftJumpsToParent; // Enable pressing left to jump to parent
                    if (node->Childs.Size == 0)
                        tree_node_flags |= ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_Leaf;
                    if (selection->Contains((ImGuiID)node->UID))
                        tree_node_flags |= ImGuiTreeNodeFlags_Selected;

                    // Using SetNextItemStorageID() to specify storage id, so we can easily peek into
                    // the storage holding open/close stage, using our TreeNodeGetOpen/TreeNodeSetOpen() functions.
                    ImGui::SetNextItemSelectionUserData((ImGuiSelectionUserData)(intptr_t)node);
                    ImGui::SetNextItemStorageID((ImGuiID)node->UID);
                    if (ImGui::TreeNodeEx(node->Name, tree_node_flags))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            DrawNode(child, selection);
                        ImGui::TreePop();
                    }
                    else if (ImGui::IsItemToggledOpen())
                    {
                        TreeCloseAndUnselectChildNodes(node, selection);
                    }
                }

                static bool TreeNodeGetOpen(ExampleTreeNode* node)
                {
                    return ImGui::GetStateStorage()->GetBool((ImGuiID)node->UID);
                }

                static void TreeNodeSetOpen(ExampleTreeNode* node, bool open)
                {
                    ImGui::GetStateStorage()->SetBool((ImGuiID)node->UID, open);
                }

                // When closing a node: 1) close and unselect all child nodes, 2) select parent if any child was selected.
                // FIXME: This is currently handled by user logic but I'm hoping to eventually provide tree node
                // features to do this automatically, e.g. a ImGuiTreeNodeFlags_AutoCloseChildNodes etc.
                static int TreeCloseAndUnselectChildNodes(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection, int depth = 0)
                {
                    // Recursive close (the test for depth == 0 is because we call this on a node that was just closed!)
                    int unselected_count = selection->Contains((ImGuiID)node->UID) ? 1 : 0;
                    if (depth == 0 || TreeNodeGetOpen(node))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            unselected_count += TreeCloseAndUnselectChildNodes(child, selection, depth + 1);
                        TreeNodeSetOpen(node, false);
                    }

                    // Select root node if any of its child was selected, otherwise unselect
                    selection->SetItemSelected((ImGuiID)node->UID, (depth == 0 && unselected_count > 0));
                    return unselected_count;
                }

                // Apply multi-selection requests
                static void ApplySelectionRequests(ImGuiMultiSelectIO* ms_io, ExampleTreeNode* tree, ImGuiSelectionBasicStorage* selection)
                {
                    for (ImGuiSelectionRequest& req : ms_io->Requests)
                    {
                        if (req.Type == ImGuiSelectionRequestType_SetAll)
                        {
                            if (req.Selected)
                                TreeSetAllInOpenNodes(tree, selection, req.Selected);
                            else
                                selection->Clear();
                        }
                        else if (req.Type == ImGuiSelectionRequestType_SetRange)
                        {
                            ExampleTreeNode* first_node = (ExampleTreeNode*)(intptr_t)req.RangeFirstItem;
                            ExampleTreeNode* last_node = (ExampleTreeNode*)(intptr_t)req.RangeLastItem;
                            for (ExampleTreeNode* node = first_node; node != NULL; node = TreeGetNextNodeInVisibleOrder(node, last_node))
                                selection->SetItemSelected((ImGuiID)node->UID, req.Selected);
                        }
                    }
                }

                static void TreeSetAllInOpenNodes(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection, bool selected)
                {
                    if (node->Parent != NULL) // Root node isn't visible nor selectable in our scheme
                        selection->SetItemSelected((ImGuiID)node->UID, selected);
                    if (node->Parent == NULL || TreeNodeGetOpen(node))
                        for (ExampleTreeNode* child : node->Childs)
                            TreeSetAllInOpenNodes(child, selection, selected);
                }

                // Interpolate in *user-visible order* AND only *over opened nodes*.
                // If you have a sequential mapping tables (e.g. generated after a filter/search pass) this would be simpler.
                // Here the tricks are that:
                // - we store/maintain ExampleTreeNode::IndexInParent which allows implementing a linear iterator easily, without searches, without recursion.
                //   this could be replaced by a search in parent, aka 'int index_in_parent = curr_node->Parent->Childs.find_index(curr_node)'
                //   which would only be called when crossing from child to a parent, aka not too much.
                // - we call SetNextItemStorageID() before our TreeNode() calls with an ID which doesn't relate to UI stack,
                //   making it easier to call TreeNodeGetOpen()/TreeNodeSetOpen() from any location.
                static ExampleTreeNode* TreeGetNextNodeInVisibleOrder(ExampleTreeNode* curr_node, ExampleTreeNode* last_node)
                {
                    // Reached last node
                    if (curr_node == last_node)
                        return NULL;

                    // Recurse into childs. Query storage to tell if the node is open.
                    if (curr_node->Childs.Size > 0 && TreeNodeGetOpen(curr_node))
                        return curr_node->Childs[0];

                    // Next sibling, then into our own parent
                    while (curr_node->Parent != NULL)
                    {
                        if (curr_node->IndexInParent + 1 < curr_node->Parent->Childs.Size)
                            return curr_node->Parent->Childs[curr_node->IndexInParent + 1];
                        curr_node = curr_node->Parent;
                    }
                    return NULL;
                }

            }; // ExampleTreeFuncs

            static ImGuiSelectionBasicStorage selection;
            if (demo_data->DemoTree == NULL)
                demo_data->DemoTree = ExampleTree_CreateDemoTree(); // Create tree once
            ImGui::Text(u8"选择大小: %d", selection.Size);

            if (ImGui::BeginChild("##Tree", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ExampleTreeNode* tree = demo_data->DemoTree;
                ImGuiMultiSelectFlags ms_flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect2d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(ms_flags, selection.Size, -1);
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
                for (ExampleTreeNode* node : tree->Childs)
                    ExampleTreeFuncs::DrawNode(node, &selection);
                ms_io = ImGui::EndMultiSelect();
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
            }
            ImGui::EndChild();

            ImGui::TreePop();
        }

        // BeginMultiSelect() 的高级演示
        // - 展示裁剪.
        // - 展示删除.
        // - 展示基本拖放.
        // - 展示 TreeNode 变体（注意树节点在演示中不会展开：支持展开树节点 + 裁剪是另一回事）.
        // - 展示在表格中使用.
        IMGUI_DEMO_MARKER(u8"控件/选择状态/多选 (高级)");
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode(u8"多选 (高级)"))
        {
            // 选项
            enum WidgetType { WidgetType_Selectable, WidgetType_TreeNode };
            static bool use_clipper = true;
            static bool use_deletion = true;
            static bool use_drag_drop = true;
            static bool show_in_table = false;
            static bool show_color_button = true;
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
            static WidgetType widget_type = WidgetType_Selectable;

            if (ImGui::TreeNode(u8"选项"))
            {
                if (ImGui::RadioButton(u8"可选项目", widget_type == WidgetType_Selectable)) { widget_type = WidgetType_Selectable; }
                ImGui::SameLine();
                if (ImGui::RadioButton(u8"树节点", widget_type == WidgetType_TreeNode)) { widget_type = WidgetType_TreeNode; }
                ImGui::SameLine();
                HelpMarker(u8"TreeNode() 在技术上受支持，但...正确使用这个更复杂（您需要对树进行某种线性/随机访问，这适合已经实现过滤器和裁剪器的高级树设置.我们将努力简化并演示这个.\n\n目前树演示实际上有点无意义，因为它是一个只有根节点的空树.");
                ImGui::Checkbox(u8"启用裁剪器", &use_clipper);
                ImGui::Checkbox(u8"启用删除", &use_deletion);
                ImGui::Checkbox(u8"启用拖放", &use_drag_drop);
                ImGui::Checkbox(u8"在表格中显示", &show_in_table);
                ImGui::Checkbox(u8"显示颜色按钮", &show_color_button);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SingleSelect", &flags, ImGuiMultiSelectFlags_SingleSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoSelectAll", &flags, ImGuiMultiSelectFlags_NoSelectAll);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoRangeSelect", &flags, ImGuiMultiSelectFlags_NoRangeSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoSelect", &flags, ImGuiMultiSelectFlags_NoAutoSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClear", &flags, ImGuiMultiSelectFlags_NoAutoClear);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClearOnReselect", &flags, ImGuiMultiSelectFlags_NoAutoClearOnReselect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect1d", &flags, ImGuiMultiSelectFlags_BoxSelect1d);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect2d", &flags, ImGuiMultiSelectFlags_BoxSelect2d);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelectNoScroll", &flags, ImGuiMultiSelectFlags_BoxSelectNoScroll);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnEscape", &flags, ImGuiMultiSelectFlags_ClearOnEscape);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnClickVoid", &flags, ImGuiMultiSelectFlags_ClearOnClickVoid);
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeWindow", &flags, ImGuiMultiSelectFlags_ScopeWindow) && (flags & ImGuiMultiSelectFlags_ScopeWindow))
                    flags &= ~ImGuiMultiSelectFlags_ScopeRect;
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeRect", &flags, ImGuiMultiSelectFlags_ScopeRect) && (flags & ImGuiMultiSelectFlags_ScopeRect))
                    flags &= ~ImGuiMultiSelectFlags_ScopeWindow;
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SelectOnClick", &flags, ImGuiMultiSelectFlags_SelectOnClick) && (flags & ImGuiMultiSelectFlags_SelectOnClick))
                    flags &= ~ImGuiMultiSelectFlags_SelectOnClickRelease;
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SelectOnClickRelease", &flags, ImGuiMultiSelectFlags_SelectOnClickRelease) && (flags & ImGuiMultiSelectFlags_SelectOnClickRelease))
                    flags &= ~ImGuiMultiSelectFlags_SelectOnClick;
                ImGui::SameLine(); HelpMarker(u8"允许拖动未选中的项目而不改变选择.");
                ImGui::TreePop();
            }

            // 使用 1000 个项目初始化默认列表.
            // 使用默认选择.Adapter：将索引传递给 SetNextItemSelectionUserData()，将索引存储在 Selection 中
            static ImVector<int> items;
            static int items_next_id = 0;
            if (items_next_id == 0) { for (int n = 0; n < 1000; n++) { items.push_back(items_next_id++); } }
            static ExampleSelectionWithDeletion selection;
            static bool request_deletion_from_menu = false; // 从上下文菜单触发的排队删除

            ImGui::Text(u8"选择大小: %d/%d", selection.Size, items.Size);

            const float items_height = (widget_type == WidgetType_TreeNode) ? ImGui::GetTextLineHeight() : ImGui::GetTextLineHeightWithSpacing();
            ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImVec2 color_button_sz(ImGui::GetFontSize(), ImGui::GetFontSize());
                if (widget_type == WidgetType_TreeNode)
                    ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, 0.0f);

                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = (ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (selection.Size > 0)) || request_deletion_from_menu;
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;
                request_deletion_from_menu = false;

                if (show_in_table)
                {
                    if (widget_type == WidgetType_TreeNode)
                        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
                    ImGui::BeginTable("##Split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_NoPadOuterX);
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 0.70f);
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 0.30f);
                    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacingY, 0.0f);
                }

                ImGuiListClipper clipper;
                if (use_clipper)
                {
                    clipper.Begin(items.Size);
                    if (item_curr_idx_to_focus != -1)
                        clipper.IncludeItemByIndex(item_curr_idx_to_focus); // 确保聚焦的项目不被裁剪.
                    if (ms_io->RangeSrcItem != -1)
                        clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // 确保 RangeSrc 项目不被裁剪.
                }

                while (!use_clipper || clipper.Step())
                {
                    const int item_begin = use_clipper ? clipper.DisplayStart : 0;
                    const int item_end = use_clipper ? clipper.DisplayEnd : items.Size;
                    for (int n = item_begin; n < item_end; n++)
                    {
                        if (show_in_table)
                            ImGui::TableNextColumn();

                        const int item_id = items[n];
                        const char* item_category = ExampleNames[item_id % IM_ARRAYSIZE(ExampleNames)];
                        char label[64];
                        sprintf(label, u8"对象 %05d: %s", item_id, item_category);

                        // 重要：为了使删除重新聚焦工作，我们需要对象 ID 稳定，
                        // 即不依赖于它们在列表中的索引.这里我们使用持久的 item_id
                        // 而不是索引来构建一个将持续存在的唯一 ID.
                        // （如果我们使用 PushID(index) 代替，删除后焦点将无法正确恢复）.
                        ImGui::PushID(item_id);

                        // 发出一个颜色按钮，以测试 Shift+左箭头落在不属于
                        // 选择范围的项目上不会错误地改变我们的选择.
                        if (show_color_button)
                        {
                            ImU32 dummy_col = (ImU32)((unsigned int)n * 0xC250B74B) | IM_COL32_A_MASK;
                            ImGui::ColorButton("##", ImColor(dummy_col), ImGuiColorEditFlags_NoTooltip, color_button_sz);
                            ImGui::SameLine();
                        }

                        // 提交项目
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        bool item_is_open = false;
                        ImGui::SetNextItemSelectionUserData(n);
                        if (widget_type == WidgetType_Selectable)
                        {
                            ImGui::Selectable(label, item_is_selected, ImGuiSelectableFlags_None);
                        }
                        else if (widget_type == WidgetType_TreeNode)
                        {
                            ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                            if (item_is_selected)
                                tree_node_flags |= ImGuiTreeNodeFlags_Selected;
                            item_is_open = ImGui::TreeNodeEx(label, tree_node_flags);
                        }

                        // 聚焦（用于删除后）
                        if (item_curr_idx_to_focus == n)
                            ImGui::SetKeyboardFocusHere(-1);

                        // 拖放
                        if (use_drag_drop && ImGui::BeginDragDropSource())
                        {
                            // 创建包含完整选择 OR 单个未选中项目的有效负载.
                            // （后者仅在使用 ImGuiMultiSelectFlags_SelectOnClickRelease 时可能）
                            if (ImGui::GetDragDropPayload() == NULL)
                            {
                                ImVector<int> payload_items;
                                void* it = NULL;
                                ImGuiID id = 0;
                                if (!item_is_selected)
                                    payload_items.push_back(item_id);
                                else
                                    while (selection.GetNextSelectedItem(&it, &id))
                                        payload_items.push_back((int)id);
                                ImGui::SetDragDropPayload("MULTISELECT_DEMO_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
                            }

                            // 在工具提示中显示有效负载内容
                            const ImGuiPayload* payload = ImGui::GetDragDropPayload();
                            const int* payload_items = (int*)payload->Data;
                            const int payload_count = (int)payload->DataSize / (int)sizeof(int);
                            if (payload_count == 1)
                                ImGui::Text(u8"对象 %05d: %s", payload_items[0], ExampleNames[payload_items[0] % IM_ARRAYSIZE(ExampleNames)]);
                            else
                                ImGui::Text(u8"拖动 %d 个对象", payload_count);

                            ImGui::EndDragDropSource();
                        }

                        if (widget_type == WidgetType_TreeNode && item_is_open)
                            ImGui::TreePop();

                        // 右键点击：上下文菜单
                        if (ImGui::BeginPopupContextItem())
                        {
                            ImGui::BeginDisabled(!use_deletion || selection.Size == 0);
                            sprintf(label, u8"删除 %d 个项目###DeleteSelected", selection.Size);
                            if (ImGui::Selectable(label))
                                request_deletion_from_menu = true;
                            ImGui::EndDisabled();
                            ImGui::Selectable(u8"关闭");
                            ImGui::EndPopup();
                        }

                        // 表格中的演示内容
                        if (show_in_table)
                        {
                            ImGui::TableNextColumn();
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::InputText("###NoLabel", (char*)(void*)item_category, strlen(item_category), ImGuiInputTextFlags_ReadOnly);
                            ImGui::PopStyleVar();
                        }

                        ImGui::PopID();
                    }
                    if (!use_clipper)
                        break;
                }

                if (show_in_table)
                {
                    ImGui::EndTable();
                    if (widget_type == WidgetType_TreeNode)
                        ImGui::PopStyleVar();
                }

                // 应用多选请求
                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);

                if (widget_type == WidgetType_TreeNode)
                    ImGui::PopStyleVar();
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTabs()
//-----------------------------------------------------------------------------

static void EditTabBarFittingPolicyFlags(ImGuiTabBarFlags* p_flags)
{
    if ((*p_flags & ImGuiTabBarFlags_FittingPolicyMask_) == 0)
        *p_flags |= ImGuiTabBarFlags_FittingPolicyDefault_;
    if (ImGui::CheckboxFlags("ImGuiTabBarFlags_FittingPolicyMixed", p_flags, ImGuiTabBarFlags_FittingPolicyMixed))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyMixed);
    if (ImGui::CheckboxFlags("ImGuiTabBarFlags_FittingPolicyShrink", p_flags, ImGuiTabBarFlags_FittingPolicyShrink))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyShrink);
    if (ImGui::CheckboxFlags("ImGuiTabBarFlags_FittingPolicyScroll", p_flags, ImGuiTabBarFlags_FittingPolicyScroll))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyScroll);
}
static void DemoWindowWidgetsTabs()
{
    IMGUI_DEMO_MARKER(u8"控件/选项卡");
    if (ImGui::TreeNode(u8"选项卡"))
    {
        IMGUI_DEMO_MARKER(u8"控件/选项卡/基础");
        if (ImGui::TreeNode(u8"基础"))
        {
            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                if (ImGui::BeginTabItem(u8"牛油果"))
                {
                    ImGui::Text(u8"这是牛油果选项卡!\n等等等等等等");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(u8"西兰花"))
                {
                    ImGui::Text(u8"这是西兰花选项卡!\n等等等等等等");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(u8"黄瓜"))
                {
                    ImGui::Text(u8"这是黄瓜选项卡!\n等等等等等等");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::Separator();
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/选项卡/高级和关闭按钮");
        if (ImGui::TreeNode(u8"高级和关闭按钮"))
        {
            // 暴露一些可用标志.在大多数情况下，您可能只需调用无标志 (0) 的 BeginTabBar().
            static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
            ImGui::CheckboxFlags("ImGuiTabBarFlags_Reorderable", &tab_bar_flags, ImGuiTabBarFlags_Reorderable);
            ImGui::CheckboxFlags("ImGuiTabBarFlags_AutoSelectNewTabs", &tab_bar_flags, ImGuiTabBarFlags_AutoSelectNewTabs);
            ImGui::CheckboxFlags("ImGuiTabBarFlags_TabListPopupButton", &tab_bar_flags, ImGuiTabBarFlags_TabListPopupButton);
            ImGui::CheckboxFlags("ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", &tab_bar_flags, ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
            ImGui::CheckboxFlags("ImGuiTabBarFlags_DrawSelectedOverline", &tab_bar_flags, ImGuiTabBarFlags_DrawSelectedOverline);
            EditTabBarFittingPolicyFlags(&tab_bar_flags);

            // 选项卡栏
            ImGui::AlignTextToFramePadding();
            ImGui::Text(u8"已打开:");
            const char* names[4] = { u8"洋蓟", u8"甜菜根", u8"芹菜", u8"白萝卜" };
            static bool opened[4] = { true, true, true, true }; // 持久用户状态
            for (int n = 0; n < IM_ARRAYSIZE(opened); n++)
            {
                ImGui::SameLine();
                ImGui::Checkbox(names[n], &opened[n]);
            }

            // 将 bool* 传递给 BeginTabItem() 类似于传递给 Begin()：
            // 当选项卡关闭时，底层布尔值将被设置为 false.
            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                for (int n = 0; n < IM_ARRAYSIZE(opened); n++)
                    if (opened[n] && ImGui::BeginTabItem(names[n], &opened[n], ImGuiTabItemFlags_None))
                    {
                        ImGui::Text(u8"这是 %s 选项卡!", names[n]);
                        if (n & 1)
                            ImGui::Text(u8"我是一个奇数选项卡.");
                        ImGui::EndTabItem();
                    }
                ImGui::EndTabBar();
            }
            ImGui::Separator();
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/选项卡/TabItemButton 和前导/后置标志");
        if (ImGui::TreeNode(u8"TabItemButton 和前导/后置标志"))
        {
            static ImVector<int> active_tabs;
            static int next_tab_id = 0;
            if (next_tab_id == 0) // 用一些默认选项卡初始化
                for (int i = 0; i < 3; i++)
                    active_tabs.push_back(next_tab_id++);

            // TabItemButton() 和前导/后置标志是不同的功能，我们将一起演示.
            // （可以提交带有前导/后置标志的常规选项卡，或者没有前导/后置标志的 TabItemButton 选项卡...
            // 但它们在一起往往更有意义）
            static bool show_leading_button = true;
            static bool show_trailing_button = true;
            ImGui::Checkbox(u8"显示前导 TabItemButton()", &show_leading_button);
            ImGui::Checkbox(u8"显示后置 TabItemButton()", &show_trailing_button);

            // 暴露一些其他标志，这些标志有助于展示它们如何与前导/后置选项卡交互
            static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyShrink;
            EditTabBarFittingPolicyFlags(&tab_bar_flags);

            if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
            {
                // 演示前导 TabItemButton()：点击"?"按钮打开菜单
                if (show_leading_button)
                    if (ImGui::TabItemButton("?", ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_NoTooltip))
                        ImGui::OpenPopup("MyHelpMenu");
                if (ImGui::BeginPopup("MyHelpMenu"))
                {
                    ImGui::Selectable(u8"你好!");
                    ImGui::EndPopup();
                }

                // 演示后置选项卡：点击"+"按钮添加新选项卡.
                // （在您的应用程序中，您可能希望使用字体图标而不是"+"）
                // 我们在常规选项卡之前提交它，但由于 ImGuiTabItemFlags_Trailing 标志，它将始终出现在末尾.
                if (show_trailing_button)
                    if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
                        active_tabs.push_back(next_tab_id++); // 添加新选项卡

                // 提交我们的常规选项卡
                for (int n = 0; n < active_tabs.Size; )
                {
                    bool open = true;
                    char name[16];
                    snprintf(name, IM_ARRAYSIZE(name), "%04d", active_tabs[n]);
                    if (ImGui::BeginTabItem(name, &open, ImGuiTabItemFlags_None))
                    {
                        ImGui::Text(u8"这是 %s 选项卡!", name);
                        ImGui::EndTabItem();
                    }

                    if (!open)
                        active_tabs.erase(active_tabs.Data + n);
                    else
                        n++;
                }

                ImGui::EndTabBar();
            }
            ImGui::Separator();
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsText()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsText()
{
    IMGUI_DEMO_MARKER(u8"控件/文本");
    if (ImGui::TreeNode(u8"文本"))
    {
        IMGUI_DEMO_MARKER(u8"控件/文本/彩色文本");
        if (ImGui::TreeNode(u8"彩色文本"))
        {
            // 使用快捷方式.您可以使用 PushStyleColor()/PopStyleColor() 获得更大的灵活性.
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), u8"粉色");
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), u8"黄色");
            ImGui::TextDisabled(u8"禁用");
            ImGui::SameLine(); HelpMarker(u8"TextDisabled 颜色存储在 ImGuiStyle 中.");
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本/字体大小");
        if (ImGui::TreeNode(u8"字体大小"))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            const float global_scale = style.FontScaleMain * style.FontScaleDpi;
            ImGui::Text("style.FontScaleMain = %0.2f", style.FontScaleMain);
            ImGui::Text("style.FontScaleDpi = %0.2f", style.FontScaleDpi);
            ImGui::Text(u8"global_scale = ~%0.2f", global_scale); // 这在技术上不准确，因为可能应用内部缩放，但概念上让我们假装它是准确的.
            ImGui::Text(u8"FontSize = %0.2f", ImGui::GetFontSize());

            ImGui::SeparatorText("");
            static float custom_size = 16.0f;
            ImGui::SliderFloat("custom_size", &custom_size, 10.0f, 100.0f, "%.0f");
            ImGui::Text("ImGui::PushFont(nullptr, custom_size);");
            ImGui::PushFont(NULL, custom_size);
            ImGui::Text(u8"FontSize = %.2f (== %.2f * global_scale)", ImGui::GetFontSize(), custom_size);
            ImGui::PopFont();

            ImGui::SeparatorText("");
            static float custom_scale = 1.0f;
            ImGui::SliderFloat("custom_scale", &custom_scale, 0.5f, 4.0f, "%.2f");
            ImGui::Text("ImGui::PushFont(nullptr, style.FontSizeBase * custom_scale);");
            ImGui::PushFont(NULL, style.FontSizeBase * custom_scale);
            ImGui::Text(u8"FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", ImGui::GetFontSize(), custom_scale);
            ImGui::PopFont();

            ImGui::SeparatorText("");
            for (float scaling = 0.5f; scaling <= 4.0f; scaling += 0.5f)
            {
                ImGui::PushFont(NULL, style.FontSizeBase * scaling);
                ImGui::Text(u8"FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", ImGui::GetFontSize(), scaling);
                ImGui::PopFont();
            }

            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本/单词换行");
        if (ImGui::TreeNode(u8"单词换行"))
        {
            // 使用快捷方式.您可以使用 PushTextWrapPos()/PopTextWrapPos() 获得更大的灵活性.
            ImGui::TextWrapped(
                u8"此文本应自动在窗口边缘换行.当前的文本换行实现"
                u8"遵循适用于英语和可能其他语言的简单规则.");
            ImGui::Spacing();

            static float wrap_width = 200.0f;
            ImGui::SliderFloat(u8"换行宽度", &wrap_width, -20, 600, "%.0f");

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            for (int n = 0; n < 2; n++)
            {
                ImGui::Text(u8"测试段落 %d:", n);
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImVec2 marker_min = ImVec2(pos.x + wrap_width, pos.y);
                ImVec2 marker_max = ImVec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight());
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
                if (n == 0)
                    ImGui::Text(u8"懒狗是好狗.此段落应适应 %.0f 像素内.测试一个 1 字符的单词.敏捷的棕色狐狸跳过懒狗.", wrap_width);
                else
                    ImGui::Text(u8"aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");

                // 绘制实际文本边界框，后面是我们预期限制的标记（不应重叠!）
                draw_list->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
                draw_list->AddRectFilled(marker_min, marker_max, IM_COL32(255, 0, 255, 255));
                ImGui::PopTextWrapPos();
            }

            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本/UTF-8 文本");
        if (ImGui::TreeNode(u8"UTF-8 文本"))
        {
            // 带有日文字符的 UTF-8 测试
            // （需要合适的字体?尝试"Google Noto"或"Arial Unicode".详情请参阅 docs/FONTS.md.）
            // - 从 C++11 开始，您可以使用 u8"我的文本"语法将文字字符串编码为 UTF-8
            // - 对于早期编译器，您可以将源代码编码为 UTF-8（例如在 Visual Studio 中，您
            //   可以将源文件保存为'无签名的 UTF-8'）.
            // - 仅对于此演示文件，因为我们想支持旧编译器，我们*不*在此源文件中包含原始 UTF-8
            //   字符.相反，我们使用十六进制常量编码一些字符串.
            //   不要在您的应用程序中这样做!请在您的应用程序中使用 u8"任何语言的文本"!
            // 请注意，如果字体无法显示，字符值甚至由 InputText() 保留，
            // 因此您可以安全地将乱码字符复制并粘贴到另一个应用程序中.
            ImGui::TextWrapped(
                u8"CJK 文本仅在字体加载了适当的 CJK 字符范围时才会出现."
                u8"手动调用 io.Fonts->AddFontFromFileTTF() 以加载额外的字符范围."
                u8"详情请参阅 docs/FONTS.md.");
            ImGui::Text(u8"平假名: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
            ImGui::Text(u8"汉字: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
            static char buf[37] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
            //static char buf[32] = u8"NIHONGO"; // <- 这是您使用 C++11 编写的方式，使用真实的汉字
            ImGui::InputText(u8"UTF-8 输入", buf, IM_ARRAYSIZE(buf));
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextFilter()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextFilter()
{
    IMGUI_DEMO_MARKER(u8"控件/文本过滤器");
    if (ImGui::TreeNode(u8"文本过滤器"))
    {
        // 用于轻松设置文本过滤器的辅助类.
        // 您可能希望在您自己的应用程序中实现更功能齐全的过滤方案.
        HelpMarker(u8"本身不是控件，但 ImGuiTextFilter 是一个辅助程序，用于对文本字符串执行简单过滤.");
        static ImGuiTextFilter filter;
        ImGui::Text(u8"过滤器用法:\n"
            u8"  \"\"         显示所有行\n"
            u8"  \"xxx\"      显示包含 \"xxx\" 的行\n"
            u8"  \"xxx,yyy\"  显示包含 \"xxx\" 或 \"yyy\" 的行\n"
            u8"  \"-xxx\"     隐藏包含 \"xxx\" 的行");
        filter.Draw();
        const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
        for (int i = 0; i < IM_ARRAYSIZE(lines); i++)
            if (filter.PassFilter(lines[i]))
                ImGui::BulletText("%s", lines[i]);
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextInput()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextInput()
{
    // 要将 InputText() 与 std::string 或任何其他自定义字符串类型连接，
    // 请参见本演示的"文本输入 > 调整大小回调"部分，以及 misc/cpp/imgui_stdlib.h 文件.
    IMGUI_DEMO_MARKER(u8"控件/文本输入");
    if (ImGui::TreeNode(u8"文本输入"))
    {
        IMGUI_DEMO_MARKER(u8"控件/文本输入/多行文本输入");
        if (ImGui::TreeNode(u8"多行文本输入"))
        {
            // 注意：为简单起见，我们在这里使用固定大小的缓冲区.请参见 ImGuiInputTextFlags_CallbackResize
            // 和 misc/cpp/imgui_stdlib.h 中的代码，了解如何为动态调整大小的字符串设置 InputText().
            static char text[1024 * 16] =
                "/*\n"
                "/*\n"
                u8" Pentium F00F 漏洞，简称 F0 0F C7 C8，\n"
                u8" 是一条问题指令的十六进制编码，\n"
                u8" 更正式地说，是带有锁定 CMPXCHG8B 的无效操作数\n"
                u8" 指令错误，是大多数 Intel Pentium、Pentium MMX\n"
                u8" 和 Pentium OverDrive 处理器（所有基于 P5 微架构）\n"
                u8" 中的一个设计缺陷.\n"
                "*/\n\n"
                u8"标签:\n"
                u8"\t锁定 cmpxchg8b eax\n";

            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
            HelpMarker(u8"如果您需要将 InputTextMultiline() 连接到动态字符串类型，可以使用 ImGuiInputTextFlags_CallbackResize 功能.请参见 misc/cpp/imgui_stdlib.h 中的示例.（这未在 imgui_demo.cpp 中演示，因为我们不想在这里包含 <string>）");
            ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly", &flags, ImGuiInputTextFlags_ReadOnly);
            ImGui::CheckboxFlags("ImGuiInputTextFlags_AllowTabInput", &flags, ImGuiInputTextFlags_AllowTabInput);
            ImGui::SameLine(); HelpMarker(u8"当设置 _AllowTabInput 时，使用 Tab 键通过控件不会自动激活它，以便也循环通过后续控件.");
            ImGui::CheckboxFlags("ImGuiInputTextFlags_CtrlEnterForNewLine", &flags, ImGuiInputTextFlags_CtrlEnterForNewLine);
            ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/过滤文本输入");
        if (ImGui::TreeNode(u8"过滤文本输入"))
        {
            struct TextFilters
            {
                // 通过更改 'data->Eventchar' 修改字符输入（ImGuiInputTextFlags_CallbackCharFilter 回调）
                static int FilterCasingSwap(ImGuiInputTextCallbackData* data)
                {
                    if (data->EventChar >= 'a' && data->EventChar <= 'z') { data->EventChar -= 'a' - 'A'; } // 小写变为大写
                    else if (data->EventChar >= 'A' && data->EventChar <= 'Z') { data->EventChar += 'a' - 'A'; } // 大写变为小写
                    return 0;
                }

                // 如果字符是 'i' 或 'm' 或 'g' 或 'u' 或 'i'，则返回 0（通过），否则返回 1（过滤掉）
                static int FilterImGuiLetters(ImGuiInputTextCallbackData* data)
                {
                    if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar))
                        return 0;
                    return 1;
                }
            };

            static char buf1[32] = ""; ImGui::InputText(u8"默认", buf1, IM_ARRAYSIZE(buf1));
            static char buf2[32] = ""; ImGui::InputText(u8"十进制", buf2, IM_ARRAYSIZE(buf2), ImGuiInputTextFlags_CharsDecimal);
            static char buf3[32] = ""; ImGui::InputText(u8"十六进制", buf3, IM_ARRAYSIZE(buf3), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            static char buf4[32] = ""; ImGui::InputText(u8"大写", buf4, IM_ARRAYSIZE(buf4), ImGuiInputTextFlags_CharsUppercase);
            static char buf5[32] = ""; ImGui::InputText(u8"无空白", buf5, IM_ARRAYSIZE(buf5), ImGuiInputTextFlags_CharsNoBlank);
            static char buf6[32] = ""; ImGui::InputText(u8"大小写交换", buf6, IM_ARRAYSIZE(buf6), ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterCasingSwap); // 使用 CharFilter 回调替换字符.
            static char buf7[32] = ""; ImGui::InputText(u8"\"imgui\"", buf7, IM_ARRAYSIZE(buf7), ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters); // 使用 CharFilter 回调禁用某些字符.
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/密码输入");
        if (ImGui::TreeNode(u8"密码输入"))
        {
            static char password[64] = "password123";
            ImGui::InputText(u8"密码", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
            ImGui::SameLine(); HelpMarker(u8"将所有字符显示为 '*'.\n禁用剪贴板剪切和复制.\n禁用日志记录.\n");
            ImGui::InputTextWithHint(u8"密码 (带提示)", "<password>", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);
            ImGui::InputText(u8"密码 (清除)", password, IM_ARRAYSIZE(password));
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/完成, 历史, 编辑回调");
        if (ImGui::TreeNode(u8"完成, 历史, 编辑回调"))
        {
            struct Funcs
            {
                static int MyCallback(ImGuiInputTextCallbackData* data)
                {
                    if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
                    {
                        data->InsertChars(data->CursorPos, "..");
                    }
                    else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
                    {
                        if (data->EventKey == ImGuiKey_UpArrow)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, u8"按了上箭头!");
                            data->SelectAll();
                        }
                        else if (data->EventKey == ImGuiKey_DownArrow)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, u8"按了下箭头!");
                            data->SelectAll();
                        }
                    }
                    else if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
                    {
                        // 切换第一个字符的大小写
                        char c = data->Buf[0];
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) data->Buf[0] ^= 32;
                        data->BufDirty = true;

                        // 递增计数器
                        int* p_int = (int*)data->UserData;
                        *p_int = *p_int + 1;
                    }
                    return 0;
                }
            };
            static char buf1[64];
            ImGui::InputText(u8"完成", buf1, IM_ARRAYSIZE(buf1), ImGuiInputTextFlags_CallbackCompletion, Funcs::MyCallback);
            ImGui::SameLine(); HelpMarker(
                u8"这里我们在每次按下 Tab 时附加 \"..\"."
                u8"请参见 '示例>控制台' 以获取使用此回调的更有意义的演示.");

            static char buf2[64];
            ImGui::InputText(u8"历史", buf2, IM_ARRAYSIZE(buf2), ImGuiInputTextFlags_CallbackHistory, Funcs::MyCallback);
            ImGui::SameLine(); HelpMarker(
                u8"这里我们在每次按下上/下箭头时替换和选择文本."
                u8"请参见 '示例>控制台' 以获取使用此回调的更有意义的演示.");

            static char buf3[64];
            static int edit_count = 0;
            ImGui::InputText(u8"编辑", buf3, IM_ARRAYSIZE(buf3), ImGuiInputTextFlags_CallbackEdit, Funcs::MyCallback, (void*)&edit_count);
            ImGui::SameLine(); HelpMarker(
                u8"这里我们在每次编辑时切换第一个字符的大小写 + 计数编辑.");
            ImGui::SameLine(); ImGui::Text("(%d)", edit_count);

            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/调整大小回调");
        if (ImGui::TreeNode(u8"调整大小回调"))
        {
            // 要将 InputText() 与 std::string 或任何其他自定义字符串类型连接，
            // 您可以使用 ImGuiInputTextFlags_CallbackResize 标志 + 使用您首选的类型创建自定义 ImGui::InputText() 包装器
            // 请参见 misc/cpp/imgui_stdlib.h 中使用 std::string 的实现.
            HelpMarker(
                u8"使用 ImGuiInputTextFlags_CallbackResize 将您的自定义字符串类型连接到 InputText().\n\n"
                u8"请参见 misc/cpp/imgui_stdlib.h 中针对 std::string 的实现.");
            struct Funcs
            {
                static int MyResizeCallback(ImGuiInputTextCallbackData* data)
                {
                    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
                    {
                        ImVector<char>* my_str = (ImVector<char>*)data->UserData;
                        IM_ASSERT(my_str->begin() == data->Buf);
                        my_str->resize(data->BufSize); // 注意：在调整大小调用时，通常 data->BufSize == data->BufTextLen + 1
                        data->Buf = my_str->begin();
                    }
                    return 0;
                }

                // 注意：因为 ImGui:: 是一个命名空间，您通常会将您自己的函数添加到命名空间中.
                // 例如，您的代码可能声明一个函数 'ImGui::InputText(const char* label, MyString* my_str)'
                static bool MyInputTextMultiline(const char* label, ImVector<char>* my_str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0)
                {
                    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
                    return ImGui::InputTextMultiline(label, my_str->begin(), (size_t)my_str->size(), size, flags | ImGuiInputTextFlags_CallbackResize, Funcs::MyResizeCallback, (void*)my_str);
                }
            };

            // 对于此演示，我们使用 ImVector 作为字符串容器.
            // 请注意，因为我们需要存储一个终止零字符，我们的 size/capacity 比典型字符串类通常报告的多 1.
            static ImVector<char> my_str;
            if (my_str.empty())
                my_str.push_back(0);
            Funcs::MyInputTextMultiline("##MyStr", &my_str, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
            ImGui::Text(u8"数据: %p\n大小: %d\n容量: %d", (void*)my_str.begin(), my_str.size(), my_str.capacity());
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/省略, 对齐");
        if (ImGui::TreeNode(u8"省略, 对齐"))
        {
            static char buf1[128] = "/path/to/some/folder/with/long/filename.cpp";
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_ElideLeft;
            ImGui::CheckboxFlags("ImGuiInputTextFlags_ElideLeft", &flags, ImGuiInputTextFlags_ElideLeft);
            ImGui::InputText(u8"路径", buf1, IM_ARRAYSIZE(buf1), flags);
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/文本输入/杂项");
        if (ImGui::TreeNode(u8"杂项"))
        {
            static char buf1[16];
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EscapeClearsAll;
            ImGui::CheckboxFlags("ImGuiInputTextFlags_EscapeClearsAll", &flags, ImGuiInputTextFlags_EscapeClearsAll);
            ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly", &flags, ImGuiInputTextFlags_ReadOnly);
            ImGui::CheckboxFlags("ImGuiInputTextFlags_NoUndoRedo", &flags, ImGuiInputTextFlags_NoUndoRedo);
            ImGui::InputText(u8"你好", buf1, IM_ARRAYSIZE(buf1), flags);
            ImGui::TreePop();
        }

        ImGui::TreePop();
    }

}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTooltips()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTooltips()
{
    IMGUI_DEMO_MARKER(u8"控件/工具提示");
    if (ImGui::TreeNode(u8"工具提示"))
    {
        // 工具提示是跟随鼠标的窗口.它们不会夺走焦点.
        ImGui::SeparatorText(u8"常规");

        // 典型用例：
        // - 短格式（仅文本）：      SetItemTooltip("Hello");
        // - 短格式（任何内容）：   if (BeginItemTooltip()) { Text("Hello"); EndTooltip(); }

        // - 完整格式（仅文本）：       if (IsItemHovered(...)) { SetTooltip("Hello"); }
        // - 完整格式（任何内容）：    if (IsItemHovered(...) && BeginTooltip()) { Text("Hello"); EndTooltip(); }

        HelpMarker(
            u8"工具提示通常通过使用 IsItemHovered() + SetTooltip() 序列创建.\n\n"
            u8"我们提供了一个辅助函数 SetItemTooltip() 来使用标准标志执行这两个操作.");

        ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);

        ImGui::Button(u8"基础", sz);
        ImGui::SetItemTooltip(u8"我是一个工具提示");

        ImGui::Button(u8"花哨", sz);
        if (ImGui::BeginItemTooltip())
        {
            ImGui::Text(u8"我是一个花哨的工具提示");
            static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
            ImGui::PlotLines(u8"曲线", arr, IM_ARRAYSIZE(arr));
            ImGui::Text(u8"Sin(time) = %f", sinf((float)ImGui::GetTime()));
            ImGui::EndTooltip();
        }

        ImGui::SeparatorText(u8"始终开启");

        // 展示不依赖 IsItemHovered() 来发出工具提示.
        // 这里当 'always_on == true' 时，工具提示始终发出.
        static int always_on = 0;
        ImGui::RadioButton(u8"关闭", &always_on, 0);
        ImGui::SameLine();
        ImGui::RadioButton(u8"始终开启 (简单)", &always_on, 1);
        ImGui::SameLine();
        ImGui::RadioButton(u8"始终开启 (高级)", &always_on, 2);
        if (always_on == 1)
            ImGui::SetTooltip(u8"我跟着你到处走.");
        else if (always_on == 2 && ImGui::BeginTooltip())
        {
            ImGui::ProgressBar(sinf((float)ImGui::GetTime()) * 0.5f + 0.5f, ImVec2(ImGui::GetFontSize() * 25, 0.0f));
            ImGui::EndTooltip();
        }

        ImGui::SeparatorText(u8"自定义");

        HelpMarker(
            u8"将 ImGuiHoveredFlags_ForTooltip 传递给 IsItemHovered() 是标准化"
            u8"工具提示激活细节的首选方式.然而，您可能决定为特定工具提示实例使用自定义"
            u8"标志.");

        // 以下示例用于文档目的，但可能对大多数用户无用.
        // 将 ImGuiHoveredFlags_ForTooltip 传递给 IsItemHovered() 将从
        // 'style.HoverFlagsForTooltipMouse' 或 'style.HoverFlagsForTooltipNav' 拉取 ImGuiHoveredFlags 标志值，具体取决于使用的是鼠标还是键盘/游戏手柄.
        // 使用默认设置，ImGuiHoveredFlags_ForTooltip 等同于 ImGuiHoveredFlags_DelayShort + ImGuiHoveredFlags_Stationary.
        ImGui::Button(u8"手动", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
            ImGui::SetTooltip(u8"我是一个手动发出的工具提示.");

        ImGui::Button(u8"无延迟", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone))
            ImGui::SetTooltip(u8"我是一个无延迟的工具提示.");

        ImGui::Button(u8"短延迟", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay))
            ImGui::SetTooltip(u8"我是一个有短延迟的工具提示 (%0.2f 秒).", ImGui::GetStyle().HoverDelayShort);

        ImGui::Button(u8"长延迟", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay))
            ImGui::SetTooltip(u8"我是一个有长延迟的工具提示 (%0.2f 秒).", ImGui::GetStyle().HoverDelayNormal);

        ImGui::Button(u8"静止", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
            ImGui::SetTooltip(u8"我是一个要求鼠标在激活前保持静止的工具提示.");

        // 使用 ImGuiHoveredFlags_ForTooltip 将从 'style.HoverFlagsForTooltipMouse' 或 'style.HoverFlagsForTooltipNav' 拉取标志，
        // 默认值包括 ImGuiHoveredFlags_AllowWhenDisabled 标志.
        ImGui::BeginDisabled();
        ImGui::Button(u8"禁用项目", sz);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_ForTooltip))
            ImGui::SetTooltip(u8"我是一个用于禁用项目的工具提示.");
        ImGui::EndDisabled();

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTreeNodes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTreeNodes()
{
    IMGUI_DEMO_MARKER(u8"控件/树节点");
    if (ImGui::TreeNode(u8"树节点"))
    {
        // 请参见"示例 -> 属性编辑器"（ShowExampleAppPropertyEditor() 函数）以获取更花哨的、数据驱动的树.
        IMGUI_DEMO_MARKER(u8"控件/树节点/基础树");
        if (ImGui::TreeNode(u8"基础树"))
        {
            for (int i = 0; i < 5; i++)
            {
                // 使用 SetNextItemOpen() 以便将节点的默认状态设置为打开.我们也可以
                // 使用带有 ImGuiTreeNodeFlags_DefaultOpen 标志的 TreeNodeEx() 来实现相同的效果!
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                // 这里我们使用 PushID() 生成一个唯一的基础 ID，然后用作 TreeNode id 的 "" 不会冲突.
                // 使用 'PushID() + TreeNode("", ...)' 生成唯一 ID 的替代方法是使用 'TreeNode((void*)(intptr_t)i, ...)'，
                // 也就是生成一个虚拟的指针大小的值进行哈希.下面的演示使用了该技术.两者都可以.
                ImGui::PushID(i);
                if (ImGui::TreeNode("", u8"子节点 %d", i))
                {
                    ImGui::Text(u8"等等等等");
                    ImGui::SameLine();
                    if (ImGui::SmallButton(u8"按钮")) {}
                    ImGui::TreePop();
                }
                ImGui::PopID();
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/树节点/层次结构线");
        if (ImGui::TreeNode(u8"层次结构线"))
        {
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DefaultOpen;
            HelpMarker(u8"DrawLinesXXX 的默认选项存储在 style.TreeLinesFlags 中");
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_DrawLinesNone", &base_flags, ImGuiTreeNodeFlags_DrawLinesNone);
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_DrawLinesFull", &base_flags, ImGuiTreeNodeFlags_DrawLinesFull);
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_DrawLinesToNodes", &base_flags, ImGuiTreeNodeFlags_DrawLinesToNodes);

            if (ImGui::TreeNodeEx(u8"父节点", base_flags))
            {
                if (ImGui::TreeNodeEx(u8"子节点 1", base_flags))
                {
                    ImGui::Button(u8"子节点 1 的按钮");
                    ImGui::TreePop();
                }
                if (ImGui::TreeNodeEx(u8"子节点 2", base_flags))
                {
                    ImGui::Button(u8"子节点 2 的按钮");
                    ImGui::TreePop();
                }
                ImGui::Text(u8"剩余内容");
                ImGui::Text(u8"剩余内容");
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"控件/树节点/高级, 带可选节点");
        if (ImGui::TreeNode(u8"高级, 带可选节点"))
        {
            HelpMarker(
                u8"这是一个更典型的带可选节点的树.\n"
                u8"点击选择, CTRL+点击切换, 点击箭头或双击打开.");
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            static bool align_label_with_current_x_position = false;
            static bool test_drag_and_drop = false;
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_OpenOnArrow", &base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_OpenOnDoubleClick", &base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_SpanAvailWidth", &base_flags, ImGuiTreeNodeFlags_SpanAvailWidth); ImGui::SameLine(); HelpMarker(u8"将点击区域扩展到所有可用宽度，而不是允许在节点之后布置更多项目.");
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_SpanFullWidth", &base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_SpanLabelWidth", &base_flags, ImGuiTreeNodeFlags_SpanLabelWidth); ImGui::SameLine(); HelpMarker(u8"将点击区域减少到文本标签和一点边距.");
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_SpanAllColumns", &base_flags, ImGuiTreeNodeFlags_SpanAllColumns); ImGui::SameLine(); HelpMarker(u8"仅在表格中使用.");
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_AllowOverlap", &base_flags, ImGuiTreeNodeFlags_AllowOverlap);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_Framed", &base_flags, ImGuiTreeNodeFlags_Framed); ImGui::SameLine(); HelpMarker(u8"绘制带背景的框架（例如用于 CollapsingHeader）");
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_NavLeftJumpsToParent", &base_flags, ImGuiTreeNodeFlags_NavLeftJumpsToParent);

            HelpMarker(u8"DrawLinesXXX 的默认选项存储在 style.TreeLinesFlags 中");
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_DrawLinesNone", &base_flags, ImGuiTreeNodeFlags_DrawLinesNone);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_DrawLinesFull", &base_flags, ImGuiTreeNodeFlags_DrawLinesFull);
            ImGui::CheckboxFlags(u8"ImGuiTreeNodeFlags_DrawLinesToNodes", &base_flags, ImGuiTreeNodeFlags_DrawLinesToNodes);

            ImGui::Checkbox(u8"将标签与当前 X 位置对齐", &align_label_with_current_x_position);
            ImGui::Checkbox(u8"测试树节点作为拖放源", &test_drag_and_drop);
            ImGui::Text(u8"你好!");            if (align_label_with_current_x_position)
                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

            // 'selection_mask' is dumb representation of what may be user-side selection state.
            //  You may retain selection state inside or outside your objects in whatever format you see fit.
            // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
            /// of the loop. May be a pointer to your own node type, etc.
            static int selection_mask = (1 << 2);
            int node_clicked = -1;
            for (int i = 0; i < 6; i++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                ImGuiTreeNodeFlags node_flags = base_flags;
                const bool is_selected = (selection_mask & (1 << i)) != 0;
                if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                if (i < 3)
                {
                    // Items 0..2 are Tree Node
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, u8"可选节点 %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text(u8"这是一个拖放源");
                        ImGui::EndDragDropSource();
                    }
                    if (i == 2 && (base_flags & ImGuiTreeNodeFlags_SpanLabelWidth))
                    {
                        // 项目 2 有一个额外的内联按钮来帮助演示 SpanLabelWidth.
                        ImGui::SameLine();
                        if (ImGui::SmallButton(u8"按钮")) {}
                    }
                    if (node_open)
                    {
                        ImGui::BulletText(u8"等等等等\n等等等等");
                        ImGui::SameLine();
                        ImGui::SmallButton(u8"按钮");
                        ImGui::TreePop();
                    }
                }
                else
                {
                    // 项目 3..5 是树叶
                    // 我们使用 TreeNode 的唯一原因是允许选择叶子.否则我们可以
                    // 使用 BulletText() 或将光标前进 GetTreeNodeToLabelSpacing() 并调用 Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, u8"可选叶子 %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text(u8"这是一个拖放源");                        ImGui::EndDragDropSource();
                    }
                }
            }
            if (node_clicked != -1)
            {
                // Update selection state
                // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            if (align_label_with_current_x_position)
                ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsVerticalSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsVerticalSliders()
{
    IMGUI_DEMO_MARKER(u8"控件/垂直滑块");
    if (ImGui::TreeNode(u8"垂直滑块"))
    {
        const float spacing = 4;
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

        static int int_value = 0;
        ImGui::VSliderInt("##int", ImVec2(18, 160), &int_value, 0, 5);
        ImGui::SameLine();

        static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
        ImGui::PushID(u8"设置1");
        for (int i = 0; i < 7; i++)
        {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
            ImGui::VSliderFloat("##v", ImVec2(18, 160), &values[i], 0.0f, 1.0f, "");
            if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                ImGui::SetTooltip("%.3f", values[i]);
            ImGui::PopStyleColor(4);
            ImGui::PopID();
        }
        ImGui::PopID();

        ImGui::SameLine();
        ImGui::PushID(u8"设置2");
        static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
        const int rows = 3;
        const ImVec2 small_slider_size(18, (float)(int)((160.0f - (rows - 1) * spacing) / rows));
        for (int nx = 0; nx < 4; nx++)
        {
            if (nx > 0) ImGui::SameLine();
            ImGui::BeginGroup();
            for (int ny = 0; ny < rows; ny++)
            {
                ImGui::PushID(nx * rows + ny);
                ImGui::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("%.3f", values2[nx]);
                ImGui::PopID();
            }
            ImGui::EndGroup();
        }
        ImGui::PopID();

        ImGui::SameLine();
        ImGui::PushID(u8"设置3");
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
            ImGui::VSliderFloat("##v", ImVec2(40, 160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
            ImGui::PopStyleVar();
            ImGui::PopID();
        }
        ImGui::PopID();
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgets()
//-----------------------------------------------------------------------------

static void DemoWindowWidgets(ImGuiDemoWindowData* demo_data)
{
    IMGUI_DEMO_MARKER(u8"组件");
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (!ImGui::CollapsingHeader(u8"组件"))
        return;

    const bool disable_all = demo_data->DisableSections; // The Checkbox for that is inside the "Disabled" section at the bottom
    if (disable_all)
        ImGui::BeginDisabled();

    DemoWindowWidgetsBasic();
    DemoWindowWidgetsBullets();
    DemoWindowWidgetsCollapsingHeaders();
    DemoWindowWidgetsComboBoxes();
    DemoWindowWidgetsColorAndPickers();
    DemoWindowWidgetsDataTypes();

    if (disable_all)
        ImGui::EndDisabled();
    DemoWindowWidgetsDisableBlocks(demo_data);
    if (disable_all)
        ImGui::BeginDisabled();

    DemoWindowWidgetsDragAndDrop();
    DemoWindowWidgetsDragsAndSliders();
    DemoWindowWidgetsFonts();
    DemoWindowWidgetsImages();
    DemoWindowWidgetsListBoxes();
    DemoWindowWidgetsMultiComponents();
    DemoWindowWidgetsPlotting();
    DemoWindowWidgetsProgressBars();
    DemoWindowWidgetsQueryingStatuses();
    DemoWindowWidgetsSelectables();
    DemoWindowWidgetsSelectionAndMultiSelect(demo_data);
    DemoWindowWidgetsTabs();
    DemoWindowWidgetsText();
    DemoWindowWidgetsTextFilter();
    DemoWindowWidgetsTextInput();
    DemoWindowWidgetsTooltips();
    DemoWindowWidgetsTreeNodes();
    DemoWindowWidgetsVerticalSliders();

    if (disable_all)
        ImGui::EndDisabled();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowLayout()
//-----------------------------------------------------------------------------

static void DemoWindowLayout()
{
    IMGUI_DEMO_MARKER(u8"布局");
    if (!ImGui::CollapsingHeader(u8"布局和滚动"))
        return;

    IMGUI_DEMO_MARKER(u8"布局/子窗口");
    if (ImGui::TreeNode(u8"子窗口"))
    {
        ImGui::SeparatorText(u8"子窗口");

        HelpMarker(u8"使用子窗口在宿主窗口内开始自包含的独立滚动/裁剪区域.");
        static bool disable_mouse_wheel = false;
        static bool disable_menu = false;
        ImGui::Checkbox(u8"禁用鼠标滚轮", &disable_mouse_wheel);
        ImGui::Checkbox(u8"禁用菜单", &disable_menu);

        // 子窗口 1: 无边框，启用水平滚动条
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            if (disable_mouse_wheel)
                window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 260), ImGuiChildFlags_None, window_flags);
            for (int i = 0; i < 100; i++)
                ImGui::Text(u8"%04d: 可滚动区域", i);
            ImGui::EndChild();
        }

        ImGui::SameLine();

        // 子窗口 2: 圆角边框
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            if (disable_mouse_wheel)
                window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            if (!disable_menu)
                window_flags |= ImGuiWindowFlags_MenuBar;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("ChildR", ImVec2(0, 260), ImGuiChildFlags_Borders, window_flags);
            if (!disable_menu && ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu(u8"菜单"))
                {
                    ShowExampleMenuFile();
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            if (ImGui::BeginTable("split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
            {
                for (int i = 0; i < 100; i++)
                {
                    char buf[32];
                    sprintf(buf, u8"%03d", i);
                    ImGui::TableNextColumn();
                    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                }
                ImGui::EndTable();
            }
            ImGui::EndChild();
            ImGui::PopStyleVar();
        }

        // 子窗口 3: 手动调整大小
        ImGui::SeparatorText(u8"手动调整大小");
        {
            HelpMarker(u8"拖动底部边框调整大小.双击底部边框自动适应垂直内容.");
            //if (ImGui::Button(u8"设置高度为 200"))
            //    ImGui::SetNextWindowSize(ImVec2(-FLT_MIN, 200.0f));

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
            if (ImGui::BeginChild("ResizableChild", ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeY))
                for (int n = 0; n < 10; n++)
                    ImGui::Text(u8"行 %04d", n);
            ImGui::PopStyleColor();
            ImGui::EndChild();
        }

        // 子窗口 4: 带限制的自动调整高度
        ImGui::SeparatorText(u8"带约束的自动调整大小");
        {
            static int draw_lines = 3;
            static int max_height_in_lines = 10;
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::DragInt(u8"行数", &draw_lines, 0.2f);
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::DragInt(u8"最大高度 (行数)", &max_height_in_lines, 0.2f);

            ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines));
            if (ImGui::BeginChild("ConstrainedChild", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY))
                for (int n = 0; n < draw_lines; n++)
                    ImGui::Text(u8"行 %04d", n);
            ImGui::EndChild();
        }

        ImGui::SeparatorText(u8"杂项/高级");

        // 演示一些额外的东西
        // - 更改 ImGuiCol_ChildBg（在默认样式中是透明黑色）
        // - 使用 SetCursorPos() 定位子窗口（从父窗口的角度来看，子窗口是一个项目）
        //   您也可以调用 SetNextWindowPos() 来定位子窗口.父窗口将有效地
        //   从这个位置开始布局.
        // - 使用 ImGui::GetItemRectMin/Max() 查询"项目"状态（因为从父窗口的角度来看
        //   子窗口是一个项目）.详情请参见'演示->查询状态（已编辑/活动/悬停等）'.
        {
            static int offset_x = 0;
            static bool override_bg_color = true;
            static ImGuiChildFlags child_flags = ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY;
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::DragInt(u8"偏移 X", &offset_x, 1.0f, -1000, 1000);
            ImGui::Checkbox(u8"覆盖子窗口背景颜色", &override_bg_color);
            ImGui::CheckboxFlags(u8"ImGuiChildFlags_Borders", &child_flags, ImGuiChildFlags_Borders);
            ImGui::CheckboxFlags(u8"ImGuiChildFlags_AlwaysUseWindowPadding", &child_flags, ImGuiChildFlags_AlwaysUseWindowPadding);
            ImGui::CheckboxFlags(u8"ImGuiChildFlags_ResizeX", &child_flags, ImGuiChildFlags_ResizeX);
            ImGui::CheckboxFlags(u8"ImGuiChildFlags_ResizeY", &child_flags, ImGuiChildFlags_ResizeY);
            ImGui::CheckboxFlags(u8"ImGuiChildFlags_FrameStyle", &child_flags, ImGuiChildFlags_FrameStyle);
            ImGui::SameLine(); HelpMarker(u8"将子窗口样式设置为带框架的项目：使用 FrameBg、FrameRounding、FrameBorderSize、FramePadding 而不是 ChildBg、ChildRounding、ChildBorderSize、WindowPadding.");
            if (child_flags & ImGuiChildFlags_FrameStyle)
                override_bg_color = false;

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (float)offset_x);
            if (override_bg_color)
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 0, 0, 100));
            ImGui::BeginChild("Red", ImVec2(200, 100), child_flags, ImGuiWindowFlags_None);
            if (override_bg_color)
                ImGui::PopStyleColor();

            for (int n = 0; n < 50; n++)
                ImGui::Text(u8"一些测试 %d", n);
            ImGui::EndChild();
            bool child_is_hovered = ImGui::IsItemHovered();
            ImVec2 child_rect_min = ImGui::GetItemRectMin();
            ImVec2 child_rect_max = ImGui::GetItemRectMax();
            ImGui::Text(u8"悬停: %d", child_is_hovered);
            ImGui::Text(u8"子窗口矩形为: (%.0f,%.0f) (%.0f,%.0f)", child_rect_min.x, child_rect_min.y, child_rect_max.x, child_rect_max.y);
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/控件宽度");
    if (ImGui::TreeNode(u8"控件宽度"))
    {
        static float f = 0.0f;
        static bool show_indented_items = true;
        ImGui::Checkbox(u8"显示缩进项目", &show_indented_items);

        // 使用 SetNextItemWidth() 设置单个即将到来的项目的宽度.
        // 使用 PushItemWidth()/PopItemWidth() 设置一组项目的宽度.
        // 在实际代码中，您可能希望选择与字体大小成比例的宽度值
        // 例如，使用 '20.0f * GetFontSize()' 作为宽度而不是 '200.0f'，等等.

        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(100)");
        ImGui::SameLine(); HelpMarker(u8"固定宽度.");
        ImGui::PushItemWidth(100);
        ImGui::DragFloat(u8"浮点数##1b", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##1b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(-100)");
        ImGui::SameLine(); HelpMarker(u8"右对齐减去 100");
        ImGui::PushItemWidth(-100);
        ImGui::DragFloat(u8"浮点数##2a", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##2b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(GetContentRegionAvail().x * 0.5f)");
        ImGui::SameLine(); HelpMarker(u8"可用宽度的一半.\n(~ 右光标位置)\n(在列集内工作)");
        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5f);
        ImGui::DragFloat(u8"浮点数##3a", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##3b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(-GetContentRegionAvail().x * 0.5f)");
        ImGui::SameLine(); HelpMarker(u8"右对齐减去一半");
        ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.5f);
        ImGui::DragFloat(u8"浮点数##4a", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##4b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(-Min(GetContentRegionAvail().x * 0.40f, GetFontSize() * 12))");
        ImGui::PushItemWidth(-IM_MIN(ImGui::GetFontSize() * 12, ImGui::GetContentRegionAvail().x * 0.40f));
        ImGui::DragFloat(u8"浮点数##5a", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##5b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        // 演示使用 PushItemWidth 包围三个项目.
        // 在每个项目之前调用 SetNextItemWidth() 将具有相同的效果.
        ImGui::Text(u8"SetNextItemWidth/PushItemWidth(-FLT_MIN)");
        ImGui::SameLine(); HelpMarker(u8"右对齐");
        ImGui::PushItemWidth(-FLT_MIN);
        ImGui::DragFloat(u8"##浮点数6a", &f);
        if (show_indented_items)
        {
            ImGui::Indent();
            ImGui::DragFloat(u8"浮点数 (缩进)##6b", &f);
            ImGui::Unindent();
        }
        ImGui::PopItemWidth();

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/基础水平布局");
    if (ImGui::TreeNode(u8"基础水平布局"))
    {
        ImGui::TextWrapped(u8"(使用 ImGui::SameLine() 继续在前一个项目的右侧添加项目)");

        // 文本
        IMGUI_DEMO_MARKER(u8"布局/基础水平布局/SameLine");
        ImGui::Text(u8"两个项目: 你好"); ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), u8"水手");

        // 调整间距
        ImGui::Text(u8"更多间距: 你好"); ImGui::SameLine(0, 20);
        ImGui::TextColored(ImVec4(1, 1, 0, 1), u8"水手");

        // 按钮
        ImGui::AlignTextToFramePadding();
        ImGui::Text(u8"普通按钮"); ImGui::SameLine();
        ImGui::Button(u8"香蕉"); ImGui::SameLine();
        ImGui::Button(u8"苹果"); ImGui::SameLine();
        ImGui::Button(u8"花椰菜");

        // 按钮
        ImGui::Text(u8"小按钮"); ImGui::SameLine();
        ImGui::SmallButton(u8"像这个"); ImGui::SameLine();
        ImGui::Text(u8"可以适应文本块内.");

        // 对齐到任意位置.简单/廉价的列.
        IMGUI_DEMO_MARKER(u8"布局/基础水平布局/SameLine (带偏移)");
        ImGui::Text(u8"对齐");
        ImGui::SameLine(150); ImGui::Text(u8"x=150");
        ImGui::SameLine(300); ImGui::Text(u8"x=300");
        ImGui::Text(u8"对齐");
        ImGui::SameLine(150); ImGui::SmallButton(u8"x=150");
        ImGui::SameLine(300); ImGui::SmallButton(u8"x=300");

        // 复选框
        IMGUI_DEMO_MARKER(u8"布局/基础水平布局/SameLine (更多)");
        static bool c1 = false, c2 = false, c3 = false, c4 = false;
        ImGui::Checkbox(u8"我的", &c1); ImGui::SameLine();
        ImGui::Checkbox(u8"裁缝", &c2); ImGui::SameLine();
        ImGui::Checkbox(u8"是", &c3); ImGui::SameLine();
        ImGui::Checkbox(u8"富有的", &c4);

        // 各种
        static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
        ImGui::PushItemWidth(80);
        const char* items[] = { u8"AAAA", u8"BBBB", u8"CCCC", u8"DDDD" };
        static int item = -1;
        ImGui::Combo(u8"组合框", &item, items, IM_ARRAYSIZE(items)); ImGui::SameLine();
        ImGui::SliderFloat(u8"X", &f0, 0.0f, 5.0f); ImGui::SameLine();
        ImGui::SliderFloat(u8"Y", &f1, 0.0f, 5.0f); ImGui::SameLine();
        ImGui::SliderFloat(u8"Z", &f2, 0.0f, 5.0f);
        ImGui::PopItemWidth();

        ImGui::PushItemWidth(80);
        ImGui::Text(u8"列表:");
        static int selection[4] = { 0, 1, 2, 3 };
        for (int i = 0; i < 4; i++)
        {
            if (i > 0) ImGui::SameLine();
            ImGui::PushID(i);
            ImGui::ListBox("", &selection[i], items, IM_ARRAYSIZE(items));
            ImGui::PopID();
            //ImGui::SetItemTooltip(u8"列表框 %d 悬停", i);
        }
        ImGui::PopItemWidth();

        // 虚拟
        IMGUI_DEMO_MARKER(u8"布局/基础水平布局/虚拟");
        ImVec2 button_sz(40, 40);
        ImGui::Button("A", button_sz); ImGui::SameLine();
        ImGui::Dummy(button_sz); ImGui::SameLine();
        ImGui::Button("B", button_sz);

        // 手动换行
        // (我们最终应该将其作为自动布局功能提供，但目前您可以手动完成)
        IMGUI_DEMO_MARKER(u8"布局/基础水平布局/手动换行");
        ImGui::Text(u8"手动换行:");
        ImGuiStyle& style = ImGui::GetStyle();
        int buttons_count = 20;
        float window_visible_x2 = ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x;
        for (int n = 0; n < buttons_count; n++)
        {
            ImGui::PushID(n);
            ImGui::Button(u8"盒子", button_sz);
            float last_button_x2 = ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // 如果下一个按钮在同一行上的预期位置
            if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
                ImGui::SameLine();
            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/组");
    if (ImGui::TreeNode(u8"组"))
    {
        HelpMarker(
            u8"BeginGroup() 基本上锁定了新行的水平位置."
            u8"EndGroup() 捆绑整个组，以便您可以使用\"项目\"函数，例如"
            u8"IsItemHovered()/IsItemActive() 或 SameLine() 等在整个组上.");
        ImGui::BeginGroup();
        {
            ImGui::BeginGroup();
            ImGui::Button("AAA");
            ImGui::SameLine();
            ImGui::Button("BBB");
            ImGui::SameLine();
            ImGui::BeginGroup();
            ImGui::Button("CCC");
            ImGui::Button("DDD");
            ImGui::EndGroup();
            ImGui::SameLine();
            ImGui::Button("EEE");
            ImGui::EndGroup();
            ImGui::SetItemTooltip(u8"第一个组悬停");
        }
        // 捕获组大小并使用相同大小创建控件
        ImVec2 size = ImGui::GetItemRectSize();
        const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
        ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

        ImGui::Button(u8"动作", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x) * 0.5f, size.y));
        ImGui::SameLine();
        ImGui::Button(u8"反应", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x) * 0.5f, size.y));
        ImGui::EndGroup();
        ImGui::SameLine();

        ImGui::Button(u8"杠杆作用\n流行语", size);
        ImGui::SameLine();

        if (ImGui::BeginListBox(u8"列表", size))
        {
            ImGui::Selectable(u8"已选择", true);
            ImGui::Selectable(u8"未选择", false);
            ImGui::EndListBox();
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/文本基线对齐");
    if (ImGui::TreeNode(u8"文本基线对齐"))
    {
        {
            ImGui::BulletText(u8"文本基线:");
            ImGui::SameLine(); HelpMarker(
                u8"这正在测试应用于文本的垂直对齐方式，以使其与控件对齐."
                u8"仅由文本或\"小\"控件组成的行比带有框架控件的行使用更少的垂直空间.");
            ImGui::Indent();

            ImGui::Text(u8"KO 等等等等"); ImGui::SameLine();
            ImGui::Button(u8"一些带框架的项目"); ImGui::SameLine();
            HelpMarker(u8"按钮的基线看起来与文本不对齐..");

            // 如果您的行以文本开头，请调用 AlignTextToFramePadding() 将文本与即将到来的控件对齐.
            // （因为我们不知道 Text() 语句之后会有什么，我们需要将文本基线
            // 提前向下移动 FramePadding.y）
            ImGui::AlignTextToFramePadding();
            ImGui::Text(u8"OK 等等等等"); ImGui::SameLine();
            ImGui::Button(u8"一些带框架的项目##2"); ImGui::SameLine();
            HelpMarker(u8"我们调用 AlignTextToFramePadding() 通过 +FramePadding.y 垂直对齐文本基线");

            // SmallButton() 使用与 Text 相同的垂直填充
            ImGui::Button(u8"测试##1"); ImGui::SameLine();
            ImGui::Text(u8"测试"); ImGui::SameLine();
            ImGui::SmallButton(u8"测试##2");

            // 如果您的行以文本开头，请调用 AlignTextToFramePadding() 将文本与即将到来的控件对齐.
            ImGui::AlignTextToFramePadding();
            ImGui::Text(u8"文本对齐到带框架的项目"); ImGui::SameLine();
            ImGui::Button(u8"项目##1"); ImGui::SameLine();
            ImGui::Text(u8"项目"); ImGui::SameLine();
            ImGui::SmallButton(u8"项目##2"); ImGui::SameLine();
            ImGui::Button(u8"项目##3");

            ImGui::Unindent();
        }

        ImGui::Spacing();

        {
            ImGui::BulletText(u8"多行文本:");
            ImGui::Indent();
            ImGui::Text(u8"一\n二\n三"); ImGui::SameLine();
            ImGui::Text(u8"你好\n世界"); ImGui::SameLine();
            ImGui::Text(u8"香蕉");

            ImGui::Text(u8"香蕉"); ImGui::SameLine();
            ImGui::Text(u8"你好\n世界"); ImGui::SameLine();
            ImGui::Text(u8"一\n二\n三");

            ImGui::Button(u8"跳跃##1"); ImGui::SameLine();
            ImGui::Text(u8"香蕉"); ImGui::SameLine();
            ImGui::Text(u8"你好\n世界"); ImGui::SameLine();
            ImGui::Text(u8"香蕉");

            ImGui::Button(u8"跳跃##2"); ImGui::SameLine();
            ImGui::Text(u8"你好\n世界"); ImGui::SameLine();
            ImGui::Text(u8"香蕉");
            ImGui::Unindent();
        }

        ImGui::Spacing();

        {
            ImGui::BulletText(u8"杂项项目:");
            ImGui::Indent();

            // SmallButton() 将 FramePadding 设置为零.文本基线对齐以匹配先前按钮的基线.
            ImGui::Button(u8"80x80", ImVec2(80, 80));
            ImGui::SameLine();
            ImGui::Button(u8"50x50", ImVec2(50, 50));
            ImGui::SameLine();
            ImGui::Button(u8"按钮()");
            ImGui::SameLine();
            ImGui::SmallButton(u8"小按钮()");

            // 树
            // (这里节点出现在按钮之后并且有奇怪的缩进，因此我们使用 ImGuiTreeNodeFlags_DrawLinesNone 禁用层次结构轮廓)
            const float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
            ImGui::Button(u8"按钮##1");
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::TreeNodeEx(u8"节点##1", ImGuiTreeNodeFlags_DrawLinesNone))
            {
                // 占位符树数据
                for (int i = 0; i < 6; i++)
                    ImGui::BulletText(u8"项目 %d..", i);
                ImGui::TreePop();
            }

            // 将文本节点垂直对齐得稍低一些，以便与即将到来的控件垂直居中.
            // 否则您可以使用 SmallButton()（更合适）.
            ImGui::AlignTextToFramePadding();

            // 要避免的常见错误：如果我们要在 TreeNode 之后 SameLine，我们需要在添加
            // 节点下面的其他内容之前进行.
            bool node_open = ImGui::TreeNode(u8"节点##2");
            ImGui::SameLine(0.0f, spacing); ImGui::Button(u8"按钮##2");
            if (node_open)
            {
                // 占位符树数据
                for (int i = 0; i < 6; i++)
                    ImGui::BulletText(u8"项目 %d..", i);
                ImGui::TreePop();
            }

            // 项目符号
            ImGui::Button(u8"按钮##3");
            ImGui::SameLine(0.0f, spacing);
            ImGui::BulletText(u8"项目符号文本");

            ImGui::AlignTextToFramePadding();
            ImGui::BulletText(u8"节点");
            ImGui::SameLine(0.0f, spacing); ImGui::Button(u8"按钮##4");
            ImGui::Unindent();
        }

        ImGui::TreePop();
    }
    IMGUI_DEMO_MARKER(u8"布局/滚动");
    if (ImGui::TreeNode(u8"滚动"))
    {
        // 垂直滚动函数
        IMGUI_DEMO_MARKER(u8"布局/滚动/垂直");
        HelpMarker(u8"使用 SetScrollHereY() 或 SetScrollFromPosY() 滚动到给定的垂直位置.");

        static int track_item = 50;
        static bool enable_track = true;
        static bool enable_extra_decorations = false;
        static float scroll_to_off_px = 0.0f;
        static float scroll_to_pos_px = 200.0f;

        ImGui::Checkbox(u8"装饰", &enable_extra_decorations);

        ImGui::Checkbox(u8"跟踪", &enable_track);
        ImGui::PushItemWidth(100);
        ImGui::SameLine(140); enable_track |= ImGui::DragInt(u8"##项目", &track_item, 0.25f, 0, 99, u8"项目 = %d");

        bool scroll_to_off = ImGui::Button(u8"滚动偏移");
        ImGui::SameLine(140); scroll_to_off |= ImGui::DragFloat(u8"##偏移", &scroll_to_off_px, 1.00f, 0, FLT_MAX, u8"+%.0f 像素");

        bool scroll_to_pos = ImGui::Button(u8"滚动到位置");
        ImGui::SameLine(140); scroll_to_pos |= ImGui::DragFloat(u8"##位置", &scroll_to_pos_px, 1.00f, -10, FLT_MAX, u8"X/Y = %.0f 像素");
        ImGui::PopItemWidth();

        if (scroll_to_off || scroll_to_pos)
            enable_track = false;

        ImGuiStyle& style = ImGui::GetStyle();
        float child_w = (ImGui::GetContentRegionAvail().x - 4 * style.ItemSpacing.x) / 5;
        if (child_w < 1.0f)
            child_w = 1.0f;
        ImGui::PushID("##VerticalScrolling");
        for (int i = 0; i < 5; i++)
        {
            if (i > 0) ImGui::SameLine();
            ImGui::BeginGroup();
            const char* names[] = { u8"顶部", u8"25%", u8"中心", u8"75%", u8"底部" };
            ImGui::TextUnformatted(names[i]);

            const ImGuiWindowFlags child_flags = enable_extra_decorations ? ImGuiWindowFlags_MenuBar : 0;
            const ImGuiID child_id = ImGui::GetID((void*)(intptr_t)i);
            const bool child_is_visible = ImGui::BeginChild(child_id, ImVec2(child_w, 200.0f), ImGuiChildFlags_Borders, child_flags);
            if (ImGui::BeginMenuBar())
            {
                ImGui::TextUnformatted("abc");
                ImGui::EndMenuBar();
            }
            if (scroll_to_off)
                ImGui::SetScrollY(scroll_to_off_px);
            if (scroll_to_pos)
                ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_to_pos_px, i * 0.25f);
            if (child_is_visible) // 避免在运行剔除项目时调用 SetScrollHereY
            {
                for (int item = 0; item < 100; item++)
                {
                    if (enable_track && item == track_item)
                    {
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), u8"项目 %d", item);
                        ImGui::SetScrollHereY(i * 0.25f); // 0.0f:顶部, 0.5f:中心, 1.0f:底部
                    }
                    else
                    {
                        ImGui::Text(u8"项目 %d", item);
                    }
                }
            }
            float scroll_y = ImGui::GetScrollY();
            float scroll_max_y = ImGui::GetScrollMaxY();
            ImGui::EndChild();
            ImGui::Text("%.0f/%.0f", scroll_y, scroll_max_y);
            ImGui::EndGroup();
        }
        ImGui::PopID();

        // 水平滚动函数
        IMGUI_DEMO_MARKER(u8"布局/滚动/水平");
        ImGui::Spacing();
        HelpMarker(
            u8"使用 SetScrollHereX() 或 SetScrollFromPosX() 滚动到给定的水平位置.\n\n"
            u8"因为大多数窗口的裁剪矩形在左/右隐藏了 WindowPadding 的一半价值，"
            u8"使用 SetScrollFromPosX(+1) 通常会导致文本被裁剪，而等效的 SetScrollFromPosY(+1) 不会.");
        ImGui::PushID("##HorizontalScrolling");
        for (int i = 0; i < 5; i++)
        {
            float child_height = ImGui::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
            ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (enable_extra_decorations ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
            ImGuiID child_id = ImGui::GetID((void*)(intptr_t)i);
            bool child_is_visible = ImGui::BeginChild(child_id, ImVec2(-100, child_height), ImGuiChildFlags_Borders, child_flags);
            if (scroll_to_off)
                ImGui::SetScrollX(scroll_to_off_px);
            if (scroll_to_pos)
                ImGui::SetScrollFromPosX(ImGui::GetCursorStartPos().x + scroll_to_pos_px, i * 0.25f);
            if (child_is_visible) // 避免在运行剔除项目时调用 SetScrollHereY
            {
                for (int item = 0; item < 100; item++)
                {
                    if (item > 0)
                        ImGui::SameLine();
                    if (enable_track && item == track_item)
                    {
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), u8"项目 %d", item);
                        ImGui::SetScrollHereX(i * 0.25f); // 0.0f:左, 0.5f:中心, 1.0f:右
                    }
                    else
                    {
                        ImGui::Text(u8"项目 %d", item);
                    }
                }
            }
            float scroll_x = ImGui::GetScrollX();
            float scroll_max_x = ImGui::GetScrollMaxX();
            ImGui::EndChild();
            ImGui::SameLine();
            const char* names[] = { u8"左", u8"25%", u8"中心", u8"75%", u8"右" };
            ImGui::Text(u8"%s\n%.0f/%.0f", names[i], scroll_x, scroll_max_x);
            ImGui::Spacing();
        }
        ImGui::PopID();

        // 杂项水平滚动演示
        IMGUI_DEMO_MARKER(u8"布局/滚动/水平 (更多)");
        HelpMarker(
            u8"窗口的水平滚动通过 ImGuiWindowFlags_HorizontalScrollbar 标志启用.\n\n"
            u8"您可能还希望通过在 Begin() 之前使用 SetNextWindowContentWidth() 显式指定内容宽度.");
        static int lines = 7;
        ImGui::SliderInt(u8"行数", &lines, 1, 15);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 1.0f));
        ImVec2 scrolling_child_size = ImVec2(0, ImGui::GetFrameHeightWithSpacing() * 7 + 30);
        ImGui::BeginChild("scrolling", scrolling_child_size, ImGuiChildFlags_Borders, ImGuiWindowFlags_HorizontalScrollbar);
        for (int line = 0; line < lines; line++)
        {
            // 显示随机内容.为了这个简单的演示，我们使用基本的 Button() + SameLine()
            // 如果您想为真实应用程序创建自己的时间线，最好自己操作
            // 光标位置，也就是使用 SetCursorPos/SetCursorScreenPos 来定位控件
            // 您自己.您可能还想使用较低级别的 ImDrawList API.
            int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
            for (int n = 0; n < num_buttons; n++)
            {
                if (n > 0) ImGui::SameLine();
                ImGui::PushID(n + line * 1000);
                char num_buf[16];
                sprintf(num_buf, "%d", n);
                const char* label = (!(n % 15)) ? "FizzBuzz" : (!(n % 3)) ? "Fizz" : (!(n % 5)) ? "Buzz" : num_buf;
                float hue = n * 0.05f;
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
                ImGui::Button(label, ImVec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }
        }
        float scroll_x = ImGui::GetScrollX();
        float scroll_max_x = ImGui::GetScrollMaxX();
        ImGui::EndChild();
        ImGui::PopStyleVar(2);
        float scroll_x_delta = 0.0f;
        ImGui::SmallButton("<<");
        if (ImGui::IsItemActive())
            scroll_x_delta = -ImGui::GetIO().DeltaTime * 1000.0f;
        ImGui::SameLine();
        ImGui::Text(u8"从代码滚动"); ImGui::SameLine();
        ImGui::SmallButton(">>");
        if (ImGui::IsItemActive())
            scroll_x_delta = +ImGui::GetIO().DeltaTime * 1000.0f;
        ImGui::SameLine();
        ImGui::Text("%.0f/%.0f", scroll_x, scroll_max_x);
        if (scroll_x_delta != 0.0f)
        {
            // 演示一个技巧：您可以使用 Begin 将自己设置在另一个窗口的上下文中
            // (这里我们已经不在您的子窗口中了)
            ImGui::BeginChild("scrolling");
            ImGui::SetScrollX(ImGui::GetScrollX() + scroll_x_delta);
            ImGui::EndChild();
        }
        ImGui::Spacing();

        static bool show_horizontal_contents_size_demo_window = false;
        ImGui::Checkbox(u8"显示水平内容大小演示窗口", &show_horizontal_contents_size_demo_window);

        if (show_horizontal_contents_size_demo_window)
        {
            static bool show_h_scrollbar = true;
            static bool show_button = true;
            static bool show_tree_nodes = true;
            static bool show_text_wrapped = false;
            static bool show_columns = true;
            static bool show_tab_bar = true;
            static bool show_child = false;
            static bool explicit_content_size = false;
            static float contents_size_x = 300.0f;
            if (explicit_content_size)
                ImGui::SetNextWindowContentSize(ImVec2(contents_size_x, 0.0f));
            ImGui::Begin(u8"水平内容大小演示窗口", &show_horizontal_contents_size_demo_window, show_h_scrollbar ? ImGuiWindowFlags_HorizontalScrollbar : 0);
            IMGUI_DEMO_MARKER(u8"布局/滚动/水平内容大小演示窗口");
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 0));
            HelpMarker(
                u8"测试启用水平滚动时不同控件的反应和影响工作矩形增长的方式.\n\n"
                u8"使用'指标->工具->显示窗口矩形'来可视化矩形.");
            ImGui::Checkbox(u8"H-滚动条", &show_h_scrollbar);
            ImGui::Checkbox(u8"按钮", &show_button);            // 将增长内容大小（除非显式覆盖）
            ImGui::Checkbox(u8"树节点", &show_tree_nodes);    // 将增长内容大小并在全宽上显示高亮
            ImGui::Checkbox(u8"文本换行", &show_text_wrapped);// 将增长并使用内容大小
            ImGui::Checkbox(u8"列", &show_columns);          // 将使用内容大小
            ImGui::Checkbox(u8"选项卡栏", &show_tab_bar);          // 将使用内容大小
            ImGui::Checkbox(u8"子窗口", &show_child);              // 将增长并使用内容大小
            ImGui::Checkbox(u8"显式内容大小", &explicit_content_size);
            ImGui::Text(u8"滚动 %.1f/%.1f %.1f/%.1f", ImGui::GetScrollX(), ImGui::GetScrollMaxX(), ImGui::GetScrollY(), ImGui::GetScrollMaxY());
            if (explicit_content_size)
            {
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::DragFloat(u8"##csx", &contents_size_x);
                ImVec2 p = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + 10, p.y + 10), IM_COL32_WHITE);
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + contents_size_x - 10, p.y), ImVec2(p.x + contents_size_x, p.y + 10), IM_COL32_WHITE);
                ImGui::Dummy(ImVec2(0, 10));
            }
            ImGui::PopStyleVar(2);
            ImGui::Separator();
            if (show_button)
            {
                ImGui::Button(u8"这是一个 300 宽的按钮", ImVec2(300, 0));
            }
            if (show_tree_nodes)
            {
                bool open = true;
                if (ImGui::TreeNode(u8"这是一个树节点"))
                {
                    if (ImGui::TreeNode(u8"另一个这样的树节点..."))
                    {
                        ImGui::Text(u8"一些树内容");
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
                ImGui::CollapsingHeader(u8"折叠标题", &open);
            }
            if (show_text_wrapped)
            {
                ImGui::TextWrapped(u8"此文本应自动在工作矩形的边缘换行.");
            }
            if (show_columns)
            {
                ImGui::Text(u8"表格:");
                if (ImGui::BeginTable("table", 4, ImGuiTableFlags_Borders))
                {
                    for (int n = 0; n < 4; n++)
                    {
                        ImGui::TableNextColumn();
                        ImGui::Text(u8"宽度 %.2f", ImGui::GetContentRegionAvail().x);
                    }
                    ImGui::EndTable();
                }
                ImGui::Text(u8"列:");
                ImGui::Columns(4);
                for (int n = 0; n < 4; n++)
                {
                    ImGui::Text(u8"宽度 %.2f", ImGui::GetColumnWidth());
                    ImGui::NextColumn();
                }
                ImGui::Columns(1);
            }
            if (show_tab_bar && ImGui::BeginTabBar("Hello"))
            {
                if (ImGui::BeginTabItem("OneOneOne")) { ImGui::EndTabItem(); }
                if (ImGui::BeginTabItem("TwoTwoTwo")) { ImGui::EndTabItem(); }
                if (ImGui::BeginTabItem("ThreeThreeThree")) { ImGui::EndTabItem(); }
                if (ImGui::BeginTabItem("FourFourFour")) { ImGui::EndTabItem(); }
                ImGui::EndTabBar();
            }
            if (show_child)
            {
                ImGui::BeginChild("child", ImVec2(0, 0), ImGuiChildFlags_Borders);
                ImGui::EndChild();
            }
            ImGui::End();
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/文本裁剪");
    if (ImGui::TreeNode(u8"文本裁剪"))
    {
        static ImVec2 size(100.0f, 100.0f);
        static ImVec2 offset(30.0f, 30.0f);
        ImGui::DragFloat2(u8"大小", (float*)&size, 0.5f, 1.0f, 200.0f, "%.0f");
        ImGui::TextWrapped(u8"(点击并拖动以滚动)");

        HelpMarker(
            u8"(左) 使用 ImGui::PushClipRect():\n"
            u8"将改变 ImGui 命中测试逻辑 + ImDrawList 渲染.\n"
            u8"(如果您希望裁剪矩形影响交互，请使用此选项)\n\n"
            u8"(中) 使用 ImDrawList::PushClipRect():\n"
            u8"仅改变 ImDrawList 渲染.\n"
            u8"(如果您仅使用 ImDrawList 调用，请使用此快捷方式)\n\n"
            u8"(右) 使用 ImDrawList::AddText() 和精细的 ClipRect:\n"
            u8"仅改变此特定 ImDrawList::AddText() 渲染.\n"
            u8"这通常在内部使用，以避免更改裁剪矩形并最小化绘制调用.");

        for (int n = 0; n < 3; n++)
        {
            if (n > 0)
                ImGui::SameLine();

            ImGui::PushID(n);
            ImGui::InvisibleButton("##canvas", size);
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                offset.x += ImGui::GetIO().MouseDelta.x;
                offset.y += ImGui::GetIO().MouseDelta.y;
            }
            ImGui::PopID();
            if (!ImGui::IsItemVisible()) // 跳过渲染，因为 ImDrawList 元素不会被裁剪.
                continue;

            const ImVec2 p0 = ImGui::GetItemRectMin();
            const ImVec2 p1 = ImGui::GetItemRectMax();
            const char* text_str = u8"第1行 你好\n第2行 裁剪我!";
            const ImVec2 text_pos = ImVec2(p0.x + offset.x, p0.y + offset.y);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            switch (n)
            {
            case 0:
                ImGui::PushClipRect(p0, p1, true);
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(text_pos, IM_COL32_WHITE, text_str);
                ImGui::PopClipRect();
                break;
            case 1:
                draw_list->PushClipRect(p0, p1, true);
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(text_pos, IM_COL32_WHITE, text_str);
                draw_list->PopClipRect();
                break;
            case 2:
                ImVec4 clip_rect(p0.x, p0.y, p1.x, p1.y); // AddText() 这里接受 ImVec4*，所以让我们转换.
                draw_list->AddRectFilled(p0, p1, IM_COL32(90, 90, 120, 255));
                draw_list->AddText(ImGui::GetFont(), ImGui::GetFontSize(), text_pos, IM_COL32_WHITE, text_str, NULL, 0.0f, &clip_rect);
                break;
            }
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"布局/重叠模式");
    if (ImGui::TreeNode(u8"重叠模式"))
    {
        static bool enable_allow_overlap = true;

        HelpMarker(
            u8"命中测试默认按项目提交顺序执行，这通常被视为'从后到前'.\n\n"
            u8"通过使用 SetNextItemAllowOverlap()，您可以通知一个项目可能被另一个项目重叠."
            u8"这样做会改变悬停逻辑：使用 AllowOverlap 模式的项目需要额外一帧来接受悬停状态.");
        ImGui::Checkbox(u8"启用允许重叠", &enable_allow_overlap);

        ImVec2 button1_pos = ImGui::GetCursorScreenPos();
        ImVec2 button2_pos = ImVec2(button1_pos.x + 50.0f, button1_pos.y + 50.0f);
        if (enable_allow_overlap)
            ImGui::SetNextItemAllowOverlap();
        ImGui::Button(u8"按钮 1", ImVec2(80, 80));
        ImGui::SetCursorScreenPos(button2_pos);
        ImGui::Button(u8"按钮 2", ImVec2(80, 80));

        // 这通常与宽度跨越项目一起使用.
        // (请注意 Selectable() 有一个专用标志 ImGuiSelectableFlags_AllowOverlap，这是
        // 使用 SetNextItemAllowOverlap() 的快捷方式.为了演示目的，我们在这里使用 SetNextItemAllowOverlap().)
        if (enable_allow_overlap)
            ImGui::SetNextItemAllowOverlap();
        ImGui::Selectable(u8"一些可选项目", false);
        ImGui::SameLine();
        ImGui::SmallButton("++");

        ImGui::TreePop();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowPopups()
//-----------------------------------------------------------------------------

static void DemoWindowPopups()
{
    IMGUI_DEMO_MARKER(u8"弹出窗口");
    if (!ImGui::CollapsingHeader(u8"弹出窗口和模态窗口"))
        return;

    // 弹出窗口的属性是：
    // - 它们阻止在它们外部的正常鼠标悬停检测.（*）
    // - 除非是模态窗口，否则可以通过点击它们之外的任何地方或按 ESCAPE 来关闭它们.
    // - 它们的可见性状态（~bool）由 Dear ImGui 内部持有，而不是像我们习惯的那样由程序员持有
    //   常规的 Begin() 调用.用户可以通过调用 OpenPopup() 来操作可见性状态.
    // （*）可以使用 IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) 来绕过它并检测悬停，即使
    //     通常被弹出窗口阻止.
    // 这三个属性是相互关联的.库需要持有它们的可见性状态，因为它可以随时关闭
    // 弹出窗口.

    // 常规窗口的典型用法：
    //   bool my_tool_is_active = false; if (ImGui::Button("Open")) my_tool_is_active = true; [...] if (my_tool_is_active) Begin("My Tool", &my_tool_is_active) { [...] } End();
    // 弹出窗口的典型用法：
    //   if (ImGui::Button("Open")) ImGui::OpenPopup("MyPopup"); if (ImGui::BeginPopup("MyPopup") { [...] EndPopup(); }

    // 对于弹出窗口，我们必须通过库调用（这里是 OpenPopup）来操作可见性状态.
    // 起初这可能有点令人困惑，但应该很快就能理解.请参考下面的示例.

    IMGUI_DEMO_MARKER(u8"弹出窗口/弹出窗口");
    if (ImGui::TreeNode(u8"弹出窗口"))
    {
        ImGui::TextWrapped(
            u8"当弹出窗口处于活动状态时，它会禁止与弹出窗口后面的窗口交互."
            u8"点击弹出窗口外部会关闭它.");

        static int selected_fish = -1;
        const char* names[] = { u8"鲷鱼", u8"黑线鳕", u8"鲭鱼", u8"鳕鱼", u8"方头鱼" };
        static bool toggles[] = { true, false, false, false, false };

        // 简单选择弹出窗口（如果您想在按钮本身内显示当前选择，
        // 您可能希望使用 "###" 操作符构建字符串，以保留具有可变标签的常量 ID）
        if (ImGui::Button(u8"选择.."))
            ImGui::OpenPopup("my_select_popup");
        ImGui::SameLine();
        ImGui::TextUnformatted(selected_fish == -1 ? u8"<无>" : names[selected_fish]);
        if (ImGui::BeginPopup("my_select_popup"))
        {
            ImGui::SeparatorText(u8"水族馆");
            for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                if (ImGui::Selectable(names[i]))
                    selected_fish = i;
            ImGui::EndPopup();
        }

        // 显示带开关的菜单
        if (ImGui::Button(u8"切换.."))
            ImGui::OpenPopup("my_toggle_popup");
        if (ImGui::BeginPopup("my_toggle_popup"))
        {
            for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                ImGui::MenuItem(names[i], "", &toggles[i]);
            if (ImGui::BeginMenu(u8"子菜单"))
            {
                ImGui::MenuItem(u8"点击我");
                ImGui::EndMenu();
            }

            ImGui::Separator();
            ImGui::Text(u8"工具提示在这里");
            ImGui::SetItemTooltip(u8"我是一个弹出窗口上的工具提示");

            if (ImGui::Button(u8"堆叠弹出窗口"))
                ImGui::OpenPopup("another popup");
            if (ImGui::BeginPopup("another popup"))
            {
                for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                    ImGui::MenuItem(names[i], "", &toggles[i]);
                if (ImGui::BeginMenu(u8"子菜单"))
                {
                    ImGui::MenuItem(u8"点击我");
                    if (ImGui::Button(u8"堆叠弹出窗口"))
                        ImGui::OpenPopup("another popup");
                    if (ImGui::BeginPopup("another popup"))
                    {
                        ImGui::Text(u8"我是这里最后一个.");
                        ImGui::EndPopup();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }
            ImGui::EndPopup();
        }

        // 调用我们在本演示各个地方使用的更完整的 ShowExampleMenuFile
        if (ImGui::Button(u8"带菜单.."))
            ImGui::OpenPopup("my_file_popup");
        if (ImGui::BeginPopup("my_file_popup", ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu(u8"文件"))
                {
                    ShowExampleMenuFile();
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu(u8"编辑"))
                {
                    ImGui::MenuItem(u8"虚拟");
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Text(u8"来自弹出窗口的问候!");
            ImGui::Button(u8"这是一个虚拟按钮..");
            ImGui::EndPopup();
        }

        ImGui::TreePop();
    }
    IMGUI_DEMO_MARKER(u8"弹出窗口/上下文菜单");
    if (ImGui::TreeNode(u8"上下文菜单"))
    {
        HelpMarker(u8"\"上下文\"函数是简单的辅助函数，用于将弹出窗口与给定的项目或窗口标识符关联.");

        // BeginPopupContextItem() 是一个辅助函数，提供常见/简单的弹出行为，本质上执行：
        //     if (id == 0)
        //         id = GetItemID(); // 使用最后一个项目ID
        //     if (IsItemHovered() && IsMouseReleased(ImGuiMouseButton_Right))
        //         OpenPopup(id);
        //     return BeginPopup(id);
        // 对于高级用途，您可能需要复制和自定义此代码.
        // 更多详细信息请参见 BeginPopupContextItem().

        // 示例 1
        // 当在具有ID的项目（例如Button）之后使用时，我们可以跳过向BeginPopupContextItem()提供ID，
        // BeginPopupContextItem() 将使用最后一个项目ID作为弹出窗口ID.
        {
            const char* names[5] = { u8"标签1", u8"标签2", u8"标签3", u8"标签4", u8"标签5" };
            static int selected = -1;
            for (int n = 0; n < 5; n++)
            {
                if (ImGui::Selectable(names[n], selected == n))
                    selected = n;
                if (ImGui::BeginPopupContextItem()) // <-- 使用最后一个项目ID作为弹出窗口ID
                {
                    selected = n;
                    ImGui::Text(u8"这是 \"%s\" 的弹出窗口!", names[n]);
                    if (ImGui::Button(u8"关闭"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }
                ImGui::SetItemTooltip(u8"右键单击打开弹出窗口");
            }
        }

        // 示例 2
        // 在Text()元素上弹出窗口，该元素没有标识符：我们需要向BeginPopupContextItem()提供一个标识符.
        // 如果您想从不同位置激活弹出窗口，使用显式标识符也很方便.
        {
            HelpMarker(u8"Text()元素没有稳定的标识符，所以我们需要提供一个.");
            static float value = 0.5f;
            ImGui::Text(u8"值 = %.3f <-- (1) 右键单击此文本", value);
            if (ImGui::BeginPopupContextItem(u8"我的弹出窗口"))
            {
                if (ImGui::Selectable(u8"设置为零")) value = 0.0f;
                if (ImGui::Selectable(u8"设置为PI")) value = 3.1415f;
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::DragFloat(u8"##值", &value, 0.1f, 0.0f, 0.0f);
                ImGui::EndPopup();
            }

            // 我们也可以使用 OpenPopupOnItemClick() 来切换给定弹出窗口的可见性.
            // 这里我们使得右键单击此其他文本元素会打开与上面相同的弹出窗口.
            // 弹出窗口本身将由上面的代码提交.
            ImGui::Text(u8"(2) 或者右键单击此文本");
            ImGui::OpenPopupOnItemClick(u8"我的弹出窗口", ImGuiPopupFlags_MouseButtonRight);

            // 回到起点：手动打开相同的弹出窗口.
            if (ImGui::Button(u8"(3) 或者单击此按钮"))
                ImGui::OpenPopup(u8"我的弹出窗口");
        }

        // 示例 3
        // 当使用带有隐式标识符的BeginPopupContextItem()时（NULL == 使用最后一个项目ID），
        // 我们需要确保您的项目标识符是稳定的.
        // 在此示例中，我们展示了在保留其标识符的同时更改项目标签，使用###运算符（参见FAQ）.
        {
            HelpMarker(u8"展示使用链接到项目ID的弹出窗口ID，该项目具有变化的标签 + 使用###运算符的稳定ID.");
            static char name[32] = u8"标签1";
            char buf[64];
            sprintf(buf, u8"按钮: %s###按钮", name); // ### 运算符覆盖ID，忽略前面的标签
            ImGui::Button(buf);
            if (ImGui::BeginPopupContextItem())
            {
                ImGui::Text(u8"编辑名称:");
                ImGui::InputText(u8"##编辑", name, IM_ARRAYSIZE(name));
                if (ImGui::Button(u8"关闭"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
            ImGui::SameLine(); ImGui::Text(u8"(<-- 右键单击此处)");
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"弹出窗口/模态窗口");
    if (ImGui::TreeNode(u8"模态窗口"))
    {
        ImGui::TextWrapped(u8"模态窗口类似于弹出窗口，但用户无法通过单击外部来关闭它们.");

        if (ImGui::Button(u8"删除.."))
            ImGui::OpenPopup(u8"删除?");

        // 出现时始终将此窗口居中
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(u8"删除?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text(u8"所有那些美丽的文件将被删除.\n此操作无法撤消!");
            ImGui::Separator();

            //static int unused_i = 0;
            //ImGui::Combo(u8"组合框", &unused_i, u8"删除\0更彻底地删除\0");

            static bool dont_ask_me_next_time = false;
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
            ImGui::Checkbox(u8"下次不要再问我", &dont_ask_me_next_time);
            ImGui::PopStyleVar();

            if (ImGui::Button(u8"确定", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button(u8"取消", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();
        }

        if (ImGui::Button(u8"堆叠模态窗口.."))
            ImGui::OpenPopup(u8"堆叠 1");
        if (ImGui::BeginPopupModal(u8"堆叠 1", NULL, ImGuiWindowFlags_MenuBar))
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu(u8"文件"))
                {
                    if (ImGui::MenuItem(u8"某个菜单项")) {}
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Text(u8"你好，来自第一个堆叠窗口\n在其后面使用 style.Colors[ImGuiCol_ModalWindowDimBg].");

            // 测试小部件在模态窗口之上堆叠它们自己的常规弹出窗口的行为.
            static int item = 1;
            static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ImGui::Combo(u8"组合框", &item, u8"aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
            ImGui::ColorEdit4(u8"颜色", color);

            if (ImGui::Button(u8"添加另一个模态窗口.."))
                ImGui::OpenPopup(u8"堆叠 2");

            // 还演示了向BeginPopupModal()传递一个bool*，这将创建一个常规的关闭按钮
            // 该按钮将关闭弹出窗口.请注意，弹出窗口的可见性状态由imgui拥有，因此
            // bool的输入值实际上在这里并不重要.
            bool unused_open = true;
            if (ImGui::BeginPopupModal(u8"堆叠 2", &unused_open))
            {
                ImGui::Text(u8"你好，来自第二个堆叠窗口!");
                ImGui::ColorEdit4(u8"颜色", color); // 允许打开另一个嵌套弹出窗口
                if (ImGui::Button(u8"关闭"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }

            if (ImGui::Button(u8"关闭"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }

        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"弹出窗口/常规窗口内的菜单");
    if (ImGui::TreeNode(u8"常规窗口内的菜单"))
    {
        ImGui::TextWrapped(u8"下面我们测试向常规窗口添加菜单项.这相当不寻常，但应该工作!");
        ImGui::Separator();

        ImGui::MenuItem(u8"菜单项", u8"CTRL+M");
        if (ImGui::BeginMenu(u8"常规窗口内的菜单")) {
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        ImGui::Separator();
        ImGui::TreePop();
    }
}

// Dummy data structure that we use for the Table demo.
// (pre-C++11 doesn't allow us to instantiate ImVector<MyItem> template if this structure is defined inside the demo function)
namespace
{
    // We are passing our own identifier to TableSetupColumn() to facilitate identifying columns in the sorting code.
    // This identifier will be passed down into ImGuiTableSortSpec::ColumnUserID.
    // But it is possible to omit the user id parameter of TableSetupColumn() and just use the column index instead! (ImGuiTableSortSpec::ColumnIndex)
    // If you don't use sorting, you will generally never care about giving column an ID!
    enum MyItemColumnID
    {
        MyItemColumnID_ID,
        MyItemColumnID_Name,
        MyItemColumnID_Action,
        MyItemColumnID_Quantity,
        MyItemColumnID_Description
    };

    struct MyItem
    {
        int         ID;
        const char* Name;
        int         Quantity;

        // We have a problem which is affecting _only this demo_ and should not affect your code:
        // As we don't rely on std:: or other third-party library to compile dear imgui, we only have reliable access to qsort(),
        // however qsort doesn't allow passing user data to comparing function.
        // As a workaround, we are storing the sort specs in a static/global for the comparing function to access.
        // In your own use case you would probably pass the sort specs to your sorting/comparing functions directly and not use a global.
        // We could technically call ImGui::TableGetSortSpecs() in CompareWithSortSpecs(), but considering that this function is called
        // very often by the sorting algorithm it would be a little wasteful.
        static const ImGuiTableSortSpecs* s_current_sort_specs;

        static void SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, MyItem* items, int items_count)
        {
            s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
            if (items_count > 1)
                qsort(items, (size_t)items_count, sizeof(items[0]), MyItem::CompareWithSortSpecs);
            s_current_sort_specs = NULL;
        }

        // Compare function to be used by qsort()
        static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs)
        {
            const MyItem* a = (const MyItem*)lhs;
            const MyItem* b = (const MyItem*)rhs;
            for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
            {
                // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
                // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
                const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
                int delta = 0;
                switch (sort_spec->ColumnUserID)
                {
                case MyItemColumnID_ID:             delta = (a->ID - b->ID);                break;
                case MyItemColumnID_Name:           delta = (strcmp(a->Name, b->Name));     break;
                case MyItemColumnID_Quantity:       delta = (a->Quantity - b->Quantity);    break;
                case MyItemColumnID_Description:    delta = (strcmp(a->Name, b->Name));     break;
                default: IM_ASSERT(0); break;
                }
                if (delta > 0)
                    return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
                if (delta < 0)
                    return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
            }

            // qsort() is instable so always return a way to differentiate items.
            // Your own compare function may want to avoid fallback on implicit sort specs.
            // e.g. a Name compare if it wasn't already part of the sort specs.
            return (a->ID - b->ID);
        }
    };
    const ImGuiTableSortSpecs* MyItem::s_current_sort_specs = NULL;
}

// Make the UI compact because there are so many fields
static void PushStyleCompact()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::PushStyleVarY(ImGuiStyleVar_FramePadding, (float)(int)(style.FramePadding.y * 0.60f));
    ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, (float)(int)(style.ItemSpacing.y * 0.60f));
}

static void PopStyleCompact()
{
    ImGui::PopStyleVar(2);
}

// Show a combo box with a choice of sizing policies
static void EditTableSizingFlags(ImGuiTableFlags* p_flags)
{
    struct EnumDesc { ImGuiTableFlags Value; const char* Name; const char* Tooltip; };
    static const EnumDesc policies[] =
    {
        { ImGuiTableFlags_None,               u8"默认",                            u8"使用默认 sizing 策略:\n- 如果 ScrollX 开启或宿主窗口有 ImGuiWindowFlags_AlwaysAutoResize，则使用 ImGuiTableFlags_SizingFixedFit.\n- 否则使用 ImGuiTableFlags_SizingStretchSame." },
        { ImGuiTableFlags_SizingFixedFit,     u8"ImGuiTableFlags_SizingFixedFit",     u8"列默认为 _WidthFixed (如果可调整大小) 或 _WidthAuto (如果不可调整大小), 匹配内容宽度." },
        { ImGuiTableFlags_SizingFixedSame,    u8"ImGuiTableFlags_SizingFixedSame",    u8"所有列宽度相同，匹配最大内容宽度.\n隐式禁用 ImGuiTableFlags_Resizable 并启用 ImGuiTableFlags_NoKeepColumnsVisible." },
        { ImGuiTableFlags_SizingStretchProp,  u8"ImGuiTableFlags_SizingStretchProp",  u8"列默认为 _WidthStretch，权重与其宽度成比例." },
        { ImGuiTableFlags_SizingStretchSame,  u8"ImGuiTableFlags_SizingStretchSame",  u8"列默认为 _WidthStretch，权重相同." }
    };
    int idx;
    for (idx = 0; idx < IM_ARRAYSIZE(policies); idx++)
        if (policies[idx].Value == (*p_flags & ImGuiTableFlags_SizingMask_))
            break;
    const char* preview_text = (idx < IM_ARRAYSIZE(policies)) ? policies[idx].Name + (idx > 0 ? strlen("ImGuiTableFlags") : 0) : "";
    if (ImGui::BeginCombo(u8"Sizing Policy", preview_text))
    {
        for (int n = 0; n < IM_ARRAYSIZE(policies); n++)
            if (ImGui::Selectable(policies[n].Name, idx == n))
                *p_flags = (*p_flags & ~ImGuiTableFlags_SizingMask_) | policies[n].Value;
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::TextDisabled(u8"(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 50.0f);
        for (int m = 0; m < IM_ARRAYSIZE(policies); m++)
        {
            ImGui::Separator();
            ImGui::Text(u8"%s:", policies[m].Name);
            ImGui::Separator();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().IndentSpacing * 0.5f);
            ImGui::TextUnformatted(policies[m].Tooltip);
        }
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

static void EditTableColumnsFlags(ImGuiTableColumnFlags* p_flags)
{
    ImGui::CheckboxFlags(u8"_Disabled", p_flags, ImGuiTableColumnFlags_Disabled); ImGui::SameLine(); HelpMarker(u8"主禁用标志（同时从上下文菜单中隐藏）");
    ImGui::CheckboxFlags(u8"_DefaultHide", p_flags, ImGuiTableColumnFlags_DefaultHide);
    ImGui::CheckboxFlags(u8"_DefaultSort", p_flags, ImGuiTableColumnFlags_DefaultSort);
    if (ImGui::CheckboxFlags(u8"_WidthStretch", p_flags, ImGuiTableColumnFlags_WidthStretch))
        *p_flags &= ~(ImGuiTableColumnFlags_WidthMask_ ^ ImGuiTableColumnFlags_WidthStretch);
    if (ImGui::CheckboxFlags(u8"_WidthFixed", p_flags, ImGuiTableColumnFlags_WidthFixed))
        *p_flags &= ~(ImGuiTableColumnFlags_WidthMask_ ^ ImGuiTableColumnFlags_WidthFixed);
    ImGui::CheckboxFlags(u8"_NoResize", p_flags, ImGuiTableColumnFlags_NoResize);
    ImGui::CheckboxFlags(u8"_NoReorder", p_flags, ImGuiTableColumnFlags_NoReorder);
    ImGui::CheckboxFlags(u8"_NoHide", p_flags, ImGuiTableColumnFlags_NoHide);
    ImGui::CheckboxFlags(u8"_NoClip", p_flags, ImGuiTableColumnFlags_NoClip);
    ImGui::CheckboxFlags(u8"_NoSort", p_flags, ImGuiTableColumnFlags_NoSort);
    ImGui::CheckboxFlags(u8"_NoSortAscending", p_flags, ImGuiTableColumnFlags_NoSortAscending);
    ImGui::CheckboxFlags(u8"_NoSortDescending", p_flags, ImGuiTableColumnFlags_NoSortDescending);
    ImGui::CheckboxFlags(u8"_NoHeaderLabel", p_flags, ImGuiTableColumnFlags_NoHeaderLabel);
    ImGui::CheckboxFlags(u8"_NoHeaderWidth", p_flags, ImGuiTableColumnFlags_NoHeaderWidth);
    ImGui::CheckboxFlags(u8"_PreferSortAscending", p_flags, ImGuiTableColumnFlags_PreferSortAscending);
    ImGui::CheckboxFlags(u8"_PreferSortDescending", p_flags, ImGuiTableColumnFlags_PreferSortDescending);
    ImGui::CheckboxFlags(u8"_IndentEnable", p_flags, ImGuiTableColumnFlags_IndentEnable); ImGui::SameLine(); HelpMarker(u8"列 0 的默认值");
    ImGui::CheckboxFlags(u8"_IndentDisable", p_flags, ImGuiTableColumnFlags_IndentDisable); ImGui::SameLine(); HelpMarker(u8"列 >0 的默认值");
    ImGui::CheckboxFlags(u8"_AngledHeader", p_flags, ImGuiTableColumnFlags_AngledHeader);
}

static void ShowTableColumnsStatusFlags(ImGuiTableColumnFlags flags)
{
    ImGui::CheckboxFlags(u8"_IsEnabled", &flags, ImGuiTableColumnFlags_IsEnabled);
    ImGui::CheckboxFlags(u8"_IsVisible", &flags, ImGuiTableColumnFlags_IsVisible);
    ImGui::CheckboxFlags(u8"_IsSorted", &flags, ImGuiTableColumnFlags_IsSorted);
    ImGui::CheckboxFlags(u8"_IsHovered", &flags, ImGuiTableColumnFlags_IsHovered);
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowTables()
//-----------------------------------------------------------------------------

static void DemoWindowTables()
{
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    IMGUI_DEMO_MARKER(u8"表格");
    if (!ImGui::CollapsingHeader(u8"表格和列"))
        return;

    // 使用这些作为基础值来创建基于我们字体大小的宽度/高度
    const float TEXT_BASE_WIDTH = ImGui::CalcTextSize(u8"A").x;
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

    ImGui::PushID(u8"表格");

    int open_action = -1;
    if (ImGui::Button(u8"全部展开"))
        open_action = 1;
    ImGui::SameLine();
    if (ImGui::Button(u8"全部折叠"))
        open_action = 0;
    ImGui::SameLine();

    // 选项
    static bool disable_indent = false;
    ImGui::Checkbox(u8"禁用树节点缩进", &disable_indent);
    ImGui::SameLine();
    HelpMarker(u8"禁用树节点的缩进，以便演示表格可以使用整个窗口宽度.");
    ImGui::Separator();
    if (disable_indent)
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);

    // 关于表格样式
    // 大多数设置是通过传递给 BeginTable() 和 TableSetupColumns API 的标志在每个表格的基础上配置的.
    // 但是，有一些设置是共享的，并且是 ImGuiStyle 结构的一部分：
    //   style.CellPadding                          // 每个单元格内的内边距
    //   style.Colors[ImGuiCol_TableHeaderBg]       // 表头背景
    //   style.Colors[ImGuiCol_TableBorderStrong]   // 表格外边框和表头边框
    //   style.Colors[ImGuiCol_TableBorderLight]    // 表格内边框
    //   style.Colors[ImGuiCol_TableRowBg]          // 当启用 ImGuiTableFlags_RowBg 时的表格行背景（偶数行）
    //   style.Colors[ImGuiCol_TableRowBgAlt]       // 当启用 ImGuiTableFlags_RowBg 时的表格行背景（奇数行）

    // 演示
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/基础");
    if (ImGui::TreeNode(u8"基础"))
    {
        // 这里我们将展示三种不同的输出表格的方法.
        // 它们是同一事物的非常简单的变化!

        // [方法 1] 使用 TableNextRow() 创建新行，并使用 TableSetColumnIndex() 选择列.
        // 在许多情况下，这是最灵活和易于使用的模式.
        HelpMarker(u8"使用 TableNextRow() + 在每个单元格之前调用 TableSetColumnIndex()，在循环中.");
        if (ImGui::BeginTable("table1", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"行 %d 列 %d", row, column);
                }
            }
            ImGui::EndTable();
        }

        // [方法 2] 多次调用 TableNextColumn()，而不是使用 for 循环 + TableSetColumnIndex().
        // 当您手动提交每列的内容时，这通常更方便.
        HelpMarker(u8"使用 TableNextRow() + 在每个单元格之前调用 TableNextColumn()，手动.");
        if (ImGui::BeginTable("table2", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text(u8"行 %d", row);
                ImGui::TableNextColumn();
                ImGui::Text(u8"一些内容");
                ImGui::TableNextColumn();
                ImGui::Text(u8"123.456");
            }
            ImGui::EndTable();
        }

        // [方法 3] 我们在每个单元格之前调用 TableNextColumn().我们从不调用 TableNextRow()，
        // 因为 TableNextColumn() 会自动换行并根据需要创建新行.
        // 当您的所有单元格都包含相同类型的数据时，这通常更方便.
        HelpMarker(
            u8"仅使用 TableNextColumn()，这对于每个单元格都包含相同类型内容的表格往往很方便.\n这也更类似于旧 Columns API 的 NextColumn() 函数，并提供以便于 Columns->Tables API 的过渡.");
        if (ImGui::BeginTable("table3", 3))
        {
            for (int item = 0; item < 14; item++)
            {
                ImGui::TableNextColumn();
                ImGui::Text(u8"项目 %d", item);
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/边框, 背景");
    if (ImGui::TreeNode(u8"边框, 背景"))
    {
        // 交互式地公开一些与边框相关的标志
        enum ContentsType { CT_Text, CT_FillButton };
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        static bool display_headers = false;
        static int contents_type = CT_Text;

        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_Borders", &flags, ImGuiTableFlags_Borders);
        ImGui::SameLine(); HelpMarker(u8"ImGuiTableFlags_Borders\n = ImGuiTableFlags_BordersInnerV\n | ImGuiTableFlags_BordersOuterV\n | ImGuiTableFlags_BordersInnerH\n | ImGuiTableFlags_BordersOuterH");
        ImGui::Indent();

        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersH", &flags, ImGuiTableFlags_BordersH);
        ImGui::Indent();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersOuterH", &flags, ImGuiTableFlags_BordersOuterH);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersInnerH", &flags, ImGuiTableFlags_BordersInnerH);
        ImGui::Unindent();

        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
        ImGui::Indent();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersOuterV", &flags, ImGuiTableFlags_BordersOuterV);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersInnerV", &flags, ImGuiTableFlags_BordersInnerV);
        ImGui::Unindent();

        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersOuter", &flags, ImGuiTableFlags_BordersOuter);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersInner", &flags, ImGuiTableFlags_BordersInner);
        ImGui::Unindent();

        ImGui::AlignTextToFramePadding(); ImGui::Text(u8"单元格内容:");
        ImGui::SameLine(); ImGui::RadioButton(u8"文本", &contents_type, CT_Text);
        ImGui::SameLine(); ImGui::RadioButton(u8"填充按钮", &contents_type, CT_FillButton);
        ImGui::Checkbox(u8"显示表头", &display_headers);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody); ImGui::SameLine(); HelpMarker(u8"在列主体中禁用垂直边框（边框将始终出现在表头中）");
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            // 显示表头以便我们可以检查它们与边框的交互
            // (表头不是本演示部分的主要目的，因此我们现在不详细说明.有关详细信息，请参阅其他部分)
            if (display_headers)
            {
                ImGui::TableSetupColumn(u8"一");
                ImGui::TableSetupColumn(u8"二");
                ImGui::TableSetupColumn(u8"三");
                ImGui::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    char buf[32];
                    sprintf(buf, u8"Hello %d,%d", column, row);
                    if (contents_type == CT_Text)
                        ImGui::TextUnformatted(buf);
                    else if (contents_type == CT_FillButton)
                        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/可调整大小, 拉伸");
    if (ImGui::TreeNode(u8"可调整大小, 拉伸"))
    {
        // 默认情况下，如果我们不启用 ScrollX，每列的 sizing 策略是 "Stretch"
        // 所有列都维护一个 sizing 权重，它们将占据所有可用宽度.
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
        ImGui::SameLine(); HelpMarker(
            u8"使用 _Resizable 标志会自动启用 _BordersInnerV 标志，\n"
            u8"这就是为什么在取消勾选此项时调整大小的边框仍然显示.");
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/可调整大小, 固定");
    if (ImGui::TreeNode(u8"可调整大小, 固定"))
    {
        // 这里我们使用 ImGuiTableFlags_SizingFixedFit（即使没有设置 _ScrollX）
        // 所以列将采用 "Fixed" 策略，并将保持固定宽度，无论整个可用宽度如何（除非表格很小）
        // 如果没有足够的可用宽度来容纳所有列，它们将被调整大小.
        // FIXME-TABLE: 提供一个初始拉伸对于没有保存设置的表格尤其有意义
        HelpMarker(
            u8"使用 _Resizable + _SizingFixedFit 标志.\n"
            u8"固定宽度的列通常更有意义，如果您想使用水平滚动.\n\n"
            u8"双击列边框以自动调整列以适应其内容.");
        PushStyleCompact();
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/可调整大小, 混合");
    if (ImGui::TreeNode(u8"可调整大小, 混合"))
    {
        HelpMarker(
            u8"使用 TableSetupColumn() 来按列更改调整大小策略.\n\n"
            u8"当结合固定和拉伸列时，通常您只希望一个或两个尾随列使用 _WidthStretch.");
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

        if (ImGui::BeginTable("table1", 3, flags))
        {
            ImGui::TableSetupColumn(u8"AAA", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(u8"BBB", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(u8"CCC", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"%s %d,%d", (column == 2) ? u8"拉伸" : u8"固定", column, row);
                }
            }
            ImGui::EndTable();
        }
        if (ImGui::BeginTable("table2", 6, flags))
        {
            ImGui::TableSetupColumn(u8"AAA", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(u8"BBB", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn(u8"CCC", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide);
            ImGui::TableSetupColumn(u8"DDD", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn(u8"EEE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn(u8"FFF", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultHide);
            ImGui::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 6; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"%s %d,%d", (column >= 3) ? u8"拉伸" : u8"固定", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/可重新排序, 可隐藏, 带表头");
    if (ImGui::TreeNode(u8"可重新排序, 可隐藏, 带表头"))
    {
        HelpMarker(
            u8"单击并拖动列标题以重新排序列.\n\n"
            u8"右键单击标题以打开上下文菜单.");
        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;
        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_Reorderable", &flags, ImGuiTableFlags_Reorderable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_Hideable", &flags, ImGuiTableFlags_Hideable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_NoBordersInBodyUntilResize", &flags, ImGuiTableFlags_NoBordersInBodyUntilResize); ImGui::SameLine(); HelpMarker(u8"在列主体中禁用垂直边框，直到悬停调整大小（边框将始终出现在表头中）");
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
        PopStyleCompact();

        if (ImGui::BeginTable(u8"表格1", 3, flags))
        {
            // 使用 TableSetupColumn() 提交列名，并调用 TableHeadersRow() 以创建带有每个列标题的行.
            // （稍后我们将展示 TableSetupColumn() 的其他用途、可选标志、 sizing 权重等.）
            ImGui::TableSetupColumn(u8"一");
            ImGui::TableSetupColumn(u8"二");
            ImGui::TableSetupColumn(u8"三");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        // 使用 outer_size.x == 0.0f 而不是默认值，以使表格尽可能紧凑
        // （仅在无滚动且无拉伸列时有效）
        if (ImGui::BeginTable(u8"表格2", 3, flags | ImGuiTableFlags_SizingFixedFit, ImVec2(0.0f, 0.0f)))
        {
            ImGui::TableSetupColumn(u8"一");
            ImGui::TableSetupColumn(u8"二");
            ImGui::TableSetupColumn(u8"三");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"固定 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/内边距");
    if (ImGui::TreeNode(u8"内边距"))
    {
        // 第一个示例：展示 padding 标志的使用以及 BorderOuterV/BorderInnerV 对 X 内边距的影响.
        // 我们不在这里暴露 BorderOuterH/BorderInnerH，因为它们对 X 内边距没有影响.
        HelpMarker(
            u8"我们通常希望在任何使用使列边缘可见的功能时激活外部内边距：\n"
            u8"例如：\n"
            u8"- 边界外V(BorderOuterV)\n"
            u8"- 任何形式的行选择\n"
            u8"因此，激活 BorderOuterV 会将默认值设置为 PadOuterX.\n"
            u8"使用 PadOuterX 或 NoPadOuterX，您可以覆盖默认值.\n\n"
            u8"实际的内边距值使用 style.CellPadding.\n\n"
            u8"在此演示中，我们不显示水平边框以强调它们如何不影响默认的水平内边距.");

        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV;
        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_垫外X", &flags1, ImGuiTableFlags_PadOuterX);
        ImGui::SameLine(); HelpMarker(u8"启用最外层的内边距（如果设置了 ImGuiTableFlags_BordersOuterV，则为默认值）");
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_无垫OuterX", &flags1, ImGuiTableFlags_NoPadOuterX);
        ImGui::SameLine(); HelpMarker(u8"禁用最外层的内边距（如果未设置 ImGuiTableFlags_BordersOuterV，则为默认值）");
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_无垫内X（NoPadInnerX）", &flags1, ImGuiTableFlags_NoPadInnerX);
        ImGui::SameLine(); HelpMarker(u8"禁用列之间的内部内边距（如果 BordersOuterV 开启，则为双内部内边距；如果 BordersOuterV 关闭，则为单内部内边距）");
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界外层V", &flags1, ImGuiTableFlags_BordersOuterV);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界内部V", &flags1, ImGuiTableFlags_BordersInnerV);
        static bool show_headers = false;
        ImGui::Checkbox("显示", &show_headers);
        PopStyleCompact();

        if (ImGui::BeginTable(u8"表_填充", 3, flags1))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn(u8"一");
                ImGui::TableSetupColumn(u8"二");
                ImGui::TableSetupColumn(u8"三");
                ImGui::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                    {
                        ImGui::Text(u8"可用 %.2f", ImGui::GetContentRegionAvail().x);
                    }
                    else
                    {
                        char buf[32];
                        sprintf(buf, "Hello %d,%d", column, row);
                        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                    }
                    //if (ImGui::TableGetColumnFlags() & ImGuiTableColumnFlags_IsHovered)
                    //    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 100, 0, 255));
                }
            }
            ImGui::EndTable();
        }
        // Second example: set style.CellPadding to (0.0) or a custom value.
        // FIXME-TABLE: Vertical border effectively not displayed the same way as horizontal one...
        HelpMarker(u8"将 style.CellPadding 设置为 (0,0) 或自定义值.");
        static ImGuiTableFlags flags2 = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        static ImVec2 cell_padding(0.0f, 0.0f);
        static bool show_widget_frame_bg = true;

        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界", &flags2, ImGuiTableFlags_Borders);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界H", &flags2, ImGuiTableFlags_BordersH);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界V", &flags2, ImGuiTableFlags_BordersV);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_内边框", &flags2, ImGuiTableFlags_BordersInner);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_边界外", &flags2, ImGuiTableFlags_BordersOuter);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_行?Bg", &flags2, ImGuiTableFlags_RowBg);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_可调整大小", &flags2, ImGuiTableFlags_Resizable);
        ImGui::Checkbox(u8"显示_控件_框架_bg", &show_widget_frame_bg);
        ImGui::SliderFloat2(u8"单元格填充", &cell_padding.x, 0.0f, 10.0f, "%.0f");
        PopStyleCompact();

        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cell_padding);
        if (ImGui::BeginTable(u8"表格_填充_2", 3, flags2))
        {
            static char text_bufs[3 * 5][16]; // 3x5 单元格的迷你文本存储
            static bool init = true;
            if (!show_widget_frame_bg)
                ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);
            for (int cell = 0; cell < 3 * 5; cell++)
            {
                ImGui::TableNextColumn();
                if (init)
                    strcpy(text_bufs[cell], u8"编辑我");
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::PushID(cell);
                ImGui::InputText("##cell", text_bufs[cell], IM_ARRAYSIZE(text_bufs[cell]));
                ImGui::PopID();
            }
            if (!show_widget_frame_bg)
                ImGui::PopStyleColor();
            init = false;
            ImGui::EndTable();
        }
        ImGui::PopStyleVar();

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/显式宽度");
    if (ImGui::TreeNode(u8"调整大小策略"))
    {
        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_可调整大小", &flags1, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags1, ImGuiTableFlags_NoHostExtendX);
        PopStyleCompact();

        static ImGuiTableFlags sizing_policy_flags[4] = { ImGuiTableFlags_SizingFixedFit, ImGuiTableFlags_SizingFixedSame, ImGuiTableFlags_SizingStretchProp, ImGuiTableFlags_SizingStretchSame };
        for (int table_n = 0; table_n < 4; table_n++)
        {
            ImGui::PushID(table_n);
            ImGui::SetNextItemWidth(TEXT_BASE_WIDTH * 30);
            EditTableSizingFlags(&sizing_policy_flags[table_n]);

            // 为了更容易理解不同的 sizing 策略，
            // 对于每个策略：我们显示一个表格，其中列具有相等的内容宽度，
            // 和一个列具有不同内容宽度的表格.
            if (ImGui::BeginTable(u8"表格1", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                }
                ImGui::EndTable();
            }
            if (ImGui::BeginTable(u8"表格2", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn(); ImGui::Text(u8"AAAA");
                    ImGui::TableNextColumn(); ImGui::Text(u8"BBBBBBBB");
                    ImGui::TableNextColumn(); ImGui::Text(u8"CCCCCCCCCCCC");
                }
                ImGui::EndTable();
            }
            ImGui::PopID();
        }

        ImGui::Spacing();
        ImGui::TextUnformatted(u8"高级");
        ImGui::SameLine();
        HelpMarker(
            u8"此部分允许您交互并查看各种 sizing 策略的效果，"
            u8"具体取决于是否启用了 Scroll 以及列的内容.");

        enum ContentsType { CT_ShowWidth, CT_ShortText, CT_LongText, CT_Button, CT_FillButton, CT_InputText };
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
        static int contents_type = CT_ShowWidth;
        static int column_count = 3;

        PushStyleCompact();
        ImGui::PushID(u8"高级");
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 30);
        EditTableSizingFlags(&flags);
        ImGui::Combo(u8"内容", &contents_type, u8"显示宽度\0短文本\0长文本\0按钮\0填充按钮\0输入文本\0");
        if (contents_type == CT_FillButton)
        {
            ImGui::SameLine();
            HelpMarker(
                u8"请注意，使用右对齐（例如 size.x = -FLT_MIN）会创建一个反馈循环，"
                u8"其中内容宽度可以反馈到自动列宽度，然后反馈到内容宽度.");
        }
        ImGui::DragInt(u8"列数", &column_count, 0.1f, 1, 64, "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_可调整大小", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_精确宽度", &flags, ImGuiTableFlags_PreciseWidths);
        ImGui::SameLine(); HelpMarker(u8"禁用将剩余宽度分配给拉伸列（在 100 宽度的表上分配 3 列：无此标志：33,33,34.有此标志：33,33,33）.列数较多时，调整大小会显得不太平滑.");
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动条X", &flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动条Y", &flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_无夹", &flags, ImGuiTableFlags_NoClip);
        ImGui::PopItemWidth();
        ImGui::PopID();
        PopStyleCompact();

        if (ImGui::BeginTable(u8"表格2", column_count, flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 7)))
        {
            for (int cell = 0; cell < 10 * column_count; cell++)
            {
                ImGui::TableNextColumn();
                int column = ImGui::TableGetColumnIndex();
                int row = ImGui::TableGetRowIndex();

                ImGui::PushID(cell);
                char label[32];
                static char text_buf[32] = "";
                sprintf(label, "Hello %d,%d", column, row);
                switch (contents_type)
                {
                case CT_ShortText:  ImGui::TextUnformatted(label); break;
                case CT_LongText:   ImGui::Text(u8"一些 %s 文本 %d,%d\n超过两行..", column == 0 ? u8"长" : u8"更长", column, row); break;
                case CT_ShowWidth:  ImGui::Text(u8"宽: %.1f", ImGui::GetContentRegionAvail().x); break;
                case CT_Button:     ImGui::Button(label); break;
                case CT_FillButton: ImGui::Button(label, ImVec2(-FLT_MIN, 0.0f)); break;
                case CT_InputText:  ImGui::SetNextItemWidth(-FLT_MIN); ImGui::InputText(u8"##", text_buf, IM_ARRAYSIZE(text_buf)); break;
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/垂直滚动, 带裁剪");
    if (ImGui::TreeNode(u8"垂直滚动, 带裁剪"))
    {
        HelpMarker(
            u8"这里我们激活 ScrollY，它将创建一个子窗口容器来允许托管可滚动内容.\n\n"
            u8"我们还演示了使用 ImGuiListClipper 来虚拟化许多项目的提交.");
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动Y", &flags, ImGuiTableFlags_ScrollY);
        PopStyleCompact();

        // 当使用 ScrollX 或 ScrollY 时，我们需要为表格容器指定一个大小!
        // 否则，默认情况下表格将适合所有可用空间，就像 BeginChild() 调用一样.
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (ImGui::BeginTable(u8"表格_scrolly", 3, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(0, 1); // 使顶行始终可见
            ImGui::TableSetupColumn(u8"一", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn(u8"二", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn(u8"三", ImGuiTableColumnFlags_None);
            ImGui::TableHeadersRow();

            // 演示使用 clipper 处理大型垂直列表
            ImGuiListClipper clipper;
            clipper.Begin(1000);
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 3; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text("Hello %d,%d", column, row);
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/水平滚动");
    if (ImGui::TreeNode(u8"水平滚动"))
    {
        HelpMarker(
            u8"当启用滚动时，默认的 sizing 策略变为 ImGuiTableFlags_SizingFixedFit."
            u8"因为自动拉伸列在水平滚动时没有太大意义.\n\n"
            u8"另请注意，在当前版本中，您几乎总是希望同时启用滚动Y和滚动X"
            u8"因为容器窗口不会自动垂直扩展以修复内容"
            u8"这可能会在未来的版本中改进.");
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
        static int freeze_cols = 1;
        static int freeze_rows = 1;

        PushStyleCompact();
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_可调整大小", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动X", &flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动Y", &flags, ImGuiTableFlags_ScrollY);
        ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
        ImGui::DragInt(u8"冻结_cols", &freeze_cols, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
        ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
        ImGui::DragInt(u8"冻结_rows", &freeze_rows, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
        PopStyleCompact();

        // 当使用 ScrollX 或 ScrollY 时，我们需要为表格容器指定一个大小!
        // 否则，默认情况下表格将适合所有可用空间，就像 BeginChild() 调用一样.
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (ImGui::BeginTable(u8"表格_scrollx", 7, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);
            ImGui::TableSetupColumn(u8"行号", ImGuiTableColumnFlags_NoHide); // 使第一列不可隐藏以匹配我们对 TableSetupScrollFreeze() 的使用
            ImGui::TableSetupColumn(u8"一");
            ImGui::TableSetupColumn(u8"二");
            ImGui::TableSetupColumn(u8"三");
            ImGui::TableSetupColumn(u8"四");
            ImGui::TableSetupColumn(u8"五");
            ImGui::TableSetupColumn(u8"六");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 20; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 7; column++)
                {
                    // TableNextColumn() 和 TableSetColumnIndex() 在列可见或执行宽度测量时都返回 true.
                    // 因为这里我们知道：
                    // - A) 我们所有的列对行高的贡献相同
                    // - B) 列 0 始终可见，
                    // 我们只始终提交这一列，可以跳过其他列.
                    // 更高级的每列裁剪行为可能会受益于通过 TableGetColumnFlags() 轮询状态标志.
                    if (!ImGui::TableSetColumnIndex(column) && column > 0)
                        continue;
                    if (column == 0)
                        ImGui::Text(u8"行 %d", row);
                    else
                        ImGui::Text("Hello world %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::TextUnformatted(u8"拉伸+滚动X");
        ImGui::SameLine();
        HelpMarker(
            u8"展示同时使用伸展列和滚动X："
            u8"这相当不寻常，只有在为表格指定 'inner_width' 时才有意义!\n"
            u8"没有显式值时，inner_width == outer_size.x，因此使用伸展列"
            u8"与滚动X一起使用没有意义.");
        static ImGuiTableFlags flags2 = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
        static float inner_width = 1000.0f;
        PushStyleCompact();
        ImGui::PushID(u8"flags3");
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 30);
        ImGui::CheckboxFlags(u8"ImGuiTableFlags_滚动X", &flags2, ImGuiTableFlags_ScrollX);
        ImGui::DragFloat(u8"inner_宽度", &inner_width, 1.0f, 0.0f, FLT_MAX, "%.1f");
        ImGui::PopItemWidth();
        ImGui::PopID();
        PopStyleCompact();
        if (ImGui::BeginTable(u8"表格2", 7, flags2, outer_size, inner_width))
        {
            for (int cell = 0; cell < 20 * 7; cell++)
            {
                ImGui::TableNextColumn();
                ImGui::Text("Hello world %d,%d", ImGui::TableGetColumnIndex(), ImGui::TableGetRowIndex());
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/列标志");
    if (ImGui::TreeNode(u8"列标志"))
    {
        // 创建第一个表格，仅用于显示我们想要在示例中展示的所有选项/标志!
        const int column_count = 3;
        const char* column_names[column_count] = { u8"第一列", u8"第二列", u8"第三列" };
        static ImGuiTableColumnFlags column_flags[column_count] = { ImGuiTableColumnFlags_DefaultSort, ImGuiTableColumnFlags_None, ImGuiTableColumnFlags_DefaultHide };
        static ImGuiTableColumnFlags column_flags_out[column_count] = { 0, 0, 0 }; // TableGetColumnFlags() 的输出

        if (ImGui::BeginTable("table_columns_flags_checkboxes", column_count, ImGuiTableFlags_None))
        {
            PushStyleCompact();
            for (int column = 0; column < column_count; column++)
            {
                ImGui::TableNextColumn();
                ImGui::PushID(column);
                ImGui::AlignTextToFramePadding(); // FIXME-TABLE: 跨列文本基线传播错误的解决方法
                ImGui::Text("'%s'", column_names[column]);
                ImGui::Spacing();
                ImGui::Text(u8"输入标志:");
                EditTableColumnsFlags(&column_flags[column]);
                ImGui::Spacing();
                ImGui::Text(u8"输出标志:");
                ImGui::BeginDisabled();
                ShowTableColumnsStatusFlags(column_flags_out[column]);
                ImGui::EndDisabled();
                ImGui::PopID();
            }
            PopStyleCompact();
            ImGui::EndTable();
        }

        // 创建我们真正关心的示例表格!
        // 我们使用滚动表格来展示上面 _IsEnabled 和 _IsVisible 标志之间的区别，
        // 否则在非滚动表格中，列始终可见（除非使用 ImGuiTableFlags_NoKeepColumnsVisible
        // 并调整父窗口大小）.
        const ImGuiTableFlags flags
            = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV
            | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable;
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 9);
        if (ImGui::BeginTable("table_columns_flags", column_count, flags, outer_size))
        {
            bool has_angled_header = false;
            for (int column = 0; column < column_count; column++)
            {
                has_angled_header |= (column_flags[column] & ImGuiTableColumnFlags_AngledHeader) != 0;
                ImGui::TableSetupColumn(column_names[column], column_flags[column]);
            }
            if (has_angled_header)
                ImGui::TableAngledHeadersRow();
            ImGui::TableHeadersRow();
            for (int column = 0; column < column_count; column++)
                column_flags_out[column] = ImGui::TableGetColumnFlags(column);
            float indent_step = (float)((int)TEXT_BASE_WIDTH / 2);
            for (int row = 0; row < 8; row++)
            {
                // Add some indentation to demonstrate usage of per-column IndentEnable/IndentDisable flags.
                ImGui::Indent(indent_step);
                ImGui::TableNextRow();
                for (int column = 0; column < column_count; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"%s %s", (column == 0) ? u8"缩进" : u8"你好", ImGui::TableGetColumnName(column));
                }
            }
            ImGui::Unindent(indent_step * 8.0f);

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/列宽度");
    if (ImGui::TreeNode(u8"列宽度"))
    {
        HelpMarker(u8"使用 TableSetupColumn() 来设置默认宽度.");

        static ImGuiTableFlags flags1 = ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBodyUntilResize;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags1, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBodyUntilResize", &flags1, ImGuiTableFlags_NoBordersInBodyUntilResize);
        PopStyleCompact();
        if (ImGui::BeginTable("table1", 3, flags1))
        {
            // 我们也可以在表格上设置 ImGuiTableFlags_SizingFixedFit，这样所有列将默认为 ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn(u8"第一列", ImGuiTableColumnFlags_WidthFixed, 100.0f); // 默认为 100.0f
            ImGui::TableSetupColumn(u8"第二列", ImGuiTableColumnFlags_WidthFixed, 200.0f); // 默认为 200.0f
            ImGui::TableSetupColumn(u8"第三列", ImGuiTableColumnFlags_WidthFixed);       // 默认为自动
            ImGui::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                        ImGui::Text(u8"(宽度: %5.1f)", ImGui::GetContentRegionAvail().x);
                    else
                        ImGui::Text(u8"你好 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        HelpMarker(
            u8"使用 TableSetupColumn() 来设置显式宽度.\n\n除非设置了 _NoKeepColumnsVisible 标志，"
            u8"否则如果宿主空间不足，设置了宽度的固定列仍可能会被缩小.");

        static ImGuiTableFlags flags2 = ImGuiTableFlags_None;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_NoKeepColumnsVisible", &flags2, ImGuiTableFlags_NoKeepColumnsVisible);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags2, ImGuiTableFlags_BordersInnerV);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags2, ImGuiTableFlags_BordersOuterV);
        PopStyleCompact();
        if (ImGui::BeginTable("table2", 4, flags2))
        {
            // 我们也可以在表格上设置 ImGuiTableFlags_SizingFixedFit，然后所有列
            // 将默认为 ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 30.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 4; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                        ImGui::Text(u8"(宽度: %5.1f)", ImGui::GetContentRegionAvail().x);
                    else
                        ImGui::Text(u8"你好 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/嵌套表格");
    if (ImGui::TreeNode(u8"嵌套表格"))
    {
        HelpMarker(u8"这演示了如何将表格嵌入到另一个表格单元格中.");

        if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
        {
            ImGui::TableSetupColumn("A0");
            ImGui::TableSetupColumn("A1");
            ImGui::TableHeadersRow();

            ImGui::TableNextColumn();
            ImGui::Text("A0 Row 0");
            {
                float rows_height = TEXT_BASE_HEIGHT * 2;
                if (ImGui::BeginTable("table_nested2", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
                {
                    ImGui::TableSetupColumn("B0");
                    ImGui::TableSetupColumn("B1");
                    ImGui::TableHeadersRow();

                    ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                    ImGui::TableNextColumn();
                    ImGui::Text("B0 Row 0");
                    ImGui::TableNextColumn();
                    ImGui::Text("B1 Row 0");
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                    ImGui::TableNextColumn();
                    ImGui::Text("B0 Row 1");
                    ImGui::TableNextColumn();
                    ImGui::Text("B1 Row 1");

                    ImGui::EndTable();
                }
            }
            ImGui::TableNextColumn(); ImGui::Text("A1 Row 0");
            ImGui::TableNextColumn(); ImGui::Text("A0 Row 1");
            ImGui::TableNextColumn(); ImGui::Text("A1 Row 1");
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/行高");
    if (ImGui::TreeNode(u8"行高"))
    {
        HelpMarker(
            u8"您可以向 TableNextRow() 传递 'min_row_height' 参数.\n\n行的顶部和底部会使用 'style.CellPadding.y' 进行填充，"
            u8"因此实际的最小行高将始终 >= 'style.CellPadding.y * 2.0f'.\n\n"
            u8"我们无法支持_最大_行高，因为那需要为每一行使用独立的裁剪矩形.");
        if (ImGui::BeginTable("table_row_height", 1, ImGuiTableFlags_Borders))
        {
            for (int row = 0; row < 8; row++)
            {
                float min_row_height = (float)(int)(TEXT_BASE_HEIGHT * 0.30f * row);
                ImGui::TableNextRow(ImGuiTableRowFlags_None, min_row_height);
                ImGui::TableNextColumn();
                ImGui::Text(u8"min_row_height = %.2f", min_row_height);
            }
            ImGui::EndTable();
        }

        HelpMarker(
            u8"展示使用 SameLine(0,0) 在单元格之间共享当前行高.\n\n"
            u8"请注意，表格行高与当前行高不是同一概念，"
            u8"因为一个表格单元格可能包含多行文本.");
        if (ImGui::BeginTable("table_share_lineheight", 2, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::ColorButton("##1", ImVec4(0.13f, 0.26f, 0.40f, 1.0f), ImGuiColorEditFlags_None, ImVec2(40, 40));
            ImGui::TableNextColumn();
            ImGui::Text(u8"第 1 行");
            ImGui::Text(u8"第 2 行");

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::ColorButton("##2", ImVec4(0.13f, 0.26f, 0.40f, 1.0f), ImGuiColorEditFlags_None, ImVec2(40, 40));
            ImGui::TableNextColumn();
            ImGui::SameLine(0.0f, 0.0f); // 重用前一列的当前行高
            ImGui::Text(u8"第 1 行，使用 SameLine(0,0)");
            ImGui::Text(u8"第 2 行");

            ImGui::EndTable();
        }

        HelpMarker(u8"展示在行之间更改 CellPadding.y.请注意，CellPadding.x 对于整个表格是锁定的.");
        if (ImGui::BeginTable("table_changing_cellpadding_y", 1, ImGuiTableFlags_Borders))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            for (int row = 0; row < 8; row++)
            {
                if ((row % 3) == 2)
                    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(style.CellPadding.x, 20.0f));
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                ImGui::TableNextColumn();
                ImGui::Text(u8"CellPadding.y = %.2f", style.CellPadding.y);
                if ((row % 3) == 2)
                    ImGui::PopStyleVar();
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/外部尺寸");
    if (ImGui::TreeNode(u8"外部尺寸"))
    {
        // 展示使用 ImGuiTableFlags_NoHostExtendX 和 ImGuiTableFlags_NoHostExtendY
        // 需要注意的是这两个标志的行为略有不同!
        ImGui::Text(u8"使用 NoHostExtendX 和 NoHostExtendY:");
        PushStyleCompact();
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX;
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
        ImGui::SameLine(); HelpMarker(u8"使外部宽度自动适应列，覆盖 outer_size.x 值.\n\n仅在 ScrollX/ScrollY 禁用且未使用拉伸列时可用.");
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendY", &flags, ImGuiTableFlags_NoHostExtendY);
        ImGui::SameLine(); HelpMarker(u8"使外部高度精确停止在 outer_size.y（防止表格自动扩展超过限制）.\n\n仅在 ScrollX/ScrollY 禁用时可用.限制以下的数据将被裁剪且不可见.");
        PopStyleCompact();

        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 5.5f);
        if (ImGui::BeginTable("table1", 3, flags, outer_size))
        {
            for (int row = 0; row < 10; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"单元格 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::SameLine();
        ImGui::Text(u8"你好!");

        ImGui::Spacing();

        ImGui::Text(u8"使用显式尺寸:");
        if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"单元格 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::SameLine();
        if (ImGui::BeginTable("table3", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            for (int row = 0; row < 3; row++)
            {
                ImGui::TableNextRow(0, TEXT_BASE_HEIGHT * 1.5f);
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"单元格 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/背景颜色");
    if (ImGui::TreeNode(u8"背景颜色"))
    {
        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg;
        static int row_bg_type = 1;
        static int row_bg_target = 1;
        static int cell_bg_type = 1;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &flags, ImGuiTableFlags_Borders);
        ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
        ImGui::SameLine(); HelpMarker(u8"ImGuiTableFlags_RowBg 自动将 RowBg0 设置为从样式中提取的交替颜色.");
        ImGui::Combo(u8"行背景类型", (int*)&row_bg_type, u8"无\0红色\0渐变\0");
        ImGui::Combo(u8"行背景目标", (int*)&row_bg_target, u8"RowBg0\0RowBg1\0"); ImGui::SameLine(); HelpMarker(u8"目标 RowBg0 可覆盖交替的奇偶行颜色，\n目标 RowBg1 可与它们混合.");
        ImGui::Combo(u8"单元格背景类型", (int*)&cell_bg_type, u8"无\0蓝色\0"); ImGui::SameLine(); HelpMarker(u8"我们正在将 B1->C2 的单元格着色.");
        IM_ASSERT(row_bg_type >= 0 && row_bg_type <= 2);
        IM_ASSERT(row_bg_target >= 0 && row_bg_target <= 1);
        IM_ASSERT(cell_bg_type >= 0 && cell_bg_type <= 1);
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 5, flags))
        {
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();

                // 演示使用 'ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBgX, ...)' 设置行背景颜色
                // 我们使用透明颜色，这样如果目标是 RowBg1 且 RowBg0 已被 ImGuiTableFlags_RowBg 标志设置，我们可以看到后面的颜色.
                if (row_bg_type != 0)
                {
                    ImU32 row_bg_color = ImGui::GetColorU32(row_bg_type == 1 ? ImVec4(0.7f, 0.3f, 0.3f, 0.65f) : ImVec4(0.2f + row * 0.1f, 0.2f, 0.2f, 0.65f)); // 平面或渐变?
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + row_bg_target, row_bg_color);
                }

                // 填充单元格
                for (int column = 0; column < 5; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%c%c", 'A' + row, '0' + column);

                    // 更改 B1->C2 单元格的背景
                    // 演示使用 'ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ...)' 设置单元格背景颜色
                    // (CellBg 颜色将与 RowBg 和 ColumnBg 颜色混合)
                    // 我们还可以将列号作为第三个参数传递给 TableSetBgColor()，并在列循环外部执行此操作.
                    if (row >= 1 && row <= 2 && column >= 1 && column <= 2 && cell_bg_type == 1)
                    {
                        ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER("Tables/Tree view");
    if (ImGui::TreeNode("Tree view"))
    {
        static ImGuiTableFlags table_flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

        static ImGuiTreeNodeFlags tree_node_flags_base = ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_DrawLinesFull;
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth", &tree_node_flags_base, ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanLabelWidth", &tree_node_flags_base, ImGuiTreeNodeFlags_SpanLabelWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAllColumns", &tree_node_flags_base, ImGuiTreeNodeFlags_SpanAllColumns);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_LabelSpanAllColumns", &tree_node_flags_base, ImGuiTreeNodeFlags_LabelSpanAllColumns);
        ImGui::SameLine(); HelpMarker("Useful if you know that you aren't displaying contents in other columns");

        HelpMarker("See \"Columns flags\" section to configure how indentation is applied to individual columns.");
        if (ImGui::BeginTable("3ways", 3, table_flags))
        {
            // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
            ImGui::TableHeadersRow();
            // Simple storage to output a dummy file-system.
            struct MyTreeNode
            {
                const char* Name;
                const char* Type;
                int             Size;
                int             ChildIdx;
                int             ChildCount;
                static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);

                    ImGuiTreeNodeFlags node_flags = tree_node_flags_base;
                    if (node != &all_nodes[0])
                        node_flags &= ~ImGuiTreeNodeFlags_LabelSpanAllColumns; // Only demonstrate this on the root node.

                    if (is_folder)
                    {
                        bool open = ImGui::TreeNodeEx(node->Name, node_flags);
                        if ((node_flags & ImGuiTreeNodeFlags_LabelSpanAllColumns) == 0)
                        {
                            ImGui::TableNextColumn();
                            ImGui::TextDisabled("--");
                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted(node->Type);
                        }
                        if (open)
                        {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            ImGui::TreePop();
                        }
                    }
                    else
                    {
                        ImGui::TreeNodeEx(node->Name, node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", node->Size);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] =
            {
                { u8"根节点（长名称）",          u8"文件夹",       -1,       1, 3    }, // 0
                { u8"音乐",                        u8"文件夹",       -1,       4, 2    }, // 1
                { u8"纹理",                     u8"文件夹",       -1,       6, 3    }, // 2
                { "desktop.ini",                  u8"系统文件",  1024,    -1,-1    }, // 3
                { "File1_a.wav",                  u8"音频文件",   123000,  -1,-1    }, // 4
                { "File1_b.wav",                  u8"音频文件",   456000,  -1,-1    }, // 5
                { "Image001.png",                 u8"图像文件",   203128,  -1,-1    }, // 6
                { u8"Image001.png 的副本",         u8"图像文件",   203256,  -1,-1    }, // 7
                { u8"Image001 的副本 (Final2).png",u8"图像文件",   203512,  -1,-1    }, // 8
            };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/项目宽度");
    if (ImGui::TreeNode(u8"项目宽度"))
    {
        HelpMarker(
            u8"展示使用 PushItemWidth() 以及它如何在每列基础上保留.\n\n"
            u8"请注意，在自动调整大小的不可调整固定列上，查询内容宽度以进行右对齐等操作没有意义.");
        if (ImGui::BeginTable("table_item_width", 3, ImGuiTableFlags_Borders))
        {
            ImGui::TableSetupColumn(u8"小");
            ImGui::TableSetupColumn(u8"一半");
            ImGui::TableSetupColumn(u8"右对齐");
            ImGui::TableHeadersRow();

            for (int row = 0; row < 3; row++)
            {
                ImGui::TableNextRow();
                if (row == 0)
                {
                    // 设置一次 ItemWidth（而不是每次都设置，虽然也可以但效率较低）
                    ImGui::TableSetColumnIndex(0);
                    ImGui::PushItemWidth(TEXT_BASE_WIDTH * 3.0f); // 小
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.5f);
                    ImGui::TableSetColumnIndex(2);
                    ImGui::PushItemWidth(-FLT_MIN); // 右对齐
                }

                // 绘制内容
                static float dummy_f = 0.0f;
                ImGui::PushID(row);
                ImGui::TableSetColumnIndex(0);
                ImGui::SliderFloat(u8"浮点数0", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(1);
                ImGui::SliderFloat(u8"浮点数1", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(2);
                ImGui::SliderFloat("##float2", &dummy_f, 0.0f, 1.0f); // 没有可见标签，因为是右对齐
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // 演示使用 TableHeader() 调用而不是 TableHeadersRow()
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/自定义表头");
    if (ImGui::TreeNode(u8"自定义表头"))
    {
        const int COLUMNS_COUNT = 3;
        if (ImGui::BeginTable("table_custom_headers", COLUMNS_COUNT, ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
        {
            ImGui::TableSetupColumn(u8"杏子");
            ImGui::TableSetupColumn(u8"香蕉");
            ImGui::TableSetupColumn(u8"樱桃");

            // Dummy entire-column selection storage
            // FIXME: It would be nice to actually demonstrate full-featured selection using those checkbox.
            static bool column_selected[3] = {};

            // Instead of calling TableHeadersRow() we'll submit custom headers ourselves.
            // (A different approach is also possible:
            //    - Specify ImGuiTableColumnFlags_NoHeaderLabel in some TableSetupColumn() call.
            //    - Call TableHeadersRow() normally. This will submit TableHeader() with no name.
            //    - Then call TableSetColumnIndex() to position yourself in the column and submit your stuff e.g. Checkbox().)
            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            for (int column = 0; column < COLUMNS_COUNT; column++)
            {
                ImGui::TableSetColumnIndex(column);
                const char* column_name = ImGui::TableGetColumnName(column); // Retrieve name passed to TableSetupColumn()
                ImGui::PushID(column);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::Checkbox("##checkall", &column_selected[column]);
                ImGui::PopStyleVar();
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::TableHeader(column_name);
                ImGui::PopID();
            }

            // Submit table contents
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    char buf[32];
                    sprintf(buf, "Cell %d,%d", column, row);
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Selectable(buf, column_selected[column]);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // Demonstrate using ImGuiTableColumnFlags_AngledHeader flag to create angled headers
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/倾斜表头");
    if (ImGui::TreeNode(u8"倾斜表头"))
    {
        const char* column_names[] = { u8"轨道", u8"沙锤", u8"骑镲", u8"重击", u8"高音桶", u8"中音桶", u8"低音桶", u8"开踩镲", u8"闭踩镲", u8"边击", u8"中心击", u8"拍手", u8"rim", u8"底鼓" };
        const int columns_count = IM_ARRAYSIZE(column_names);
        const int rows_count = 12;

        static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_HighlightHoveredColumn;
        static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed;
        static bool bools[columns_count * rows_count] = {}; // 虚拟选择存储
        static int frozen_cols = 1;
        static int frozen_rows = 2;
        ImGui::CheckboxFlags("_ScrollX", &table_flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags("_ScrollY", &table_flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("_Resizable", &table_flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("_Sortable", &table_flags, ImGuiTableFlags_Sortable);
        ImGui::CheckboxFlags("_NoBordersInBody", &table_flags, ImGuiTableFlags_NoBordersInBody);
        ImGui::CheckboxFlags("_HighlightHoveredColumn", &table_flags, ImGuiTableFlags_HighlightHoveredColumn);
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::SliderInt(u8"冻结列数", &frozen_cols, 0, 2);
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::SliderInt(u8"冻结行数", &frozen_rows, 0, 2);
        ImGui::CheckboxFlags(u8"禁用表头影响列宽", &column_flags, ImGuiTableColumnFlags_NoHeaderWidth);

        if (ImGui::TreeNode(u8"样式设置"))
        {
            ImGui::SameLine();
            HelpMarker(u8"为了方便，在此演示中提供对一些 ImGuiStyle 值的访问.");
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::SliderAngle(u8"style.TableAngledHeadersAngle", &ImGui::GetStyle().TableAngledHeadersAngle, -50.0f, +50.0f);
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::SliderFloat2(u8"style.TableAngledHeadersTextAlign", (float*)&ImGui::GetStyle().TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");
            ImGui::TreePop();
        }

        if (ImGui::BeginTable("table_angled_headers", columns_count, table_flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 12)))
        {
            ImGui::TableSetupColumn(column_names[0], ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
            for (int n = 1; n < columns_count; n++)
                ImGui::TableSetupColumn(column_names[n], column_flags);
            ImGui::TableSetupScrollFreeze(frozen_cols, frozen_rows);

            ImGui::TableAngledHeadersRow(); // 为所有具有 ImGuiTableColumnFlags_AngledHeader 标志的列绘制倾斜表头
            ImGui::TableHeadersRow();       // 绘制剩余表头并允许访问上下文菜单和其他功能
            for (int row = 0; row < rows_count; row++)
            {
                ImGui::PushID(row);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                ImGui::Text(u8"轨道 %d", row);
                for (int column = 1; column < columns_count; column++)
                    if (ImGui::TableSetColumnIndex(column))
                    {
                        ImGui::PushID(column);
                        ImGui::Checkbox("", &bools[row * columns_count + column]);
                        ImGui::PopID();
                    }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // 演示在列内创建自定义上下文菜单，
    // 同时与 TableHeadersRow()/TableHeader() 提供的上下文菜单配合使用
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/上下文菜单");
    if (ImGui::TreeNode(u8"上下文菜单"))
    {
        HelpMarker(
            u8"默认情况下，在 TableHeadersRow()/TableHeader() 行上右键单击将打开默认上下文菜单.\n"
            u8"使用 ImGuiTableFlags_ContextMenuInBody，我们还允许在列体上右键单击.");
        static ImGuiTableFlags flags1 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_ContextMenuInBody;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_ContextMenuInBody", &flags1, ImGuiTableFlags_ContextMenuInBody);
        PopStyleCompact();

        // 上下文菜单：第一个示例
        // [1.1] 在 TableHeadersRow() 行上右键单击以打开默认表格上下文菜单
        // [1.2] 在列中右键单击也打开默认表格上下文菜单（如果设置了 ImGuiTableFlags_ContextMenuInBody）
        const int COLUMNS_COUNT = 3;
        if (ImGui::BeginTable("table_context_menu", COLUMNS_COUNT, flags1))
        {
            ImGui::TableSetupColumn(u8"第一列");
            ImGui::TableSetupColumn(u8"第二列");
            ImGui::TableSetupColumn(u8"第三列");

            // [1.1] 在 TableHeadersRow() 行上右键单击以打开默认表格上下文菜单
            ImGui::TableHeadersRow();

            // 提交虚拟内容
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"单元格 %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        // 上下文菜单：第二个示例
        // [2.1] 在 TableHeadersRow() 行上右键单击以打开默认表格上下文菜单
        // [2.2] 在 ".." 上右键单击以打开自定义弹出窗口
        // [2.3] 在列中右键单击以打开另一个自定义弹出窗口
        HelpMarker(
            u8"演示混合表格上下文菜单（在表头上）、项目上下文按钮（在按钮上）"
            u8"和每列自定义上下文菜单（在列体上）.");
        ImGuiTableFlags flags2 = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("table_context_menu_2", COLUMNS_COUNT, flags2))
        {
            ImGui::TableSetupColumn(u8"第一列");
            ImGui::TableSetupColumn(u8"第二列");
            ImGui::TableSetupColumn(u8"第三列");

            // [2.1] 在 TableHeadersRow() 行上右键单击以打开默认表格上下文菜单
            ImGui::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    // 提交虚拟内容
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text(u8"单元格 %d,%d", column, row);
                    ImGui::SameLine();

                    // [2.2] 在 ".." 上右键单击以打开自定义弹出窗口
                    ImGui::PushID(row * COLUMNS_COUNT + column);
                    ImGui::SmallButton("..");
                    if (ImGui::BeginPopupContextItem())
                    {
                        ImGui::Text(u8"这是单元格 %d,%d 中按钮(\"..\")的弹出窗口", column, row);
                        if (ImGui::Button(u8"关闭"))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                    }
                    ImGui::PopID();
                }
            }

            // [2.3] 在列中任意位置右键单击以打开另一个自定义弹出窗口
            // (我们可以测试 !IsAnyItemHovered()，也可以使用 ImGuiPopupFlags_NoOpenOverExistingPopup 调用 OpenPopup()
            // 来管理弹出窗口优先级，因为弹出窗口触发器在这里"我们是否悬停在列上"是重叠的)
            int hovered_column = -1;
            for (int column = 0; column < COLUMNS_COUNT + 1; column++)
            {
                ImGui::PushID(column);
                if (ImGui::TableGetColumnFlags(column) & ImGuiTableColumnFlags_IsHovered)
                    hovered_column = column;
                if (hovered_column == column && !ImGui::IsAnyItemHovered() && ImGui::IsMouseReleased(1))
                    ImGui::OpenPopup("MyPopup");
                if (ImGui::BeginPopup("MyPopup"))
                {
                    if (column == COLUMNS_COUNT)
                        ImGui::Text(u8"这是最后一列之后未使用空间的自定义弹出窗口");
                    else
                        ImGui::Text(u8"这是列 %d 的自定义弹出窗口", column);
                    if (ImGui::Button(u8"关闭"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }
                ImGui::PopID();
            }

            ImGui::EndTable();
            ImGui::Text(u8"悬停的列: %d", hovered_column);
        }
        ImGui::TreePop();
    }

    // 演示创建具有相同 ID 的多个表格
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/同步实例");
    if (ImGui::TreeNode(u8"同步实例"))
    {
        HelpMarker(u8"具有相同标识符的多个表格将共享它们的设置、宽度、可见性、顺序等.");

        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings;
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("ImGuiTableFlags_SizingFixedFit", &flags, ImGuiTableFlags_SizingFixedFit);
        ImGui::CheckboxFlags("ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
        for (int n = 0; n < 3; n++)
        {
            char buf[32];
            sprintf(buf, u8"同步表格 %d", n);
            bool open = ImGui::CollapsingHeader(buf, ImGuiTreeNodeFlags_DefaultOpen);
            if (open && ImGui::BeginTable("Table", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5)))
            {
                ImGui::TableSetupColumn(u8"第一列");
                ImGui::TableSetupColumn(u8"第二列");
                ImGui::TableSetupColumn(u8"第三列");
                ImGui::TableHeadersRow();
                const int cell_count = (n == 1) ? 27 : 9; // 让第二个表格有滚动条，以验证额外的装饰不影响列位置
                for (int cell = 0; cell < cell_count; cell++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text(u8"此单元格 %d", cell);
                }
                ImGui::EndTable();
            }
        }
        ImGui::TreePop();
    }

    // 演示使用排序功能
    // 这是"高级"示例的简化版本，我们主要关注处理排序所需的代码
    // 请注意，"高级"示例还展示了手动触发排序（例如，如果项目数量已修改）
    static const char* template_items_names[] =
    {
        u8"香蕉", u8"苹果", u8"樱桃", u8"西瓜", u8"葡萄柚", u8"草莓", u8"芒果",
        u8"猕猴桃", u8"橙子", u8"菠萝", u8"蓝莓", u8"李子", u8"椰子", u8"梨", u8"杏子"
    };
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/排序");
    if (ImGui::TreeNode(u8"排序"))
    {
        // Create item list
        static ImVector<MyItem> items;
        if (items.Size == 0)
        {
            items.resize(50, MyItem());
            for (int n = 0; n < items.Size; n++)
            {
                const int template_n = n % IM_ARRAYSIZE(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (n * n - n) % 20; // Assign default quantities
            }
        }

        // Options
        static ImGuiTableFlags flags =
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollY;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_SortMulti", &flags, ImGuiTableFlags_SortMulti);
        ImGui::SameLine(); HelpMarker(u8"启用排序时：按住Shift键单击表头可按多列排序.TableGetSortSpecs()可能返回(SpecsCount > 1)的规格.");
        ImGui::CheckboxFlags("ImGuiTableFlags_SortTristate", &flags, ImGuiTableFlags_SortTristate);
        ImGui::SameLine(); HelpMarker(u8"启用排序时：允许不排序，禁用默认排序.TableGetSortSpecs()可能返回(SpecsCount == 0)的规格.");
        PopStyleCompact();

        if (ImGui::BeginTable("table_sorting", 4, flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 15), 0.0f))
        {
            // 声明列
            // 我们使用TableSetupColumn()的"user_id"参数来指定将存储在排序规格中的用户ID.
            // 这样我们的排序函数可以根据我们自己的标识符识别列.我们也可以根据索引来识别它们!
            // 演示使用可用排序相关标志的混合：
            // - ImGuiTableColumnFlags_DefaultSort
            // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
            // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
            ImGui::TableSetupColumn(u8"ID", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_ID);
            ImGui::TableSetupColumn(u8"名称", ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
            ImGui::TableSetupColumn(u8"操作", ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
            ImGui::TableSetupColumn(u8"数量", ImGuiTableColumnFlags_PreferSortDescending | ImGuiTableColumnFlags_WidthStretch, 0.0f, MyItemColumnID_Quantity);
            ImGui::TableSetupScrollFreeze(0, 1); // 使行始终可见
            ImGui::TableHeadersRow();

            // 如果排序规格已更改，则对我们的数据进行排序!
            if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs())
                if (sort_specs->SpecsDirty)
                {
                    MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                    sort_specs->SpecsDirty = false;
                }

            // 演示对大型垂直列表使用裁剪器
            ImGuiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
                {
                    // 显示数据项
                    MyItem* item = &items[row_n];
                    ImGui::PushID(item->ID);
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%04d", item->ID);
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted(item->Name);
                    ImGui::TableNextColumn();
                    ImGui::SmallButton(u8"无");
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", item->Quantity);
                    ImGui::PopID();
                }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // In this example we'll expose most table flags and settings.
    // For specific flags and settings refer to the corresponding section for more detailed explanation.
    // This section is mostly useful to experiment with combining certain flags or settings with each others.
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once); // [DEBUG]
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    IMGUI_DEMO_MARKER(u8"表格/高级");
    if (ImGui::TreeNode(u8"高级"))
    {
        static ImGuiTableFlags flags =
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
            | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_SizingFixedFit;
        static ImGuiTableColumnFlags columns_base_flags = ImGuiTableColumnFlags_None;

        enum ContentsType { CT_Text, CT_Button, CT_SmallButton, CT_FillButton, CT_Selectable, CT_SelectableSpanRow };
        static int contents_type = CT_SelectableSpanRow;
        const char* contents_type_names[] = { u8"文本", u8"按钮", u8"小按钮", u8"填充按钮", u8"可选", u8"可选 (跨行)" };
        static int freeze_cols = 1;
        static int freeze_rows = 1;
        static int items_count = IM_ARRAYSIZE(template_items_names) * 2;
        static ImVec2 outer_size_value = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static float row_min_height = 0.0f; // 自动
        static float inner_width_with_scroll = 0.0f; // 自动扩展
        static bool outer_size_enabled = true;
        static bool show_headers = true;
        static bool show_wrapped_text = false;
        //static ImGuiTextFilter filter;
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once); // FIXME-TABLE: 启用此选项会导致表格初始首次通过时被裁剪，这往往会影响列大小调整
        if (ImGui::TreeNode(u8"选项"))
        {
            // 使UI紧凑，因为有很多字段
            PushStyleCompact();
            ImGui::PushItemWidth(TEXT_BASE_WIDTH * 28.0f);

            if (ImGui::TreeNodeEx(u8"功能:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Reorderable", &flags, ImGuiTableFlags_Reorderable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Hideable", &flags, ImGuiTableFlags_Hideable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Sortable", &flags, ImGuiTableFlags_Sortable);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoSavedSettings", &flags, ImGuiTableFlags_NoSavedSettings);
                ImGui::CheckboxFlags("ImGuiTableFlags_ContextMenuInBody", &flags, ImGuiTableFlags_ContextMenuInBody);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"装饰:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags, ImGuiTableFlags_BordersOuterV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags, ImGuiTableFlags_BordersInnerV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersH", &flags, ImGuiTableFlags_BordersH);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterH", &flags, ImGuiTableFlags_BordersOuterH);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerH", &flags, ImGuiTableFlags_BordersInnerH);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody); ImGui::SameLine(); HelpMarker(u8"禁用列体中的垂直边框（边框将始终出现在表头中）");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBodyUntilResize", &flags, ImGuiTableFlags_NoBordersInBodyUntilResize); ImGui::SameLine(); HelpMarker(u8"在列体中禁用垂直边框，直到悬停调整大小（边框将始终出现在表头中）");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"大小调整:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                EditTableSizingFlags(&flags);
                ImGui::SameLine(); HelpMarker(u8"在高级演示中，我们覆盖了每列的策略，因此这些表格范围的设置比典型设置影响小.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
                ImGui::SameLine(); HelpMarker(u8"使外部宽度自动适应列，覆盖outer_size.x值.\n\n仅在ScrollX/ScrollY禁用且未使用拉伸列时可用.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendY", &flags, ImGuiTableFlags_NoHostExtendY);
                ImGui::SameLine(); HelpMarker(u8"使外部高度精确停止在outer_size.y（防止表格自动扩展超过限制）.\n\n仅在ScrollX/ScrollY禁用时可用.限制以下的数据将被裁剪且不可见.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoKeepColumnsVisible", &flags, ImGuiTableFlags_NoKeepColumnsVisible);
                ImGui::SameLine(); HelpMarker(u8"仅在ScrollX禁用时可用.");
                ImGui::CheckboxFlags("ImGuiTableFlags_PreciseWidths", &flags, ImGuiTableFlags_PreciseWidths);
                ImGui::SameLine(); HelpMarker(u8"禁用将剩余宽度分配给拉伸列（在100宽的表上有3列时的宽度分配：无此标志：33,33,34.有此标志：33,33,33）.列数较多时，调整大小会显得不太平滑.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoClip", &flags, ImGuiTableFlags_NoClip);
                ImGui::SameLine(); HelpMarker(u8"禁用每个单独列的裁剪矩形（减少绘制命令计数，项目将能够溢出到其他列）.通常与ScrollFreeze选项不兼容.");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"内边距:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_PadOuterX", &flags, ImGuiTableFlags_PadOuterX);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoPadOuterX", &flags, ImGuiTableFlags_NoPadOuterX);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoPadInnerX", &flags, ImGuiTableFlags_NoPadInnerX);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"滚动:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags, ImGuiTableFlags_ScrollX);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
                ImGui::DragInt(u8"冻结列数", &freeze_cols, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
                ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
                ImGui::DragInt(u8"冻结行数", &freeze_rows, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"排序:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_SortMulti", &flags, ImGuiTableFlags_SortMulti);
                ImGui::SameLine(); HelpMarker(u8"启用排序时：按住Shift键单击表头可按多列排序.TableGetSortSpecs()可能返回(SpecsCount > 1)的规格.");
                ImGui::CheckboxFlags("ImGuiTableFlags_SortTristate", &flags, ImGuiTableFlags_SortTristate);
                ImGui::SameLine(); HelpMarker(u8"启用排序时：允许不排序，禁用默认排序.TableGetSortSpecs()可能返回(SpecsCount == 0)的规格.");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"表头:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox(u8"显示表头", &show_headers);
                ImGui::CheckboxFlags("ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
                ImGui::CheckboxFlags("ImGuiTableColumnFlags_AngledHeader", &columns_base_flags, ImGuiTableColumnFlags_AngledHeader);
                ImGui::SameLine(); HelpMarker(u8"在所有列上启用AngledHeader.最好在选定的窄列上启用（参见演示的\"倾斜表头\"部分）.");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx(u8"其他:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox(u8"显示包裹文本", &show_wrapped_text);

                ImGui::DragFloat2("##OuterSize", &outer_size_value.x);
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Checkbox(u8"外部尺寸", &outer_size_enabled);
                ImGui::SameLine();
                HelpMarker(u8"如果滚动被禁用（ScrollX和ScrollY未设置）：\n"
                    u8"- 表格直接输出在父窗口中.\n"
                    u8"- OuterSize.x < 0.0f 将使表格右对齐.\n"
                    u8"- OuterSize.x = 0.0f 将狭窄适应表格，除非有任何拉伸列.\n"
                    u8"- OuterSize.y 然后成为表格的最小尺寸，如果有更多行，将垂直扩展（除非设置了NoHostExtendY）.");

                // 从用户的角度来看，我们将根据表格是否嵌入滚动来不同地使用'internal_width'.
                // 为了方便试验此演示，当ScrollX禁用时，我们实际上将0.0f传递给BeginTable().
                ImGui::DragFloat(u8"内部宽度 (当ScrollX激活时)", &inner_width_with_scroll, 1.0f, 0.0f, FLT_MAX);

                ImGui::DragFloat(u8"行最小高度", &row_min_height, 1.0f, 0.0f, FLT_MAX);
                ImGui::SameLine(); HelpMarker(u8"指定可选项目的高度.");

                ImGui::DragInt(u8"项目数量", &items_count, 0.1f, 0, 9999);
                ImGui::Combo(u8"项目类型 (第一列)", &contents_type, contents_type_names, IM_ARRAYSIZE(contents_type_names));
                //filter.Draw("filter");
                ImGui::TreePop();
            }

            ImGui::PopItemWidth();
            PopStyleCompact();
            ImGui::Spacing();
            ImGui::TreePop();
        }
        // Update item list if we changed the number of items
        static ImVector<MyItem> items;
        static ImVector<int> selection;
        static bool items_need_sort = false;
        if (items.Size != items_count)
        {
            items.resize(items_count, MyItem());
            for (int n = 0; n < items_count; n++)
            {
                const int template_n = n % IM_ARRAYSIZE(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (template_n == 3) ? 10 : (template_n == 4) ? 20 : 0; // Assign default quantities
            }
        }

        const ImDrawList* parent_draw_list = ImGui::GetWindowDrawList();
        const int parent_draw_list_draw_cmd_count = parent_draw_list->CmdBuffer.Size;
        ImVec2 table_scroll_cur, table_scroll_max; // For debug display
        const ImDrawList* table_draw_list = NULL;  // "

        // Submit table
        const float inner_width_to_use = (flags & ImGuiTableFlags_ScrollX) ? inner_width_with_scroll : 0.0f;
        if (ImGui::BeginTable("table_advanced", 6, flags, outer_size_enabled ? outer_size_value : ImVec2(0, 0), inner_width_to_use))
        {
            // 声明列
            // 我们使用 TableSetupColumn() 的 "user_id" 参数来指定将存储在排序规范中的用户 ID.
            // 这样我们的排序函数就可以根据我们自己的标识符来识别列.我们也可以根据索引来识别它们!
            ImGui::TableSetupColumn(u8"ID", columns_base_flags | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f, MyItemColumnID_ID);
            ImGui::TableSetupColumn(u8"名称", columns_base_flags | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
            ImGui::TableSetupColumn(u8"操作", columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
            ImGui::TableSetupColumn(u8"数量", columns_base_flags | ImGuiTableColumnFlags_PreferSortDescending, 0.0f, MyItemColumnID_Quantity);
            ImGui::TableSetupColumn(u8"描述", columns_base_flags | ((flags & ImGuiTableFlags_NoHostExtendX) ? 0 : ImGuiTableColumnFlags_WidthStretch), 0.0f, MyItemColumnID_Description);
            ImGui::TableSetupColumn(u8"隐藏", columns_base_flags | ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_NoSort);
            ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);

            // Sort our data if sort specs have been changed!
            ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs();
            if (sort_specs && sort_specs->SpecsDirty)
                items_need_sort = true;
            if (sort_specs && items_need_sort && items.Size > 1)
            {
                MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                sort_specs->SpecsDirty = false;
            }
            items_need_sort = false;

            // Take note of whether we are currently sorting based on the Quantity field,
            // we will use this to trigger sorting when we know the data of this column has been modified.
            const bool sorts_specs_using_quantity = (ImGui::TableGetColumnFlags(3) & ImGuiTableColumnFlags_IsSorted) != 0;

            // Show headers
            if (show_headers && (columns_base_flags & ImGuiTableColumnFlags_AngledHeader) != 0)
                ImGui::TableAngledHeadersRow();
            if (show_headers)
                ImGui::TableHeadersRow();

            // Show data
            // FIXME-TABLE FIXME-NAV: How we can get decent up/down even though we have the buttons here?
#if 1
            // Demonstrate using clipper for large vertical lists
            ImGuiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
            {
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
#else
            // Without clipper
                {
                    for (int row_n = 0; row_n < items.Size; row_n++)
#endif
                    {
                        MyItem* item = &items[row_n];
                        //if (!filter.PassFilter(item->Name))
                        //    continue;

                        const bool item_is_selected = selection.contains(item->ID);
                        ImGui::PushID(item->ID);
                        ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                        // For the demo purpose we can select among different type of items submitted in the first column
                        ImGui::TableSetColumnIndex(0);
                        char label[32];
                        sprintf(label, "%04d", item->ID);
                        if (contents_type == CT_Text)
                            ImGui::TextUnformatted(label);
                        else if (contents_type == CT_Button)
                            ImGui::Button(label);
                        else if (contents_type == CT_SmallButton)
                            ImGui::SmallButton(label);
                        else if (contents_type == CT_FillButton)
                            ImGui::Button(label, ImVec2(-FLT_MIN, 0.0f));
                        else if (contents_type == CT_Selectable || contents_type == CT_SelectableSpanRow)
                        {
                            ImGuiSelectableFlags selectable_flags = (contents_type == CT_SelectableSpanRow) ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap : ImGuiSelectableFlags_None;
                            if (ImGui::Selectable(label, item_is_selected, selectable_flags, ImVec2(0, row_min_height)))
                            {
                                if (ImGui::GetIO().KeyCtrl)
                                {
                                    if (item_is_selected)
                                        selection.find_erase_unsorted(item->ID);
                                    else
                                        selection.push_back(item->ID);
                                }
                                else
                                {
                                    selection.clear();
                                    selection.push_back(item->ID);
                                }
                            }
                        }

                        if (ImGui::TableSetColumnIndex(1))
                            ImGui::TextUnformatted(item->Name);

                        // Here we demonstrate marking our data set as needing to be sorted again if we modified a quantity,
                        // and we are currently sorting on the column showing the Quantity.
                        // To avoid triggering a sort while holding the button, we only trigger it when the button has been released.
                        // You will probably need some extra logic if you want to automatically sort when a specific entry changes.
                        if (ImGui::TableSetColumnIndex(2))
                        {
                            if (ImGui::SmallButton(u8"切碎")) { item->Quantity += 1; }
                            if (sorts_specs_using_quantity && ImGui::IsItemDeactivated()) { items_need_sort = true; }
                            ImGui::SameLine();
                            if (ImGui::SmallButton(u8"吃掉")) { item->Quantity -= 1; }
                            if (sorts_specs_using_quantity && ImGui::IsItemDeactivated()) { items_need_sort = true; }
                        }

                        if (ImGui::TableSetColumnIndex(3))
                            ImGui::Text("%d", item->Quantity);

                        ImGui::TableSetColumnIndex(4);
                        if (show_wrapped_text)
                            ImGui::TextWrapped(u8"这是一段示例文本");
                        else
                            ImGui::Text(u8"这是一段示例文本");
                        if (ImGui::TableSetColumnIndex(5))
                            ImGui::Text("1234");

                        ImGui::PopID();
                    }
                }

                // Store some info to display debug details below
                table_scroll_cur = ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY());
                table_scroll_max = ImVec2(ImGui::GetScrollMaxX(), ImGui::GetScrollMaxY());
                table_draw_list = ImGui::GetWindowDrawList();
                ImGui::EndTable();
            }
        static bool show_debug_details = false;
        ImGui::Checkbox(u8"调试详情", &show_debug_details);
        if (show_debug_details && table_draw_list)
        {
            ImGui::SameLine(0.0f, 0.0f);
            const int table_draw_list_draw_cmd_count = table_draw_list->CmdBuffer.Size;
            if (table_draw_list == parent_draw_list)
                ImGui::Text(u8": 绘制命令: +%d (在同一窗口中)",
                    table_draw_list_draw_cmd_count - parent_draw_list_draw_cmd_count);
            else
                ImGui::Text(u8": 绘制命令: +%d (在子窗口中), 滚动: (%.f/%.f) (%.f/%.f)", table_draw_list_draw_cmd_count - 1, table_scroll_cur.x, table_scroll_max.x, table_scroll_cur.y, table_scroll_max.y);
        }
        ImGui::TreePop();
        }

    ImGui::PopID();

    DemoWindowColumns();

    if (disable_indent)
        ImGui::PopStyleVar();
    }

// Demonstrate old/legacy Columns API!
// [2020: Columns are under-featured and not maintained. Prefer using the more flexible and powerful BeginTable() API!]
static void DemoWindowColumns()
{
    IMGUI_DEMO_MARKER(u8"列 (传统 API)");
    bool open = ImGui::TreeNode(u8"传统列 API");
    ImGui::SameLine();
    HelpMarker(u8"Columns() 是一个旧的 API!建议使用更灵活和强大的 BeginTable() API!");
    if (!open)
        return;

    // 基本列
    IMGUI_DEMO_MARKER(u8"列 (传统 API)/基本");
    if (ImGui::TreeNode(u8"基本"))
    {
        ImGui::Text(u8"无边框:");
        ImGui::Columns(3, "mycolumns3", false);  // 3列，无边框
        ImGui::Separator();
        for (int n = 0; n < 14; n++)
        {
            char label[32];
            sprintf(label, u8"项目 %d", n);
            if (ImGui::Selectable(label)) {}
            //if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::Separator();

        ImGui::Text(u8"有边框:");
        ImGui::Columns(4, "mycolumns"); // 4列，有边框
        ImGui::Separator();
        ImGui::Text(u8"ID"); ImGui::NextColumn();
        ImGui::Text(u8"名称"); ImGui::NextColumn();
        ImGui::Text(u8"路径"); ImGui::NextColumn();
        ImGui::Text(u8"悬停"); ImGui::NextColumn();
        ImGui::Separator();
        const char* names[3] = { u8"一", u8"二", u8"三" };
        const char* paths[3] = { u8"/路径/一", u8"/路径/二", u8"/路径/三" };
        static int selected = -1;
        for (int i = 0; i < 3; i++)
        {
            char label[32];
            sprintf(label, u8"%04d", i);
            if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
                selected = i;
            bool hovered = ImGui::IsItemHovered();
            ImGui::NextColumn();
            ImGui::Text(names[i]); ImGui::NextColumn();
            ImGui::Text(paths[i]); ImGui::NextColumn();
            ImGui::Text(u8"%d", hovered); ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"列 (传统 API)/边框");
    if (ImGui::TreeNode(u8"边框"))
    {
        // 注意：未来的列 API 应该允许自动水平边框.
        static bool h_borders = true;
        static bool v_borders = true;
        static int columns_count = 4;
        const int lines_count = 3;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt(u8"##columns_count", &columns_count, 0.1f, 2, 10, u8"%d 列");
        if (columns_count < 2)
            columns_count = 2;
        ImGui::SameLine();
        ImGui::Checkbox(u8"水平", &h_borders);
        ImGui::SameLine();
        ImGui::Checkbox(u8"垂直", &v_borders);
        ImGui::Columns(columns_count, NULL, v_borders);
        for (int i = 0; i < columns_count * lines_count; i++)
        {
            if (h_borders && ImGui::GetColumnIndex() == 0)
                ImGui::Separator();
            ImGui::PushID(i);
            ImGui::Text(u8"%c%c%c", 'a' + i, 'a' + i, 'a' + i);
            ImGui::Text(u8"宽度 %.2f", ImGui::GetColumnWidth());
            ImGui::Text(u8"可用 %.2f", ImGui::GetContentRegionAvail().x);
            ImGui::Text(u8"偏移 %.2f", ImGui::GetColumnOffset());
            ImGui::Text(u8"可能被裁剪的长文本");
            ImGui::Button(u8"按钮", ImVec2(-FLT_MIN, 0.0f));
            ImGui::PopID();
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        if (h_borders)
            ImGui::Separator();
        ImGui::TreePop();
    }

    // 在同一单元格中创建多个项目，然后切换到下一列
    IMGUI_DEMO_MARKER(u8"列 (传统 API)/混合项目");
    if (ImGui::TreeNode(u8"混合项目"))
    {
        ImGui::Columns(3, "mixed");
        ImGui::Separator();

        ImGui::Text(u8"你好");
        ImGui::Button(u8"香蕉");
        ImGui::NextColumn();

        ImGui::Text(u8"ImGui");
        ImGui::Button(u8"苹果");
        static float foo = 1.0f;
        ImGui::InputFloat(u8"红色", &foo, 0.05f, 0, "%.3f");
        ImGui::Text(u8"这里多了一行.");
        ImGui::NextColumn();

        ImGui::Text(u8"水手");
        ImGui::Button(u8"花椰菜");
        static float bar = 1.0f;
        ImGui::InputFloat(u8"蓝色", &bar, 0.05f, 0, "%.3f");
        ImGui::NextColumn();

        if (ImGui::CollapsingHeader(u8"类别 A")) { ImGui::Text(u8"等等等等"); } ImGui::NextColumn();
        if (ImGui::CollapsingHeader(u8"类别 B")) { ImGui::Text(u8"等等等等"); } ImGui::NextColumn();
        if (ImGui::CollapsingHeader(u8"类别 C")) { ImGui::Text(u8"等等等等"); } ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    // 单词换行
    IMGUI_DEMO_MARKER(u8"列 (传统 API)/单词换行");
    if (ImGui::TreeNode(u8"单词换行"))
    {
        ImGui::Columns(2, "word-wrapping");
        ImGui::Separator();
        ImGui::TextWrapped(u8"快速的棕色狐狸跳过了懒惰的狗.");
        ImGui::TextWrapped(u8"左边你好");
        ImGui::NextColumn();
        ImGui::TextWrapped(u8"快速的棕色狐狸跳过了懒惰的狗.");
        ImGui::TextWrapped(u8"右边你好");
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"列 (传统 API)/水平滚动");
    if (ImGui::TreeNode(u8"水平滚动"))
    {
        ImGui::SetNextWindowContentSize(ImVec2(1500.0f, 0.0f));
        ImVec2 child_size = ImVec2(0, ImGui::GetFontSize() * 20.0f);
        ImGui::BeginChild(u8"##滚动区域", child_size, ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::Columns(10);

        // 同时演示使用裁剪器处理大型垂直列表
        int ITEMS_COUNT = 2000;
        ImGuiListClipper clipper;
        clipper.Begin(ITEMS_COUNT);
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                for (int j = 0; j < 10; j++)
                {
                    ImGui::Text(u8"行 %d 列 %d...", i, j);
                    ImGui::NextColumn();
                }
        }
        ImGui::Columns(1);
        ImGui::EndChild();
        ImGui::TreePop();
    }

    IMGUI_DEMO_MARKER(u8"列 (传统 API)/树");
    if (ImGui::TreeNode(u8"树"))
    {
        ImGui::Columns(2, "tree", true);
        for (int x = 0; x < 3; x++)
        {
            bool open1 = ImGui::TreeNode((void*)(intptr_t)x, u8"节点%d", x);
            ImGui::NextColumn();
            ImGui::Text(u8"节点内容");
            ImGui::NextColumn();
            if (open1)
            {
                for (int y = 0; y < 3; y++)
                {
                    bool open2 = ImGui::TreeNode((void*)(intptr_t)y, u8"节点%d.%d", x, y);
                    ImGui::NextColumn();
                    ImGui::Text(u8"节点内容");
                    if (open2)
                    {
                        ImGui::Text(u8"更多内容");
                        if (ImGui::TreeNode(u8"列中的树"))
                        {
                            ImGui::Text(u8"快速的棕色狐狸跳过了懒惰的狗");
                            ImGui::TreePop();
                        }
                    }
                    ImGui::NextColumn();
                    if (open2)
                        ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }
        ImGui::Columns(1);
        ImGui::TreePop();
    }

    ImGui::TreePop();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowInputs()
//-----------------------------------------------------------------------------

static void DemoWindowInputs()
{
    IMGUI_DEMO_MARKER(u8"输入与焦点");
    if (ImGui::CollapsingHeader(u8"输入与焦点"))
    {
        ImGuiIO& io = ImGui::GetIO();

        // 显示提交到 ImGuiIO 的输入
        IMGUI_DEMO_MARKER(u8"输入与焦点/输入");
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        bool inputs_opened = ImGui::TreeNode(u8"输入");
        ImGui::SameLine();
        HelpMarker(
            u8"这是一个简化视图.查看更详细的输入状态：\n"
            u8"- 在 '工具->指标/调试器->输入' 中.\n"
            u8"- 在 '工具->调试日志->IO' 中.");
        if (inputs_opened)
        {
            if (ImGui::IsMousePosValid())
                ImGui::Text(u8"鼠标位置: (%g, %g)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text(u8"鼠标位置: <无效>");
            ImGui::Text(u8"鼠标增量: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
            ImGui::Text(u8"鼠标按下:");
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text(u8"b%d (%.02f 秒)", i, io.MouseDownDuration[i]); }
            ImGui::Text(u8"鼠标滚轮: %.1f", io.MouseWheel);
            ImGui::Text(u8"鼠标点击计数:");
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseClickedCount[i] > 0) { ImGui::SameLine(); ImGui::Text("b%d: %d", i, io.MouseClickedCount[i]); }

            // 我们同时迭代传统的本地范围和命名的 ImGuiKey 范围.这有点不寻常/奇怪，但这允许
            // 显示旧/新后端的数据.
            // 用户代码永远不应该经历这样的麻烦!
            // 您通常可以在 ImGuiKey_NamedKey_BEGIN 和 ImGuiKey_NamedKey_END 之间迭代.
            struct funcs { static bool IsLegacyNativeDupe(ImGuiKey) { return false; } };
            ImGuiKey start_key = ImGuiKey_NamedKey_BEGIN;
            ImGui::Text(u8"按键按下:");         for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine(); ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key); }
            ImGui::Text(u8"按键修饰符: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
            ImGui::Text(u8"字符队列:");       for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // 修复：我们应该在这里将 'c' 转换为 UTF-8，但函数不是公开的.

            ImGui::TreePop();
        }

        // 显示 ImGuiIO 输出标志
        IMGUI_DEMO_MARKER(u8"输入与焦点/输出");
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        bool outputs_opened = ImGui::TreeNode(u8"输出");
        ImGui::SameLine();
        HelpMarker(
            u8"io.WantCaptureMouse 和 io.WantCaptureKeyboard 的值通常由 Dear ImGui 设置，"
            u8"以指示您的应用程序如何路由输入.通常，当值为 true 时，意味着 "
            u8"Dear ImGui 想要相应的输入，我们期望底层应用程序忽略它们.\n\n"
            u8"最典型的情况是：当悬停在一个窗口上时，Dear ImGui 将 io.WantCaptureMouse 设置为 true，"
            u8"底层应用程序应该忽略鼠标输入（实际上有许多更细微的 "
            u8"规则来决定如何设置这些标志）.");
        if (outputs_opened)
        {
            ImGui::Text(u8"io.WantCaptureMouse: %d (是否捕获鼠标)", io.WantCaptureMouse);
            ImGui::Text(u8"io.WantCaptureMouseUnlessPopupClose: %d (除非弹出框关闭否则捕获鼠标)", io.WantCaptureMouseUnlessPopupClose);
            ImGui::Text(u8"io.WantCaptureKeyboard: %d (是否捕获键盘)", io.WantCaptureKeyboard);
            ImGui::Text(u8"io.WantTextInput: %d (是否需要文本输入)", io.WantTextInput);
            ImGui::Text(u8"io.WantSetMousePos: %d (是否设置鼠标位置)", io.WantSetMousePos);
            ImGui::Text(u8"io.NavActive: %d, io.NavVisible: %d (导航激活: %d, 导航可见: %d)", io.NavActive, io.NavVisible, io.NavActive, io.NavVisible);

            IMGUI_DEMO_MARKER(u8"输入与焦点/输出/WantCapture 覆盖");
            if (ImGui::TreeNode(u8"WantCapture 覆盖"))
            {
                HelpMarker(
                    u8"悬停彩色画布将覆盖 io.WantCaptureXXX 字段.\n"
                    u8"请注意，通常（当设置为无时），io.WantCaptureKeyboard 的值在悬停时为 false "
                    u8"而在点击时为 true.");
                static int capture_override_mouse = -1;
                static int capture_override_keyboard = -1;
                const char* capture_override_desc[] = { u8"无", u8"设置为 false", u8"设置为 true" };
                ImGui::SetNextItemWidth(ImGui::GetFontSize() * 15);
                ImGui::SliderInt(u8"悬停时 SetNextFrameWantCaptureMouse()", &capture_override_mouse, -1, +1, capture_override_desc[capture_override_mouse + 1], ImGuiSliderFlags_AlwaysClamp);
                ImGui::SetNextItemWidth(ImGui::GetFontSize() * 15);
                ImGui::SliderInt(u8"悬停时 SetNextFrameWantCaptureKeyboard()", &capture_override_keyboard, -1, +1, capture_override_desc[capture_override_keyboard + 1], ImGuiSliderFlags_AlwaysClamp);

                ImGui::ColorButton(u8"##控制板", ImVec4(0.7f, 0.1f, 0.7f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, ImVec2(128.0f, 96.0f)); // Dummy item
                if (ImGui::IsItemHovered() && capture_override_mouse != -1)
                    ImGui::SetNextFrameWantCaptureMouse(capture_override_mouse == 1);
                if (ImGui::IsItemHovered() && capture_override_keyboard != -1)
                    ImGui::SetNextFrameWantCaptureKeyboard(capture_override_keyboard == 1);

                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        // Demonstrate using Shortcut() and Routing Policies.
        // The general flow is:
        // - Code interested in a chord (e.g. "Ctrl+A") declares their intent.
        // - Multiple locations may be interested in same chord! Routing helps find a winner.
        // - Every frame, we resolve all claims and assign one owner if the modifiers are matching.
        // - The lower-level function is 'bool SetShortcutRouting()', returns true when caller got the route.
        // - Most of the times, SetShortcutRouting() is not called directly. User mostly calls Shortcut() with routing flags.
        // - If you call Shortcut() WITHOUT any routing option, it uses ImGuiInputFlags_RouteFocused.
        // TL;DR: Most uses will simply be:
        // - Shortcut(ImGuiMod_Ctrl | ImGuiKey_A); // Use ImGuiInputFlags_RouteFocused policy.
        IMGUI_DEMO_MARKER(u8"输入与焦点/快捷键");
        if (ImGui::TreeNode(u8"快捷键"))
        {
            static ImGuiInputFlags route_options = ImGuiInputFlags_Repeat;
            static ImGuiInputFlags route_type = ImGuiInputFlags_RouteFocused;
            ImGui::CheckboxFlags(u8"ImGuiInputFlags_Repeat (重复)", &route_options, ImGuiInputFlags_Repeat);
            ImGui::RadioButton(u8"ImGuiInputFlags_RouteActive (活动路由)", &route_type, ImGuiInputFlags_RouteActive);
            ImGui::RadioButton(u8"ImGuiInputFlags_RouteFocused (默认) (焦点路由)", &route_type, ImGuiInputFlags_RouteFocused);
            ImGui::RadioButton(u8"ImGuiInputFlags_RouteGlobal (全局路由)", &route_type, ImGuiInputFlags_RouteGlobal);
            ImGui::Indent();
            ImGui::BeginDisabled(route_type != ImGuiInputFlags_RouteGlobal);
            ImGui::CheckboxFlags(u8"ImGuiInputFlags_RouteOverFocused (覆盖焦点)", &route_options, ImGuiInputFlags_RouteOverFocused);
            ImGui::CheckboxFlags(u8"ImGuiInputFlags_RouteOverActive (覆盖活动)", &route_options, ImGuiInputFlags_RouteOverActive);
            ImGui::CheckboxFlags(u8"ImGuiInputFlags_RouteUnlessBgFocused (除非背景焦点)", &route_options, ImGuiInputFlags_RouteUnlessBgFocused);
            ImGui::EndDisabled();
            ImGui::Unindent();
            ImGui::RadioButton(u8"ImGuiInputFlags_RouteAlways (总是路由)", &route_type, ImGuiInputFlags_RouteAlways);
            ImGuiInputFlags flags = route_type | route_options; // 合并标志
            if (route_type != ImGuiInputFlags_RouteGlobal)
                flags &= ~(ImGuiInputFlags_RouteOverFocused | ImGuiInputFlags_RouteOverActive | ImGuiInputFlags_RouteUnlessBgFocused);

            ImGui::SeparatorText(u8"使用 SetNextItemShortcut()");
            ImGui::Text("Ctrl+S");
            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_S, flags | ImGuiInputFlags_Tooltip);
            ImGui::Button(u8"保存");
            ImGui::Text("Alt+F");
            ImGui::SetNextItemShortcut(ImGuiMod_Alt | ImGuiKey_F, flags | ImGuiInputFlags_Tooltip);
            static float f = 0.5f;
            ImGui::SliderFloat(u8"系数", &f, 0.0f, 1.0f);

            ImGui::SeparatorText(u8"使用 Shortcut()");
            const float line_height = ImGui::GetTextLineHeightWithSpacing();
            const ImGuiKeyChord key_chord = ImGuiMod_Ctrl | ImGuiKey_A;

            ImGui::Text("Ctrl+A");
            ImGui::Text(u8"窗口是否聚焦: %d, 快捷键: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags) ? u8"已按下" : "...");

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.0f, 1.0f, 0.1f));

            ImGui::BeginChild(u8"窗口A", ImVec2(-FLT_MIN, line_height * 14), true);
            ImGui::Text(u8"按下 CTRL+A 看看谁接收到了!");
            ImGui::Separator();

            // 1: 窗口轮询 CTRL+A
            ImGui::Text(u8"(在 窗口A 中)");
            ImGui::Text(u8"窗口是否聚焦: %d, 快捷键: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags) ? u8"已按下" : "...");

            // 2: InputText 也在轮询 CTRL-A：它内部总是使用 _RouteFocused（活动时获得优先级）
            // (已注释，因为 Shortcut() 的所有者感知版本仍在 imgui_internal.h 中)
            //char str[16] = "Press CTRL+A";
            //ImGui::Spacing();
            //ImGui::InputText("InputTextB", str, IM_ARRAYSIZE(str), ImGuiInputTextFlags_ReadOnly);
            //ImGuiID item_id = ImGui::GetItemID();
            //ImGui::SameLine(); HelpMarker("内部小部件总是使用 _RouteFocused");
            //ImGui::Text("IsWindowFocused: %d, Shortcut: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags, item_id) ? "PRESSED" : "...");

            // 3: 虚拟子窗口不声明路由：聚焦它们不应从 WindowA 偷走路由
            ImGui::BeginChild(u8"子窗口D", ImVec2(-FLT_MIN, line_height * 4), true);
            ImGui::Text(u8"(在 子窗口D 中：不使用相同的快捷键)");
            ImGui::Text(u8"窗口是否聚焦: %d", ImGui::IsWindowFocused());
            ImGui::EndChild();

            // 4: 子窗口轮询 CTRL-A.它比 WindowA 更深，聚焦时获得优先级.
            ImGui::BeginChild(u8"子窗口E", ImVec2(-FLT_MIN, line_height * 4), true);
            ImGui::Text(u8"(在 子窗口E 中：使用相同的快捷键)");
            ImGui::Text(u8"窗口是否聚焦: %d, 快捷键: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags) ? u8"已按下" : "...");
            ImGui::EndChild();

            // 5: 在弹出框中
            if (ImGui::Button(u8"打开弹出框"))
                ImGui::OpenPopup(u8"弹出框F");
            if (ImGui::BeginPopup(u8"弹出框F"))
            {
                ImGui::Text(u8"(在 弹出框F 中)");
                ImGui::Text(u8"窗口是否聚焦: %d, 快捷键: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags) ? u8"已按下" : "...");
                // (已注释，因为 Shortcut() 的所有者感知版本仍在 imgui_internal.h 中)
                //ImGui::InputText("InputTextG", str, IM_ARRAYSIZE(str), ImGuiInputTextFlags_ReadOnly);
                //ImGui::Text("IsWindowFocused: %d, Shortcut: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags, ImGui::GetItemID()) ? "PRESSED" : "...");
                ImGui::EndPopup();
            }
            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::TreePop();
        }

        // 显示鼠标光标
        IMGUI_DEMO_MARKER(u8"输入与焦点/鼠标光标");
        if (ImGui::TreeNode(u8"鼠标光标"))
        {
            const char* mouse_cursors_names[] = { u8"箭头", u8"文本输入", u8"调整全部", u8"调整NS", u8"调整EW", u8"调整NESW", u8"调整NWSE", u8"手型", u8"等待", u8"进度", u8"禁止" };
            IM_ASSERT(IM_ARRAYSIZE(mouse_cursors_names) == ImGuiMouseCursor_COUNT);

            ImGuiMouseCursor current = ImGui::GetMouseCursor();
            const char* cursor_name = (current >= ImGuiMouseCursor_Arrow) && (current < ImGuiMouseCursor_COUNT) ? mouse_cursors_names[current] : u8"不适用";
            ImGui::Text(u8"当前鼠标光标 = %d: %s", current, cursor_name);
            ImGui::BeginDisabled(true);
            ImGui::CheckboxFlags(u8"io.BackendFlags: HasMouseCursors (有鼠标光标)", &io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
            ImGui::EndDisabled();

            ImGui::Text(u8"悬停以查看鼠标光标:");
            ImGui::SameLine(); HelpMarker(
                u8"您的应用程序可以根据 ImGui::GetMouseCursor() 返回的值渲染不同的鼠标光标."
                u8"如果设置了软件光标渲染 (io.MouseDrawCursor)，ImGui 将为您绘制正确的光标，"
                u8"否则您的后端需要处理它.");
            for (int i = 0; i < ImGuiMouseCursor_COUNT; i++)
            {
                char label[32];
                sprintf(label, u8"鼠标光标 %d: %s", i, mouse_cursors_names[i]);
                ImGui::Bullet(); ImGui::Selectable(label, false);
                if (ImGui::IsItemHovered())
                    ImGui::SetMouseCursor(i);
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"输入与焦点/Tab切换");
        if (ImGui::TreeNode(u8"Tab切换"))
        {
            ImGui::Text(u8"使用 TAB/SHIFT+TAB 在可键盘编辑的字段之间循环切换.");
            static char buf[32] = "hello";
            ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
            ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
            ImGui::InputText("3", buf, IM_ARRAYSIZE(buf));
            ImGui::PushItemFlag(ImGuiItemFlags_NoTabStop, true);
            ImGui::InputText(u8"4 (跳过tab)", buf, IM_ARRAYSIZE(buf));
            ImGui::SameLine(); HelpMarker(u8"使用 TAB 或 Shift+Tab 时不会循环到此项目.");
            ImGui::PopItemFlag();
            ImGui::InputText(u8"5", buf, IM_ARRAYSIZE(buf));
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"输入与焦点/代码设置焦点");
        if (ImGui::TreeNode(u8"代码设置焦点"))
        {
            bool focus_1 = ImGui::Button(u8"聚焦到 1"); ImGui::SameLine();
            bool focus_2 = ImGui::Button(u8"聚焦到 2"); ImGui::SameLine();
            bool focus_3 = ImGui::Button(u8"聚焦到 3");
            int has_focus = 0;
            static char buf[128] = "click on a button to set focus";

            if (focus_1) ImGui::SetKeyboardFocusHere();
            ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 1;

            if (focus_2) ImGui::SetKeyboardFocusHere();
            ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 2;

            ImGui::PushItemFlag(ImGuiItemFlags_NoTabStop, true);
            if (focus_3) ImGui::SetKeyboardFocusHere();
            ImGui::InputText(u8"3 (跳过tab)", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 3;
            ImGui::SameLine(); HelpMarker(u8"使用 TAB 或 Shift+Tab 时不会循环到此项目.");
            ImGui::PopItemFlag();

            if (has_focus)
                ImGui::Text(u8"具有焦点的项目: %d", has_focus);
            else
                ImGui::Text(u8"具有焦点的项目: <无>");

            // 使用 >= 0 参数调用 SetKeyboardFocusHere() 来聚焦即将到来的项目
            static float f3[3] = { 0.0f, 0.0f, 0.0f };
            int focus_ahead = -1;
            if (ImGui::Button(u8"聚焦到 X")) { focus_ahead = 0; } ImGui::SameLine();
            if (ImGui::Button(u8"聚焦到 Y")) { focus_ahead = 1; } ImGui::SameLine();
            if (ImGui::Button(u8"聚焦到 Z")) { focus_ahead = 2; }
            if (focus_ahead != -1) ImGui::SetKeyboardFocusHere(focus_ahead);
            ImGui::SliderFloat3(u8"浮点3", &f3[0], 0.0f, 1.0f);

            ImGui::TextWrapped(u8"注意：在代码中重新聚焦最后使用的项目时，光标和选择会被保留.");
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER(u8"输入与焦点/拖拽");
        if (ImGui::TreeNode(u8"拖拽"))
        {
            ImGui::TextWrapped(u8"您可以使用 ImGui::GetMouseDragDelta(0) 来查询任何小部件上的拖拽量.");
            for (int button = 0; button < 3; button++)
            {
                ImGui::Text(u8"IsMouseDragging(%d):", button);
                ImGui::Text(u8"  使用默认阈值: %d,", ImGui::IsMouseDragging(button));
                ImGui::Text(u8"  使用零阈值: %d,", ImGui::IsMouseDragging(button, 0.0f));
                ImGui::Text(u8"  使用大阈值: %d,", ImGui::IsMouseDragging(button, 20.0f));
            }

            ImGui::Button(u8"拖拽我");
            if (ImGui::IsItemActive())
                ImGui::GetForegroundDrawList()->AddLine(io.MouseClickedPos[0], io.MousePos, ImGui::GetColorU32(ImGuiCol_Button), 4.0f); // 在按钮和鼠标光标之间绘制一条线

            // 当鼠标移动超过某个阈值时，拖拽操作会"解锁"
            // (默认阈值存储在 io.MouseDragThreshold 中).您可以使用 IsMouseDragging() 和 GetMouseDragDelta() 的第二个参数请求更低或更高的阈值.
            ImVec2 value_raw = ImGui::GetMouseDragDelta(0, 0.0f);
            ImVec2 value_with_lock_threshold = ImGui::GetMouseDragDelta(0);
            ImVec2 mouse_delta = io.MouseDelta;
            ImGui::Text(u8"GetMouseDragDelta(0):");
            ImGui::Text(u8"使用默认阈值: (%.1f, %.1f)", value_with_lock_threshold.x, value_with_lock_threshold.y);
            ImGui::Text(u8"使用零阈值: (%.1f, %.1f)", value_raw.x, value_raw.y);
            ImGui::Text(u8"io.MouseDelta: (%.1f, %.1f)", mouse_delta.x, mouse_delta.y);
            ImGui::TreePop();
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] About Window / ShowAboutWindow()
// Access from Dear ImGui Demo -> Tools -> About
//-----------------------------------------------------------------------------

void ImGui::ShowAboutWindow(bool* p_open)
{
    if (!ImGui::Begin(u8"关于 Dear ImGui", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::End();
        return;
    }
    IMGUI_DEMO_MARKER(u8"工具/关于 Dear ImGui");
    ImGui::Text(u8"Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

    ImGui::TextLinkOpenURL(u8"主页", "https://github.com/ocornut/imgui");
    ImGui::SameLine();
    ImGui::TextLinkOpenURL(u8"常见问题", "https://github.com/ocornut/imgui/blob/master/docs/FAQ.md");
    ImGui::SameLine();
    ImGui::TextLinkOpenURL(u8"维基", "https://github.com/ocornut/imgui/wiki");
    ImGui::SameLine();
    ImGui::TextLinkOpenURL(u8"扩展", "https://github.com/ocornut/imgui/wiki/Useful-Extensions");
    ImGui::SameLine();
    ImGui::TextLinkOpenURL(u8"发布版本", "https://github.com/ocornut/imgui/releases");
    ImGui::SameLine();
    ImGui::TextLinkOpenURL(u8"资助", "https://github.com/ocornut/imgui/wiki/Funding");

    ImGui::Separator();
    ImGui::Text(u8"(c) 2014-2025 Omar Cornut");
    ImGui::Text(u8"由 Omar Cornut 和所有 Dear ImGui 贡献者开发.");
    ImGui::Text(u8"Dear ImGui 采用 MIT 许可证授权，更多信息请参阅 LICENSE.");
    ImGui::Text(u8"如果您的公司使用此软件，请考虑资助该项目.");

    static bool show_config_info = false;
    ImGui::Checkbox(u8"配置/构建信息", &show_config_info);
    if (show_config_info)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        bool copy_to_clipboard = ImGui::Button(u8"复制到剪贴板");
        ImVec2 child_size = ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 18);
        ImGui::BeginChild(ImGui::GetID("cfg_infos"), child_size, ImGuiChildFlags_FrameStyle);
        if (copy_to_clipboard)
        {
            ImGui::LogToClipboard();
            ImGui::LogText("```cpp\n"); // 反引号将使文本在 GitHub 上粘贴时无格式显示
        }

        ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
        ImGui::Separator();
        ImGui::Text(u8"数据类型大小: size_t=%d字节, ImDrawIdx=%d字节, ImDrawVert=%d字节", (int)sizeof(size_t), (int)sizeof(ImDrawIdx), (int)sizeof(ImDrawVert));
        ImGui::Text(u8"定义: __cplusplus=%d", (int)__cplusplus);
#ifdef IMGUI_ENABLE_TEST_ENGINE
        ImGui::Text(u8"定义: IMGUI_ENABLE_TEST_ENGINE (启用测试引擎)");
#endif
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_OBSOLETE_FUNCTIONS (禁用过时函数)");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS (禁用Win32默认剪贴板函数)");
#endif
#ifdef IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS (禁用Win32默认输入法函数)");
#endif
#ifdef IMGUI_DISABLE_WIN32_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_WIN32_FUNCTIONS (禁用Win32函数)");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_SHELL_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_DEFAULT_SHELL_FUNCTIONS (禁用默认Shell函数)");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_DEFAULT_FORMAT_FUNCTIONS (禁用默认格式化函数)");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_DEFAULT_MATH_FUNCTIONS (禁用默认数学函数)");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_DEFAULT_FILE_FUNCTIONS (禁用默认文件函数)");
#endif
#ifdef IMGUI_DISABLE_FILE_FUNCTIONS
        ImGui::Text(u8"定义: IMGUI_DISABLE_FILE_FUNCTIONS (禁用文件函数)");
#endif
#ifdef IMGUI_DISABLE_DEFAULT_ALLOCATORS
        ImGui::Text(u8"定义: IMGUI_DISABLE_DEFAULT_ALLOCATORS (禁用默认分配器)");
#endif
#ifdef IMGUI_USE_BGRA_PACKED_COLOR
        ImGui::Text(u8"定义: IMGUI_USE_BGRA_PACKED_COLOR (使用BGRA打包颜色)");
#endif
#ifdef _WIN32
        ImGui::Text(u8"定义: _WIN32 (Windows 32位)");
#endif
#ifdef _WIN64
        ImGui::Text(u8"定义: _WIN64 (Windows 64位)");
#endif
#ifdef __linux__
        ImGui::Text(u8"定义: __linux__ (Linux系统)");
#endif
#ifdef __APPLE__
        ImGui::Text(u8"定义: __APPLE__ (苹果系统)");
#endif
#ifdef _MSC_VER
        ImGui::Text(u8"定义: _MSC_VER=%d (Visual Studio编译器版本)", _MSC_VER);
#endif
#ifdef _MSVC_LANG
        ImGui::Text(u8"定义: _MSVC_LANG=%d (MSVC语言标准)", (int)_MSVC_LANG);
#endif
#ifdef __MINGW32__
        ImGui::Text(u8"定义: __MINGW32__ (MinGW 32位)");
#endif
#ifdef __MINGW64__
        ImGui::Text(u8"定义: __MINGW64__ (MinGW 64位)");
#endif
#ifdef __GNUC__
        ImGui::Text(u8"定义: __GNUC__=%d (GCC编译器版本)", (int)__GNUC__);
#endif
#ifdef __clang_version__
        ImGui::Text(u8"定义: __clang_version__=%s (Clang编译器版本)", __clang_version__);
#endif
#ifdef __EMSCRIPTEN__
        ImGui::Text(u8"定义: __EMSCRIPTEN__ (Emscripten环境)");
        ImGui::Text(u8"Emscripten: %d.%d.%d", __EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__);
#endif
#ifdef IMGUI_HAS_VIEWPORT
        ImGui::Text(u8"定义: IMGUI_HAS_VIEWPORT (支持多视口)");
#endif
#ifdef IMGUI_HAS_DOCK
        ImGui::Text(u8"定义: IMGUI_HAS_DOCK (支持停靠功能)");
#endif
        ImGui::Separator();
        ImGui::Text(u8"io.BackendPlatformName: %s (后端平台名称)", io.BackendPlatformName ? io.BackendPlatformName : "NULL");
        ImGui::Text(u8"io.BackendRendererName: %s (后端渲染器名称)", io.BackendRendererName ? io.BackendRendererName : "NULL");
        ImGui::Text(u8"io.ConfigFlags: 0x%08X (配置标志)", io.ConfigFlags);
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        ImGui::Text(u8"启用键盘导航");
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         ImGui::Text(u8"启用游戏手柄导航");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  ImGui::Text(u8"禁用鼠标");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      ImGui::Text(u8"禁止鼠标光标改变");
        if (io.ConfigFlags & ImGuiConfigFlags_NoKeyboard)               ImGui::Text(u8"禁用键盘");
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)            ImGui::Text(u8"启用停靠");
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)          ImGui::Text(u8"启用多视口");
        if (io.MouseDrawCursor)                                         ImGui::Text(u8"io.MouseDrawCursor (绘制鼠标光标)");
        if (io.ConfigDpiScaleFonts)                                     ImGui::Text(u8"io.ConfigDpiScaleFonts (DPI缩放字体)");
        if (io.ConfigDpiScaleViewports)                                 ImGui::Text(u8"io.ConfigDpiScaleViewports (DPI缩放视口)");
        if (io.ConfigViewportsNoAutoMerge)                              ImGui::Text(u8"io.ConfigViewportsNoAutoMerge (视口不自动合并)");
        if (io.ConfigViewportsNoTaskBarIcon)                            ImGui::Text(u8"io.ConfigViewportsNoTaskBarIcon (视口无任务栏图标)");
        if (io.ConfigViewportsNoDecoration)                             ImGui::Text(u8"io.ConfigViewportsNoDecoration (视口无装饰)");
        if (io.ConfigViewportsNoDefaultParent)                          ImGui::Text(u8"io.ConfigViewportsNoDefaultParent (视口无默认父窗口)");
        if (io.ConfigDockingNoSplit)                                    ImGui::Text(u8"io.ConfigDockingNoSplit (停靠禁止拆分)");
        if (io.ConfigDockingWithShift)                                  ImGui::Text(u8"io.ConfigDockingWithShift (Shift键停靠)");
        if (io.ConfigDockingAlwaysTabBar)                               ImGui::Text(u8"io.ConfigDockingAlwaysTabBar (总是显示停靠标签栏)");
        if (io.ConfigDockingTransparentPayload)                         ImGui::Text(u8"io.ConfigDockingTransparentPayload (透明停靠载荷)");
        if (io.ConfigMacOSXBehaviors)                                   ImGui::Text(u8"io.ConfigMacOSXBehaviors (macOS行为)");
        if (io.ConfigNavMoveSetMousePos)                                ImGui::Text(u8"io.ConfigNavMoveSetMousePos (导航移动设置鼠标位置)");
        if (io.ConfigNavCaptureKeyboard)                                ImGui::Text(u8"io.ConfigNavCaptureKeyboard (导航捕获键盘)");
        if (io.ConfigInputTextCursorBlink)                              ImGui::Text(u8"io.ConfigInputTextCursorBlink (输入文本光标闪烁)");
        if (io.ConfigWindowsResizeFromEdges)                            ImGui::Text(u8"io.ConfigWindowsResizeFromEdges (从边缘调整窗口大小)");
        if (io.ConfigWindowsMoveFromTitleBarOnly)                       ImGui::Text(u8"io.ConfigWindowsMoveFromTitleBarOnly (仅从标题栏移动窗口)");
        if (io.ConfigMemoryCompactTimer >= 0.0f)                        ImGui::Text(u8"io.ConfigMemoryCompactTimer = %.1f (内存压缩计时器)", io.ConfigMemoryCompactTimer);
        ImGui::Text(u8"io.后端标志: 0x%08X", io.BackendFlags);
        if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             ImGui::Text(u8"支持游戏手柄");
        if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        ImGui::Text(u8"支持鼠标光标");
        if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         ImGui::Text(u8"支持设置鼠标位置");
        if (io.BackendFlags & ImGuiBackendFlags_PlatformHasViewports)   ImGui::Text(u8"平台支持多视口");
        if (io.BackendFlags & ImGuiBackendFlags_HasMouseHoveredViewport)ImGui::Text(u8"支持鼠标悬停视口检测");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset)   ImGui::Text(u8"渲染器支持顶点偏移");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasTextures)    ImGui::Text(u8"渲染器支持纹理");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasViewports)   ImGui::Text(u8"渲染器支持多视口");
        ImGui::Separator();
        ImGui::Text(u8"io.Fonts: %d 字体,标志: 0x%08X, 文本大小: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexData->Width, io.Fonts->TexData->Height);
        ImGui::Text(u8"io.Fonts->FontLoaderName: %s (字体加载器名称)", io.Fonts->FontLoaderName ? io.Fonts->FontLoaderName : "NULL");
        ImGui::Text(u8"io.DisplaySize: %.2f,%.2f (显示尺寸)", io.DisplaySize.x, io.DisplaySize.y);
        ImGui::Text(u8"io.DisplayFramebufferScale: %.2f,%.2f (帧缓冲缩放)", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        ImGui::Separator();
        ImGui::Text(u8"style.WindowPadding: %.2f,%.2f (窗口内边距)", style.WindowPadding.x, style.WindowPadding.y);
        ImGui::Text(u8"style.WindowBorderSize: %.2f (窗口边框大小)", style.WindowBorderSize);
        ImGui::Text(u8"style.FramePadding: %.2f,%.2f (框架内边距)", style.FramePadding.x, style.FramePadding.y);
        ImGui::Text(u8"style.FrameRounding: %.2f (框架圆角)", style.FrameRounding);
        ImGui::Text(u8"style.FrameBorderSize: %.2f (框架边框大小)", style.FrameBorderSize);
        ImGui::Text(u8"style.ItemSpacing: %.2f,%.2f (项间距)", style.ItemSpacing.x, style.ItemSpacing.y);
        ImGui::Text(u8"style.ItemInnerSpacing: %.2f,%.2f (项内间距)", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y);

        if (copy_to_clipboard)
        {
            ImGui::LogText("\n```\n");
            ImGui::LogFinish();
        }
        ImGui::EndChild();
    }
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Style Editor / ShowStyleEditor()
//-----------------------------------------------------------------------------
// - ShowStyleSelector()
// - ShowStyleEditor()
//-----------------------------------------------------------------------------

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
// Here we use the simplified Combo() api that packs items into a single literal string.
// Useful for quick combo boxes where the choices are known locally.
bool ImGui::ShowStyleSelector(const char* label)
{
    static int style_idx = -1;
    if (ImGui::Combo(label, &style_idx, u8"深色\0浅色\0经典\0"))
    {
        switch (style_idx)
        {
        case 0: ImGui::StyleColorsDark(); break;
        case 1: ImGui::StyleColorsLight(); break;
        case 2: ImGui::StyleColorsClassic(); break;
        }
        return true;
    }
    return false;
}

static const char* GetTreeLinesFlagsName(ImGuiTreeNodeFlags flags)
{
    if (flags == ImGuiTreeNodeFlags_DrawLinesNone) return u8"无树线";
    if (flags == ImGuiTreeNodeFlags_DrawLinesFull) return u8"完整树线";
    if (flags == ImGuiTreeNodeFlags_DrawLinesToNodes) return u8"节点树线";
    return "";
}

// We omit the ImGui:: prefix in this function, as we don't expect user to be copy and pasting this code.
void ImGui::ShowStyleEditor(ImGuiStyle * ref)
{
    IMGUI_DEMO_MARKER(u8"工具/");
    // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to
    // (without a reference style pointer, we will use one compared locally as a reference)
    ImGuiStyle& style = GetStyle();
    static ImGuiStyle ref_saved_style;

    // Default to using internal storage as reference
    static bool init = true;
    if (init && ref == NULL)
        ref_saved_style = style;
    init = false;
    if (ref == NULL)
        ref = &ref_saved_style;

    PushItemWidth(GetWindowWidth() * 0.50f);

    {
        // General
        SeparatorText(u8"常规");
        if ((GetIO().BackendFlags & ImGuiBackendFlags_RendererHasTextures) == 0)
        {
            BulletText(u8"警告：字体缩放将不平滑，因为\n未设置 ImGuiBackendFlags_RendererHasTextures 标志!");
            BulletText(u8"有关说明，请参见：");
            SameLine();
            TextLinkOpenURL(u8"docs/BACKENDS.md", "https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md");
        }

        if (ShowStyleSelector(u8"颜色##选择器"))
            ref_saved_style = style;
        ShowFontSelector(u8"字体##选择器");
        if (DragFloat(u8"基础字体大小", &style.FontSizeBase, 0.20f, 5.0f, 100.0f, "%.0f"))
            style._NextFrameFontSizeBase = style.FontSizeBase; // 修复：临时 hack，直到我们完成剩余工作.
        SameLine(0.0f, 0.0f); Text(u8" (输出 %.2f)", GetFontSize());
        DragFloat(u8"主字体缩放", &style.FontScaleMain, 0.02f, 0.5f, 4.0f);
        //BeginDisabled(GetIO().ConfigDpiScaleFonts);
        DragFloat(u8"DPI 字体缩放", &style.FontScaleDpi, 0.02f, 0.5f, 4.0f);
        //SetItemTooltip(u8"当设置 io.ConfigDpiScaleFonts 时，此值会自动被覆盖.");
        //EndDisabled();

        // 简化设置（将浮点边框大小暴露为表示 0.0f 或 1.0f 的布尔值）
        if (SliderFloat(u8"框架圆角", &style.FrameRounding, 0.0f, 12.0f, "%.0f"))
            style.GrabRounding = style.FrameRounding; // 使 GrabRounding 始终与 FrameRounding 相同
        { bool border = (style.WindowBorderSize > 0.0f); if (Checkbox(u8"窗口边框", &border)) { style.WindowBorderSize = border ? 1.0f : 0.0f; } }
        SameLine();
        { bool border = (style.FrameBorderSize > 0.0f);  if (Checkbox(u8"框架边框", &border)) { style.FrameBorderSize = border ? 1.0f : 0.0f; } }
        SameLine();
        { bool border = (style.PopupBorderSize > 0.0f);  if (Checkbox(u8"弹出框边框", &border)) { style.PopupBorderSize = border ? 1.0f : 0.0f; } }
    }

    // 保存/恢复按钮
    if (Button(u8"保存参考"))
        *ref = ref_saved_style = style;
    SameLine();
    if (Button(u8"恢复参考"))
        style = *ref;
    SameLine();
    HelpMarker(
        u8"在本地非持久存储中保存/恢复.默认颜色定义不受影响."
        u8"使用下面的\"导出\"将它们保存到某处.");

    SeparatorText(u8"详细信息");
    if (BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        if (BeginTabItem(u8"尺寸"))
        {
            SeparatorText(u8"主要");
            SliderFloat2(u8"窗口内边距", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
            SliderFloat2(u8"框架内边距", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
            SliderFloat2(u8"项间距", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
            SliderFloat2(u8"项内间距", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
            SliderFloat2(u8"触摸额外内边距", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
            SliderFloat(u8"缩进间距", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
            SliderFloat(u8"抓取最小大小", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");

            SeparatorText(u8"边框");
            SliderFloat(u8"窗口边框大小", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
            SliderFloat(u8"子窗口边框大小", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
            SliderFloat(u8"弹出框边框大小", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
            SliderFloat(u8"框架边框大小", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");

            SeparatorText(u8"圆角"); 
            SliderFloat(u8"窗口圆角", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"子窗口圆角", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"框架圆角", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"弹出框圆角", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"抓取圆角", &style.GrabRounding, 0.0f, 12.0f, "%.0f");

            SeparatorText(u8"滚动条");
            SliderFloat(u8"滚动条大小", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
            SliderFloat(u8"滚动条圆角", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"滚动条内边距", &style.ScrollbarPadding, 0.0f, 10.0f, "%.0f");

            SeparatorText(u8"标签");
            SliderFloat(u8"标签边框大小", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
            SliderFloat(u8"标签栏边框大小", &style.TabBarBorderSize, 0.0f, 2.0f, "%.0f");
            SliderFloat(u8"标签栏上划线大小", &style.TabBarOverlineSize, 0.0f, 3.0f, "%.0f");
            SameLine(); HelpMarker(u8"仅当设置 ImGuiTabBarFlags_DrawSelectedOverline 时，上划线仅在选中的标签上绘制.");
            DragFloat(u8"标签最小宽度基础", &style.TabMinWidthBase, 0.5f, 1.0f, 500.0f, "%.0f");
            DragFloat(u8"标签最小宽度收缩", &style.TabMinWidthShrink, 0.5f, 1.0f, 500.0f, "%0.f");
            DragFloat(u8"选中标签关闭按钮最小宽度", &style.TabCloseButtonMinWidthSelected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthSelected < 0.0f) ? "%.0f (总是)" : "%.0f");
            DragFloat(u8"未选中标签关闭按钮最小宽度", &style.TabCloseButtonMinWidthUnselected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthUnselected < 0.0f) ? "%.0f (总是)" : "%.0f");
            SliderFloat(u8"标签圆角", &style.TabRounding, 0.0f, 12.0f, "%.0f");

            SeparatorText(u8"表格");
            SliderFloat2(u8"单元格内边距", (float*)&style.CellPadding, 0.0f, 20.0f, "%.0f");
            SliderAngle(u8"表格角度标题角度", &style.TableAngledHeadersAngle, -50.0f, +50.0f);
            SliderFloat2(u8"表格角度标题文本对齐", (float*)&style.TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");

            SeparatorText(u8"树形");
            bool combo_open = BeginCombo(u8"树线标志", GetTreeLinesFlagsName(style.TreeLinesFlags));
            SameLine();
            HelpMarker(u8"[实验性] 树线可能不适用于所有情况（例如使用裁剪器），并可能产生轻微的遍历开销.\n\nImGuiTreeNodeFlags_DrawLinesFull 比 ImGuiTreeNodeFlags_DrawLinesToNode 更快.");
            if (combo_open)
            {
                const ImGuiTreeNodeFlags options[] = { ImGuiTreeNodeFlags_DrawLinesNone, ImGuiTreeNodeFlags_DrawLinesFull, ImGuiTreeNodeFlags_DrawLinesToNodes };
                for (ImGuiTreeNodeFlags option : options)
                    if (Selectable(GetTreeLinesFlagsName(option), style.TreeLinesFlags == option))
                        style.TreeLinesFlags = option;
                EndCombo();
            }
            SliderFloat(u8"树线大小", &style.TreeLinesSize, 0.0f, 2.0f, "%.0f");
            SliderFloat(u8"树线圆角", &style.TreeLinesRounding, 0.0f, 12.0f, "%.0f");

            SeparatorText(u8"窗口");
            SliderFloat2(u8"窗口标题对齐", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
            SliderFloat(u8"窗口边框悬停内边距", &style.WindowBorderHoverPadding, 1.0f, 20.0f, "%.0f");
            int window_menu_button_position = style.WindowMenuButtonPosition + 1;
            if (Combo(u8"窗口菜单按钮位置", (int*)&window_menu_button_position, u8"无\0左\0右\0"))
                style.WindowMenuButtonPosition = (ImGuiDir)(window_menu_button_position - 1);

            SeparatorText(u8"小部件");
            Combo(u8"颜色按钮位置", (int*)&style.ColorButtonPosition, u8"左\0右\0");
            SliderFloat2(u8"按钮文本对齐", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
            SameLine(); HelpMarker(u8"当按钮大于其文本内容时应用对齐.");
            SliderFloat2(u8"可选文本对齐", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
            SameLine(); HelpMarker(u8"当可选项大于其文本内容时应用对齐.");
            SliderFloat(u8"分隔符文本边框大小", &style.SeparatorTextBorderSize, 0.0f, 10.0f, "%.0f");
            SliderFloat2(u8"分隔符文本对齐", (float*)&style.SeparatorTextAlign, 0.0f, 1.0f, "%.2f");
            SliderFloat2(u8"分隔符文本内边距", (float*)&style.SeparatorTextPadding, 0.0f, 40.0f, "%.0f");
            SliderFloat(u8"对数滑块死区", &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
            SliderFloat(u8"图像边框大小", &style.ImageBorderSize, 0.0f, 1.0f, "%.0f");

            SeparatorText(u8"停靠");
            SliderFloat(u8"停靠分隔符大小", &style.DockingSeparatorSize, 0.0f, 12.0f, "%.0f");

            SeparatorText(u8"工具提示");
            for (int n = 0; n < 2; n++)
                if (TreeNodeEx(n == 0 ? u8"鼠标工具提示悬停标志" : u8"导航工具提示悬停标志"))
                {
                    ImGuiHoveredFlags* p = (n == 0) ? &style.HoverFlagsForTooltipMouse : &style.HoverFlagsForTooltipNav;
                    CheckboxFlags("ImGuiHoveredFlags_DelayNone", p, ImGuiHoveredFlags_DelayNone);
                    CheckboxFlags("ImGuiHoveredFlags_DelayShort", p, ImGuiHoveredFlags_DelayShort);
                    CheckboxFlags("ImGuiHoveredFlags_DelayNormal", p, ImGuiHoveredFlags_DelayNormal);
                    CheckboxFlags("ImGuiHoveredFlags_Stationary", p, ImGuiHoveredFlags_Stationary);
                    CheckboxFlags("ImGuiHoveredFlags_NoSharedDelay", p, ImGuiHoveredFlags_NoSharedDelay);
                    TreePop();
                }

            SeparatorText(u8"杂项");
            SliderFloat2(u8"显示窗口内边距", (float*)&style.DisplayWindowPadding, 0.0f, 30.0f, "%.0f"); SameLine(); HelpMarker(u8"应用于常规窗口：当靠近屏幕边缘移动时，我们强制保留可见的量.");
            SliderFloat2(u8"显示安全区内边距", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f"); SameLine(); HelpMarker(u8"应用于每个窗口、菜单、弹出框、工具提示：我们避免显示内容的量.如果您看不到屏幕边缘（例如在未配置缩放的电视上），请调整.");

            EndTabItem();
        }

        if (BeginTabItem(u8"颜色"))
        {
            static int output_dest = 0;
            static bool output_only_modified = true;
            if (Button(u8"导出"))
            {
                if (output_dest == 0)
                    LogToClipboard();
                else
                    LogToTTY();
                LogText("ImVec4* colors = GetStyle().Colors;" IM_NEWLINE);
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const ImVec4& col = style.Colors[i];
                    const char* name = GetStyleColorName(i);

                    if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
                        LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE,
                            name, 23 - (int)strlen(name), "", col.x, col.y, col.z, col.w);
                }
                LogFinish();
            }
            SameLine(); SetNextItemWidth(120); Combo(u8"##输出类型", &output_dest, u8"到剪贴板\0到 TTY\0");
            SameLine(); Checkbox(u8"仅修改的颜色", &output_only_modified);

            static ImGuiTextFilter filter;
            filter.Draw(u8"过滤颜色", GetFontSize() * 16);

            static ImGuiColorEditFlags alpha_flags = 0;
            if (RadioButton(u8"不透明", alpha_flags == ImGuiColorEditFlags_AlphaOpaque)) { alpha_flags = ImGuiColorEditFlags_AlphaOpaque; } SameLine();
            if (RadioButton(u8"透明度", alpha_flags == ImGuiColorEditFlags_None)) { alpha_flags = ImGuiColorEditFlags_None; } SameLine();
            if (RadioButton(u8"两者", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } SameLine();
            HelpMarker(
                u8"在颜色列表中：\n"
                u8"左键单击颜色方块打开颜色选择器，\n"
                u8"右键单击打开编辑选项菜单.");

            SetNextWindowSizeConstraints(ImVec2(0.0f, GetTextLineHeightWithSpacing() * 10), ImVec2(FLT_MAX, FLT_MAX));
            BeginChild(u8"##颜色", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
            PushItemWidth(GetFontSize() * -12);
            for (int i = 0; i < ImGuiCol_COUNT; i++)
            {
                const char* name = TranslateColorName(i);
                
                if (!filter.PassFilter(name))
                    continue;
                PushID(i);
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
                if (Button("?"))
                    DebugFlashStyleColor((ImGuiCol)i);
                SetItemTooltip(u8"闪烁给定颜色以识别使用它的地方.");
                SameLine();
#endif
                ColorEdit4(u8"##颜色", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
                if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
                {
                    // 提示：在真实的用户应用程序中，您可能希望将图标字体合并到主字体中，
                    // 这样您将使用图标而不是"保存"/"恢复"!
                    // 阅读常见问题解答和 docs/FONTS.md 关于使用图标字体.这真的很容易且超级方便!
                    SameLine(0.0f, style.ItemInnerSpacing.x); if (Button(u8"保存")) { ref->Colors[i] = style.Colors[i]; }
                    SameLine(0.0f, style.ItemInnerSpacing.x); if (Button(u8"恢复")) { style.Colors[i] = ref->Colors[i]; }
                }
                SameLine(0.0f, style.ItemInnerSpacing.x);
                TextUnformatted(name);
                PopID();
            }
            PopItemWidth();
            EndChild();

            EndTabItem();
        }

        if (BeginTabItem(u8"字体"))
        {
            ImGuiIO& io = GetIO();
            ImFontAtlas* atlas = io.Fonts;
            ShowFontAtlas(atlas);

            // Post-baking font scaling. Note that this is NOT the nice way of scaling fonts, read below.
            // (we enforce hard clamping manually as by default DragFloat/SliderFloat allows CTRL+Click text to get out of bounds).
            /*
            SeparatorText("Legacy Scaling");
            const float MIN_SCALE = 0.3f;
            const float MAX_SCALE = 2.0f;
            HelpMarker(
                "Those are old settings provided for convenience.\n"
                "However, the _correct_ way of scaling your UI is currently to reload your font at the designed size, "
                "rebuild the font atlas, and call style.ScaleAllSizes() on a reference ImGuiStyle structure.\n"
                "Using those settings here will give you poor quality results.");
            PushItemWidth(GetFontSize() * 8);
            DragFloat("global scale", &io.FontGlobalScale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp); // Scale everything
            //static float window_scale = 1.0f;
            //if (DragFloat("window scale", &window_scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp)) // Scale only this window
            //    SetWindowFontScale(window_scale);
            PopItemWidth();
            */

            EndTabItem();
        }

        if (BeginTabItem(u8"渲染"))
        {
            Checkbox(u8"抗锯齿线条", &style.AntiAliasedLines);
            SameLine();
            HelpMarker(u8"禁用抗锯齿线条时，您可能还希望在样式中禁用边框.");

            Checkbox(u8"抗锯齿线条使用纹理", &style.AntiAliasedLinesUseTex);
            SameLine();
            HelpMarker(u8"使用纹理数据绘制更快的线条.需要后端使用双线性滤波（而非点/最近邻滤波）进行渲染.");

            Checkbox(u8"抗锯齿填充", &style.AntiAliasedFill);
            PushItemWidth(GetFontSize() * 8);
            DragFloat(u8"曲线细分容差", &style.CurveTessellationTol, 0.02f, 0.10f, 10.0f, "%.2f");
            if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;

            // 编辑"圆形细分最大误差"值时，绘制其对自动细分圆形的效果预览.
            DragFloat(u8"圆形细分最大误差", &style.CircleTessellationMaxError, 0.005f, 0.10f, 5.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
            const bool show_samples = IsItemActive();
            if (show_samples)
                SetNextWindowPos(GetCursorScreenPos());
            if (show_samples && BeginTooltip())
            {
                TextUnformatted(u8"(R = 半径, N = 近似分段数)");
                Spacing();
                ImDrawList* draw_list = GetWindowDrawList();
                const float min_widget_width = CalcTextSize("R: MMM\nN: MMM").x;
                for (int n = 0; n < 8; n++)
                {
                    const float RAD_MIN = 5.0f;
                    const float RAD_MAX = 70.0f;
                    const float rad = RAD_MIN + (RAD_MAX - RAD_MIN) * (float)n / (8.0f - 1.0f);

                    BeginGroup();

                    // 由于 PathArcTo() 函数内部工作原理，N 在这里并不总是精确的
                    Text("R: %.f\nN: %d", rad, draw_list->_CalcCircleAutoSegmentCount(rad));

                    const float canvas_width = IM_MAX(min_widget_width, rad * 2.0f);
                    const float offset_x = floorf(canvas_width * 0.5f);
                    const float offset_y = floorf(RAD_MAX);

                    const ImVec2 p1 = GetCursorScreenPos();
                    draw_list->AddCircle(ImVec2(p1.x + offset_x, p1.y + offset_y), rad, GetColorU32(ImGuiCol_Text));
                    Dummy(ImVec2(canvas_width, RAD_MAX * 2));

                    /*
                    const ImVec2 p2 = GetCursorScreenPos();
                    draw_list->AddCircleFilled(ImVec2(p2.x + offset_x, p2.y + offset_y), rad, GetColorU32(ImGuiCol_Text));
                    Dummy(ImVec2(canvas_width, RAD_MAX * 2));
                    */

                    EndGroup();
                    SameLine();
                }
                EndTooltip();
            }
            SameLine();
            HelpMarker(u8"当使用 \"num_segments == 0\" 绘制圆形图元时，将自动计算细分.");

            DragFloat(u8"全局透明度", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // 这里不暴露零值，以免用户"丢失"UI（零透明度会裁剪所有小部件）.但应用程序代码可以有一个切换开关在零和非零之间切换.
            DragFloat(u8"禁用状态透明度", &style.DisabledAlpha, 0.005f, 0.0f, 1.0f, "%.2f"); SameLine(); HelpMarker(u8"禁用项的额外透明度乘数（乘以当前的 Alpha 值）.");
            PopItemWidth();

            EndTabItem();
        }

        EndTabBar();
    }
    PopItemWidth();
}

//-----------------------------------------------------------------------------
// [SECTION] 用户指南 / ShowUserGuide()
//-----------------------------------------------------------------------------

// 我们在此函数中省略了 ImGui:: 前缀，因为我们不希望用户复制粘贴此代码.
void ImGui::ShowUserGuide()
{
    ImGuiIO& io = GetIO();
    BulletText(u8"双击标题栏以折叠窗口.");
    BulletText(
        u8"点击并拖动右下角以调整窗口大小\n"
        u8"(双击以自动调整窗口以适应其内容).");
    BulletText(u8"CTRL+点击滑块或拖动框以文本形式输入值.");
    BulletText(u8"TAB/SHIFT+TAB 循环切换可键盘编辑的字段.");
    BulletText(u8"CTRL+Tab 选择窗口.");
    if (io.FontAllowUserScaling)
        BulletText(u8"CTRL+鼠标滚轮缩放窗口内容.");
    BulletText(u8"输入文本时：\n");
    Indent();
    BulletText(u8"CTRL+左/右箭头键进行单词跳转.");
    BulletText(u8"CTRL+A 或双击选择全部.");
    BulletText(u8"CTRL+X/C/V 使用剪贴板剪切/复制/粘贴.");
    BulletText(u8"CTRL+Z 撤销，CTRL+Y/CTRL+SHIFT+Z 重做.");
    BulletText(u8"ESC 键恢复.");
    Unindent();
    BulletText(u8"启用键盘导航时：");
    Indent();
    BulletText(u8"箭头键导航.");
    BulletText(u8"空格键激活小部件.");
    BulletText(u8"回车键向小部件输入文本.");
    BulletText(u8"ESC 键停用小部件、关闭弹出窗口、退出子窗口.");
    BulletText(u8"Alt 键跳转到窗口的菜单层.");
    Unindent();
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：主菜单栏 / ShowExampleAppMainMenuBar()
//-----------------------------------------------------------------------------
// - ShowExampleAppMainMenuBar()
// - ShowExampleMenuFile()
//-----------------------------------------------------------------------------

// 演示创建"主"全屏菜单栏并填充它.
// 注意 BeginMainMenuBar() 和 BeginMenuBar() 的区别：
// - BeginMenuBar() = 当前窗口内的菜单栏（需要 ImGuiWindowFlags_MenuBar 标志!）
// - BeginMainMenuBar() = 在主视口顶部创建菜单栏大小窗口的辅助函数 + 在其中调用 BeginMenuBar().
static void ShowExampleAppMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu(u8"文件"))
        {
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(u8"编辑"))
        {
            if (ImGui::MenuItem(u8"撤销", "CTRL+Z")) {}
            if (ImGui::MenuItem(u8"重做", "CTRL+Y", false, false)) {} // 禁用项
            ImGui::Separator();
            if (ImGui::MenuItem(u8"剪切", "CTRL+X")) {}
            if (ImGui::MenuItem(u8"复制", "CTRL+C")) {}
            if (ImGui::MenuItem(u8"粘贴", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

// 请注意，快捷键目前仅用于显示
//（未来版本将向 BeginMenu() 添加显式标志以请求处理快捷键）
static void ShowExampleMenuFile()
{
    IMGUI_DEMO_MARKER(u8"示例/菜单");
    ImGui::MenuItem(u8"(演示菜单)", NULL, false, false);
    if (ImGui::MenuItem(u8"新建")) {}
    if (ImGui::MenuItem(u8"打开", "Ctrl+O")) {}
    if (ImGui::BeginMenu(u8"打开最近"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu(u8"更多.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu(u8"递归.."))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem(u8"保存", "Ctrl+S")) {}
    if (ImGui::MenuItem(u8"另存为..")) {}

    ImGui::Separator();
    IMGUI_DEMO_MARKER(u8"示例/菜单/选项");
    if (ImGui::BeginMenu(u8"选项"))
    {
        static bool enabled = true;
        ImGui::MenuItem(u8"启用", "", &enabled);
        ImGui::BeginChild(u8"子项", ImVec2(0, 60), ImGuiChildFlags_Borders);
        for (int i = 0; i < 10; i++)
            ImGui::Text(u8"滚动文本 %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        ImGui::SliderFloat(u8"值", &f, 0.0f, 1.0f);
        ImGui::InputFloat(u8"输入", &f, 0.1f);
        ImGui::Combo(u8"组合框", &n, u8"是\0否\0可能\0\0");
        ImGui::EndMenu();
    }

    IMGUI_DEMO_MARKER(u8"示例/菜单/颜色");
    if (ImGui::BeginMenu(u8"颜色"))
    {
        float sz = ImGui::GetTextLineHeight();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ImGui::Dummy(ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::EndMenu();
    }

    // 这里我们演示再次附加到"选项"菜单（我们在上面已经创建）
    // 当然在这个演示中，这个函数两次调用 BeginMenu("Options") 有点傻.
    // 在真实代码库中，从非常不同的代码位置使用此功能是有意义的.
    if (ImGui::BeginMenu(u8"选项")) // <-- 附加!
    {
        IMGUI_DEMO_MARKER(u8"示例/菜单/附加到现有菜单");
        static bool b = true;
        ImGui::Checkbox(u8"某些选项", &b);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu(u8"禁用", false)) // 禁用
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem(u8"已选中", NULL, true)) {}
    ImGui::Separator();
    if (ImGui::MenuItem(u8"退出", "Alt+F4")) {}
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.
struct ExampleAppConsole
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;

    ExampleAppConsole()
    {
        IMGUI_DEMO_MARKER(u8"示例/控制台");
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" 在这里提供测试用例，其中 "C"+[tab] 补全为 "CL" 并显示多个匹配项.
        Commands.push_back(u8"帮助");     // u8"帮助"
        Commands.push_back(u8"历史");  // u8"历史"
        Commands.push_back(u8"清空");    // u8"清空"
        Commands.push_back(u8"分类"); // u8"分类"
        AutoScroll = true;
        ScrollToBottom = false;
        AddLog(u8"欢迎使用 Dear ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            ImGui::MemFree(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = ImGui::MemAlloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            ImGui::MemFree(Items[i]);
        Items.clear();
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf) - 1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
    }

    void    Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem(u8"关闭控制台"))
                *p_open = false;
            ImGui::EndPopup();
        }

        ImGui::TextWrapped(
            u8"此示例实现了一个具有基本着色、补全（TAB 键）和历史记录（上/下箭头键）功能的控制台.更复杂的"
            u8"实现可能希望存储条目以及额外数据，如时间戳、发射器等.");
        ImGui::TextWrapped(u8"输入 'HELP' 获取帮助.");

        // TODO: 从底部开始显示项目

        if (ImGui::SmallButton(u8"添加调试文本")) { AddLog(u8"%d 一些文本", Items.Size); AddLog(u8"更多文本"); AddLog(u8"在此显示非常重要的消息!"); }
        ImGui::SameLine();
        if (ImGui::SmallButton(u8"添加调试错误")) { AddLog(u8"[错误]出了点问题"); }
        ImGui::SameLine();
        if (ImGui::SmallButton(u8"清空")) { ClearLog(); }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton(u8"复制");
        //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog(u8"垃圾信息 %f", t); }

        ImGui::Separator();

        // 选项菜单
        if (ImGui::BeginPopup(u8"选项"))
        {
            ImGui::Checkbox(u8"自动滚动", &AutoScroll);
            ImGui::EndPopup();
        }

        // 选项, 过滤
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_O, ImGuiInputFlags_Tooltip);
        if (ImGui::Button(u8"选项"))
            ImGui::OpenPopup(u8"选项");
        ImGui::SameLine();
        Filter.Draw(u8"过滤 (\"包含,-排除\") (\"错误\")", 180);
        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        if (ImGui::BeginChild(u8"滚动区域", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::Selectable(u8"清除")) ClearLog();
                ImGui::EndPopup();
            }

            // Display every line as a separate entry so we can change their color or add custom widgets.
            // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
            // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
            // to only process visible items. The clipper will automatically measure the height of your first item and then
            // "seek" to display only items in the visible area.
            // To use the clipper we can replace your standard loop:
            //      for (int i = 0; i < Items.Size; i++)
            //   With:
            //      ImGuiListClipper clipper;
            //      clipper.Begin(Items.Size);
            //      while (clipper.Step())
            //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            // - That your items are evenly spaced (same height)
            // - That you have cheap random access to your elements (you can access them given their index,
            //   without processing all the ones before)
            // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
            // We would need random-access on the post-filtered list.
            // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
            // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
            // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
            // to improve this example code!
            // If your items are of variable height:
            // - Split them into same height items would be simpler and facilitate random-seeking into your list.
            // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
            if (copy_to_clipboard)
                ImGui::LogToClipboard();
            for (const char* item : Items)
            {
                if (!Filter.PassFilter(item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                ImVec4 color;
                bool has_color = false;
                if (strstr(item, u8"[错误]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    ImGui::PushStyleColor(ImGuiCol_Text, color);
                ImGui::TextUnformatted(item);
                if (has_color)
                    ImGui::PopStyleColor();
            }
            if (copy_to_clipboard)
                ImGui::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
                ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ImGui::PopStyleVar();
        }
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        if (ImGui::InputText(u8"输入", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
        {
            char* s = InputBuf;
            Strtrim(s);
            if (s[0])
                ExecCommand(s);
            strcpy(s, "");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

        ImGui::End();
    }

    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back.
        // This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size - 1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0)
            {
                ImGui::MemFree(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, u8"清除") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, u8"帮助") == 0)
        {
            AddLog(u8"命令:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, u8"历史") == 0)
        {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog(u8"未知命令: '%s'\n", command_line);
        }

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data)
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ImGuiInputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < Commands.Size; i++)
                if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(Commands[i]);

            if (candidates.Size == 0)
            {
                // No match
                AddLog(u8"没有匹配 \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputting "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                AddLog(u8"可能的匹配项:\n");
                for (int i = 0; i < candidates.Size; i++)
                    AddLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = HistoryPos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (HistoryPos == -1)
                    HistoryPos = History.Size - 1;
                else if (HistoryPos > 0)
                    HistoryPos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (HistoryPos != -1)
                    if (++HistoryPos >= History.Size)
                        HistoryPos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != HistoryPos)
            {
                const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
        }
        return 0;
    }
};

static void ShowExampleAppConsole(bool* p_open)
{
    static ExampleAppConsole console;
    console.Draw(u8"示例:控制台", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
//-----------------------------------------------------------------------------

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

    ExampleAppLog()
    {
        AutoScroll = true;
        Clear();
    }

    void    Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // Options menu
        if (ImGui::BeginPopup(u8"选项"))
        {
            ImGui::Checkbox(u8"自动滚动", &AutoScroll);
            ImGui::EndPopup();
        }

        // 主窗口
        if (ImGui::Button(u8"选项"))
            ImGui::OpenPopup(u8"选项");
        ImGui::SameLine();
        bool clear = ImGui::Button(u8"清空");
        ImGui::SameLine();
        bool copy = ImGui::Button(u8"复制");
        ImGui::SameLine();
        Filter.Draw(u8"过滤", -100.0f);

        ImGui::Separator();

        if (ImGui::BeginChild(u8"滚动区域", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (clear)
                Clear();
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();
            if (Filter.IsActive())
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have random access to the result of our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    if (Filter.PassFilter(line_start, line_end))
                        ImGui::TextUnformatted(line_start, line_end);
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   ImGui::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using ImGuiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we have an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                ImGuiListClipper clipper;
                clipper.Begin(LineOffsets.Size);
                while (clipper.Step())
                {
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                    {
                        const char* line_start = buf + LineOffsets[line_no];
                        const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                        ImGui::TextUnformatted(line_start, line_end);
                    }
                }
                clipper.End();
            }
            ImGui::PopStyleVar();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
        ImGui::End();
    }
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
    static ExampleAppLog log;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin(u8"示例：日志", p_open);
    IMGUI_DEMO_MARKER(u8"示例/日志");
    if (ImGui::SmallButton(u8"[调试] 添加 5 条条目"))
    {
        static int counter = 0;
        const char* categories[3] = { u8"信息", u8"警告", u8"错误" };
        const char* words[] = { u8"困惑", u8"混乱", u8"切割", u8"书籍恐惧症", u8"突然离开", u8"傻瓜", u8"寡言的" };
        for (int n = 0; n < 5; n++)
        {
            const char* category = categories[counter % IM_ARRAYSIZE(categories)];
            const char* word = words[counter % IM_ARRAYSIZE(words)];
            log.AddLog(u8"[%05d] [%s] 你好，当前时间是 %.1f，这里有一个词：'%s'\n",
                ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
            counter++;
        }
    }
    ImGui::End();

    // 实际调用常规的日志辅助函数（将在我们刚才创建的同一窗口中 Begin()）
    log.Draw(u8"示例：日志", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：简单布局 / ShowExampleAppLayout()
//-----------------------------------------------------------------------------

// 演示创建具有多个子窗口的窗口.
static void ShowExampleAppLayout(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(u8"示例：简单布局", p_open, ImGuiWindowFlags_MenuBar))
    {
        IMGUI_DEMO_MARKER(u8"示例/简单布局");
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu(u8"文件"))
            {
                if (ImGui::MenuItem(u8"关闭", u8"Ctrl+W")) { *p_open = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // 左侧
        static int selected = 0;
        {
            ImGui::BeginChild(u8"左侧面板", ImVec2(150, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
            for (int i = 0; i < 100; i++)
            {
                // 修复：使用 ImGuiSelectableFlags_SelectOnNav 的好候选
                char label[128];
                sprintf(label, u8"我的对象 %d", i);
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        // 右侧
        {
            ImGui::BeginGroup();
            ImGui::BeginChild(u8"项目视图", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // 为下方的一行留出空间
            ImGui::Text(u8"我的对象: %d", selected);
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem(u8"描述"))
                {
                    ImGui::TextWrapped(u8"这是一段示例文本，用于演示布局功能.您可以在此处添加对象的详细描述信息.");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem(u8"详情"))
                {
                    ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            if (ImGui::Button(u8"重置")) {}
            ImGui::SameLine();
            if (ImGui::Button(u8"保存")) {}
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Property Editor / ShowExampleAppPropertyEditor()
//-----------------------------------------------------------------------------
// Some of the interactions are a bit lack-luster:
// - We would want pressing validating or leaving the filter to somehow restore focus.
// - We may want more advanced filtering (child nodes) and clipper support: both will need extra work.
// - We would want to customize some keyboard interactions to easily keyboard navigate between the tree and the properties.
//-----------------------------------------------------------------------------

struct ExampleAppPropertyEditor
{
    ImGuiTextFilter     Filter;
    ExampleTreeNode* VisibleNode = NULL;

    void Draw(ExampleTreeNode* root_node)
    {
        // Left side: draw tree
        // - Currently using a table to benefit from RowBg feature
        if (ImGui::BeginChild("##tree", ImVec2(300, 0), ImGuiChildFlags_ResizeX | ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened))
        {
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F, ImGuiInputFlags_Tooltip);
            ImGui::PushItemFlag(ImGuiItemFlags_NoNavDefaultFocus, true);
            if (ImGui::InputTextWithHint(u8"##筛选", u8"包括,-不包括", Filter.InputBuf, IM_ARRAYSIZE(Filter.InputBuf), ImGuiInputTextFlags_EscapeClearsAll))
                Filter.Build();
            ImGui::PopItemFlag();

            if (ImGui::BeginTable("##bg", 1, ImGuiTableFlags_RowBg))
            {
                for (ExampleTreeNode* node : root_node->Childs)
                    if (Filter.PassFilter(node->Name)) // Filter root node
                        DrawTreeNode(node);
                ImGui::EndTable();
            }
        }
        ImGui::EndChild();

        // Right side: draw properties
        ImGui::SameLine();

        ImGui::BeginGroup(); // Lock X position
        if (ExampleTreeNode* node = VisibleNode)
        {
            ImGui::Text("%s", node->Name);
            ImGui::TextDisabled("UID: 0x%08X", node->UID);
            ImGui::Separator();
            if (ImGui::BeginTable(u8"##性能", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
            {
                // Push object ID after we entered the table, so table is shared for all objects
                ImGui::PushID((int)node->UID);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 2.0f); // Default twice larger
                if (node->HasData)
                {
                    // In a typical application, the structure description would be derived from a data-driven system.
                    // - We try to mimic this with our ExampleMemberInfo structure and the ExampleTreeNodeMemberInfos[] array.
                    // - Limits and some details are hard-coded to simplify the demo.
                    for (const ExampleMemberInfo& field_desc : ExampleTreeNodeMemberInfos)
                    {
                        ImGui::TableNextRow();
                        ImGui::PushID(field_desc.Name);
                        ImGui::TableNextColumn();
                        ImGui::AlignTextToFramePadding();
                        ImGui::TextUnformatted(field_desc.Name);
                        ImGui::TableNextColumn();
                        void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
                        switch (field_desc.DataType)
                        {
                        case ImGuiDataType_Bool:
                        {
                            IM_ASSERT(field_desc.DataCount == 1);
                            ImGui::Checkbox(u8"##编辑", (bool*)field_ptr);
                            break;
                        }
                        case ImGuiDataType_S32:
                        {
                            int v_min = INT_MIN, v_max = INT_MAX;
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::DragScalarN(u8"##编辑", field_desc.DataType, field_ptr, field_desc.DataCount, 1.0f, &v_min, &v_max);
                            break;
                        }
                        case ImGuiDataType_Float:
                        {
                            float v_min = 0.0f, v_max = 1.0f;
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::SliderScalarN(u8"##编辑", field_desc.DataType, field_ptr, field_desc.DataCount, &v_min, &v_max);
                            break;
                        }
                        case ImGuiDataType_String:
                        {
                            ImGui::InputText(u8"##编辑", reinterpret_cast<char*>(field_ptr), 28);
                            break;
                        }
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::PopID();
                ImGui::EndTable();
            }
        }
        ImGui::EndGroup();
    }

    void DrawTreeNode(ExampleTreeNode* node)
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::PushID(node->UID);
        ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_None;
        tree_flags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;// Standard opening mode as we are likely to want to add selection afterwards
        tree_flags |= ImGuiTreeNodeFlags_NavLeftJumpsToParent;  // Left arrow support
        tree_flags |= ImGuiTreeNodeFlags_SpanFullWidth;         // Span full width for easier mouse reach
        tree_flags |= ImGuiTreeNodeFlags_DrawLinesToNodes;      // Always draw hierarchy outlines
        if (node == VisibleNode)
            tree_flags |= ImGuiTreeNodeFlags_Selected;
        if (node->Childs.Size == 0)
            tree_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
        if (node->DataMyBool == false)
            ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
        bool node_open = ImGui::TreeNodeEx("", tree_flags, "%s", node->Name);
        if (node->DataMyBool == false)
            ImGui::PopStyleColor();
        if (ImGui::IsItemFocused())
            VisibleNode = node;
        if (node_open)
        {
            for (ExampleTreeNode* child : node->Childs)
                DrawTreeNode(child);
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
};

// Demonstrate creating a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open, ImGuiDemoWindowData * demo_data)
{
    ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(u8"示例：属性编辑器", p_open))
    {
        ImGui::End();
        return;
    }

    IMGUI_DEMO_MARKER(u8"示例/属性编辑器");
    static ExampleAppPropertyEditor property_editor;
    if (demo_data->DemoTree == NULL)
        demo_data->DemoTree = ExampleTree_CreateDemoTree();
    property_editor.Draw(demo_data->DemoTree);

    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：长文本 / ShowExampleAppLongText()
//-----------------------------------------------------------------------------

// 演示/测试渲染大量文本，以及裁剪的情况.
static void ShowExampleAppLongText(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(u8"示例：长文本显示", p_open))
    {
        ImGui::End();
        return;
    }
    IMGUI_DEMO_MARKER(u8"示例/长文本显示");

    static int test_type = 0;
    static ImGuiTextBuffer log;
    static int lines = 0;
    ImGui::Text(u8"打印异常大量的文本.");
    ImGui::Combo(u8"测试类型", &test_type,
        u8"单次调用 TextUnformatted()\0"
        u8"多次调用 Text()，已裁剪\0"
        u8"多次调用 Text()，未裁剪（慢）\0");
    ImGui::Text(u8"缓冲区内容：%d 行，%d 字节", lines, log.size());
    if (ImGui::Button(u8"清空")) { log.clear(); lines = 0; }
    ImGui::SameLine();
    if (ImGui::Button(u8"添加 1000 行"))
    {
        for (int i = 0; i < 1000; i++)
            log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines + i);
        lines += 1000;
    }
    ImGui::BeginChild(u8"日志");
    switch (test_type)
    {
    case 0:
        // 单次调用 TextUnformatted()，使用大缓冲区
        ImGui::TextUnformatted(log.begin(), log.end());
        break;
    case 1:
    {
        // 多次调用 Text()，手动粗略裁剪 - 演示如何使用 ImGuiListClipper 辅助器.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiListClipper clipper;
        clipper.Begin(lines);
        while (clipper.Step())
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
        ImGui::PopStyleVar();
        break;
    }
    case 2:
        // 多次调用 Text()，未裁剪（慢）
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        for (int i = 0; i < lines; i++)
            ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
        ImGui::PopStyleVar();
        break;
    }
    ImGui::EndChild();
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：自动调整大小 / ShowExampleAppAutoResize()
//-----------------------------------------------------------------------------

// 演示创建一个根据内容自动调整大小的窗口.
static void ShowExampleAppAutoResize(bool* p_open)
{
    if (!ImGui::Begin(u8"示例：自动调整大小窗口", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::End();
        return;
    }
    IMGUI_DEMO_MARKER(u8"示例/自动调整大小窗口");

    static int lines = 10;
    ImGui::TextUnformatted(
        u8"窗口将在每帧根据其内容调整大小.\n"
        u8"请注意，您可能不希望查询窗口大小来\n"
        u8"输出您的内容，因为这会创建一个反馈循环.");
    ImGui::SliderInt(u8"行数", &lines, 1, 20);
    for (int i = 0; i < lines; i++)
        ImGui::Text(u8"%*s这是第 %d 行", i * 4, "", i); // 用空格填充以水平扩展大小
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Constrained Resize / ShowExampleAppConstrainedResize()
//-----------------------------------------------------------------------------

// Demonstrate creating a window with custom resize constraints.
// Note that size constraints currently don't work on a docked window (when in 'docking' branch)
static void ShowExampleAppConstrainedResize(bool* p_open)
{
    struct CustomConstraints
    {
        // Helper functions to demonstrate programmatic constraints
        // FIXME: This doesn't take account of decoration size (e.g. title bar), library should make this easier.
        // FIXME: None of the three demos works consistently when resizing from borders.
        static void AspectRatio(ImGuiSizeCallbackData* data)
        {
            float aspect_ratio = *(float*)data->UserData;
            data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio);
        }
        static void Square(ImGuiSizeCallbackData* data)
        {
            data->DesiredSize.x = data->DesiredSize.y = IM_MAX(data->DesiredSize.x, data->DesiredSize.y);
        }
        static void Step(ImGuiSizeCallbackData* data)
        {
            float step = *(float*)data->UserData;
            data->DesiredSize = ImVec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step);
        }
    };

    const char* test_desc[] =
    {
u8"在 100x100 和 500x500 之间",
u8"至少 100x100",
u8"垂直调整大小 + 锁定当前宽度",
u8"水平调整大小 + 锁定当前高度",
u8"宽度在 400 到 500 之间",
u8"高度至少 400",
u8"自定义：宽高比 16:9",
u8"自定义：始终保持正方形",
u8"自定义：固定步长 (100)",
    };

    // Options
    static bool auto_resize = false;
    static bool window_padding = true;
    static int type = 6; // Aspect Ratio
    static int display_lines = 10;

    // Submit constraint
    float aspect_ratio = 16.0f / 9.0f;
    float fixed_step = 100.0f;
    if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));         // Between 100x100 and 500x500
    if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
    if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));      // Resize vertical + lock current width
    if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));      // Resize horizontal + lock current height
    if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1), ImVec2(500, -1));          // Width Between and 400 and 500
    if (type == 5) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 400), ImVec2(-1, FLT_MAX));      // Height at least 400
    if (type == 6) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::AspectRatio, (void*)&aspect_ratio);   // Aspect ratio
    if (type == 7) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);                              // Always Square
    if (type == 8) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)&fixed_step);            // Fixed Step

    // Submit window
    if (!window_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    const ImGuiWindowFlags window_flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : 0;
    const bool window_open = ImGui::Begin(u8"示例：受限调整大小", p_open, window_flags);
    if (!window_padding)
        ImGui::PopStyleVar();
    if (window_open)
    {
        IMGUI_DEMO_MARKER(u8"示例/受限调整大小窗口");
        if (ImGui::GetIO().KeyShift)
        {
            // 显示一个虚拟视口（在真实应用中，您可能会使用 ImageButton() 来显示纹理.
            ImVec2 avail_size = ImGui::GetContentRegionAvail();
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGui::ColorButton(u8"视口", ImVec4(0.5f, 0.2f, 0.5f, 1.0f), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop, avail_size);
            ImGui::SetCursorScreenPos(ImVec2(pos.x + 10, pos.y + 10));
            ImGui::Text("%.2f x %.2f", avail_size.x, avail_size.y);
        }
        else
        {
            ImGui::Text(u8"(按住 SHIFT 显示虚拟视口)");
            if (ImGui::IsWindowDocked())
                ImGui::Text(u8"警告：如果窗口已停靠，大小约束将不起作用!");
            if (ImGui::Button(u8"设置为 200x200")) { ImGui::SetWindowSize(ImVec2(200, 200)); } ImGui::SameLine();
            if (ImGui::Button(u8"设置为 500x500")) { ImGui::SetWindowSize(ImVec2(500, 500)); } ImGui::SameLine();
            if (ImGui::Button(u8"设置为 800x200")) { ImGui::SetWindowSize(ImVec2(800, 200)); }
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
            ImGui::Combo(u8"约束", &type, test_desc, IM_ARRAYSIZE(test_desc));
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
            ImGui::DragInt(u8"行数", &display_lines, 0.2f, 1, 100);
            ImGui::Checkbox(u8"自动调整大小", &auto_resize);
            ImGui::Checkbox(u8"窗口内边距", &window_padding);
            for (int i = 0; i < display_lines; i++)
                ImGui::Text(u8"%*s你好，水手!使这一行足够长以作为示例.", i * 4, "");
        }
    }
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple overlay / ShowExampleAppSimpleOverlay()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple static window with no decoration
// + a context-menu to choose which corner of the screen to use.
static void ShowExampleAppSimpleOverlay(bool* p_open)
{
    static int location = 0;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (location >= 0)
    {
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    else if (location == -2)
    {
        // Center window
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        window_flags |= ImGuiWindowFlags_NoMove;
    }
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin(u8"示例：简单覆盖层", p_open, window_flags))
    {
        IMGUI_DEMO_MARKER(u8"示例/简单覆盖层");
        ImGui::Text(u8"简单覆盖层\n" u8"(右键点击更改位置)");
        ImGui::Separator();
        if (ImGui::IsMousePosValid())
            ImGui::Text(u8"鼠标位置: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text(u8"鼠标位置: <无效>");
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem(u8"自定义", NULL, location == -1)) location = -1;
            if (ImGui::MenuItem(u8"居中", NULL, location == -2)) location = -2;
            if (ImGui::MenuItem(u8"左上角", NULL, location == 0)) location = 0;
            if (ImGui::MenuItem(u8"右上角", NULL, location == 1)) location = 1;
            if (ImGui::MenuItem(u8"左下角", NULL, location == 2)) location = 2;
            if (ImGui::MenuItem(u8"右下角", NULL, location == 3)) location = 3;
            if (p_open && ImGui::MenuItem(u8"关闭")) *p_open = false;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Fullscreen window / ShowExampleAppFullscreen()
//-----------------------------------------------------------------------------

// Demonstrate creating a window covering the entire screen/viewport
static void ShowExampleAppFullscreen(bool* p_open)
{
    static bool use_work_area = true;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one or the other.
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    if (ImGui::Begin(u8"示例：全屏窗口", p_open, flags))
    {
        ImGui::Checkbox(u8"使用工作区代替主区域", &use_work_area);
        ImGui::SameLine();
        HelpMarker(u8"主区域 = 整个视口,\n工作区 = 整个视口减去主菜单栏、任务栏等使用的部分.\n\n在示例菜单中启用主菜单栏以查看差异.");

        ImGui::CheckboxFlags(u8"ImGuiWindowFlags_NoBackground", &flags, ImGuiWindowFlags_NoBackground);
        ImGui::CheckboxFlags(u8"ImGuiWindowFlags_NoDecoration", &flags, ImGuiWindowFlags_NoDecoration);
        ImGui::Indent();
        ImGui::CheckboxFlags(u8"ImGuiWindowFlags_NoTitleBar", &flags, ImGuiWindowFlags_NoTitleBar);
        ImGui::CheckboxFlags(u8"ImGuiWindowFlags_NoCollapse", &flags, ImGuiWindowFlags_NoCollapse);
        ImGui::CheckboxFlags(u8"ImGuiWindowFlags_NoScrollbar", &flags, ImGuiWindowFlags_NoScrollbar);
        ImGui::Unindent();

        if (p_open && ImGui::Button(u8"关闭此窗口"))
            *p_open = false;
    }
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：操作窗口标题 / ShowExampleAppWindowTitles()
//-----------------------------------------------------------------------------

// 演示在标识符中使用 "##" 和 "###" 来操作 ID 生成.
// 这适用于所有常规项.
// 详情请阅读常见问题解答部分"如何拥有多个具有相同标签的小部件?".
static void ShowExampleAppWindowTitles(bool*)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 base_pos = viewport->Pos;

    // 默认情况下，窗口由其标题唯一标识.
    // 您可以使用 "##" 和 "###" 标记来操作显示/ID.

    // 使用 "##" 显示相同标题但具有唯一标识符.
    ImGui::SetNextWindowPos(ImVec2(base_pos.x + 100, base_pos.y + 100), ImGuiCond_FirstUseEver);
    ImGui::Begin(u8"与另一个窗口相同的标题##1");
    IMGUI_DEMO_MARKER(u8"示例/操作窗口标题");
    ImGui::Text(u8"这是窗口 1.\n我的标题与窗口 2 相同，但我的标识符是唯一的.");
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(base_pos.x + 100, base_pos.y + 200), ImGuiCond_FirstUseEver);
    ImGui::Begin(u8"与另一个窗口相同的标题##2");
    ImGui::Text(u8"这是窗口 2.\n我的标题与窗口 1 相同，但我的标识符是唯一的.");
    ImGui::End();

    // 使用 "###" 显示变化的标题但保持静态标识符 "AnimatedTitle"
    char buf[128];
    sprintf(buf, u8"动画标题 %c %d###AnimatedTitle", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], ImGui::GetFrameCount());
    ImGui::SetNextWindowPos(ImVec2(base_pos.x + 100, base_pos.y + 300), ImGuiCond_FirstUseEver);
    ImGui::Begin(buf);
    ImGui::Text(u8"此窗口有一个变化的标题.");
    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] 示例应用：使用 ImDrawList API 进行自定义渲染 / ShowExampleAppCustomRendering()
//-----------------------------------------------------------------------------

// 添加一个 |_| 形状
static void PathConcaveShape(ImDrawList * draw_list, float x, float y, float sz)
{
    const ImVec2 pos_norms[] = { { 0.0f, 0.0f }, { 0.3f, 0.0f }, { 0.3f, 0.7f }, { 0.7f, 0.7f }, { 0.7f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    for (const ImVec2& p : pos_norms)
        draw_list->PathLineTo(ImVec2(x + 0.5f + (int)(sz * p.x), y + 0.5f + (int)(sz * p.y)));
}

// 演示使用低级 ImDrawList 绘制自定义形状.
static void ShowExampleAppCustomRendering(bool* p_open)
{
    if (!ImGui::Begin(u8"示例：自定义渲染", p_open))
    {
        ImGui::End();
        return;
    }
    IMGUI_DEMO_MARKER(u8"示例/自定义渲染");

    // 提示：如果您进行大量自定义渲染，您可能希望使用自己的几何类型并受益于
    // 重载运算符等.在 imconfig.h 中定义 IM_VEC2_CLASS_EXTRA 以在您的类型和
    // ImVec2/ImVec4 之间创建隐式转换.Dear ImGui 定义了重载运算符，但它们内部于 imgui.cpp
    // 并且不会暴露到外部（以避免弄乱您的类型）在此示例中，我们没有使用数学运算符!

    if (ImGui::BeginTabBar("##TabBar"))
    {
        if (ImGui::BeginTabItem(u8"图元"))
        {
            ImGui::PushItemWidth(-ImGui::GetFontSize() * 15);
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            // 绘制渐变
            // （请注意，这些目前加剧了我们的 sRGB/线性问题）
            // 调用 ImGui::GetColorU32() 会将给定颜色乘以当前样式 Alpha，但您也可以直接传递 IM_COL32().
            ImGui::Text(u8"渐变");
            ImVec2 gradient_size = ImVec2(ImGui::CalcItemWidth(), ImGui::GetFrameHeight());
            {
                ImVec2 p0 = ImGui::GetCursorScreenPos();
                ImVec2 p1 = ImVec2(p0.x + gradient_size.x, p0.y + gradient_size.y);
                ImU32 col_a = ImGui::GetColorU32(IM_COL32(0, 0, 0, 255));
                ImU32 col_b = ImGui::GetColorU32(IM_COL32(255, 255, 255, 255));
                draw_list->AddRectFilledMultiColor(p0, p1, col_a, col_b, col_b, col_a);
                ImGui::InvisibleButton("##gradient1", gradient_size);
            }
            {
                ImVec2 p0 = ImGui::GetCursorScreenPos();
                ImVec2 p1 = ImVec2(p0.x + gradient_size.x, p0.y + gradient_size.y);
                ImU32 col_a = ImGui::GetColorU32(IM_COL32(0, 255, 0, 255));
                ImU32 col_b = ImGui::GetColorU32(IM_COL32(255, 0, 0, 255));
                draw_list->AddRectFilledMultiColor(p0, p1, col_a, col_b, col_b, col_a);
                ImGui::InvisibleButton("##gradient2", gradient_size);
            }

            // 绘制一堆图元
            ImGui::Text(u8"所有图元");
            static float sz = 36.0f;
            static float thickness = 3.0f;
            static int ngon_sides = 6;
            static bool circle_segments_override = false;
            static int circle_segments_override_v = 12;
            static bool curve_segments_override = false;
            static int curve_segments_override_v = 8;
            static ImVec4 colf = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
            ImGui::DragFloat(u8"大小", &sz, 0.2f, 2.0f, 100.0f, "%.0f");
            ImGui::DragFloat(u8"厚度", &thickness, 0.05f, 1.0f, 8.0f, "%.02f");
            ImGui::SliderInt(u8"N边形边数", &ngon_sides, 3, 12);
            ImGui::Checkbox("##circlesegmentoverride", &circle_segments_override);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            circle_segments_override |= ImGui::SliderInt(u8"圆形分段覆盖", &circle_segments_override_v, 3, 40);
            ImGui::Checkbox("##curvessegmentoverride", &curve_segments_override);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            curve_segments_override |= ImGui::SliderInt(u8"曲线分段覆盖", &curve_segments_override_v, 3, 40);
            ImGui::ColorEdit4(u8"颜色", &colf.x);

            const ImVec2 p = ImGui::GetCursorScreenPos();
            const ImU32 col = ImColor(colf);
            const float spacing = 10.0f;
            const ImDrawFlags corners_tl_br = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight;
            const float rounding = sz / 5.0f;
            const int circle_segments = circle_segments_override ? circle_segments_override_v : 0;
            const int curve_segments = curve_segments_override ? curve_segments_override_v : 0;
            const ImVec2 cp3[3] = { ImVec2(0.0f, sz * 0.6f), ImVec2(sz * 0.5f, -sz * 0.4f), ImVec2(sz, sz) }; // Control points for curves
            const ImVec2 cp4[4] = { ImVec2(0.0f, 0.0f), ImVec2(sz * 1.3f, sz * 0.3f), ImVec2(sz - sz * 1.3f, sz - sz * 0.3f), ImVec2(sz, sz) };

            float x = p.x + 4.0f;
            float y = p.y + 4.0f;
            for (int n = 0; n < 2; n++)
            {
                // First line uses a thickness of 1.0f, second line uses the configurable thickness
                float th = (n == 0) ? 1.0f : thickness;
                draw_list->AddNgon(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, ngon_sides, th);                 x += sz + spacing;  // N-gon
                draw_list->AddCircle(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, circle_segments, th);          x += sz + spacing;  // Circle
                draw_list->AddEllipse(ImVec2(x + sz * 0.5f, y + sz * 0.5f), ImVec2(sz * 0.5f, sz * 0.3f), col, -0.3f, circle_segments, th); x += sz + spacing;  // Ellipse
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 0.0f, ImDrawFlags_None, th);          x += sz + spacing;  // Square
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, rounding, ImDrawFlags_None, th);      x += sz + spacing;  // Square with all rounded corners
                draw_list->AddRect(ImVec2(x, y), ImVec2(x + sz, y + sz), col, rounding, corners_tl_br, th);         x += sz + spacing;  // Square with two rounded corners
                draw_list->AddTriangle(ImVec2(x + sz * 0.5f, y), ImVec2(x + sz, y + sz - 0.5f), ImVec2(x, y + sz - 0.5f), col, th); x += sz + spacing;  // Triangle
                //draw_list->AddTriangle(ImVec2(x+sz*0.2f,y), ImVec2(x, y+sz-0.5f), ImVec2(x+sz*0.4f, y+sz-0.5f), col, th);x+= sz*0.4f + spacing; // Thin triangle
                PathConcaveShape(draw_list, x, y, sz); draw_list->PathStroke(col, ImDrawFlags_Closed, th);          x += sz + spacing;  // Concave Shape
                //draw_list->AddPolyline(concave_shape, IM_ARRAYSIZE(concave_shape), col, ImDrawFlags_Closed, th);
                draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y), col, th);                                       x += sz + spacing;  // Horizontal line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLine(ImVec2(x, y), ImVec2(x, y + sz), col, th);                                       x += spacing;       // Vertical line (note: drawing a filled rectangle will be faster!)
                draw_list->AddLine(ImVec2(x, y), ImVec2(x + sz, y + sz), col, th);                                  x += sz + spacing;  // Diagonal line

                // Path
                draw_list->PathArcTo(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, 3.141592f, 3.141592f * -0.5f);
                draw_list->PathStroke(col, ImDrawFlags_None, th);
                x += sz + spacing;

                // Quadratic Bezier Curve (3 control points)
                draw_list->AddBezierQuadratic(ImVec2(x + cp3[0].x, y + cp3[0].y), ImVec2(x + cp3[1].x, y + cp3[1].y), ImVec2(x + cp3[2].x, y + cp3[2].y), col, th, curve_segments);
                x += sz + spacing;

                // Cubic Bezier Curve (4 control points)
                draw_list->AddBezierCubic(ImVec2(x + cp4[0].x, y + cp4[0].y), ImVec2(x + cp4[1].x, y + cp4[1].y), ImVec2(x + cp4[2].x, y + cp4[2].y), ImVec2(x + cp4[3].x, y + cp4[3].y), col, th, curve_segments);

                x = p.x + 4;
                y += sz + spacing;
            }

            // Filled shapes
            draw_list->AddNgonFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, ngon_sides);             x += sz + spacing;  // N-gon
            draw_list->AddCircleFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, col, circle_segments);      x += sz + spacing;  // Circle
            draw_list->AddEllipseFilled(ImVec2(x + sz * 0.5f, y + sz * 0.5f), ImVec2(sz * 0.5f, sz * 0.3f), col, -0.3f, circle_segments); x += sz + spacing;// Ellipse
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col);                                    x += sz + spacing;  // Square
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f);                             x += sz + spacing;  // Square with all rounded corners
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + sz), col, 10.0f, corners_tl_br);              x += sz + spacing;  // Square with two rounded corners
            draw_list->AddTriangleFilled(ImVec2(x + sz * 0.5f, y), ImVec2(x + sz, y + sz - 0.5f), ImVec2(x, y + sz - 0.5f), col);  x += sz + spacing;  // Triangle
            //draw_list->AddTriangleFilled(ImVec2(x+sz*0.2f,y), ImVec2(x, y+sz-0.5f), ImVec2(x+sz*0.4f, y+sz-0.5f), col); x += sz*0.4f + spacing; // Thin triangle
            PathConcaveShape(draw_list, x, y, sz); draw_list->PathFillConcave(col);                                 x += sz + spacing;  // Concave shape
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + sz, y + thickness), col);                             x += sz + spacing;  // Horizontal line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + thickness, y + sz), col);                             x += spacing * 2.0f;// Vertical line (faster than AddLine, but only handle integer thickness)
            draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + 1, y + 1), col);                                      x += sz;            // Pixel (faster than AddLine)

            // Path
            draw_list->PathArcTo(ImVec2(x + sz * 0.5f, y + sz * 0.5f), sz * 0.5f, 3.141592f * -0.5f, 3.141592f);
            draw_list->PathFillConvex(col);
            x += sz + spacing;

            // Quadratic Bezier Curve (3 control points)
            draw_list->PathLineTo(ImVec2(x + cp3[0].x, y + cp3[0].y));
            draw_list->PathBezierQuadraticCurveTo(ImVec2(x + cp3[1].x, y + cp3[1].y), ImVec2(x + cp3[2].x, y + cp3[2].y), curve_segments);
            draw_list->PathFillConvex(col);
            x += sz + spacing;

            draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + sz, y + sz), IM_COL32(0, 0, 0, 255), IM_COL32(255, 0, 0, 255), IM_COL32(255, 255, 0, 255), IM_COL32(0, 255, 0, 255));
            x += sz + spacing;

            ImGui::Dummy(ImVec2((sz + spacing) * 13.2f, (sz + spacing) * 3.0f));
            ImGui::PopItemWidth();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"画布"))
        {
            static ImVector<ImVec2> points;
            static ImVec2 scrolling(0.0f, 0.0f);
            static bool opt_enable_grid = true;
            static bool opt_enable_context_menu = true;
            static bool adding_line = false;

            ImGui::Checkbox(u8"启用网格", &opt_enable_grid);
            ImGui::Checkbox(u8"启用上下文菜单", &opt_enable_context_menu);
            ImGui::Text(u8"鼠标左键: 拖动添加线条,\n鼠标右键: 拖动滚动, 点击显示上下文菜单.");

            // Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
            // Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
            // To use a child window instead we could use, e.g:
            //      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));      // Disable padding
            //      ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(50, 50, 50, 255));  // Set a background color
            //      ImGui::BeginChild("canvas", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoMove);
            //      ImGui::PopStyleColor();
            //      ImGui::PopStyleVar();
            //      [...]
            //      ImGui::EndChild();

            // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
            ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
            ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
            if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
            if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
            ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

            // Draw border and background color
            ImGuiIO& io = ImGui::GetIO();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
            draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

            // This will catch our interactions
            ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
            const bool is_hovered = ImGui::IsItemHovered(); // Hovered
            const bool is_active = ImGui::IsItemActive();   // Held
            const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
            const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

            // Add first and second point
            if (is_hovered && !adding_line && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                points.push_back(mouse_pos_in_canvas);
                points.push_back(mouse_pos_in_canvas);
                adding_line = true;
            }
            if (adding_line)
            {
                points.back() = mouse_pos_in_canvas;
                if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
                    adding_line = false;
            }

            // Pan (we use a zero mouse threshold when there's no context menu)
            // You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
            const float mouse_threshold_for_pan = opt_enable_context_menu ? -1.0f : 0.0f;
            if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
            {
                scrolling.x += io.MouseDelta.x;
                scrolling.y += io.MouseDelta.y;
            }

            // Context menu (under default mouse threshold)
            ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
            if (opt_enable_context_menu && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
                ImGui::OpenPopupOnItemClick(u8"上下文", ImGuiPopupFlags_MouseButtonRight);
            if (ImGui::BeginPopup(u8"上下文"))
            {
                if (adding_line)
                    points.resize(points.size() - 2);
                adding_line = false;
                if (ImGui::MenuItem(u8"删除一条", NULL, false, points.Size > 0)) { points.resize(points.size() - 2); }
                if (ImGui::MenuItem(u8"删除全部", NULL, false, points.Size > 0)) { points.clear(); }
                ImGui::EndPopup();
            }

            // 在画布上绘制网格和所有线条
            draw_list->PushClipRect(canvas_p0, canvas_p1, true);
            if (opt_enable_grid)
            {
                const float GRID_STEP = 64.0f;
                for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
                    draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
                for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
                    draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
            }
            for (int n = 0; n < points.Size; n += 2)
                draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y), ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
            draw_list->PopClipRect();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem(u8"背景/前景绘制列表"))
        {
            static bool draw_bg = true;
            static bool draw_fg = true;
            ImGui::Checkbox(u8"在背景绘制列表中绘制", &draw_bg);
            ImGui::SameLine(); HelpMarker(u8"背景绘制列表将在所有 Dear ImGui 窗口下方渲染.");
            ImGui::Checkbox(u8"在前景绘制列表中绘制", &draw_fg);
            ImGui::SameLine(); HelpMarker(u8"前景绘制列表将在所有 Dear ImGui 窗口上方渲染.");
            ImVec2 window_pos = ImGui::GetWindowPos();
            ImVec2 window_size = ImGui::GetWindowSize();
            ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);
            if (draw_bg)
                ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4);
            if (draw_fg)
                ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
            ImGui::EndTabItem();
        }

        // 通过通道分割演示乱序渲染
        // 我们使用 ImDrawList 中的函数，因为每个绘制列表都包含一个方便的分离器，
        // 但如果您需要嵌套它们，也可以实例化自己的 ImDrawListSplitter.
        if (ImGui::BeginTabItem(u8"绘制通道"))
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            {
                ImGui::Text(u8"蓝色形状先绘制：显示在后方");
                ImGui::Text(u8"红色形状后绘制：显示在前方");
                ImVec2 p0 = ImGui::GetCursorScreenPos();
                draw_list->AddRectFilled(ImVec2(p0.x, p0.y), ImVec2(p0.x + 50, p0.y + 50), IM_COL32(0, 0, 255, 255)); // 蓝色
                draw_list->AddRectFilled(ImVec2(p0.x + 25, p0.y + 25), ImVec2(p0.x + 75, p0.y + 75), IM_COL32(255, 0, 0, 255)); // 红色
                ImGui::Dummy(ImVec2(75, 75));
            }
            ImGui::Separator();
            {
                ImGui::Text(u8"蓝色形状先绘制到通道 1：显示在前方");
                ImGui::Text(u8"红色形状后绘制到通道 0：显示在后方");
                ImVec2 p1 = ImGui::GetCursorScreenPos();

                // 创建 2 个通道，先绘制蓝色形状，然后绘制红色形状.
                // 您可以创建任意数量的通道.表格 API 每列使用 1 个通道以更好地批处理绘制调用.
                draw_list->ChannelsSplit(2);
                draw_list->ChannelsSetCurrent(1);
                draw_list->AddRectFilled(ImVec2(p1.x, p1.y), ImVec2(p1.x + 50, p1.y + 50), IM_COL32(0, 0, 255, 255)); // 蓝色
                draw_list->ChannelsSetCurrent(0);
                draw_list->AddRectFilled(ImVec2(p1.x + 25, p1.y + 25), ImVec2(p1.x + 75, p1.y + 75), IM_COL32(255, 0, 0, 255)); // 红色

                // 展平/重新排序通道.红色形状在通道 0 中，它显示在通道 1 中的蓝色形状下方.
                // 这通过仅复制绘制索引（不复制顶点）来实现.
                draw_list->ChannelsMerge();
                ImGui::Dummy(ImVec2(75, 75));
                ImGui::Text(u8"重新排序后，通道 0 的内容显示在通道 1 的下方.");
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
//-----------------------------------------------------------------------------

// Demonstrate using DockSpace() to create an explicit docking node within an existing window.
// Note: You can use most Docking facilities without calling any API. You DO NOT need to call DockSpace() to use Docking!
// - Drag from window title bar or their tab to dock/undock. Hold SHIFT to disable docking.
// - Drag from window menu button (upper-left button) to undock an entire node (all windows).
// - When io.ConfigDockingWithShift == true, you instead need to hold SHIFT to enable docking.
// About dockspaces:
// - Use DockSpace() to create an explicit dock node _within_ an existing window.
// - Use DockSpaceOverViewport() to create an explicit dock node covering the screen or a specific viewport.
//   This is often used with ImGuiDockNodeFlags_PassthruCentralNode.
// - Important: Dockspaces need to be submitted _before_ any window they can host. Submit it early in your frame! (*)
// - Important: Dockspaces need to be kept alive if hidden, otherwise windows docked into it will be undocked.
//   e.g. if you have multiple tabs with a dockspace inside each tab: submit the non-visible dockspaces with ImGuiDockNodeFlags_KeepAliveOnly.
// (*) because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node,
// because that window is submitted as part of the part of the NewFrame() call. An easy workaround is that you can create
// your own implicit "Debug##2" window after calling DockSpace() and leave it in the window stack for anyone to use.
void ShowExampleAppDockSpace(bool* p_open)
{
    // READ THIS !!!
    // TL;DR; this demo is more complicated than what most users you would normally use.
    // If we remove all options we are showcasing, this demo would become:
    //     void ShowExampleAppDockSpace()
    //     {
    //         ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    //     }
    // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
    // In this specific demo, we are not using DockSpaceOverViewport() because:
    // - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
    // - (2) we allow the host window to have padding (when opt_padding == true)
    // - (3) we expose many flags and need a way to have them visible.
    // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
    //      in your code, but we don't here because we allow the window to be floating)

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(u8"DockSpace 演示", p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // 提交 DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID(u8"MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        ShowDockingDisabledMessage();
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(u8"选项"))
        {
            // 禁用全屏模式将允许窗口移动到其他窗口的前面，
            // 目前如果没有更精细的窗口深度/z轴控制，我们无法撤销此操作.
            ImGui::MenuItem(u8"全屏", NULL, &opt_fullscreen);
            ImGui::MenuItem(u8"内边距", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem(u8"标志：禁止在中央节点上停靠", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
            if (ImGui::MenuItem(u8"标志：禁止拆分", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
            if (ImGui::MenuItem(u8"标志：禁止取消停靠", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
            if (ImGui::MenuItem(u8"标志：禁止调整大小", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem(u8"标志：自动隐藏标签栏", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem(u8"标志：穿透中央节点", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            if (ImGui::MenuItem(u8"关闭", NULL, false, p_open != NULL))
                *p_open = false;
            ImGui::EndMenu();
        }
        HelpMarker(
            u8"启用停靠后，您总是可以将大多数窗口停靠到另一个窗口中!现在试试吧!" "\n"
            u8"- 从窗口标题栏或其标签拖动以停靠/取消停靠." "\n"
            u8"- 从窗口菜单按钮（左上角按钮）拖动以取消停靠整个节点（所有窗口）." "\n"
            u8"- 按住 SHIFT 键禁用停靠（如果 io.ConfigDockingWithShift == false，默认）" "\n"
            u8"- 按住 SHIFT 键启用停靠（如果 io.ConfigDockingWithShift == true）" "\n"
            u8"此演示应用程序与启用停靠无关!" "\n\n"
            u8"此演示应用程序仅演示了 ImGui::DockSpace() 的使用，它允许您在另一个窗口内手动创建停靠节点." "\n\n"
            u8"有关更多详细信息，请阅读 ShowExampleAppDockSpace() 中的注释.");

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Documents Handling / ShowExampleAppDocuments()
//-----------------------------------------------------------------------------

// Simplified structure to mimic a Document model
struct MyDocument
{
    char        Name[32];   // Document title
    int         UID;        // Unique ID (necessary as we can change title)
    bool        Open;       // Set when open (we keep an array of all available documents to simplify demo code!)
    bool        OpenPrev;   // Copy of Open from last update.
    bool        Dirty;      // Set when the document has been modified
    ImVec4      Color;      // An arbitrary variable associated to the document

    MyDocument(int uid, const char* name, bool open = true, const ImVec4& color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
    {
        UID = uid;
        snprintf(Name, sizeof(Name), "%s", name);
        Open = OpenPrev = open;
        Dirty = false;
        Color = color;
    }
    void DoOpen() { Open = true; }
    void DoForceClose() { Open = false; Dirty = false; }
    void DoSave() { Dirty = false; }
};

struct ExampleAppDocuments
{
    ImVector<MyDocument>    Documents;
    ImVector<MyDocument*>   CloseQueue;
    MyDocument* RenamingDoc = NULL;
    bool                    RenamingStarted = false;

    ExampleAppDocuments()
    {
        Documents.push_back(MyDocument(0, u8"生菜", true, ImVec4(0.4f, 0.8f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument(1, u8"茄子", true, ImVec4(0.8f, 0.5f, 1.0f, 1.0f)));
        Documents.push_back(MyDocument(2, u8"胡萝卜", true, ImVec4(1.0f, 0.8f, 0.5f, 1.0f)));
        Documents.push_back(MyDocument(3, u8"番茄", false, ImVec4(1.0f, 0.3f, 0.4f, 1.0f)));
        Documents.push_back(MyDocument(4, u8"一个相当长的标题", false, ImVec4(0.4f, 0.8f, 0.8f, 1.0f)));
        Documents.push_back(MyDocument(5, u8"某个文档", false, ImVec4(0.8f, 0.8f, 1.0f, 1.0f)));
    }

    // 由于我们允许更改文档名称，因此附加一个永不变的文档ID以保持标签稳定
    void GetTabName(MyDocument* doc, char* out_buf, size_t out_buf_size)
    {
        snprintf(out_buf, out_buf_size, "%s###doc%d", doc->Name, doc->UID);
    }

    // 显示文档的占位符内容
    void DisplayDocContents(MyDocument* doc)
    {
        ImGui::PushID(doc);
        ImGui::Text(u8"文档 \"%s\"", doc->Name);
        ImGui::PushStyleColor(ImGuiCol_Text, doc->Color);
        ImGui::TextWrapped(u8"这是一段示例文本，用于演示文档内容的显示.您可以在此处添加实际的文档内容.");
        ImGui::PopStyleColor();

        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_R, ImGuiInputFlags_Tooltip);
        if (ImGui::Button(u8"重命名.."))
        {
            RenamingDoc = doc;
            RenamingStarted = true;
        }
        ImGui::SameLine();

        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_M, ImGuiInputFlags_Tooltip);
        if (ImGui::Button(u8"修改"))
            doc->Dirty = true;

        ImGui::SameLine();
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_S, ImGuiInputFlags_Tooltip);
        if (ImGui::Button(u8"保存"))
            doc->DoSave();

        ImGui::SameLine();
        ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_W, ImGuiInputFlags_Tooltip);
        if (ImGui::Button(u8"关闭"))
            CloseQueue.push_back(doc);
        ImGui::ColorEdit3(u8"颜色", &doc->Color.x);  // 用于测试拖放和按住拖动打开标签行为
        ImGui::PopID();
    }

    // 显示文档的上下文菜单
    void DisplayDocContextMenu(MyDocument* doc)
    {
        if (!ImGui::BeginPopupContextItem())
            return;

        char buf[256];
        sprintf(buf, u8"保存 %s", doc->Name);
        if (ImGui::MenuItem(buf, "Ctrl+S", false, doc->Open))
            doc->DoSave();
        if (ImGui::MenuItem(u8"重命名...", "Ctrl+R", false, doc->Open))
            RenamingDoc = doc;
        if (ImGui::MenuItem(u8"关闭", "Ctrl+W", false, doc->Open))
            CloseQueue.push_back(doc);
        ImGui::EndPopup();
    }

    // [Optional] Notify the system of Tabs/Windows closure that happened outside the regular tab interface.
    // If a tab has been closed programmatically (aka closed from another source such as the Checkbox() in the demo,
    // as opposed to clicking on the regular tab closing button) and stops being submitted, it will take a frame for
    // the tab bar to notice its absence. During this frame there will be a gap in the tab bar, and if the tab that has
    // disappeared was the selected one, the tab bar will report no selected tab during the frame. This will effectively
    // give the impression of a flicker for one frame.
    // We call SetTabItemClosed() to manually notify the Tab Bar or Docking system of removed tabs to avoid this glitch.
    // Note that this completely optional, and only affect tab bars with the ImGuiTabBarFlags_Reorderable flag.
    void NotifyOfDocumentsClosedElsewhere()
    {
        for (MyDocument& doc : Documents)
        {
            if (!doc.Open && doc.OpenPrev)
                ImGui::SetTabItemClosed(doc.Name);
            doc.OpenPrev = doc.Open;
        }
    }
};

void ShowExampleAppDocuments(bool* p_open)
{
    static ExampleAppDocuments app;

    // Options
    enum Target
    {
        Target_None,
        Target_Tab,                 // Create documents as local tab into a local tab bar
        Target_DockSpaceAndWindow   // Create documents as regular windows, and create an embedded dockspace
    };
    static Target opt_target = Target_Tab;
    static bool opt_reorderable = true;
    static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

    // When (opt_target == Target_DockSpaceAndWindow) there is the possibily that one of our child Document window (e.g. "Eggplant")
    // that we emit gets docked into the same spot as the parent window ("Example: Documents").
    // This would create a problematic feedback loop because selecting the "Eggplant" tab would make the "Example: Documents" tab
    // not visible, which in turn would stop submitting the "Eggplant" window.
    // We avoid this problem by submitting our documents window even if our parent window is not currently visible.
    // Another solution may be to make the "Example: Documents" window use the ImGuiWindowFlags_NoDocking.

    bool window_contents_visible = ImGui::Begin(u8"示例：文档", p_open, ImGuiWindowFlags_MenuBar);
    if (!window_contents_visible && opt_target != Target_DockSpaceAndWindow)
    {
        ImGui::End();
        return;
    }

    // 菜单
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(u8"文件"))
        {
            int open_count = 0;
            for (MyDocument& doc : app.Documents)
                open_count += doc.Open ? 1 : 0;

            if (ImGui::BeginMenu(u8"打开", open_count < app.Documents.Size))
            {
                for (MyDocument& doc : app.Documents)
                    if (!doc.Open && ImGui::MenuItem(doc.Name))
                        doc.DoOpen();
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem(u8"关闭所有文档", NULL, false, open_count > 0))
                for (MyDocument& doc : app.Documents)
                    app.CloseQueue.push_back(&doc);
            if (ImGui::MenuItem(u8"退出") && p_open)
                *p_open = false;
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // [调试] 用复选框列出所有文档
    for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
    {
        MyDocument& doc = app.Documents[doc_n];
        if (doc_n > 0)
            ImGui::SameLine();
        ImGui::PushID(&doc);
        if (ImGui::Checkbox(doc.Name, &doc.Open))
            if (!doc.Open)
                doc.DoForceClose();
        ImGui::PopID();
    }
    ImGui::PushItemWidth(ImGui::GetFontSize() * 12);
    ImGui::Combo(u8"输出", (int*)&opt_target, u8"无\0标签栏+标签\0停靠空间+窗口\0");
    ImGui::PopItemWidth();
    bool redock_all = false;
    if (opt_target == Target_Tab) { ImGui::SameLine(); ImGui::Checkbox(u8"可重新排序标签", &opt_reorderable); }
    if (opt_target == Target_DockSpaceAndWindow) { ImGui::SameLine(); redock_all = ImGui::Button(u8"重新停靠所有"); }

    ImGui::Separator();

    // About the ImGuiWindowFlags_UnsavedDocument / ImGuiTabItemFlags_UnsavedDocument flags.
    // They have multiple effects:
    // - Display a dot next to the title.
    // - Tab is selected when clicking the X close button.
    // - Closure is not assumed (will wait for user to stop submitting the tab).
    //   Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    //   We need to assume closure by default otherwise waiting for "lack of submission" on the next frame would leave an empty
    //   hole for one-frame, both in the tab-bar and in tab-contents when closing a tab/window.
    //   The rarely used SetTabItemClosed() function is a way to notify of programmatic closure to avoid the one-frame hole.

    // Tabs
    if (opt_target == Target_Tab)
    {
        ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
        tab_bar_flags |= ImGuiTabBarFlags_DrawSelectedOverline;
        if (ImGui::BeginTabBar(u8"##标签", tab_bar_flags))
        {
            if (opt_reorderable)
                app.NotifyOfDocumentsClosedElsewhere();

            // [DEBUG] Stress tests
            //if ((ImGui::GetFrameCount() % 30) == 0) docs[1].Open ^= 1;            // [DEBUG] Automatically show/hide a tab. Test various interactions e.g. dragging with this on.
            //if (ImGui::GetIO().KeyCtrl) ImGui::SetTabItemSelected(docs[1].Name);  // [DEBUG] Test SetTabItemSelected(), probably not very useful as-is anyway..

            // Submit Tabs
            for (MyDocument& doc : app.Documents)
            {
                if (!doc.Open)
                    continue;

                // As we allow to change document name, we append a never-changing document id so tabs are stable
                char doc_name_buf[64];
                app.GetTabName(&doc, doc_name_buf, sizeof(doc_name_buf));
                ImGuiTabItemFlags tab_flags = (doc.Dirty ? ImGuiTabItemFlags_UnsavedDocument : 0);
                bool visible = ImGui::BeginTabItem(doc_name_buf, &doc.Open, tab_flags);

                // Cancel attempt to close when unsaved add to save queue so we can display a popup.
                if (!doc.Open && doc.Dirty)
                {
                    doc.Open = true;
                    app.CloseQueue.push_back(&doc);
                }

                app.DisplayDocContextMenu(&doc);
                if (visible)
                {
                    app.DisplayDocContents(&doc);
                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
    }
    else if (opt_target == Target_DockSpaceAndWindow)
    {
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            app.NotifyOfDocumentsClosedElsewhere();

            // Create a DockSpace node where any window can be docked
            ImGuiID dockspace_id = ImGui::GetID(u8"我的空间");
            ImGui::DockSpace(dockspace_id);

            // Create Windows
            for (int doc_n = 0; doc_n < app.Documents.Size; doc_n++)
            {
                MyDocument* doc = &app.Documents[doc_n];
                if (!doc->Open)
                    continue;

                ImGui::SetNextWindowDockID(dockspace_id, redock_all ? ImGuiCond_Always : ImGuiCond_FirstUseEver);
                ImGuiWindowFlags window_flags = (doc->Dirty ? ImGuiWindowFlags_UnsavedDocument : 0);
                bool visible = ImGui::Begin(doc->Name, &doc->Open, window_flags);

                // Cancel attempt to close when unsaved add to save queue so we can display a popup.
                if (!doc->Open && doc->Dirty)
                {
                    doc->Open = true;
                    app.CloseQueue.push_back(doc);
                }

                app.DisplayDocContextMenu(doc);
                if (visible)
                    app.DisplayDocContents(doc);

                ImGui::End();
            }
        }
        else
        {
            ShowDockingDisabledMessage();
        }
    }

    // Early out other contents
    if (!window_contents_visible)
    {
        ImGui::End();
        return;
    }

    // Display renaming UI
    if (app.RenamingDoc != NULL)
    {
        if (app.RenamingStarted)
            ImGui::OpenPopup(u8"重命名");
        if (ImGui::BeginPopup(u8"重命名"))
        {
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 30);
            if (ImGui::InputText(u8"###名字", app.RenamingDoc->Name, IM_ARRAYSIZE(app.RenamingDoc->Name), ImGuiInputTextFlags_EnterReturnsTrue))
            {
                ImGui::CloseCurrentPopup();
                app.RenamingDoc = NULL;
            }
            if (app.RenamingStarted)
                ImGui::SetKeyboardFocusHere(-1);
            ImGui::EndPopup();
        }
        else
        {
            app.RenamingDoc = NULL;
        }
        app.RenamingStarted = false;
    }

    // Display closing confirmation UI
    if (!app.CloseQueue.empty())
    {
        int close_queue_unsaved_documents = 0;
        for (int n = 0; n < app.CloseQueue.Size; n++)
            if (app.CloseQueue[n]->Dirty)
                close_queue_unsaved_documents++;

        if (close_queue_unsaved_documents == 0)
        {
            // Close documents when all are unsaved
            for (int n = 0; n < app.CloseQueue.Size; n++)
                app.CloseQueue[n]->DoForceClose();
            app.CloseQueue.clear();
        }
        else
        {
            if (!ImGui::IsPopupOpen(u8"保存确认"))
                ImGui::OpenPopup(u8"保存确认");
            if (ImGui::BeginPopupModal(u8"保存确认", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text(u8"是否保存对以下项目的更改?");
                float item_height = ImGui::GetTextLineHeightWithSpacing();
                if (ImGui::BeginChild(ImGui::GetID("frame"), ImVec2(-FLT_MIN, 6.25f * item_height), ImGuiChildFlags_FrameStyle))
                    for (MyDocument* doc : app.CloseQueue)
                        if (doc->Dirty)
                            ImGui::Text("%s", doc->Name);
                ImGui::EndChild();

                ImVec2 button_size(ImGui::GetFontSize() * 7.0f, 0.0f);
                if (ImGui::Button(u8"是", button_size))
                {
                    for (MyDocument* doc : app.CloseQueue)
                    {
                        if (doc->Dirty)
                            doc->DoSave();
                        doc->DoForceClose();
                    }
                    app.CloseQueue.clear();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button(u8"否", button_size))
                {
                    for (MyDocument* doc : app.CloseQueue)
                        doc->DoForceClose();
                    app.CloseQueue.clear();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button(u8"取消", button_size))
                {
                    app.CloseQueue.clear();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
    }

    ImGui::End();
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Assets Browser / ShowExampleAppAssetsBrowser()
//-----------------------------------------------------------------------------

//#include "imgui_internal.h" // NavMoveRequestTryWrapping()

struct ExampleAsset
{
    ImGuiID ID;
    int     Type;

    ExampleAsset(ImGuiID id, int type) { ID = id; Type = type; }

    static const ImGuiTableSortSpecs* s_current_sort_specs;

    static void SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, ExampleAsset* items, int items_count)
    {
        s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
        if (items_count > 1)
            qsort(items, (size_t)items_count, sizeof(items[0]), ExampleAsset::CompareWithSortSpecs);
        s_current_sort_specs = NULL;
    }

    // Compare function to be used by qsort()
    static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs)
    {
        const ExampleAsset* a = (const ExampleAsset*)lhs;
        const ExampleAsset* b = (const ExampleAsset*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
        {
            const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            if (sort_spec->ColumnIndex == 0)
                delta = ((int)a->ID - (int)b->ID);
            else if (sort_spec->ColumnIndex == 1)
                delta = (a->Type - b->Type);
            if (delta > 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
            if (delta < 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
        }
        return ((int)a->ID - (int)b->ID);
    }
};
const ImGuiTableSortSpecs* ExampleAsset::s_current_sort_specs = NULL;

struct ExampleAssetsBrowser
{
    // Options
    bool            ShowTypeOverlay = true;
    bool            AllowSorting = true;
    bool            AllowDragUnselected = false;
    bool            AllowBoxSelect = true;
    float           IconSize = 32.0f;
    int             IconSpacing = 10;
    int             IconHitSpacing = 4;         // Increase hit-spacing if you want to make it possible to clear or box-select from gaps. Some spacing is required to able to amend with Shift+box-select. Value is small in Explorer.
    bool            StretchSpacing = true;

    // State
    ImVector<ExampleAsset> Items;               // Our items
    ExampleSelectionWithDeletion Selection;     // Our selection (ImGuiSelectionBasicStorage + helper funcs to handle deletion)
    ImGuiID         NextItemId = 0;             // Unique identifier when creating new items
    bool            RequestDelete = false;      // Deferred deletion request
    bool            RequestSort = false;        // Deferred sort request
    float           ZoomWheelAccum = 0.0f;      // Mouse wheel accumulator to handle smooth wheels better

    // Calculated sizes for layout, output of UpdateLayoutSizes(). Could be locals but our code is simpler this way.
    ImVec2          LayoutItemSize;
    ImVec2          LayoutItemStep;             // == LayoutItemSize + LayoutItemSpacing
    float           LayoutItemSpacing = 0.0f;
    float           LayoutSelectableSpacing = 0.0f;
    float           LayoutOuterPadding = 0.0f;
    int             LayoutColumnCount = 0;
    int             LayoutLineCount = 0;

    // Functions
    ExampleAssetsBrowser()
    {
        AddItems(10000);
    }
    void AddItems(int count)
    {
        if (Items.Size == 0)
            NextItemId = 0;
        Items.reserve(Items.Size + count);
        for (int n = 0; n < count; n++, NextItemId++)
            Items.push_back(ExampleAsset(NextItemId, (NextItemId % 20) < 15 ? 0 : (NextItemId % 20) < 18 ? 1 : 2));
        RequestSort = true;
    }
    void ClearItems()
    {
        Items.clear();
        Selection.Clear();
    }

    // Logic would be written in the main code BeginChild() and outputting to local variables.
    // We extracted it into a function so we can call it easily from multiple places.
    void UpdateLayoutSizes(float avail_width)
    {
        // Layout: when not stretching: allow extending into right-most spacing.
        LayoutItemSpacing = (float)IconSpacing;
        if (StretchSpacing == false)
            avail_width += floorf(LayoutItemSpacing * 0.5f);

        // Layout: calculate number of icon per line and number of lines
        LayoutItemSize = ImVec2(floorf(IconSize), floorf(IconSize));
        LayoutColumnCount = IM_MAX((int)(avail_width / (LayoutItemSize.x + LayoutItemSpacing)), 1);
        LayoutLineCount = (Items.Size + LayoutColumnCount - 1) / LayoutColumnCount;

        // Layout: when stretching: allocate remaining space to more spacing. Round before division, so item_spacing may be non-integer.
        if (StretchSpacing && LayoutColumnCount > 1)
            LayoutItemSpacing = floorf(avail_width - LayoutItemSize.x * LayoutColumnCount) / LayoutColumnCount;

        LayoutItemStep = ImVec2(LayoutItemSize.x + LayoutItemSpacing, LayoutItemSize.y + LayoutItemSpacing);
        LayoutSelectableSpacing = IM_MAX(floorf(LayoutItemSpacing) - IconHitSpacing, 0.0f);
        LayoutOuterPadding = floorf(LayoutItemSpacing * 0.5f);
    }

    void Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(IconSize * 25, IconSize * 15), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open, ImGuiWindowFlags_MenuBar))
        {
            ImGui::End();
            return;
        }

        // Menu bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu(u8"文件"))
            {
                if (ImGui::MenuItem(u8"添加10000个项目"))
                    AddItems(10000);
                if (ImGui::MenuItem(u8"清空项目"))
                    ClearItems();
                ImGui::Separator();
                if (ImGui::MenuItem(u8"关闭", NULL, false, p_open != NULL))
                    *p_open = false;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(u8"编辑"))
            {
                if (ImGui::MenuItem(u8"删除", u8"Del", false, Selection.Size > 0))
                    RequestDelete = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(u8"选项"))
            {
                ImGui::PushItemWidth(ImGui::GetFontSize() * 10);

                ImGui::SeparatorText(u8"内容");
                ImGui::Checkbox(u8"显示类型叠加层", &ShowTypeOverlay);
                ImGui::Checkbox(u8"允许排序", &AllowSorting);

                ImGui::SeparatorText(u8"选择行为");
                ImGui::Checkbox(u8"允许拖动未选中的项目", &AllowDragUnselected);
                ImGui::Checkbox(u8"允许框选", &AllowBoxSelect);

                ImGui::SeparatorText(u8"布局");
                ImGui::SliderFloat(u8"图标大小", &IconSize, 16.0f, 128.0f, "%.0f");
                ImGui::SameLine(); HelpMarker(u8"使用 CTRL+滚轮 进行缩放");
                ImGui::SliderInt(u8"图标间距", &IconSpacing, 0, 32);
                ImGui::SliderInt(u8"图标点击间距", &IconHitSpacing, 0, 32);
                ImGui::Checkbox(u8"拉伸间距", &StretchSpacing);
                ImGui::PopItemWidth();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Show a table with ONLY one header row to showcase the idea/possibility of using this to provide a sorting UI
        if (AllowSorting)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            ImGuiTableFlags table_flags_for_sort_specs = ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders;
            if (ImGui::BeginTable(u8"仅用于排序规范", 2, table_flags_for_sort_specs, ImVec2(0.0f, ImGui::GetFrameHeight())))
            {
                ImGui::TableSetupColumn(u8"索引");
                ImGui::TableSetupColumn(u8"类型");
                ImGui::TableHeadersRow();
                if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs())
                    if (sort_specs->SpecsDirty || RequestSort)
                    {
                        ExampleAsset::SortWithSortSpecs(sort_specs, Items.Data, Items.Size);
                        sort_specs->SpecsDirty = RequestSort = false;
                    }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
        }

        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowContentSize(ImVec2(0.0f, LayoutOuterPadding + LayoutLineCount * (LayoutItemSize.y + LayoutItemSpacing)));
        if (ImGui::BeginChild(u8"资产", ImVec2(0.0f, -ImGui::GetTextLineHeightWithSpacing()), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoMove))
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            const float avail_width = ImGui::GetContentRegionAvail().x;
            UpdateLayoutSizes(avail_width);

            // Calculate and store start position.
            ImVec2 start_pos = ImGui::GetCursorScreenPos();
            start_pos = ImVec2(start_pos.x + LayoutOuterPadding, start_pos.y + LayoutOuterPadding);
            ImGui::SetCursorScreenPos(start_pos);

            // Multi-select
            ImGuiMultiSelectFlags ms_flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_ClearOnClickVoid;

            // - Enable box-select (in 2D mode, so that changing box-select rectangle X1/X2 boundaries will affect clipped items)
            if (AllowBoxSelect)
                ms_flags |= ImGuiMultiSelectFlags_BoxSelect2d;

            // - This feature allows dragging an unselected item without selecting it (rarely used)
            if (AllowDragUnselected)
                ms_flags |= ImGuiMultiSelectFlags_SelectOnClickRelease;

            // - Enable keyboard wrapping on X axis
            // (FIXME-MULTISELECT: We haven't designed/exposed a general nav wrapping api yet, so this flag is provided as a courtesy to avoid doing:
            //    ImGui::NavMoveRequestTryWrapping(ImGui::GetCurrentWindow(), ImGuiNavMoveFlags_WrapX);
            // When we finish implementing a more general API for this, we will obsolete this flag in favor of the new system)
            ms_flags |= ImGuiMultiSelectFlags_NavWrapX;

            ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(ms_flags, Selection.Size, Items.Size);

            // Use custom selection adapter: store ID in selection (recommended)
            Selection.UserData = this;
            Selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self_, int idx) { ExampleAssetsBrowser* self = (ExampleAssetsBrowser*)self_->UserData; return self->Items[idx].ID; };
            Selection.ApplyRequests(ms_io);

            const bool want_delete = (ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (Selection.Size > 0)) || RequestDelete;
            const int item_curr_idx_to_focus = want_delete ? Selection.ApplyDeletionPreLoop(ms_io, Items.Size) : -1;
            RequestDelete = false;

            // Push LayoutSelectableSpacing (which is LayoutItemSpacing minus hit-spacing, if we decide to have hit gaps between items)
            // Altering style ItemSpacing may seem unnecessary as we position every items using SetCursorScreenPos()...
            // But it is necessary for two reasons:
            // - Selectables uses it by default to visually fill the space between two items.
            // - The vertical spacing would be measured by Clipper to calculate line height if we didn't provide it explicitly (here we do).
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(LayoutSelectableSpacing, LayoutSelectableSpacing));

            // Rendering parameters
            const ImU32 icon_type_overlay_colors[3] = { 0, IM_COL32(200, 70, 70, 255), IM_COL32(70, 170, 70, 255) };
            const ImU32 icon_bg_color = ImGui::GetColorU32(IM_COL32(35, 35, 35, 220));
            const ImVec2 icon_type_overlay_size = ImVec2(4.0f, 4.0f);
            const bool display_label = (LayoutItemSize.x >= ImGui::CalcTextSize("999").x);

            const int column_count = LayoutColumnCount;
            ImGuiListClipper clipper;
            clipper.Begin(LayoutLineCount, LayoutItemStep.y);
            if (item_curr_idx_to_focus != -1)
                clipper.IncludeItemByIndex(item_curr_idx_to_focus / column_count); // Ensure focused item line is not clipped.
            if (ms_io->RangeSrcItem != -1)
                clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem / column_count); // Ensure RangeSrc item line is not clipped.
            while (clipper.Step())
            {
                for (int line_idx = clipper.DisplayStart; line_idx < clipper.DisplayEnd; line_idx++)
                {
                    const int item_min_idx_for_current_line = line_idx * column_count;
                    const int item_max_idx_for_current_line = IM_MIN((line_idx + 1) * column_count, Items.Size);
                    for (int item_idx = item_min_idx_for_current_line; item_idx < item_max_idx_for_current_line; ++item_idx)
                    {
                        ExampleAsset* item_data = &Items[item_idx];
                        ImGui::PushID((int)item_data->ID);

                        // Position item
                        ImVec2 pos = ImVec2(start_pos.x + (item_idx % column_count) * LayoutItemStep.x, start_pos.y + line_idx * LayoutItemStep.y);
                        ImGui::SetCursorScreenPos(pos);

                        ImGui::SetNextItemSelectionUserData(item_idx);
                        bool item_is_selected = Selection.Contains((ImGuiID)item_data->ID);
                        bool item_is_visible = ImGui::IsRectVisible(LayoutItemSize);
                        ImGui::Selectable("", item_is_selected, ImGuiSelectableFlags_None, LayoutItemSize);

                        // Update our selection state immediately (without waiting for EndMultiSelect() requests)
                        // because we use this to alter the color of our text/icon.
                        if (ImGui::IsItemToggledSelection())
                            item_is_selected = !item_is_selected;

                        // Focus (for after deletion)
                        if (item_curr_idx_to_focus == item_idx)
                            ImGui::SetKeyboardFocusHere(-1);

                        // Drag and drop
                        if (ImGui::BeginDragDropSource())
                        {
                            // Create payload with full selection OR single unselected item.
                            // (the later is only possible when using ImGuiMultiSelectFlags_SelectOnClickRelease)
                            if (ImGui::GetDragDropPayload() == NULL)
                            {
                                ImVector<ImGuiID> payload_items;
                                void* it = NULL;
                                ImGuiID id = 0;
                                if (!item_is_selected)
                                    payload_items.push_back(item_data->ID);
                                else
                                    while (Selection.GetNextSelectedItem(&it, &id))
                                        payload_items.push_back(id);
                                ImGui::SetDragDropPayload("ASSETS_BROWSER_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
                            }

                            // Display payload content in tooltip, by extracting it from the payload data
                            // (we could read from selection, but it is more correct and reusable to read from payload)
                            const ImGuiPayload* payload = ImGui::GetDragDropPayload();
                            const int payload_count = (int)payload->DataSize / (int)sizeof(ImGuiID);
                            ImGui::Text(u8"%d 资产", payload_count);

                            ImGui::EndDragDropSource();
                        }

                        // Render icon (a real app would likely display an image/thumbnail here)
                        // Because we use ImGuiMultiSelectFlags_BoxSelect2d, clipping vertical may occasionally be larger, so we coarse-clip our rendering as well.
                        if (item_is_visible)
                        {
                            ImVec2 box_min(pos.x - 1, pos.y - 1);
                            ImVec2 box_max(box_min.x + LayoutItemSize.x + 2, box_min.y + LayoutItemSize.y + 2); // Dubious
                            draw_list->AddRectFilled(box_min, box_max, icon_bg_color); // Background color
                            if (ShowTypeOverlay && item_data->Type != 0)
                            {
                                ImU32 type_col = icon_type_overlay_colors[item_data->Type % IM_ARRAYSIZE(icon_type_overlay_colors)];
                                draw_list->AddRectFilled(ImVec2(box_max.x - 2 - icon_type_overlay_size.x, box_min.y + 2), ImVec2(box_max.x - 2, box_min.y + 2 + icon_type_overlay_size.y), type_col);
                            }
                            if (display_label)
                            {
                                ImU32 label_col = ImGui::GetColorU32(item_is_selected ? ImGuiCol_Text : ImGuiCol_TextDisabled);
                                char label[32];
                                sprintf(label, "%d", item_data->ID);
                                draw_list->AddText(ImVec2(box_min.x, box_max.y - ImGui::GetFontSize()), label_col, label);
                            }
                        }

                        ImGui::PopID();
                    }
                }
            }
            clipper.End();
            ImGui::PopStyleVar(); // ImGuiStyleVar_ItemSpacing

            // Context menu
            if (ImGui::BeginPopupContextWindow())
            {
                ImGui::Text(u8"选择:%d项", Selection.Size);
                ImGui::Separator();
                if (ImGui::MenuItem(u8"删除", "Del", false, Selection.Size > 0))
                    RequestDelete = true;
                ImGui::EndPopup();
            }

            ms_io = ImGui::EndMultiSelect();
            Selection.ApplyRequests(ms_io);
            if (want_delete)
                Selection.ApplyDeletionPostLoop(ms_io, Items, item_curr_idx_to_focus);

            // Zooming with CTRL+Wheel
            if (ImGui::IsWindowAppearing())
                ZoomWheelAccum = 0.0f;
            if (ImGui::IsWindowHovered() && io.MouseWheel != 0.0f && ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsAnyItemActive() == false)
            {
                ZoomWheelAccum += io.MouseWheel;
                if (fabsf(ZoomWheelAccum) >= 1.0f)
                {
                    // Calculate hovered item index from mouse location
                    // FIXME: Locking aiming on 'hovered_item_idx' (with a cool-down timer) would ensure zoom keeps on it.
                    const float hovered_item_nx = (io.MousePos.x - start_pos.x + LayoutItemSpacing * 0.5f) / LayoutItemStep.x;
                    const float hovered_item_ny = (io.MousePos.y - start_pos.y + LayoutItemSpacing * 0.5f) / LayoutItemStep.y;
                    const int hovered_item_idx = ((int)hovered_item_ny * LayoutColumnCount) + (int)hovered_item_nx;
                    //ImGui::SetTooltip("%f,%f -> item %d", hovered_item_nx, hovered_item_ny, hovered_item_idx); // Move those 4 lines in block above for easy debugging

                    // Zoom
                    IconSize *= powf(1.1f, (float)(int)ZoomWheelAccum);
                    IconSize = IM_CLAMP(IconSize, 16.0f, 128.0f);
                    ZoomWheelAccum -= (int)ZoomWheelAccum;
                    UpdateLayoutSizes(avail_width);

                    // Manipulate scroll to that we will land at the same Y location of currently hovered item.
                    // - Calculate next frame position of item under mouse
                    // - Set new scroll position to be used in next ImGui::BeginChild() call.
                    float hovered_item_rel_pos_y = ((float)(hovered_item_idx / LayoutColumnCount) + fmodf(hovered_item_ny, 1.0f)) * LayoutItemStep.y;
                    hovered_item_rel_pos_y += ImGui::GetStyle().WindowPadding.y;
                    float mouse_local_y = io.MousePos.y - ImGui::GetWindowPos().y;
                    ImGui::SetScrollY(hovered_item_rel_pos_y - mouse_local_y);
                }
            }
        }
        ImGui::EndChild();

        ImGui::Text(u8"已选择:%d/%d项", Selection.Size, Items.Size);
        ImGui::End();
    }
};

void ShowExampleAppAssetsBrowser(bool* p_open)
{
    IMGUI_DEMO_MARKER(u8"示例/资产浏览器");
    static ExampleAssetsBrowser assets_browser;
    assets_browser.Draw(u8"示例：资产浏览器", p_open);
}

// End of Demo code
#else

void ImGui::ShowAboutWindow(bool*) {}
void ImGui::ShowDemoWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}
bool ImGui::ShowStyleSelector(const char*) { return false; }

#endif // #ifndef IMGUI_DISABLE_DEMO_WINDOWS

#endif // #ifndef IMGUI_DISABLE
