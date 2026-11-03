#include "ImAdd.h"
#include "../imgui/imgui_internal.h"

CImAdd* ImAdd;
CImGrp* ImGrp;

// ImGui Groups
void CImGrp::CheckboxSliderFloat(const char* cb_label, const char* s_label, bool* bv, float* fv, float v_min, float v_max, const char* format, bool custom_spacing)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    int width = 70;

    ImGui::Checkbox(cb_label, bv);
    if (custom_spacing)
        ImGui::SameLine(ImGui::GetWindowSize().x - width - style.WindowPadding.x);
    else
        ImGui::SameLine();
    ImGui::PushItemWidth(width);

    ImGui::SliderFloat(s_label, fv, v_min, v_max, format);
    ImGui::PopItemWidth();
}

void CImGrp::CheckboxSliderInt(const char* cb_label, const char* s_label, bool* bv, int* fv, int v_min, int v_max, bool custom_spacing)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    int width = 70;

    ImGui::Checkbox(cb_label, bv);
    if (custom_spacing)
        ImGui::SameLine(ImGui::GetWindowSize().x - width - style.WindowPadding.x);
    else
        ImGui::SameLine();
    ImGui::PushItemWidth(width);

    ImGui::SliderInt(s_label, fv, v_min, v_max);
    ImGui::PopItemWidth();
}

void CImGrp::ToggleButton(const char* text, bool* v)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::BeginGroup();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.FramePadding);
    ImGui::Spacing();
    ImGui::PopStyleVar();
    ImGui::SetCursorPosX(style.WindowPadding.x + ImGui::CalcTextSize(" ").x);
    ImGui::Text(text);
    ImGui::EndGroup();
    ImGui::SameLine(ImGui::GetWindowSize().x - style.WindowPadding.x - ImGui::GetFrameHeight() * 2);
    std::string str1 = "##";
    std::string str2 = text;
    ImAdd->ToggleButton((str1 + str2).c_str(), v);
}

void CImGrp::ToggleButtonCombo(const char* text, bool* v, int* current_item, const char* items_separated_by_zeros)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::BeginGroup();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.FramePadding);
    ImGui::Spacing();
    ImGui::PopStyleVar();
    ImGui::SetCursorPosX(style.WindowPadding.x + ImGui::CalcTextSize(" ").x);
    ImGui::Text(text);
    ImGui::EndGroup();
    ImGui::SameLine(ImGui::GetWindowSize().x - (style.WindowPadding.x * 2) - 70 - ImGui::GetFrameHeight() * 2);
    ImGui::PushItemWidth(70.f);
    std::string str1 = "##";
    std::string str2 = text;
    ImGui::Combo((str1 + str2).c_str(), current_item, items_separated_by_zeros);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImAdd->ToggleButton(text, v);
}

