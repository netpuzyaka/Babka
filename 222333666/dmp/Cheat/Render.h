#pragma once
#define PI			3.14159265358979323846
#include <DirectXMath.h>
#define RAD2DEG(x) DirectX::XMConvertToDegrees(x)
#define DEG2RAD(x) DirectX::XMConvertToRadians(x)

namespace render2 {
	enum e_textflags {
		none = 0,
		outline = 1 << 0,
		centered_x = 1 << 1,
		centered_y = 1 << 2,
		dropShadow = 1 << 3,
	};
	enum e_cornerflags {
		default = 15,
		corner_left_top = 1 << 0,
		corner_right_top = 1 << 1,
		corner_left_bot = 1 << 2,
		corner_right_bot = 1 << 3,
		corner_top = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight,   // 0x3
		corner_bot = ImDrawFlags_RoundCornersBottomLeft | ImDrawFlags_RoundCornersBottomRight,   // 0xC
		corner_left = ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomLeft,    // 0x5
		corner_right = ImDrawFlags_RoundCornersTopRight | ImDrawFlags_RoundCornersBottomRight,  // 0xA
	};
}
class ImGuiRendering {
public:
	ImFont* smallest_pixel;
	ImFont* esp_name;
	ImFont* esp_weapon;
	void BeginScene();
	void EndScene();
	void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
		window->DrawList->PathStroke(ImColor(col), false, thickness);
	}
	void two_sided_arc(float x, float y, float radius, float scale, ImColor col, float thickness) {
		arc(x, y, radius, -270, -90 - 90 * (scale * 2), col, thickness);
		arc(x, y, radius, -90 + 90 * (scale * 2), 90, col, thickness);
	}
	void PolyLine(const ImVec2* points, const int points_count, ImColor clr, bool closed, float thickness, ImColor fill) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddConvexPolyFilled(points, points_count, fill);
		window->DrawList->AddPolyline(points, points_count, clr, closed, thickness);
	}
	void never_arrows(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
		window->DrawList->PathStroke(ImColor(col), false, thickness);
	}
	void DrawLine(float x1, float y1, float x2, float y2, ImColor clr, float thickness, bool outline = false) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (outline)
			window->DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(0,0,0), thickness * 2);
		window->DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr, thickness);
	}
	void DrawCircle(float x, float y, float r, float s, ImColor color) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		////void ImDrawList::AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness)
		window->DrawList->AddCircle(ImVec2(x, y), r, color, 0, s);
	}
	void DrawFilledCircle(float x, float y, float r, ImColor color) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		////void ImDrawList::AddCircle(const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness)
		window->DrawList->AddCircleFilled(ImVec2(x, y), r+1, ImColor(0,0,0,255), 64);
		window->DrawList->AddCircleFilled(ImVec2(x, y), r, color, 64);
	}
	std::string string_To_UTF8(const std::string& str) {

		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
		return retStr;
	}
	void DrawString(float x, float y, ImColor color, int flags, int font, float size_text, const char* message, ...) {
		auto coord = ImVec2(x, y);
		std::string utf_8_1 = std::string(message);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		ImFont* FontType;
		float sizefont = 10.f;
		if (font != 3) {

			if (vars::stuff::font == 0)
			{
				FontType = DefaultFonts;
				sizefont = 13.f;
			}
			else if (vars::stuff::font == 1)
			{
				FontType = Small_fonts;
				sizefont = 10.f;
			}
			else if (vars::stuff::font == 3)
			{
				if (font == 1)
					FontType = DefaultFonts;
				else if (font == 2)
					FontType = Small_fonts;
				sizefont = size_text;
			}
		}
		else {
			FontType = DefaultFonts;
			sizefont = 13.f;
		}


		
		auto size = FontType->CalcTextSizeA(sizefont, FLT_MAX, 0, utf_8_2.c_str(), NULL);
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		auto coord_out = ImVec2{ coord.x, coord.y };
		ImColor outline_clr = ImColor(0, 0, 0, 255);
		int width = 0, height = 0;
		if (!(flags & render2::centered_x)) size.x = 0;
		if (!(flags & render2::centered_y)) size.y = 0;
		ImVec2 pos = ImVec2(coord.x - (size.x / 2), coord.y - (size.y / 2));
		if (flags & render2::outline) {
			if (vars::stuff::font == 1)
			{
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x + 1, pos.y), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x, pos.y - 1), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x - 1, pos.y), outline_clr, utf_8_2.c_str());
			}
			else
			{
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x + 1, pos.y), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x, pos.y - 1), outline_clr, utf_8_2.c_str());
				window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x - 1, pos.y), outline_clr, utf_8_2.c_str());
			}
		}
		if (flags & render2::dropShadow) {
			window->DrawList->AddText(FontType, sizefont, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
		}
		window->DrawList->AddText(FontType, sizefont, pos, color, utf_8_2.c_str());
	}
	void DrawTexture(ImVec2 pos, int flags, ImVec2 size, ImColor color,ImTextureID texture) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		auto coord = ImVec2(pos.x, pos.y);
		ImVec2 Size_ = ImVec2(size.x, size.y);
		if (!(flags & render2::centered_x)) Size_.x = 0;

		ImVec2 pos_ = ImVec2(coord.x - (Size_.x / 2), coord.y);

		window->DrawList->AddImage(texture, pos_, pos_ + size, ImVec2(0, 0), ImVec2(1, 1), color);

	}
	void DrawEspBox(Vector2 leftUpCorn, Vector2 rightDownCorn, ImColor clr, float width, bool outline = true) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
		ImVec2 max = ImVec2(min.x + rightDownCorn.x, min.y + rightDownCorn.y);

		window->DrawList->AddRect(min + ImVec2(0, 1), max + ImVec2(0, 1), ImColor(0, 0, 0, 255), 0.0F, -1, width);
		window->DrawList->AddRect(min + ImVec2(1, 0), max + ImVec2(1, 0), ImColor(0, 0, 0, 255), 0.0F, -1, width);
		window->DrawList->AddRect(min - ImVec2(0, 1), max - ImVec2(0, 1), ImColor(0, 0, 0, 255), 0.0F, -1, width);
		window->DrawList->AddRect(min - ImVec2(1, 0), max - ImVec2(1, 0), ImColor(0, 0, 0, 255), 0.0F, -1, width);
		window->DrawList->AddRect(min, max, clr, 0.0F, -1, width);
	}
	void DrawLineGradient(float x1, float y1, float x2, float y2, ImColor clr1, ImColor cl2, float thickness, bool flip) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (!flip)
			window->DrawList->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x1 + x2, y1 + y2), clr1, cl2, cl2, clr1);
		else
			window->DrawList->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x1 + x2, y1 + y2), clr1, clr1, cl2, cl2);
	}
	void Rect(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
	}
	void FilledRect(float x, float y, float w, float h, ImColor clr, float rounding=0.f, ImDrawFlags flags=0.f) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
	}
	void FilledRectGradient(float x, float y, float w, float h, ImColor clr, ImColor clr2, ImColor clr3, ImColor clr4) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), clr, clr2, clr3, clr4);
	}
	void FilledRect2(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(w, h), clr, rounding, flags);
	}
	void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr, float thickness) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr, thickness);
	}
	void TriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr);
	}
	void AddTriangleCsGo(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->PathLineTo(p1);
		window->DrawList->PathLineTo(p2);
		window->DrawList->PathLineTo(p3);
		window->DrawList->PathLineTo(p4);
		window->DrawList->PathFillConvex(col);
	}
	void QuadFilled(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, ImColor clr) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddQuadFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImVec2(x4, y4), clr);
	}
	ImColor PercentColor(float Num, float alpha = 1.0f)
	{
		float red, green, blue;
		if (Num < 0.5)
		{
			red = Num * 2.f * 255.f;
			green = 255.f;
			blue = 0.f;
		}
		else
		{
			red = 255.f;
			green = (2.f - 2.f * Num) * 255.f;
			blue = 0.f;
		}

		return ImColor(red / 255, green / 255, blue / 255, alpha);
	}

	void Progbar(Vector2 start, Vector2 end, float a, float b, float alpha)
	{
		FilledRect( start.x, start.y,  end.x, end.y + 1 , ImColor(0.f, 0.f, 0.f, alpha), 0, 0);
		if ((a / b) > 3) a = b;
		FilledRect(start.x + 1, start.y + 1, end.x * (a / b) - 1, end.y - 1, PercentColor(a / b, alpha), 0, 0);
	}
	//void Circle3D(Vector3 pos, Color clr, float radius, float penis = 0) {
	//	Vector3 prev = Vector3(pos.x + radius, pos.y, pos.z);
	//	for (float num = 0.f; num < 6.2831855f; num += 0.05f) {

	//		float val_x = cos(num) * radius;
	//		float val_z = sin(num) * radius;
	//		Vector3 newPos = Vector3(pos.x + val_x, pos.y + penis, pos.z + val_z);

	//		DDraw::Line(prev, newPos, clr, 0.01, false, true);

	//		prev = newPos;
	//	}
	//}
	void DrawRing3D(Vector3 pos, float radius, float points, ImColor color1, ImColor color2, float thickness, float prog, bool fl)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		static float Step = (M_PI * 2.0f) / (points);
		std::vector<ImVec2> point;
		for (float lat = 0.f; lat <= M_PI * 2.0f; lat += Step)
		{
			const auto& point3d = Vector3(sin(lat), 0.f, 1) * radius;
			float val_x = cos(lat) * radius;
		    float val_z = sin(lat) * radius;
			Vector3 newPos = Vector3(pos.x + val_x, pos.y, pos.z + val_z);

			Vector2 point2d;
			if (utils::w2s(newPos, point2d))
				point.push_back(ImVec2(point2d.x, point2d.y));
		}
		//if(fl)
		window->DrawList->AddConvexPolyFilled(point.data(), point.size(), color2);
		window->DrawList->AddPolyline(point.data(), max(0, point.size() * prog), color1, prog == 1.f, thickness);
	}
	void RadialGradient3D(Vector3 pos, float radius, ImColor in, ImColor out, bool one) {
		ImVec2 center; Vector2 g_pos;
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		// Use arc with automatic segment count

		utils::w2s(Vector3(pos), g_pos);
		center = ImVec2(g_pos.x + (radius / 2.f), g_pos.y + (radius / 2.f));
		window->DrawList->_PathArcToFastEx(center, radius, 0, 48, 0);
		const int count = window->DrawList->_Path.Size - 1;
		static float step = (M_PI * 2.0f) / (count+1);
		std::vector<ImVec2> point;
		for (float lat = 0.f; lat <= M_PI * 2.0f; lat += step)
		{
			const auto& point3d = Vector3(sin(lat), cos(lat), 1) * radius;
			float val_x = cos(lat) * radius;
			float val_z = sin(lat) * radius;
			Vector3 newPos = Vector3(pos.x + val_x, pos.y, pos.z + val_z);

			Vector2 point2d;
			if (utils::w2s(newPos, point2d))
				point.push_back(ImVec2(point2d.x, point2d.y));
		}
		if (in.Value.w == 0 && out.Value.w == 0 || radius < 0.5f || point.size() < count + 1)
			return;

		unsigned int vtx_base = window->DrawList->_VtxCurrentIdx;
		window->DrawList->PrimReserve(count * 3, count + 1);

		// Submit vertices
		const ImVec2 uv = window->DrawList->_Data->TexUvWhitePixel;
		window->DrawList->PrimWriteVtx(center, uv, in);
		for (int n = 0; n < count; n++)
			window->DrawList->PrimWriteVtx(point[n + 1], uv, out);

		// Submit a fan of triangles
		for (int n = 0; n < count; n++)
		{
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
		}
		window->DrawList->_Path.Size = 0;
	}
