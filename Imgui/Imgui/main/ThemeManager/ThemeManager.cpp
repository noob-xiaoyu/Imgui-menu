// ThemeManager.cpp
#include "ThemeManager.h"
#include "imgui.h"
#include <fstream>
#include <filesystem> // 需要 C++17
#include <sstream>
#include <iomanip>
#include <Shlobj.h>
#include <string>
#include <vector>
// 辅助函数：去除字符串两端的空格
static void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

std::string GetThemeDirectory() {
    TCHAR szPath[MAX_PATH];

    // SHGetFolderPath 获取 AppData/Roaming 目录的路径
    // CSIDL_APPDATA 是一个常量，代表 Roaming AppData 文件夹
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath))) {
        // 使用 C++17 的 filesystem 来处理路径，更安全、更方便
        std::filesystem::path themeDir = szPath;
        themeDir /= "Imgui-theme"; // 相当于 Path.Combine

        try {
            // 如果目录不存在，则创建它
            if (!std::filesystem::exists(themeDir)) {
                std::filesystem::create_directories(themeDir);
            }
            return themeDir.string(); // 将路径对象转换为字符串并返回
        }
        catch (const std::filesystem::filesystem_error& e) {
            // 处理创建目录时可能发生的错误
            // 在这里可以添加日志记录等
            return "";
        }
    }
    return ""; // 获取 AppData 路径失败
}