void CImGrp::ToggleButton(const char* text, bool* v, std::function<void()> addictional_settings)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::BeginGroup();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.FramePadding);
    ImGui::Spacing();
    ImGui::PopStyleVar();
    ImGui::SetCursorPosX(style.WindowPadding.x + ImGui::CalcTextSize(" ").x);
    ImGui::Text(text);
    ImGui::EndGroup();
    ImGui::SameLine(ImGui::GetWindowSize().x - (style.WindowPadding.x * 2) - 22 - ImGui::GetFrameHeight() * 2);
    ImGui::PushItemWidth(70.f);
    std::string PopupAddictional = std::string(text) + std::string("PopupAddictional");
    std::string NAmeAddictional = std::string(text) + std::string(" Addictional");
    std::string str1IC = "##";
    std::string str2Ic = text;
    if (ImGui::Button((ICON_FA_GEAR+str1IC + str2Ic).c_str(),ImVec2(0,0))) {


        ImGui::OpenPopup(PopupAddictional.c_str());

      
    }
    if (ImGui::BeginPopup(PopupAddictional.c_str(), ImGuiWindowFlags_NoMove))
    {

        ImGui::BeginChild("weapons1", ImVec2(200, 200), true, ImGuiWindowFlags_MenuBar);
        {
            if (ImGui::BeginMenuBar()) ImGui::TextUnformatted(text), ImGui::EndMenuBar();
            {
                addictional_settings();
            }
        }
        ImGui::EndChild();

        ImGui::EndPopup();
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();

    std::string str1 = "##";
    std::string str2 = text;
    ImAdd->ToggleButton((str1 + str2).c_str(), v);
}
void CImGrp::ToggleButtonComboCheckBox(const char* text, const char* popup, bool* bt, bool* bc, int* current_item, const char* items_separated_by_zeros)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImGui::BeginGroup();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.FramePadding);
    ImGui::Spacing();
    ImGui::PopStyleVar();
    ImGui::SetCursorPosX(style.WindowPadding.x + ImGui::CalcTextSize(" ").x);
    ImGui::Text(text);
    ImGui::EndGroup();
    ImGui::SameLine(ImGui::GetWindowSize().x - (style.WindowPadding.x * 2) - 70 - ImGui::GetFrameHeight() * 2);
    ImGui::PushItemWidth(70.f - ImGui::GetFrameHeight() - style.WindowPadding.x);
    std::string str1 = "##";
    std::string str2 = text;
    std::string str3 = text;
    ImGui::Combo((str1 + str2).c_str(), current_item, items_separated_by_zeros);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Checkbox((str1 + str2 + str3).c_str(), bc);
    if (strlen(popup) && ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(popup);
        ImGui::EndTooltip();
    }
    ImGui::SameLine();
    ImAdd->ToggleButton(text, bt);
}

// ImGui Addons
void CImAdd::Tooltip(const char* szText)
{
    if (strlen(szText) && ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(szText);
        ImGui::EndTooltip();
    }
}

void CImAdd::HotKey(int* k, const ImVec2& size_arg)
{
    static const char* keyname = KeyNames[*k];
    static bool ispressed = false;
    if (ImGui::Button(keyname, size_arg))
    {
        keyname = "...";
        ispressed = true;
    }
    if (ispressed)
    {
        bool ignore_key = false;
        for (auto ignored_key : IgnoredKeys) {
            if (GetAsyncKeyState(ignored_key) & 0x8000) {
                ignore_key = true;
                break;
            }
        }
        if (!ignore_key) {
            for (auto& Key : KeyCodes)
            {
                if (GetAsyncKeyState(Key) & 0x8000) {
                    *k = Key;
                    ispressed = false;
                }
            }
        }
    }
    else
    {
        keyname = KeyNames[*k];
    }
}

ImVec4 CImAdd::Hex2RGBA(int hexValue, float alpha)
{
    float r = (hexValue >> 16) & 0xFF;
    float g = (hexValue >> 8) & 0xFF;
    float b = hexValue & 0xFF;

    return ImVec4(r / 255, g / 255, b / 255, alpha);
}

void CImAdd::SeparatorText(const char* text)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    auto pos = ImGui::GetCursorScreenPos();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.62f, 0.62f, 0.63f, 1.00f));
    ImGui::Text(text);
    ImGui::PopStyleColor();
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + ImGui::CalcTextSize(text).x + style.WindowPadding.x, pos.y + ImGui::CalcTextSize(text).y / 2), ImVec2(pos.x + ImGui::GetWindowSize().x - style.WindowPadding.x * 2, pos.y + ImGui::CalcTextSize(text).y / 2), ImGui::GetColorU32(ImGuiCol_Border));
}

struct checkbox_animation {
    float animation;
};

