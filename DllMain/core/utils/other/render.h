inline ImDrawList* DrawList;

void DrawLine(float x1, float y1, float x2, float y2, ImColor clr, float thickness, bool outline = false) {
    if (outline)
        DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(0, 0, 0), thickness * 1.5f);
    DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr, thickness);
}

void DrawLine(ImVec2 start, ImVec2 end, ImColor clr, float thickness, bool outline = false) {
    if (outline)
        DrawList->AddLine(start, end, ImColor(0, 0, 0), thickness * 2.0f);
    DrawList->AddLine(start, end, clr, thickness);
}

void FilledRect(float x, float y, float w, float h, ImColor clr, float rounding = 0.0f, ImDrawFlags flags = 0) {
    DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
}

void Rect(float x, float y, float w, float h, ImColor clr, float rounding = 0.0f, ImDrawFlags flags = 0) {
    DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
}

void AddRadialGradient(const ImVec2& center, float radius, ImU32 col_in, ImU32 col_out) {
    if (((col_in | col_out) & IM_COL32_A_MASK) == 0 || radius < 0.5f) return;

    DrawList->PathArcToFast(center, radius, 0, IM_DRAWLIST_ARCFAST_SAMPLE_MAX);
    const int count = DrawList->_Path.Size - 1;
    unsigned int vtx_base = DrawList->_VtxCurrentIdx;
    DrawList->PrimReserve(count * 3, count + 1);
    const ImVec2 uv = DrawList->_Data->TexUvWhitePixel;

    DrawList->PrimWriteVtx(center, uv, col_in);
    for (int n = 0; n < count; n++)
        DrawList->PrimWriteVtx(DrawList->_Path[n], uv, col_out);

    for (int n = 0; n < count; n++) {
        DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
        DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
        DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
    }
    DrawList->_Path.Size = 0;
}

std::string ConvertToUTF8(const std::string& str) {
    if (str.empty()) return str;

    int wideSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    if (wideSize <= 0) return str;

    std::vector<wchar_t> wideStr(wideSize);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), wideStr.data(), wideSize);

    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideStr.data(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Size <= 0) return str;

    std::vector<char> utf8Str(utf8Size);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.data(), wideSize, utf8Str.data(), utf8Size, nullptr, nullptr);

    return std::string(utf8Str.data());
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr) {
    DrawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr);
}

void DrawString(float x, float y, ImColor color, const char* text,
    bool outline = true,
    bool center = true,
    ImColor outlineColor = ImColor(0, 0, 0, 255))
{
    ImFont* font = fonts[fonts_::esp_font].get(settings::player::font_size);
    if (!font || !text) return;

    std::string utf8Text = ConvertToUTF8(std::string(text));

    ImVec2 textSize = font->CalcTextSizeA(settings::player::font_size, FLT_MAX, 0.0f, utf8Text.c_str());
    ImVec2 pos = center ? ImVec2(x - textSize.x * 0.5f, y - textSize.y * 0.5f) : ImVec2(x, y);


    DrawList->AddText(font, settings::player::font_size, ImVec2(pos.x, pos.y + 1), outlineColor, utf8Text.c_str());
    DrawList->AddText(font, settings::player::font_size, ImVec2(pos.x + 1, pos.y), outlineColor, utf8Text.c_str());
    DrawList->AddText(font, settings::player::font_size, ImVec2(pos.x, pos.y - 1), outlineColor, utf8Text.c_str());
    DrawList->AddText(font, settings::player::font_size, ImVec2(pos.x - 1, pos.y), outlineColor, utf8Text.c_str());

    DrawList->AddText(font, settings::player::font_size, pos, color, utf8Text.c_str());
}


void DrawCircle(float x, float y, float radius, ImColor color, float thickness = 1.0f) {
    DrawList->AddCircle(ImVec2(x, y), radius, color, 0, thickness);
}