void ThemeManager::SaveTheme(const std::string& filename) {
    std::string theme_dir = GetThemeDirectory();
    if (theme_dir.empty()) {
        // 你可以在这里添加错误日志，例如:
        // printf("Error: Could not get or create theme directory.\n");
        return;
    }
    std::filesystem::path full_path = theme_dir;
    full_path /= filename;
    std::ofstream file(full_path);
    if (!file.is_open()) {
        // printf("Error: Could not open file for writing: %s\n", full_path.string().c_str());
        return;
    }
    ImGuiStyle& style = ImGui::GetStyle();
    file << std::fixed << std::setprecision(3); // 设置浮点数精度

    // 保存颜色
    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        const ImVec4& col = style.Colors[i];
        file << ImGui::GetStyleColorName(i) << " = " << col.x << "," << col.y << "," << col.z << "," << col.w << std::endl;
    }

    // 保存其他样式变量
    file << "WindowPadding = " << style.WindowPadding.x << "," << style.WindowPadding.y << std::endl;
    file << "FramePadding = " << style.FramePadding.x << "," << style.FramePadding.y << std::endl;
    file << "ItemSpacing = " << style.ItemSpacing.x << "," << style.ItemSpacing.y << std::endl;
    file << "ItemInnerSpacing = " << style.ItemInnerSpacing.x << "," << style.ItemInnerSpacing.y << std::endl;
    file << "TouchExtraPadding = " << style.TouchExtraPadding.x << "," << style.TouchExtraPadding.y << std::endl;
    file << "IndentSpacing = " << style.IndentSpacing << std::endl;
    file << "GrabMinSize = " << style.GrabMinSize << std::endl;

    // 边框
    file << "WindowBorderSize = " << style.WindowBorderSize << std::endl;
    file << "ChildBorderSize = " << style.ChildBorderSize << std::endl;
    file << "PopupBorderSize = " << style.PopupBorderSize << std::endl;
    file << "FrameBorderSize = " << style.FrameBorderSize << std::endl;

    // 圆角
    file << "WindowRounding = " << style.WindowRounding << std::endl;
    file << "ChildRounding = " << style.ChildRounding << std::endl;
    file << "FrameRounding = " << style.FrameRounding << std::endl;
    file << "PopupRounding = " << style.PopupRounding << std::endl;
    file << "GrabRounding = " << style.GrabRounding << std::endl;

    // 滚动条
    file << "ScrollbarSize = " << style.ScrollbarSize << std::endl;
    file << "ScrollbarRounding = " << style.ScrollbarRounding << std::endl;
    // ScrollbarPadding is obsolete and was removed in ImGui 1.82. You can remove this line if using a newer version.
    // file << "ScrollbarPadding = " << style.ScrollbarPadding.x << "," << style.ScrollbarPadding.y << std::endl;

    // 标签
    file << "TabBorderSize = " << style.TabBorderSize << std::endl;
    // TabBarBorderSize is obsolete, renamed to TabBorderSize in ImGui 1.90. Keeping both for compatibility is an option.
    // file << "TabBarBorderSize = " << style.TabBarBorderSize << std::endl;
    // TabBarOverlineSize is obsolete.
    // TabMinWidthBase and TabMinWidthShrink are obsolete.
    // TabCloseButtonMinWidthSelected and TabCloseButtonMinWidthUnselected are obsolete.
    file << "TabRounding = " << style.TabRounding << std::endl;

    // 表格
    file << "CellPadding = " << style.CellPadding.x << "," << style.CellPadding.y << std::endl;
    file << "TableAngledHeadersAngle = " << style.TableAngledHeadersAngle << std::endl;
    file << "TableAngledHeadersTextAlign = " << style.TableAngledHeadersTextAlign.x << "," << style.TableAngledHeadersTextAlign.y << std::endl;

    // 树形 (TreeLines* properties are obsolete since ImGui 1.89, merged into TreeLinesFlags)
    file << "TreeLinesFlags = " << style.TreeLinesFlags << std::endl;
    // file << "TreeLinesSize = " << style.TreeLinesSize << std::endl; // Obsolete
    // file << "TreeLinesRounding = " << style.TreeLinesRounding << std::endl; // Obsolete

    // 窗口
    file << "WindowTitleAlign = " << style.WindowTitleAlign.x << "," << style.WindowTitleAlign.y << std::endl;
    // WindowBorderHoverPadding is obsolete.
    file << "WindowMenuButtonPosition = " << style.WindowMenuButtonPosition << std::endl;

    // 小部件
    file << "ColorButtonPosition = " << style.ColorButtonPosition << std::endl;
    file << "ButtonTextAlign = " << style.ButtonTextAlign.x << "," << style.ButtonTextAlign.y << std::endl;
    file << "SelectableTextAlign = " << style.SelectableTextAlign.x << "," << style.SelectableTextAlign.y << std::endl;
    file << "SeparatorTextBorderSize = " << style.SeparatorTextBorderSize << std::endl;
    file << "SeparatorTextAlign = " << style.SeparatorTextAlign.x << "," << style.SeparatorTextAlign.y << std::endl;
    file << "SeparatorTextPadding = " << style.SeparatorTextPadding.x << "," << style.SeparatorTextPadding.y << std::endl;
    file << "LogSliderDeadzone = " << style.LogSliderDeadzone << std::endl;
    file << "ImageBorderSize = " << style.ImageBorderSize << std::endl;

    // 停靠
    file << "DockingSeparatorSize = " << style.DockingSeparatorSize << std::endl;

    // 工具提示
    file << "HoverFlagsForTooltipMouse = " << style.HoverFlagsForTooltipMouse << std::endl;
    file << "HoverFlagsForTooltipNav = " << style.HoverFlagsForTooltipNav << std::endl;

    // 杂项
    file << "DisplayWindowPadding = " << style.DisplayWindowPadding.x << "," << style.DisplayWindowPadding.y << std::endl;
    file << "DisplaySafeAreaPadding = " << style.DisplaySafeAreaPadding.x << "," << style.DisplaySafeAreaPadding.y << std::endl;
}