bool CImAdd::ToggleButton(const char* label, bool* v)
{

    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    float height = ImGui::GetFrameHeight();
    const ImVec2 pos = window->DC.CursorPos;

    float width = height * 2.f;
    float radius = height * 0.50f;

    const ImRect total_bb(pos, ImVec2(pos.x + width + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y + style.FramePadding.y));

    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    float last_active_id_timer = g.LastActiveIdTimer;

    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
    if (pressed)
    {
        *v = !(*v);
        MarkItemEdited(id);
        g.LastActiveIdTimer = 0.f;
    }

    if (g.LastActiveIdTimer == 0.f && g.LastActiveId == id && !pressed)
        g.LastActiveIdTimer = last_active_id_timer;

    float t = *v ? 1.0f : 0.0f;

    if (g.LastActiveId == id)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / 0.1f);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : *v ? ImGuiCol_SliderGrab : ImGuiCol_FrameBg);

    const ImRect frame_bb(pos, ImVec2(pos.x + width, pos.y + height));

    RenderFrame(frame_bb.Min, frame_bb.Max, col_bg, true, height * 0.5f);
    RenderNavHighlight(total_bb, id);

    ImVec2 label_pos = ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y);
    RenderText(label_pos, label);
    window->DrawList->AddCircleFilled(ImVec2(pos.x + radius + t * (width - radius * 2.0f), pos.y + radius), radius - style.FramePadding.x, ImGui::GetColorU32(*v ? ImGuiCol_CheckMark : ImGuiCol_TextDisabled), 36);

    return pressed;
}

struct button_state {

    ImVec4 background_color;

};

bool CImAdd::AnimButton(const char* label, const ImVec2& size_arg, float speed, ImGuiButtonFlags flags)
{
    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, { pos.x + size.x , pos.y + size.y });
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    static std::map<ImGuiID, button_state> anim;
    auto it_anim = anim.find(id);

    if (it_anim == anim.end())
    {
        anim.insert({ id, button_state() });
        it_anim = anim.find(id);
    }

    it_anim->second.background_color = ImLerp(it_anim->second.background_color, IsItemActive() ? ImColor(GetColorU32(ImGuiCol_ButtonActive)) : hovered ? ImColor(GetColorU32(ImGuiCol_ButtonHovered)) : ImColor(GetColorU32(ImGuiCol_Button)), g.IO.DeltaTime * speed);

    RenderFrame(bb.Min, bb.Max, GetColorU32(it_anim->second.background_color), true, style.FrameRounding);

    RenderTextClipped({ bb.Min.x + style.FramePadding.x , bb.Min.y + style.FramePadding.y }, { bb.Max.x - style.FramePadding.x , bb.Max.y - style.FramePadding.y }, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return pressed;
}

void CImAdd::NavigationRadioIcon(const char* icon, const char* text, ImVec2 size, int id, int* t_ids, bool popup, bool allowpopups)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    auto pos = ImGui::GetCursorPos();
    auto spos = ImGui::GetCursorScreenPos();

    ImVec4 FocText;

    if (id == *t_ids)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_SliderGrabActive));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyleColorVec4(ImGuiCol_SliderGrabActive));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyleColorVec4(ImGuiCol_SliderGrabActive));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
        AnimButton(text, size, 5, 0);

        ImGui::PopStyleColor(4);
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.00f, 0.00f, 0.00f));
        if (AnimButton(text, size, 5, 0))
        {
            *t_ids = id;
        }
        ImGui::PopStyleColor(4);
    }
    static bool hovered = false;
    if (ImGui::IsItemHovered())
    {
        FocText = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
        hovered = true;
    }
    else
    {
        FocText = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        hovered = false;
    }

    if (id == *t_ids)
    {
        ImGui::SameLine(pos.x + ((size.x / 2) - (ImGui::CalcTextSize(icon).x / 2)));
        ImGui::SetCursorPosY(pos.y + ((size.y / 2) - (ImGui::CalcTextSize(icon).y / 2)) - style.FramePadding.y + 1);
        ImGui::Text(icon);
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Text, FocText);
        ImGui::SameLine(pos.x + ((size.x / 2) - (ImGui::CalcTextSize(icon).x / 2)));
        ImGui::SetCursorPosY(pos.y + ((size.y / 2) - (ImGui::CalcTextSize(icon).y / 2)) - style.FramePadding.y + 1);
        ImGui::Text(icon);
        ImGui::PopStyleColor();
    }

    if (allowpopups && (hovered || popup))
    {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(spos.x - (style.WindowPadding.x * 4) - ImGui::CalcTextSize
        (text).x, spos.y), ImVec2(spos.x - (style.WindowPadding.x * 2), spos.y + size.y), ImGui::GetColorU32(ImGuiCol_ChildBg), style.WindowRounding);
        ImGui::GetBackgroundDrawList()->AddText(g.Font, ImGui::GetFontSize(), ImVec2(spos.x - (style.WindowPadding.x * 3) - ImGui::CalcTextSize
        (text).x, spos.y + ((size.y / 2) - (ImGui::CalcTextSize(text).y / 2))), ImGui::GetColorU32(ImGuiCol_Text), text);
    }
}