void DrawESPBox(Vector2 min, Vector2 max, ImColor clr) {
    ImVec2 minPos = ImVec2(min.x, min.y);
    ImVec2 maxPos = ImVec2(max.x, max.y);
    DrawList->AddRect(minPos, maxPos, ImColor(0, 0, 0, 255), 0.0f, -1, 2.0f);
    DrawList->AddRect(minPos, maxPos, clr, 0.0f, -1, 1.0f);
}

void DrawCornerBox(ImVec2 min, ImVec2 max, ImColor color) {
    float width = max.x - min.x;
    float height = max.y - min.y;
    float cornerWidth = width * 0.25f;
    float cornerHeight = height * 0.14f;

    DrawLine(min.x, min.y, min.x + cornerWidth, min.y, color, 1.0f, true);
    DrawLine(max.x, min.y, max.x - cornerWidth, min.y, color, 1.0f, true);
    DrawLine(min.x, min.y, min.x, min.y + cornerHeight, color, 1.0f, true);
    DrawLine(min.x, max.y, min.x, max.y - cornerHeight, color, 1.0f, true);
    DrawLine(max.x, min.y, max.x, min.y + cornerHeight, color, 1.0f, true);
    DrawLine(max.x, max.y, max.x, max.y - cornerHeight, color, 1.0f, true);
    DrawLine(min.x, max.y, min.x + cornerWidth, max.y, color, 1.0f, true);
    DrawLine(max.x, max.y, max.x - cornerWidth, max.y, color, 1.0f, true);
}

void DrawProgressBar(Vector2 start, Vector2 end, float current, float maximum) {
    if (maximum <= 0) return;

    float ratio = min(current / maximum, 1.0f);
    if (ratio < 0) ratio = 0;

    FilledRect(start.x, start.y, end.x, end.y + 1, ImColor(8, 8, 8), 3, ImDrawFlags_RoundCornersAll);
    Rect(start.x, start.y, end.x, end.y + 1, ImColor(25, 25, 25, 255), 3, ImDrawFlags_RoundCornersAll);

    if (ratio > 0) {
        FilledRect(start.x + 1, start.y + 1, (end.x - 2) * ratio, end.y - 1,
            ImColor(0, 255, 0, 255), 3, ImDrawFlags_RoundCornersAll);
    }
}
Vector2 ComputeDirectionPoint(float angle_deg, float range, int origin_x, int origin_y, int line_length) {
    const float angle_rad = (angle_deg + 45.0f) * (PI / 180.0f);
    const float cos_yaw = std::cos(angle_rad);
    const float sin_yaw = std::sin(angle_rad);

    const float dx = range * (-cos_yaw) + range * (sin_yaw);
    const float dy = range * (-cos_yaw) - range * (sin_yaw);

    const int x2 = origin_x + static_cast<int>(dx / range * line_length);
    const int y2 = origin_y + static_cast<int>(dy / range * line_length);

    return Vector2(x2, y2);
}

void Progbar(Vector2 start, Vector2 size, float a, float b, ImColor fill, float rounding, bool Vertical = false)
{
    const float eps = 1e-6f;
    const float maxv = (b > eps) ? b : 1.0f;
    float t = a / maxv;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    FilledRect(start.x, start.y, size.x, size.y, ImColor(0, 0, 0, 255), rounding, ImDrawFlags_RoundCornersAll);

    const float inner_w = (size.x > 2.0f) ? (size.x - 2.0f) : 0.0f;
    const float inner_h = (size.y > 2.0f) ? (size.y - 2.0f) : 0.0f;

    if (!Vertical)
    {
        const float w_filled = inner_w * t;
        if (w_filled > 0.0f)
            FilledRect(start.x + 1.0f, start.y + 1.0f, w_filled, inner_h, fill, rounding, ImDrawFlags_RoundCornersAll);
    }
    else
    {
        const float h_filled = inner_h * t;
        if (h_filled > 0.0f)
        {
            const float y = start.y + 1.0f + (inner_h - h_filled);
            FilledRect(start.x + 1.0f, y, inner_w, h_filled, fill, rounding, ImDrawFlags_RoundCornersAll);
        }
    }
}
