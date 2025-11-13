// CustomWidgets.cpp
#include "imgui.h"
#include "imgui_internal.h"
#include "CustomWidgets.h"


#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}
static const char* GetTreeLinesFlagsName(ImGuiTreeNodeFlags flags)
{
    if (flags == ImGuiTreeNodeFlags_DrawLinesNone) return "DrawLinesNone";
    if (flags == ImGuiTreeNodeFlags_DrawLinesFull) return "DrawLinesFull";
    if (flags == ImGuiTreeNodeFlags_DrawLinesToNodes) return "DrawLinesToNodes";
    return "";
}
static int CalcFontGlyphSrcOverlapMask(ImFontAtlas* atlas, ImFont* font, unsigned int codepoint)
{
    int mask = 0, count = 0;
    for (int src_n = 0; src_n < font->Sources.Size; src_n++)
    {
        ImFontConfig* src = font->Sources[src_n];
        if (!(src->FontLoader ? src->FontLoader : atlas->FontLoader)->FontSrcContainsGlyph(atlas, src, (ImWchar)codepoint))
            continue;
        mask |= (1 << src_n);
        count++;
    }
    return count > 1 ? mask : 0;
}
void ImFontAtlasFontDestroyOutput(ImFontAtlas* atlas, ImFont* font)
{
    font->ClearOutputData();
    for (ImFontConfig* src : font->Sources)
    {
        const ImFontLoader* loader = src->FontLoader ? src->FontLoader : atlas->FontLoader;
        if (loader && loader->FontSrcDestroy != NULL)
            loader->FontSrcDestroy(atlas, src);
    }
}
bool ImFontAtlasFontInitOutput(ImFontAtlas* atlas, ImFont* font)
{
    bool ret = true;
    for (ImFontConfig* src : font->Sources)
        if (!ImFontAtlasFontSourceInit(atlas, src))
            ret = false;
    IM_ASSERT(ret); // Unclear how to react to this meaningfully. Assume that result will be same as initial AddFont() call.
    return ret;
}
void DebugNodeFont_cn(ImFont* font)
{
    ImGuiContext& g = *GImGui;
    ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;
    ImFontAtlas* atlas = font->ContainerAtlas;
    bool opened = ImGui::TreeNode(font, u8"字体: \"%s\": %d 来源(s)", font->GetDebugName(), font->Sources.Size);

    // Display preview text
    if (!opened)
        ImGui::Indent();
    ImGui::Indent();
    if (cfg->ShowFontPreview)
    {
        ImGui::PushFont(font, 0.0f);
        ImGui::Text("The quick brown fox jumps over the lazy dog");
        ImGui::Text(u8"敏捷的棕色狐狸跳过那只懒狗");

        ImGui::PopFont();
    }
    if (!opened)
    {
        ImGui::Unindent();
        ImGui::Unindent();
        return;
    }
    if (ImGui::SmallButton(u8"设为默认"))
        ImGui::GetIO().FontDefault = font;
    ImGui::SameLine();
    ImGui::BeginDisabled(atlas->Fonts.Size <= 1 || atlas->Locked);
    if (ImGui::SmallButton(u8"删除"))
        atlas->RemoveFont(font);
    ImGui::EndDisabled();
    ImGui::SameLine();
    if (ImGui::SmallButton(u8"清洁烘焙"))
        ImFontAtlasFontDiscardBakes(atlas, font, 0);
    ImGui::SameLine();
    if (ImGui::SmallButton(u8"清除未使用的"))
        ImFontAtlasFontDiscardBakes(atlas, font, 2);

    // Display details
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
    ImGui::DragFloat(u8"字体缩放", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");
    /*SameLine(); MetricsHelpMarker(
        "Note that the default embedded font is NOT meant to be scaled.\n\n"
        "Font are currently rendered into bitmaps at a given size at the time of building the atlas. "
        "You may oversample them to get some flexibility with scaling. "
        "You can also render at multiple sizes and select which one to use at runtime.\n\n"
        "(Glimmer of hope: the atlas system will be rewritten in the future to make scaling more flexible.)");*/
#endif

    char c_str[5];
    ImTextCharToUtf8(c_str, font->FallbackChar);
    ImGui::Text(u8"回退字符: '%s' (U+%04X)", c_str, font->FallbackChar);
    ImTextCharToUtf8(c_str, font->EllipsisChar);
    ImGui::Text(u8"省略号字符: '%s' (U+%04X)", c_str, font->EllipsisChar);

    for (int src_n = 0; src_n < font->Sources.Size; src_n++)
    {
        ImFontConfig* src = font->Sources[src_n];
        if (ImGui::TreeNode(src, u8"输入 %d: \'%s\' [%d], 过采样: %d,%d, 像素捕捉H: %d, 偏移: (%.1f,%.1f)",
            src_n, src->Name, src->FontNo, src->OversampleH, src->OversampleV, src->PixelSnapH, src->GlyphOffset.x, src->GlyphOffset.y))
        {
            const ImFontLoader* loader = src->FontLoader ? src->FontLoader : atlas->FontLoader;
            ImGui::Text(u8"装载机: '%s'", loader->Name ? loader->Name : "N/A");
#ifdef IMGUI_ENABLE_FREETYPE
            if (loader->Name != NULL && strcmp(loader->Name, "FreeType") == 0)
            {
                unsigned int loader_flags = src->FontLoaderFlags;
                ImGui::Text(u8"FreeType 加载器标志: 0x%08X", loader_flags);
                if (ImGuiFreeType::DebugEditFontLoaderFlags(&loader_flags))
                {
                    ImFontAtlasFontDestroyOutput(atlas, font);
                    src->FontLoaderFlags = loader_flags;
                    ImFontAtlasFontInitOutput(atlas, font);
                }
            }
#endif
            ImGui::TreePop();
        }
    }
    if (font->Sources.Size > 1 && ImGui::TreeNode(u8"输入字形重叠检测工具"))
    {
        ImGui::TextWrapped(u8"- 使用包含该字符的第一个输入.\n"
            u8"- 使用 ImFontConfig::GlyphExcludeRanges[] 指定要在给定输入中忽略的字形范围.\n- 尽量使用少量范围，因为每次加载新字形时都会扫描列表,\n  - e.g. GlyphExcludeRanges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };\n- 这个工具不缓存结果，而且很慢，不要一直打开它!");
        if (ImGui::BeginTable("table", 2))
        {
            for (unsigned int c = 0; c < 0x10000; c++)
                if (int overlap_mask = CalcFontGlyphSrcOverlapMask(atlas, font, c))
                {
                    unsigned int c_end = c + 1;
                    while (c_end < 0x10000 && CalcFontGlyphSrcOverlapMask(atlas, font, c_end) == overlap_mask)
                        c_end++;
                    if (ImGui::TableNextColumn() && ImGui::TreeNode((void*)(intptr_t)c, u8"U+%04X-U+%04X：%d 个码点在 %d 个输入中", c, c_end - 1, c_end - c, ImCountSetBits(overlap_mask)))
                    {
                        char utf8_buf[5];
                        for (unsigned int n = c; n < c_end; n++)
                        {
                            ImTextCharToUtf8(utf8_buf, n);
                            ImGui::BulletText(u8"代码点 U+%04X (%s)", n, utf8_buf);
                        }
                        ImGui::TreePop();
                    }
                    ImGui::TableNextColumn();
                    for (int src_n = 0; src_n < font->Sources.Size; src_n++)
                        if (overlap_mask & (1 << src_n))
                        {
                            ImGui::Text("%d ", src_n);
                            ImGui::SameLine();
                        }
                    c = c_end - 1;
                }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // Display all glyphs of the fonts in separate pages of 256 characters
    for (int baked_n = 0; baked_n < atlas->Builder->BakedPool.Size; baked_n++)
    {
        ImFontBaked* baked = &atlas->Builder->BakedPool[baked_n];
        if (baked->ContainerFont != font)
            continue;
        ImGui::PushID(baked_n);
        if (ImGui::TreeNode(u8"字形", u8"烘焙于 { %.2fpx, d.%.2f }: %d 字形%s", baked->Size, baked->RasterizerDensity, baked->Glyphs.Size, (baked->LastUsedFrame < atlas->Builder->FrameCount - 1) ? " *Unused*" : ""))
        {
            if (ImGui::SmallButton(u8"加载全部"))
                for (unsigned int base = 0; base <= IM_UNICODE_CODEPOINT_MAX; base++)
                    baked->FindGlyph((ImWchar)base);

            const int surface_sqrt = (int)ImSqrt((float)baked->MetricsTotalSurface);
            ImGui::Text(u8"上升：%f，下降：%f，上升-下降：%f", baked->Ascent, baked->Descent, baked->Ascent - baked->Descent);
            ImGui::Text(u8"纹理区域：约 %d px ~%dx%d px", baked->MetricsTotalSurface, surface_sqrt, surface_sqrt);
            for (int src_n = 0; src_n < font->Sources.Size; src_n++)
            {
                ImFontConfig* src = font->Sources[src_n];
                int oversample_h, oversample_v;
                ImFontAtlasBuildGetOversampleFactors(src, baked, &oversample_h, &oversample_v);
                ImGui::BulletText(u8"输入 %d：\'%s\'，过采样：(%d=>%d,%d=>%d)，像素对齐H：%d，偏移： (%.1f,%.1f)",
                    src_n, src->Name, src->OversampleH, oversample_h, src->OversampleV, oversample_v, src->PixelSnapH, src->GlyphOffset.x, src->GlyphOffset.y);
            }

            ImGui::DebugNodeFontGlyphesForSrcMask(font, baked, ~0);
            ImGui::TreePop();
        }
        ImGui::PopID();
    }
    ImGui::TreePop();
    ImGui::Unindent();
}
void ShowFontAtlas_cn(ImFontAtlas* atlas)
{
    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    ImGuiStyle& style = g.Style;

    ImGui::BeginDisabled();
    ImGui::CheckboxFlags("io.BackendFlags: RendererHasTextures", &io.BackendFlags, ImGuiBackendFlags_RendererHasTextures);
    ImGui::EndDisabled();
    ImGui::ShowFontSelector(u8"字体");
    //BeginDisabled((io.BackendFlags & ImGuiBackendFlags_RendererHasTextures) == 0);
    if (ImGui::DragFloat(u8"基本字体大小", &style.FontSizeBase, 0.20f, 5.0f, 100.0f, "%.0f"))
        style._NextFrameFontSizeBase = style.FontSizeBase; // FIXME: Temporary hack until we finish remaining work.
    ImGui::SameLine(0.0f, 0.0f); ImGui::Text(" (out %.2f)", ImGui::GetFontSize());
    ImGui::SameLine(); HelpMarker(u8"- 这仅是字体缩放。一般缩放功能将稍后推出。");
    ImGui::DragFloat(u8"字体缩放主", &style.FontScaleMain, 0.02f, 0.5f, 4.0f);
    //BeginDisabled(io.ConfigDpiScaleFonts);
    ImGui::DragFloat(u8"字体缩放DPI", &style.FontScaleDpi, 0.02f, 0.5f, 4.0f);
    //SetItemTooltip("When io.ConfigDpiScaleFonts is set, this value is automatically overwritten.");
    //EndDisabled();
    if ((io.BackendFlags & ImGuiBackendFlags_RendererHasTextures) == 0)
    {
        ImGui::BulletText(u8"警告：字体缩放不会平滑，因为未设置 ImGuiBackendFlags_RendererHasTextures！");
        ImGui::BulletText(u8"有关说明，请参见：");
        ImGui::SameLine();
        ImGui::TextLinkOpenURL("docs/BACKENDS.md", "https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md");
    }
    ImGui::BulletText(u8"加载一个好字体以获得更好的效果！");
    ImGui::BulletText(u8"请提交反馈：");
    ImGui::SameLine(); ImGui::TextLinkOpenURL("#8465", "https://github.com/ocornut/imgui/issues/8465");
    ImGui::BulletText(u8"查看常见问题以获取更多详情：");
    ImGui::SameLine(); ImGui::TextLinkOpenURL("dearimgui.com/faq", "https://www.dearimgui.com/faq/");
    //EndDisabled();

    ImGui::SeparatorText(u8"字体列表");

    ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;
    ImGui::Checkbox(u8"显示字体预览", &cfg->ShowFontPreview);

    // Font loaders
    if (ImGui::TreeNode(u8"加载器", u8"加载器: \'%s\'", atlas->FontLoaderName ? atlas->FontLoaderName : "NULL"))
    {
        const ImFontLoader* loader_current = atlas->FontLoader;
        ImGui::BeginDisabled(!atlas->RendererHasTextures);
#ifdef IMGUI_ENABLE_STB_TRUETYPE
        const ImFontLoader* loader_stbtruetype = ImFontAtlasGetFontLoaderForStbTruetype();
        if (ImGui::RadioButton("stb_truetype", loader_current == loader_stbtruetype))
            atlas->SetFontLoader(loader_stbtruetype);
#else
        ImGui::BeginDisabled();
        ImGui::RadioButton("stb_truetype", false);
        ImGui::SetItemTooltip("Requires #define IMGUI_ENABLE_STB_TRUETYPE");
        ImGui::EndDisabled();
#endif
        ImGui::SameLine();
#ifdef IMGUI_ENABLE_FREETYPE
        const ImFontLoader* loader_freetype = ImGuiFreeType::GetFontLoader();
        if (ImGui::RadioButton("FreeType", loader_current == loader_freetype))
            atlas->SetFontLoader(loader_freetype);
        if (loader_current == loader_freetype)
        {
            unsigned int loader_flags = atlas->FontLoaderFlags;
            ImGui::Text("Shared FreeType Loader Flags:  0x%08X", loader_flags);
            if (ImGuiFreeType::DebugEditFontLoaderFlags(&loader_flags))
            {
                for (ImFont* font : atlas->Fonts)
                    ImFontAtlasFontDestroyOutput(atlas, font);
                atlas->FontLoaderFlags = loader_flags;
                for (ImFont* font : atlas->Fonts)
                    ImFontAtlasFontInitOutput(atlas, font);
            }
        }
#else
        ImGui::BeginDisabled();
        ImGui::RadioButton("FreeType", false);
        ImGui::SetItemTooltip(u8"需要在 imgui_freetype.cpp 中 #define IMGUI_ENABLE_FREETYPE。");
        ImGui::EndDisabled();
#endif
        ImGui::EndDisabled();
        ImGui::TreePop();
    }

    // Font list
    for (ImFont* font : atlas->Fonts)
    {
        ImGui::PushID(font);
        DebugNodeFont_cn(font);
        ImGui::PopID();
    }

    ImGui::SeparatorText(u8"字体图集");
    if (ImGui::Button(u8"紧凑"))
        atlas->CompactCache();
    ImGui::SameLine();
    if (ImGui::Button(u8"成长"))
        ImFontAtlasTextureGrow(atlas);
    ImGui::SameLine();
    if (ImGui::Button(u8"清除所有"))
        ImFontAtlasBuildClear(atlas);
    ImGui::SetItemTooltip(u8"销毁缓存和自定义矩形。");

    for (int tex_n = 0; tex_n < atlas->TexList.Size; tex_n++)
    {
        ImTextureData* tex = atlas->TexList[tex_n];
        if (tex_n > 0)
            ImGui::SameLine();
        ImGui::Text("Tex: %dx%d", tex->Width, tex->Height);
    }
    const int packed_surface_sqrt = (int)sqrtf((float)atlas->Builder->RectsPackedSurface);
    const int discarded_surface_sqrt = (int)sqrtf((float)atlas->Builder->RectsDiscardedSurface);
    ImGui::Text(u8"打包矩形：%d，面积：約 %d 像素 ~%dx%d 像素", atlas->Builder->RectsPackedCount, atlas->Builder->RectsPackedSurface, packed_surface_sqrt, packed_surface_sqrt);
    ImGui::Text(u8"包括被丢弃的矩形: %d，面积: 约 %d 像素 ~%dx%d 像素", atlas->Builder->RectsDiscardedCount, atlas->Builder->RectsDiscardedSurface, discarded_surface_sqrt, discarded_surface_sqrt);

    ImFontAtlasRectId highlight_r_id = ImFontAtlasRectId_Invalid;
    if (ImGui::TreeNode(u8"矩形索引", u8"矩形索引 (%d)", atlas->Builder->RectsPackedCount)) // <-- Use count of used rectangles
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ImageBorderSize, 1.0f);
        if (ImGui::BeginTable("##table", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 12)))
        {
            for (const ImFontAtlasRectEntry& entry : atlas->Builder->RectsIndex)
                if (entry.IsUsed)
                {
                    ImFontAtlasRectId id = ImFontAtlasRectId_Make(atlas->Builder->RectsIndex.index_from_ptr(&entry), entry.Generation);
                    ImFontAtlasRect r = {};
                    atlas->GetCustomRect(id, &r);
                    const char* buf;
                    ImFormatStringToTempBuffer(&buf, NULL, u8"ID:X，使用率:%d，{ 宽:=, 高:= } { x:M, y:M }", id, entry.IsUsed, r.w, r.h, r.x, r.y);
                    ImGui::TableNextColumn();
                    ImGui::Selectable(buf);
                    if (ImGui::IsItemHovered())
                        highlight_r_id = id;
                    ImGui::TableNextColumn();
                    ImGui::Image(atlas->TexRef, ImVec2(r.w, r.h), r.uv0, r.uv1);
                }
            ImGui::EndTable();
        }
        ImGui::PopStyleVar();
        ImGui::TreePop();
    }

    // Texture list
    // (ensure the last texture always use the same ID, so we can keep it open neatly)
    ImFontAtlasRect highlight_r;
    if (highlight_r_id != ImFontAtlasRectId_Invalid)
        atlas->GetCustomRect(highlight_r_id, &highlight_r);
    for (int tex_n = 0; tex_n < atlas->TexList.Size; tex_n++)
    {
        if (tex_n == atlas->TexList.Size - 1)
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        ImGui::DebugNodeTexture(atlas->TexList[tex_n], atlas->TexList.Size - 1 - tex_n, (highlight_r_id != ImFontAtlasRectId_Invalid) ? &highlight_r : NULL);
    }
}
namespace ImGui {
    const char* TranslateColorName(ImGuiCol col) {
        // 使用 u8 前缀确保所有中文字符串都是 UTF-8 编码
        switch (col) {
            // --- 文本 ---
        case ImGuiCol_Text: return u8"文本";
        case ImGuiCol_TextDisabled: return u8"禁用时文本";
        case ImGuiCol_TextSelectedBg: return u8"选中文本背景";
        case ImGuiCol_TextLink: return u8"链接文本";

            // --- 窗口背景 ---
        case ImGuiCol_WindowBg: return u8"窗口背景";
        case ImGuiCol_ChildBg: return u8"子窗口背景";
        case ImGuiCol_PopupBg: return u8"弹出层背景";
        //case ImGuiCol_DockingEmptyBg: return u8"空停靠区背景";

            // --- 边框 ---
        case ImGuiCol_Border: return u8"边框";
        case ImGuiCol_BorderShadow: return u8"边框阴影 (已弃用)";

            // --- 控件框架 ---
        case ImGuiCol_FrameBg: return u8"控件背景";
        case ImGuiCol_FrameBgHovered: return u8"控件背景 (悬停)";
        case ImGuiCol_FrameBgActive: return u8"控件背景 (激活)";

            // --- 标题栏 ---
        case ImGuiCol_TitleBg: return u8"标题栏背景";
        case ImGuiCol_TitleBgActive: return u8"标题栏背景 (激活)";
        case ImGuiCol_TitleBgCollapsed: return u8"标题栏背景 (折叠)";
        case ImGuiCol_MenuBarBg: return u8"菜单栏背景";

            // --- 滚动条 ---
        case ImGuiCol_ScrollbarBg: return u8"滚动条背景";
        case ImGuiCol_ScrollbarGrab: return u8"滚动条滑块";
        case ImGuiCol_ScrollbarGrabHovered: return u8"滚动条滑块 (悬停)";
        case ImGuiCol_ScrollbarGrabActive: return u8"滚动条滑块 (激活)";

            // --- 控件特定项 ---
        case ImGuiCol_CheckMark: return u8"勾选标记";
        case ImGuiCol_SliderGrab: return u8"滑块";
        case ImGuiCol_SliderGrabActive: return u8"滑块 (激活)";
        case ImGuiCol_InputTextCursor: return u8"输入框光标";

            // --- 按钮 ---
        case ImGuiCol_Button: return u8"按钮";
        case ImGuiCol_ButtonHovered: return u8"按钮 (悬停)";
        case ImGuiCol_ButtonActive: return u8"按钮 (激活)";

            // --- 标题头 ---
        case ImGuiCol_Header: return u8"标题头";
        case ImGuiCol_HeaderHovered: return u8"标题头 (悬停)";
        case ImGuiCol_HeaderActive: return u8"标题头 (激活)";

            // --- 分隔符 ---
        case ImGuiCol_Separator: return u8"分隔符";
        case ImGuiCol_SeparatorHovered: return u8"分隔符 (悬停)";
        case ImGuiCol_SeparatorActive: return u8"分隔符 (激活)";

            // --- 尺寸调整 ---
        case ImGuiCol_ResizeGrip: return u8"尺寸调整手柄";
        case ImGuiCol_ResizeGripHovered: return u8"尺寸调整手柄 (悬停)";
        case ImGuiCol_ResizeGripActive: return u8"尺寸调整手柄 (激活)";

            // --- 标签页 ---
        case ImGuiCol_Tab: return u8"标签页";
        case ImGuiCol_TabHovered: return u8"标签页 (悬停)";
        case ImGuiCol_TabSelected: return u8"选中标签页";
        case ImGuiCol_TabSelectedOverline: return u8"选中标签页上划线";
        case ImGuiCol_TabDimmed: return u8"标签页 (失焦)";
        case ImGuiCol_TabDimmedSelected: return u8"选中标签页 (失焦)";
        case ImGuiCol_TabDimmedSelectedOverline: return u8"选中标签页上划线 (失焦)";

            // --- 表格 ---
        case ImGuiCol_TableHeaderBg: return u8"表格标题背景";
        case ImGuiCol_TableBorderStrong: return u8"表格强边框";
        case ImGuiCol_TableBorderLight: return u8"表格弱边框";
        case ImGuiCol_TableRowBg: return u8"表格行背景";
        case ImGuiCol_TableRowBgAlt: return u8"表格行背景 (交替)";

            // --- 绘图 ---
        case ImGuiCol_PlotLines: return u8"绘图线条";
        case ImGuiCol_PlotLinesHovered: return u8"绘图线条 (悬停)";
        case ImGuiCol_PlotHistogram: return u8"绘图直方图";
        case ImGuiCol_PlotHistogramHovered: return u8"绘图直方图 (悬停)";

            // --- 导航与标记 ---
        case ImGuiCol_NavCursor: return u8"导航光标";
        case ImGuiCol_TreeLines: return u8"树连接线";
        case ImGuiCol_DragDropTarget: return u8"拖放目标高亮";
        case ImGuiCol_UnsavedMarker: return u8"未保存标记";
        case ImGuiCol_DockingPreview: return u8"停靠预览";
        case ImGuiCol_NavWindowingHighlight: return u8"导航窗口高亮";
        case ImGuiCol_NavWindowingDimBg: return u8"导航窗口遮罩";
        case ImGuiCol_ModalWindowDimBg: return u8"模态窗口遮罩";

        default: return ImGui::GetStyleColorName(col); // 如果有未覆盖到的新枚举，则返回其英文名
        }
    }
    bool CheckboxFloat(const char* label, float* v)
    {
        // 1. 创建一个临时的 bool 变量，它的状态取决于 float* v 的值
        //    我们用一个很小的阈值来判断，避免浮点数精度问题
        bool b = (*v > 0.001f);

        // 2. 调用原生的 ImGui::Checkbox，让它操作我们的临时 bool 变量
        //    如果用户点击了 Checkbox, a 会是 true
        bool a = ImGui::Checkbox(label, &b);

        // 3. 如果 Checkbox 被点击了 (a == true)
        if (a) {
            // 根据 Checkbox 之后的状态 b，来更新原始的 float* v
            *v = b ? 1.0f : 0.0f;
        }

        // 4. 返回 Checkbox 的状态，这样调用者就知道值是否发生了改变
        return a;
    }
    void ShowStyleEditorHelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }
    void ShowTranslatedStyleEditor(ImGuiStyle* ref)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        static ImGuiStyle ref_saved_style;
        static bool init = true;
        if (init && ref == NULL)
            ref_saved_style = style;
        init = false;
        if (ref == NULL)
            ref = &ref_saved_style;
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

        if (ImGui::ShowStyleSelector(u8"主题##Selector"))
            ref_saved_style = style;
        ImGui::ShowFontSelector(u8"字体##Selector");

        if (ImGui::SliderFloat(u8"全局透明度", &style.Alpha, 0.20f, 1.0f, "%.2f"))
            style.Colors[ImGuiCol_FrameBg].w = style.Colors[ImGuiCol_WindowBg].w = style.Alpha;
        if (Button(u8"保存参考"))
            *ref = ref_saved_style = style;
        SameLine();
        if (Button(u8"恢复参考"))
            style = *ref;
        SameLine();
        HelpMarker(
            u8"保存/还原到本地非持久存储。默认颜色定义不受影响。"
            u8"使用下面的“导出”功能将它们保存到某个位置。");
        ImGui::Separator();

        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem(u8"尺寸"))
            {
                ImGui::SeparatorText(u8"主要");
                ImGui::SliderFloat2(u8"窗口边距", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
                ImGui::SliderFloat2(u8"框架边距", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
                ImGui::SliderFloat2(u8"控件间距", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
                ImGui::SliderFloat2(u8"控件内部间距", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
                ImGui::SliderFloat2(u8"触摸额外边距", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
                ImGui::SliderFloat(u8"缩进距离", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
                ImGui::SliderFloat(u8"滑块宽度", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");

                ImGui::SeparatorText(u8"边框");
                CheckboxFloat(u8"窗口边框尺寸", &style.WindowBorderSize);
                CheckboxFloat(u8"子窗口边框尺寸", &style.ChildBorderSize);
                CheckboxFloat(u8"弹出窗口边框尺寸", &style.PopupBorderSize);
                CheckboxFloat(u8"框架边框尺寸", &style.FrameBorderSize);

                ImGui::SeparatorText(u8"圆角");
                ImGui::SliderFloat(u8"窗口圆角", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"子窗口圆角", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"框架圆角", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"弹出窗口圆角", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"滑块圆角", &style.GrabRounding, 0.0f, 12.0f, "%.0f");

                ImGui::SeparatorText(u8"滚动条");
                ImGui::SliderFloat(u8"滚动条尺寸", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
                ImGui::SliderFloat(u8"滚动条圆角", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"滚动条边距", &style.ScrollbarPadding, 0.0f, 10.0f, "%.0f");

                ImGui::SeparatorText(u8"标签页");
                CheckboxFloat(u8"标签边框尺寸", &style.TabBorderSize);
                ImGui::SliderFloat(u8"标签栏边框尺寸", &style.TabBarBorderSize, 0.0f, 2.0f, "%.0f");
                ImGui::SliderFloat(u8"标签栏上划线尺寸", &style.TabBarOverlineSize, 0.0f, 3.0f, "%.0f");
                ImGui::SameLine(); HelpMarker(u8"仅当设置了 ImGuiTabBarFlags_DrawSelectedOverline 时，才会在选定的标签上绘制上划线。");
                ImGui::DragFloat(u8"标签最小宽度(基础)", &style.TabMinWidthBase, 0.5f, 1.0f, 500.0f, "%.0f");
                ImGui::DragFloat(u8"标签最小宽度(收缩)", &style.TabMinWidthShrink, 0.5f, 1.0f, 500.0f, "%0.f");
                ImGui::DragFloat(u8"标签关闭按钮最小宽度(选中)", &style.TabCloseButtonMinWidthSelected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthSelected < 0.0f) ? u8"%.0f (总是)" : "%.0f");
                ImGui::DragFloat(u8"标签关闭按钮最小宽度(未选中)", &style.TabCloseButtonMinWidthUnselected, 0.5f, -1.0f, 100.0f, (style.TabCloseButtonMinWidthUnselected < 0.0f) ? u8"%.0f (总是)" : "%.0f");
                ImGui::SliderFloat(u8"标签圆角", &style.TabRounding, 0.0f, 12.0f, "%.0f");

                ImGui::SeparatorText(u8"表格");
                ImGui::SliderFloat2(u8"单元格边距", (float*)&style.CellPadding, 0.0f, 20.0f, "%.0f");
                ImGui::SliderAngle(u8"表格斜角标题角度", &style.TableAngledHeadersAngle, -50.0f, +50.0f);
                ImGui::SliderFloat2(u8"表格斜角标题对齐", (float*)&style.TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");

                ImGui::SeparatorText(u8"树");
                bool combo_open = ImGui::BeginCombo(u8"树连接线标志", GetTreeLinesFlagsName(style.TreeLinesFlags));
                ImGui::SameLine();
                HelpMarker(u8"[实验性] 树连接线可能在某些情况下（例如使用Clipper时）无法正常工作，并且可能会产生轻微的遍历开销。\n\nImGuiTreeNodeFlags_DrawLinesFull 比 ImGuiTreeNodeFlags_DrawLinesToNode 更快。");
                if (combo_open)
                {
                    const ImGuiTreeNodeFlags options[] = { ImGuiTreeNodeFlags_DrawLinesNone, ImGuiTreeNodeFlags_DrawLinesFull, ImGuiTreeNodeFlags_DrawLinesToNodes };
                    for (ImGuiTreeNodeFlags option : options)
                        if (Selectable(GetTreeLinesFlagsName(option), style.TreeLinesFlags == option))
                            style.TreeLinesFlags = option;
                    EndCombo();
                }
                ImGui::SliderFloat(u8"树连接线尺寸", &style.TreeLinesSize, 0.0f, 2.0f, "%.0f");
                ImGui::SliderFloat(u8"树连接线圆角", &style.TreeLinesRounding, 0.0f, 12.0f, "%.0f");

                ImGui::SeparatorText(u8"窗口");
                ImGui::SliderFloat2(u8"窗口标题对齐", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat(u8"窗口边框悬停边距", &style.WindowBorderHoverPadding, 1.0f, 20.0f, "%.0f");
                int window_menu_button_position = style.WindowMenuButtonPosition + 1;
                if (ImGui::Combo(u8"窗口菜单按钮位置", (int*)&window_menu_button_position, u8"无\0左\0右\0"))
                    style.WindowMenuButtonPosition = (ImGuiDir)(window_menu_button_position - 1);

                ImGui::SeparatorText(u8"控件");
                ImGui::Combo(u8"颜色按钮位置", (int*)&style.ColorButtonPosition, u8"左\0右\0");
                ImGui::SliderFloat2(u8"按钮文本对齐", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
                ImGui::SameLine(); HelpMarker(u8"当按钮尺寸大于其文本内容时应用对齐。");
                ImGui::SliderFloat2(u8"可选项文本对齐", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
                ImGui::SameLine(); HelpMarker(u8"当可选项尺寸大于其文本内容时应用对齐。");
                ImGui::SliderFloat(u8"分隔符文本边框尺寸", &style.SeparatorTextBorderSize, 0.0f, 10.0f, "%.0f");
                ImGui::SliderFloat2(u8"分隔符文本对齐", (float*)&style.SeparatorTextAlign, 0.0f, 1.0f, "%.2f");
                ImGui::SliderFloat2(u8"分隔符文本边距", (float*)&style.SeparatorTextPadding, 0.0f, 40.0f, "%.0f");
                ImGui::SliderFloat(u8"对数滑块死区", &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
                ImGui::SliderFloat(u8"图片边框尺寸", &style.ImageBorderSize, 0.0f, 1.0f, "%.0f");

                ImGui::SeparatorText(u8"停靠");
                ImGui::Checkbox(u8"停靠节点有关闭按钮", &style.DockingNodeHasCloseButton);
                ImGui::SliderFloat(u8"停靠分隔符尺寸", &style.DockingSeparatorSize, 0.0f, 12.0f, "%.0f");

                ImGui::SeparatorText(u8"工具提示");
                for (int n = 0; n < 2; n++)
                    if (ImGui::TreeNodeEx(n == 0 ? u8"鼠标悬停标志" : u8"导航悬停标志"))
                    {
                        ImGuiHoveredFlags* p = (n == 0) ? &style.HoverFlagsForTooltipMouse : &style.HoverFlagsForTooltipNav;
                        ImGui::CheckboxFlags(u8"无延迟", p, ImGuiHoveredFlags_DelayNone);
                        ImGui::CheckboxFlags(u8"短延迟", p, ImGuiHoveredFlags_DelayShort);
                        ImGui::CheckboxFlags(u8"正常延迟", p, ImGuiHoveredFlags_DelayNormal);
                        ImGui::CheckboxFlags(u8"静止", p, ImGuiHoveredFlags_Stationary);
                        ImGui::CheckboxFlags(u8"无共享延迟", p, ImGuiHoveredFlags_NoSharedDelay);
                        ImGui::TreePop();
                    }

                ImGui::SeparatorText(u8"杂项");
                ImGui::SliderFloat2(u8"显示窗口边距", (float*)&style.DisplayWindowPadding, 0.0f, 30.0f, "%.0f"); ImGui::SameLine(); HelpMarker(u8"应用于常规窗口：在靠近屏幕边缘移动时我们强制保持可见的量。");
                ImGui::SliderFloat2(u8"屏幕安全边距", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f"); ImGui::SameLine(); HelpMarker(u8"应用于所有窗口、菜单、弹出窗口、工具提示：我们避免在此区域显示内容。如果您看不到屏幕边缘（例如在电视上），请进行调整。");

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"颜色"))
            {
                static int output_dest = 0;
                static bool output_only_modified = true;
                if (ImGui::Button(u8"导出"))
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
                ImGui::SameLine(); ImGui::SetNextItemWidth(120); ImGui::Combo("##output_type", &output_dest, u8"到剪贴板\0到控制台\0");
                ImGui::SameLine(); ImGui::Checkbox(u8"仅导出已修改项", &output_only_modified);

                static ImGuiTextFilter filter;
                filter.Draw(u8"筛选颜色", ImGui::GetFontSize() * 16);

                static ImGuiColorEditFlags alpha_flags = 0;
                if (ImGui::RadioButton(u8"不透明", alpha_flags == ImGuiColorEditFlags_AlphaOpaque)) { alpha_flags = ImGuiColorEditFlags_AlphaOpaque; } ImGui::SameLine();
                if (ImGui::RadioButton(u8"透明", alpha_flags == ImGuiColorEditFlags_None)) { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
                if (ImGui::RadioButton(u8"两者", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();
                HelpMarker(
                    u8"在颜色列表中：\n"
                    u8"左键点击色块打开颜色选择器，\n"
                    u8"右键点击打开编辑选项菜单。");

                SetNextWindowSizeConstraints(ImVec2(0.0f, GetTextLineHeightWithSpacing() * 10), ImVec2(FLT_MAX, FLT_MAX));
                BeginChild("##colors", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
                PushItemWidth(GetFontSize() * -12);
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const char* name = GetStyleColorName(i);
                    if (!filter.PassFilter(name))
                        continue;
                    PushID(i);
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
                    if (Button("?"))
                        DebugFlashStyleColor((ImGuiCol)i);
                    SetItemTooltip(u8"闪烁此颜色以识别其使用位置。");
                    SameLine();
#endif
                    ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
                    if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
                    {
                        SameLine(0.0f, style.ItemInnerSpacing.x); if (Button(u8"保存")) { ref->Colors[i] = style.Colors[i]; }
                        SameLine(0.0f, style.ItemInnerSpacing.x); if (Button(u8"恢复")) { style.Colors[i] = ref->Colors[i]; }
                    }
                    SameLine(0.0f, style.ItemInnerSpacing.x);
                    // 调用我们之前创建的翻译函数来显示中文名
                    TextUnformatted(TranslateColorName((ImGuiCol)i));
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
                ShowFontAtlas_cn(atlas);
                EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"渲染"))
            {
                ImGui::Checkbox(u8"抗锯齿线条", &style.AntiAliasedLines);
                ImGui::SameLine();
                HelpMarker(u8"禁用抗锯齿线条时，您可能也想在样式中禁用边框。");

                ImGui::Checkbox(u8"抗锯齿线条使用纹理", &style.AntiAliasedLinesUseTex);
                ImGui::SameLine();
                HelpMarker(u8"使用纹理数据实现更快的线条。需要后端以双线性过滤（而非点/最近邻过滤）进行渲染。");

                ImGui::Checkbox(u8"抗锯齿填充", &style.AntiAliasedFill);
                ImGui::PushItemWidth(ImGui::GetFontSize() * 8);
                ImGui::DragFloat(u8"曲线细分容差", &style.CurveTessellationTol, 0.02f, 0.10f, 10.0f, "%.2f");
                if (style.CurveTessellationTol < 0.10f) style.CurveTessellationTol = 0.10f;

                ImGui::DragFloat(u8"圆形细分最大误差", &style.CircleTessellationMaxError, 0.005f, 0.10f, 5.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                const bool show_samples = IsItemActive();
                if (show_samples)
                    SetNextWindowPos(GetCursorScreenPos());
                if (show_samples && BeginTooltip())
                {
                    TextUnformatted("(R = radius, N = approx number of segments)");
                    Spacing();
                    ImDrawList* draw_list = GetWindowDrawList();
                    const float min_widget_width = CalcTextSize("R: MMM\nN: MMM").x;
                    for (int n = 0; n < 8; n++)
                    {
                        const float RAD_MIN = 5.0f;
                        const float RAD_MAX = 70.0f;
                        const float rad = RAD_MIN + (RAD_MAX - RAD_MIN) * (float)n / (8.0f - 1.0f);

                        BeginGroup();

                        // N is not always exact here due to how PathArcTo() function work internally
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
                ImGui::SameLine();
                HelpMarker(u8"在绘制圆形基元时，若 'num_segments == 0'，则将自动计算细分。");

                ImGui::DragFloat(u8"全局透明度", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f");
                ImGui::DragFloat(u8"禁用项透明度", &style.DisabledAlpha, 0.005f, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); HelpMarker(u8"为禁用项附加的透明度乘数（在当前Alpha值上乘）。");
                ImGui::PopItemWidth();

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::PopItemWidth();
    }

} // namespace ImGui