void CImAdd::NavigationRadio(const char* text, ImVec2 size, int id, int* t_ids)
{
    ImGuiStyle& style = ImGui::GetStyle();
    if (id == *t_ids)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGuiCol_SliderGrabActive);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGuiCol_SliderGrabActive);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGuiCol_SliderGrabActive);
        //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.00f, 0.20f, 1.00f));
        AnimButton(text, size, 5, 0);

        ImGui::PopStyleColor(3);
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.58f, 0.58f, 0.58f, 1.00f));
        if (AnimButton(text, size, 5, 0))
        {
            *t_ids = id;
        }
        ImGui::PopStyleColor();
    }
}

bool CImAdd::SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, float grab_radius, ImGuiSliderFlags flags)
{
    using namespace ImGui;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const float w = GetWindowSize().x - style.WindowPadding.x * 2;

    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    const ImRect frame_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y), ImVec2(w + window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y * 2));
    const ImRect total_bb(frame_bb.Min, ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x + frame_bb.Max.x : frame_bb.Max.x, frame_bb.Max.y + label_size.y));

    const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0))
        return false;

    // Default format string when passing NULL
    if (format == NULL)
        format = DataTypeGetInfo(data_type)->PrintFmt;

    // Tabbing or CTRL-clicking on Slider turns it into an input box
    const bool hovered = ItemHoverable(frame_bb, id);
    const bool clicked = (hovered && g.IO.MouseClicked[0]);
    if (clicked)
    {
        SetActiveID(id, window);
        SetFocusID(id, window);
        FocusWindow(window);
        g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
    }
    // Draw frame
    const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
    RenderNavHighlight(frame_bb, id);
    RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

    // Slider behavior
    ImRect grab_bb;
    const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
    if (value_changed)
        MarkItemEdited(id);

    // Render grab
    if (grab_bb.Max.x > grab_bb.Min.x)
        window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

    // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
    char value_buf[64];
    const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
    if (g.LogEnabled)
        LogSetNextTextDecoration("{", "}");
    RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y - style.ItemInnerSpacing.x - label_size.y * 2), frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(1.0f, 0.5f));

    if (label_size.x > 0.0f)
        RenderText(ImVec2(frame_bb.Min.x/* + style.ItemInnerSpacing.x*/, frame_bb.Min.y - label_size.y - style.ItemInnerSpacing.x), label);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return value_changed;
}

bool CImAdd::SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    return this->SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, 6, flags);
}

bool CImAdd::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    return this->SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, 6, flags);
}

#define min2(x,y) ((x)<(y)?x:y)
#define wh(a) ImColor(1.f,1.f,1.f,a)

void CImAdd::FX(ImDrawList* d, ImVec2 a, ImVec2 b, ImVec2 sz, ImVec2, float t, ImDrawFlags draw_flag)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    static float fl;
    if ((rand() % 500) == 0) fl = t;
    if ((t - fl) > 0)
    {
        auto ft = 0.25f;
        d->AddRectFilled(a, b, wh((ft - (t - fl)) / ft), 0, draw_flag);
    }

    for (int i = 0; i < 2000; ++i) {
        unsigned h = ImGui::GetID(d + i + int(t / 4));
        auto f = fmodf(t + fmodf(h / 777.f, 99), 99);
        auto tx = h % (int)sz.x;
        auto ty = h % (int)sz.y;
        if (f < 1) {
            auto py = ty - 1000 * (1 - f);
            d->AddLine({ a.x + tx, a.y + py }, { a.x + tx, a.y + min2(py + 10,ty) }, (ImU32)-1);
        }
        else if (f < 1.2f)
            d->AddCircle({ a.x + tx, a.y + ty }, (f - 1) * 10 + h % 5, wh(1 - (f - 1) * 5.f));
    }
}