// ThemeManager.cpp
#include "ThemeManager.h"
#include "imgui.h"
#include <fstream>
#include <filesystem> // 需要 C++17
#include <sstream>
#include <iomanip>

// 辅助函数：去除字符串两端的空格
static void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}


void ThemeManager::SaveTheme(const std::string& filename) {
    // 确保 "themes" 文件夹存在
    if (!std::filesystem::exists("themes")) {
        std::filesystem::create_directory("themes");
    }

    std::ofstream file("themes/" + filename);
    if (!file.is_open()) return;

    ImGuiStyle& style = ImGui::GetStyle();

    file << std::fixed << std::setprecision(3); // 设置浮点数精度

    // 保存颜色
    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        const ImVec4& col = style.Colors[i];
        file << ImGui::GetStyleColorName(i) << " = " << col.x << "," << col.y << "," << col.z << "," << col.w << std::endl;
    }

    // 保存其他样式变量
    file << "WindowRounding = " << style.WindowRounding << std::endl;
    file << "FrameRounding = " << style.FrameRounding << std::endl;
    file << "ChildRounding = " << style.ChildRounding << std::endl;
    file << "PopupRounding = " << style.PopupRounding << std::endl;
    file << "ScrollbarRounding = " << style.ScrollbarRounding << std::endl;
    file << "GrabRounding = " << style.GrabRounding << std::endl;
    file << "TabRounding = " << style.TabRounding << std::endl;
    file << "WindowBorderSize = " << style.WindowBorderSize << std::endl;
    file << "FrameBorderSize = " << style.FrameBorderSize << std::endl;
    // ... 你可以添加更多需要保存的样式变量 ...
}

bool ThemeManager::LoadTheme(const std::string& filename) {
    std::ifstream file("themes/" + filename);
    if (!file.is_open()) return false;

    ImGuiStyle& style = ImGui::GetStyle();
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key, equals;
        ss >> key;
        trim(key);
        ss >> equals; // 读取 '='

        // 解析颜色
        bool found_color = false;
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            if (key == ImGui::GetStyleColorName(i)) {
                float r, g, b, a;
                char comma;
                ss >> r >> comma >> g >> comma >> b >> comma >> a;
                style.Colors[i] = ImVec4(r, g, b, a);
                found_color = true;
                break;
            }
        }
        if (found_color) continue;

        // 解析其他样式变量
        float value;
        ss >> value;
        if (key == "WindowRounding") style.WindowRounding = value;
        else if (key == "FrameRounding") style.FrameRounding = value;
        else if (key == "ChildRounding") style.ChildRounding = value;
        else if (key == "PopupRounding") style.PopupRounding = value;
        else if (key == "ScrollbarRounding") style.ScrollbarRounding = value;
        else if (key == "GrabRounding") style.GrabRounding = value;
        else if (key == "TabRounding") style.TabRounding = value;
        else if (key == "WindowBorderSize") style.WindowBorderSize = value;
        else if (key == "FrameBorderSize") style.FrameBorderSize = value;
        // ... 添加更多需要加载的样式变量 ...
    }
    return true;
}

std::vector<std::string> ThemeManager::GetAvailableThemes() {
    std::vector<std::string> themes;
    std::string path = "themes";
    if (!std::filesystem::exists(path)) return themes;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".ini") {
            themes.push_back(entry.path().filename().string());
        }
    }
    return themes;
}