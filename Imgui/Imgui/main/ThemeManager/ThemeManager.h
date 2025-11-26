// ThemeManager.h
#pragma once
#include <string>
#include <vector>

namespace ThemeManager {
    // 将当前 ImGui 样式保存到文件
    void SaveTheme(const std::string& filename);

    // 从文件加载样式
    // 返回 true 表示成功, false 表示失败 (如文件不存在)
    bool LoadTheme(const std::string& filename);

    // 获取 "themes" 文件夹下所有主题文件的列表
    std::vector<std::string> GetAvailableThemes();
}