bool ThemeManager::LoadTheme(const std::string& filename) {
    std::string theme_dir = GetThemeDirectory();
    if (theme_dir.empty()) {
        // 失败点 1: 无法获取目录
        return false;
    }

    std::filesystem::path full_path = theme_dir;
    full_path /= filename;

    std::ifstream file(full_path);
    if (!file.is_open()) {
        // 失败点 2: 文件无法打开
        return false;
    }

    ImGuiStyle& style = ImGui::GetStyle();
    std::string line;
    while (std::getline(file, line)) {
        // 简单的键值对解析
        std::string key, value;
        size_t separator_pos = line.find(" = ");
        if (separator_pos != std::string::npos) {
            key = line.substr(0, separator_pos);
            value = line.substr(separator_pos + 3);
        }
        else {
            continue; // 跳过非键值对行，如 [Colors], [Style]
        }

        // --- 解析颜色 ---
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            if (key == ImGui::GetStyleColorName(i)) {
                float r, g, b, a;
                if (sscanf_s(value.c_str(), "%f,%f,%f,%f", &r, &g, &b, &a) == 4) {
                    style.Colors[i] = ImVec4(r, g, b, a);
                }
                break; // 找到匹配项后跳出颜色循环
            }
        }

        // --- 解析样式变量 ---
        // 使用宏来减少重复代码
#define PARSE_FLOAT(name) if (key == #name) { style.name = std::stof(value); }
#define PARSE_VEC2(name) if (key == #name) { sscanf_s(value.c_str(), "%f,%f", &style.name.x, &style.name.y); }
#define PARSE_INT(name) if (key == #name) { style.name = std::stoi(value); }

// 主要
        PARSE_VEC2(WindowPadding)
            PARSE_VEC2(FramePadding)
            PARSE_VEC2(ItemSpacing)
            PARSE_VEC2(ItemInnerSpacing)
            PARSE_VEC2(TouchExtraPadding)
            PARSE_FLOAT(IndentSpacing)
            PARSE_FLOAT(GrabMinSize)

            // 边框
            PARSE_FLOAT(WindowBorderSize)
            PARSE_FLOAT(ChildBorderSize)
            PARSE_FLOAT(PopupBorderSize)
            PARSE_FLOAT(FrameBorderSize)

            // 圆角
            PARSE_FLOAT(WindowRounding)
            PARSE_FLOAT(ChildRounding)
            PARSE_FLOAT(FrameRounding)
            PARSE_FLOAT(PopupRounding)
            PARSE_FLOAT(GrabRounding)

            // 滚动条
            PARSE_FLOAT(ScrollbarSize)
            PARSE_FLOAT(ScrollbarRounding)
            // PARSE_VEC2(ScrollbarPadding) // Obsolete

            // 标签
            PARSE_FLOAT(TabBorderSize)
            // PARSE_FLOAT(TabBarBorderSize) // Obsolete
            PARSE_FLOAT(TabRounding)

            // 表格
            PARSE_VEC2(CellPadding)
            PARSE_FLOAT(TableAngledHeadersAngle)
            PARSE_VEC2(TableAngledHeadersTextAlign)

            // 树形
            PARSE_INT(TreeLinesFlags)

            // 窗口
            PARSE_VEC2(WindowTitleAlign)
            //PARSE_INT(WindowMenuButtonPosition)

            // 小部件
            //PARSE_INT(ColorButtonPosition)
            PARSE_VEC2(ButtonTextAlign)
            PARSE_VEC2(SelectableTextAlign)
            PARSE_FLOAT(SeparatorTextBorderSize)
            PARSE_VEC2(SeparatorTextAlign)
            PARSE_VEC2(SeparatorTextPadding)
            PARSE_FLOAT(LogSliderDeadzone)
            PARSE_FLOAT(ImageBorderSize)

            // 停靠
            PARSE_FLOAT(DockingSeparatorSize)

            // 工具提示
            PARSE_INT(HoverFlagsForTooltipMouse)
            PARSE_INT(HoverFlagsForTooltipNav)

            // 杂项
            PARSE_VEC2(DisplayWindowPadding)
            PARSE_VEC2(DisplaySafeAreaPadding)

            // 宏用完后最好 undef
#undef PARSE_FLOAT
#undef PARSE_VEC2
#undef PARSE_INT
    }
    file.close();
    return true;
}

std::vector<std::string> ThemeManager::GetAvailableThemes() {
    std::vector<std::string> themes;
    std::string theme_dir = GetThemeDirectory();
    if (theme_dir.empty()) return themes; // 如果目录获取失败，返回空列表

    for (const auto& entry : std::filesystem::directory_iterator(theme_dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".ini") {
            themes.push_back(entry.path().filename().string());
        }
    }
    return themes;
}