#ifndef IM_DRAWLIST_ARCFAST_TABLE_SIZE
#define IM_DRAWLIST_ARCFAST_TABLE_SIZE                          48 // Number of samples in lookup table.
#endif
#define IM_DRAWLIST_ARCFAST_SAMPLE_MAX                          IM_DRAWLIST_ARCFAST_TABLE_SIZE // Sample index _PathArcToFastEx() for 360 angle.
	void AddRadialGradient(const ImVec2& center, float radius, ImU32 col_in, ImU32 col_out) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		if (((col_in | col_out) & IM_COL32_A_MASK) == 0 || radius < 0.5f) return;
		window->DrawList->PathArcToFast(center, radius, 0, IM_DRAWLIST_ARCFAST_SAMPLE_MAX);
		const int count = window->DrawList->_Path.Size - 1;
		unsigned int vtx_base = window->DrawList->_VtxCurrentIdx;
		window->DrawList->PrimReserve(count * 3, count + 1);
		const ImVec2 uv = window->DrawList->_Data->TexUvWhitePixel;
		window->DrawList->PrimWriteVtx(center, uv, col_in);
		for (int n = 0; n < count; n++) window->DrawList->PrimWriteVtx(window->DrawList->_Path[n], uv, col_out);
		for (int n = 0; n < count; n++) {
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
			window->DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
		}
		window->DrawList->_Path.Size = 0;
	}

	void CircleFilled(float x1, float y1, float radius, ImColor col, int segments) {
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddCircleFilled(ImVec2(x1, y1), radius, col, segments);
	}
};
inline ImGuiRendering* g_Render;