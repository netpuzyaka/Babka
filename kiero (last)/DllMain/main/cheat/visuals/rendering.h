
void DrawLine(float x1, float y1, float x2, float y2, ImColor clr, float thickness, bool outline = false) {
	if (outline)
		DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(0, 0, 0), thickness * 1.5);
	DrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr, thickness);
}

void DrawLine_(ImVec2 pos, ImVec2 Size, ImColor clr, float thickness, bool outline = false) {
	if (outline)
		DrawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(Size.x, Size.y), ImColor(0, 0, 0), thickness * 2);
	DrawList->AddLine(ImVec2(pos.x, pos.y), ImVec2(Size.x, Size.y), clr, thickness);
}

void FilledRect(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
	DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), clr, rounding, flags);
}
void Rect(float x, float y, float w, float h, ImColor clr, float rounding, ImDrawFlags flags) {
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
	for (int n = 0; n < count; n++) DrawList->PrimWriteVtx(DrawList->_Path[n], uv, col_out);
	for (int n = 0; n < count; n++) {
		DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base));
		DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + n));
		DrawList->PrimWriteIdx((ImDrawIdx)(vtx_base + 1 + ((n + 1) % count)));
	}
	DrawList->_Path.Size = 0;
}
float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(settings::screen_size.x / 2, settings::screen_size.y / 2), ScreenPos);
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
Vector2 CosTanSinLineH(float flAngle, float range, int x, int y, int LineLength) {
	float kakahka = flAngle;
	kakahka += 45.f;
	float flYaw = (kakahka) * (PI / 180.0);
	float viewcosyawzzzzzzz = cos(flYaw);
	float viewsinyawzzzzzzz = sin(flYaw);
	float x2 = range * (-viewcosyawzzzzzzz) + range * viewsinyawzzzzzzz;
	float y2 = range * (-viewcosyawzzzzzzz) - range * viewsinyawzzzzzzz;
	int posonscreenX = x + int(x2 / range * (LineLength));
	int posonscreenY = y + int(y2 / range * (LineLength));
	return Vector2(posonscreenX, posonscreenY);
}
void TriangleFilled(float x1, float y1, float x2, float y2, float x3, float y3, ImColor clr) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	DrawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), clr);
}

void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {
	DrawList->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
	DrawList->PathStroke(ImColor(col), false, thickness);
}
void DrawString(float x, float y, ImColor color, const char* message, ...) {
	auto coord = ImVec2(x, y);
	std::string utf_8_1 = std::string(message);
	ImFont* esp_font = font::default_font;

	if (settings::misc::font == 0) {
		esp_font = font::default_font;
	}
	else if (settings::misc::font == 1) {
		esp_font = font::good_font;
	}
	else if (settings::misc::font == 2) {
		esp_font = font::roboto;
	}
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	auto size = esp_font->CalcTextSizeA(12.f, FLT_MAX, 0, utf_8_2.c_str(), NULL);

	auto coord_out = ImVec2{ coord.x, coord.y };
	ImColor outline_clr = ImColor(0, 0, 0, 255);
	int width = 0, height = 0;
	ImVec2 pos = ImVec2(coord.x - (size.x / 2), coord.y - (size.y / 2));
	DrawList->AddText(esp_font, 12.f, ImVec2(pos.x, pos.y + 1), outline_clr, utf_8_2.c_str());
	DrawList->AddText(esp_font, 12.f, ImVec2(pos.x + 1, pos.y), outline_clr, utf_8_2.c_str());
	DrawList->AddText(esp_font, 12.f, ImVec2(pos.x, pos.y - 1), outline_clr, utf_8_2.c_str());
	DrawList->AddText(esp_font, 12.f, ImVec2(pos.x - 1, pos.y), outline_clr, utf_8_2.c_str());
	DrawList->AddText(esp_font, 12.f, pos, color, utf_8_2.c_str());
}
void DrawCircle(float x, float y, float r, float s, ImColor color) {
	DrawList->AddCircle(ImVec2(x, y), r, color, 0, s);
}

typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, ImColor color) {
	CBounds bounds = CBounds();
	if (player->IsDucked()) {
		bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasPlayerFlag(PlayerFlags::Wounded) || player->HasPlayerFlag(PlayerFlags::Sleeping)) {
			bounds.center = player->GetBoneByID(pelvis);
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = player->GetBoneByID(l_foot).midPoint(player->GetBoneByID(r_foot)) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}
	float y = Math::EulerAngles(player->eyes()->rotation()).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (!player->is_dead())
	{
		if (utils::w2s(frontTopLeft, frontTopLeft_2d) &&
			utils::w2s(frontTopRight, frontTopRight_2d) &&
			utils::w2s(frontBottomLeft, frontBottomLeft_2d) &&
			utils::w2s(frontBottomRight, frontBottomRight_2d) &&
			utils::w2s(backTopLeft, backTopLeft_2d) &&
			utils::w2s(backTopRight, backTopRight_2d) &&
			utils::w2s(backBottomLeft, backBottomLeft_2d) &&
			utils::w2s(backBottomRight, backBottomRight_2d)) {
			DrawLine_({ frontTopLeft_2d.x, frontTopLeft_2d.y }, { frontTopRight_2d.x, frontTopRight_2d.y }, color, 1.5f, true);
			DrawLine_({ frontTopRight_2d.x, frontTopRight_2d.y }, { frontBottomRight_2d.x, frontBottomRight_2d.y }, color, 1.5f, true);
			DrawLine_({ frontBottomRight_2d.x, frontBottomRight_2d.y }, { frontBottomLeft_2d.x, frontBottomLeft_2d.y }, color, 1.5f, true);
			DrawLine_({ frontBottomLeft_2d.x, frontBottomLeft_2d.y }, { frontTopLeft_2d.x, frontTopLeft_2d.y }, color, 1.5f, true);
			DrawLine_({ backTopLeft_2d.x, backTopLeft_2d.y }, { backTopRight_2d.x, backTopRight_2d.y }, color, 1.5f, true);
			DrawLine_({ backTopRight_2d.x, backTopRight_2d.y }, { backBottomRight_2d.x, backBottomRight_2d.y }, color, 1.5f, true);
			DrawLine_({ backBottomRight_2d.x, backBottomRight_2d.y }, { backBottomLeft_2d.x, backBottomLeft_2d.y }, color, 1.5f, true);
			DrawLine_({ backBottomLeft_2d.x, backBottomLeft_2d.y }, { backTopLeft_2d.x, backTopLeft_2d.y }, color, 1.5f, true);
			DrawLine_({ frontTopLeft_2d.x, frontTopLeft_2d.y }, { backTopLeft_2d.x, backTopLeft_2d.y }, color, 1.5f, true);
			DrawLine_({ frontTopRight_2d.x, frontTopRight_2d.y }, { backTopRight_2d.x, backTopRight_2d.y }, color, 1.5f, true);
			DrawLine_({ frontBottomRight_2d.x, frontBottomRight_2d.y }, { backBottomRight_2d.x, backBottomRight_2d.y }, color, 1.5f, true);
			DrawLine_({ frontBottomLeft_2d.x, frontBottomLeft_2d.y }, { backBottomLeft_2d.x, backBottomLeft_2d.y }, color, 1.5f, true);
		}
	}
}

void DrawEspBox(Vector2 leftUpCorn, Vector2 rightDownCorn, ImColor clr, float width) {
	ImVec2 min = ImVec2(leftUpCorn.x, leftUpCorn.y);
	ImVec2 max = ImVec2(rightDownCorn.x, rightDownCorn.y);
	DrawList->AddRect(min, max, ImColor(0, 0, 0, 255), 0.0F, -1, width + 1.f);
	DrawList->AddRect(min, max, clr, 0.0F, -1, width);
}
void DrawCornerBox(ImVec2 min, ImVec2 max, ImColor color) {

	DrawLine(min.x, min.y, min.x + (max.x - min.x) / 4.f, min.y, color, 2.0f, true);
	DrawLine(max.x, min.y, max.x - (max.x - min.x) / 4.f, min.y, color, 2.0f, true);

	DrawLine(min.x, min.y, min.x, min.y + (max.y - min.y) / 7.f, color, 2.0f, true);
	DrawLine(min.x, max.y, min.x, max.y - (max.y - min.y) / 7.f, color, 2.0f, true);

	DrawLine(max.x, min.y, max.x, min.y + (max.y - min.y) / 7.f, color, 2.0f, true);
	DrawLine(max.x, max.y, max.x, max.y - (max.y - min.y) / 7.f, color, 2.0f, true);

	DrawLine(min.x, max.y, min.x + (max.x - min.x) / 4.f, max.y, color, 2.0f, true);
	DrawLine(max.x, max.y, max.x - (max.x - min.x) / 4.f, max.y, color, 2.0f, true);

}

class c_texture2
{
public:
	ID3D11ShaderResourceView* texture = nullptr;
	void* item_byte = 0;
	int size = 0;

};

ID3D11ShaderResourceView* Logotype2 = nullptr;

class c_texture_cache2
{
private:
	std::vector<c_texture2> texture_cache{};
	ID3D11ShaderResourceView* create_texture(ID3D11Device* device, LPCVOID byte, int size)
	{

		static ID3D11ShaderResourceView* tex = nullptr;
		D3DX11_IMAGE_LOAD_INFO iInfo;
		ID3DX11ThreadPump* threadPump{ nullptr };
		// From Bytes
		D3DX11CreateShaderResourceViewFromMemory(device, byte, size, &iInfo, threadPump, &tex, 0);
		return tex;
	}
public:
	c_texture2 get_texture(void* byte, int size)
	{
		for (auto texture : texture_cache)
			if (texture.item_byte == byte)
				return texture; // check if the texture's already cached

		c_texture2 ret;
		ret.item_byte = byte;
		ret.texture = create_texture(pDevice, byte, size);

		if (!ret.texture)
			return ret; // this issue sorts itself out

		texture_cache.push_back(ret); // put the new texture into the cache

		return ret; // return the texture

	}
}; inline c_texture_cache2 texture_cache_byte;

class c_getitemicon
{
public:
	ImVec2 size = ImVec2(0, 0);
	std::string name = "";
	c_texture2 texture;

}; inline c_getitemicon getitem;
ImColor perc_col(float Num, float alpha = 1.0f)
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


void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, ImColor color) {
	if (boolean) {
		if (strstr(buff, substring)) {

			Vector2 screen_Pos;
			if (ObjectClass) {
				if (utils::w2s(reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position(), screen_Pos)) {
					if ((int)Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position()) <= drawDistance) {
						std::string string;
						char buf[256] = { 0 }; sprintf_s(buf, "%ls", targettext);
						string = buf;
						if (showDistance) {
							std::string string2;
							char buf2[256] = { 0 }; sprintf_s(buf2, "[ %.1fm ]", Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform()->position()));
							string += buf2;
						}
						DrawString(screen_Pos.x, screen_Pos.y, color, string.c_str());
					}
				}
			}
		}
	}
}
void Progbar(Vector2 start, Vector2 end, float a, float b)
{

	FilledRect(start.x, start.y, end.x, end.y + 1, ImColor(8, 8, 8), 3, ImDrawFlags_RoundCornersAll);

	Rect(start.x, start.y, end.x, end.y + 1, ImColor(25, 25, 25, 255), 3, ImDrawFlags_RoundCornersAll);
	if ((a / b) > 3)
		a = b;
	if (a != 0)
		FilledRect(start.x + 1, start.y + 1, end.x * (a / b) - 1, end.y - 1, ImColor(0, 255, 0, 255), 3, ImDrawFlags_RoundCornersAll);
}
c_getitemicon get_icon_name(BasePlayer* player) {
	c_getitemicon item;
	Item* ActWeapon = player->GetHeldItem();
	switch (ActWeapon->info_()->itemid())
	{
	case 1079279582:

		item.texture = texture_cache_byte.get_texture(medicalsyringe, sizeof(medicalsyringe));
		item.name = ("medical-syringe");
		item.size = ImVec2(30, 30);
		break;
	case -2072273936:

		item.texture = texture_cache_byte.get_texture(bandage, sizeof(bandage));
		item.name = ("bandage");
		item.size = ImVec2(30, 30);
		break;
	case 254522515:

		item.texture = texture_cache_byte.get_texture(heal, sizeof(heal));
		item.name = ("largemedkit");
		item.size = ImVec2(30, 30);
		break;
	case 1540934679:

		item.texture = texture_cache_byte.get_texture(spwooden, sizeof(spwooden));
		item.name = ("spear.wooden");
		item.size = ImVec2(30, 30);
		break;
	case 1602646136:

		item.texture = texture_cache_byte.get_texture(spstone, sizeof(spstone));
		item.name = ("spear.stone");
		item.size = ImVec2(30, 30);
		break;
	case 1545779598:
		item.texture = texture_cache_byte.get_texture(ak47, sizeof(ak47));
		item.name = ("ak47");
		item.size = ImVec2(30, 30);
		break;
	case -139037392:
		item.texture = texture_cache_byte.get_texture(ak47, sizeof(ak47));
		item.name = ("ak47");
		item.size = ImVec2(30, 30);
		break;
	case -1335497659:
		item.texture = texture_cache_byte.get_texture(ak47, sizeof(ak47));
		item.name = ("ak47");
		item.size = ImVec2(30, 30);
		break;
	case 1318558775:

		item.texture = texture_cache_byte.get_texture(mp5, sizeof(mp5));
		item.name = ("mp5");
		item.size = ImVec2(30, 30);
		break;
	case 963906841:

		item.texture = texture_cache_byte.get_texture(rock, sizeof(rock));
		item.name = ("rock");
		item.size = ImVec2(30, 30);
		break;
	case 1588298435:
		item.texture = texture_cache_byte.get_texture(boltactionrifle, sizeof(boltactionrifle));
		item.name = ("bolt-action-rifle");
		item.size = ImVec2(30, 30);
		break;
	case 143803535:
		item.texture = texture_cache_byte.get_texture(f1, sizeof(f1));
		item.name = ("grenade.f1");
		item.size = ImVec2(30, 30);
		break;
	case 1840822026:
		item.texture = texture_cache_byte.get_texture(bean, sizeof(bean));
		item.name = ("grenade.beancan");
		item.size = ImVec2(30, 30);
		break;
	case 1965232394:
		item.texture = texture_cache_byte.get_texture(crossbow, sizeof(crossbow));
		item.name = ("crossbow");
		item.size = ImVec2(30, 30);
		break;
	case -41440462:
		item.texture = texture_cache_byte.get_texture(spas12, sizeof(spas12));
		item.name = ("spas-12");
		item.size = ImVec2(30, 30);
		break;
	case -765183617:
		item.texture = texture_cache_byte.get_texture(doublebarrel, sizeof(doublebarrel));
		item.name = ("double-barrel");
		item.size = ImVec2(30, 30);
		break;
	case 884424049:
		item.texture = texture_cache_byte.get_texture(compoundbow, sizeof(compoundbow));
		item.name = ("compound-bow");
		item.size = ImVec2(30, 30);
		break;
	case 1443579727:
		item.texture = texture_cache_byte.get_texture(huntingbow, sizeof(huntingbow));
		item.name = ("hunting-bow");
		item.size = ImVec2(30, 30);
		break;
	case -852563019:
		item.texture = texture_cache_byte.get_texture(m92, sizeof(m92));
		item.name = ("m92");
		item.size = ImVec2(30, 30);
		break;
	case -1758372725:
		item.texture = texture_cache_byte.get_texture(thompson, sizeof(thompson));
		item.name = ("thompson");
		item.size = ImVec2(30, 30);
		break;
	case -904863145:
		item.texture = texture_cache_byte.get_texture(sar, sizeof(sar));
		item.name = ("sar");
		item.size = ImVec2(30, 30);
		break;
	case 818877484:
		item.texture = texture_cache_byte.get_texture(p250, sizeof(p250));
		item.name = ("p250");
		item.size = ImVec2(30, 30);
		break;
	case 795371088:
		item.texture = texture_cache_byte.get_texture(pumpshotgun, sizeof(pumpshotgun));
		item.name = ("pump-shotgun");
		item.size = ImVec2(30, 30);
		break;
	case 649912614:
		item.texture = texture_cache_byte.get_texture(revolver, sizeof(revolver));
		item.name = ("revolver");
		item.size = ImVec2(30, 30);
		break;
	case 1373971859:
		item.texture = texture_cache_byte.get_texture(python, sizeof(python));
		item.name = ("python");
		item.size = ImVec2(30, 30);
		break;
	case -1214542497:
		item.texture = texture_cache_byte.get_texture(hmlmg, sizeof(hmlmg));
		item.name = ("hmlmg");
		item.size = ImVec2(30, 30);
		break;
	case -75944661:
		item.texture = texture_cache_byte.get_texture(eoka, sizeof(eoka));
		item.name = ("eoka");
		item.size = ImVec2(30, 30);
		break;
	case 1953903201:
		item.texture = texture_cache_byte.get_texture(nailgun, sizeof(nailgun));
		item.name = ("pistol.nailgun");
		item.size = ImVec2(30, 30);
		break;
	case -1367281941:
		item.texture = texture_cache_byte.get_texture(waterpipe, sizeof(waterpipe));
		item.name = ("shotgun.waterpipe");
		item.size = ImVec2(30, 30);
		break;
	case 1248356124:
		item.texture = texture_cache_byte.get_texture(c4, sizeof(c4));
		item.name = ("explosive.timed");
		item.size = ImVec2(30, 30);
		break;
	case -1878475007:
		item.texture = texture_cache_byte.get_texture(satchel, sizeof(satchel));
		item.name = ("explosive.satchel");
		item.size = ImVec2(30, 30);
		break;
	case 442886268:
		item.texture = texture_cache_byte.get_texture(rocket_lanucher, sizeof(rocket_lanucher));
		item.name = ("rocket.launcher");
		item.size = ImVec2(30, 30);
		break;
	case 1796682209:
		item.texture = texture_cache_byte.get_texture(customsmg, sizeof(customsmg));
		item.name = ("custom-smg");
		item.size = ImVec2(30, 30);
		break;
	case -1812555177:
		item.texture = texture_cache_byte.get_texture(lr300, sizeof(lr300));
		item.name = ("lr300");
		item.size = ImVec2(30, 30);
		break;
	case -2069578888:
		item.texture = texture_cache_byte.get_texture(m249, sizeof(m249));
		item.name = ("m249");
		item.size = ImVec2(30, 30);
		break;
	case 28201841:
		item.texture = texture_cache_byte.get_texture(m39, sizeof(m39));
		item.name = ("m39");
		item.size = ImVec2(30, 30);
		break;
	case 935606207:
		item.texture = texture_cache_byte.get_texture(minigun, sizeof(minigun));
		item.name = ("minigun");
		item.size = ImVec2(30, 30);
		break;
	case 703057617:
		item.texture = texture_cache_byte.get_texture(military_flame, sizeof(military_flame));
		item.name = ("military flame");
		item.size = ImVec2(30, 30);
		break;
	case -218009552:
		item.texture = texture_cache_byte.get_texture(Homing_Missile_Launcher, sizeof(Homing_Missile_Launcher));
		item.name = ("homing missile launcher");
		item.size = ImVec2(30, 30);
		break;
	case 678698219:
		item.texture = texture_cache_byte.get_texture(M4_Shotgun, sizeof(M4_Shotgun));
		item.name = ("M4 shotgun");
		item.size = ImVec2(30, 30);
		break;
	case 1090916276:
		item.texture = texture_cache_byte.get_texture(Pitchfork, sizeof(Pitchfork));
		item.name = ("Pitchfork");
		item.size = ImVec2(30, 30);
		break;
	case 722955039:
		item.texture = texture_cache_byte.get_texture(Water_Gun, sizeof(Water_Gun));
		item.name = ("Water Gun");
		item.size = ImVec2(30, 30);
		break;
	case -885833256:
		item.texture = texture_cache_byte.get_texture(Vampire_Stake, sizeof(Vampire_Stake));
		item.name = ("Vampire Stake");
		item.size = ImVec2(30, 30);
		break;
	case 1326180354:
		item.texture = texture_cache_byte.get_texture(Salvaged_Sword, sizeof(Salvaged_Sword));
		item.name = ("Salvaged Sword");
		item.size = ImVec2(30, 30);
		break;
	case 1491189398:
		item.texture = texture_cache_byte.get_texture(Paddle, sizeof(Paddle));
		item.name = ("Paddle");
		item.size = ImVec2(30, 30);
		break;
	case -1137865085:
		item.texture = texture_cache_byte.get_texture(Machete, sizeof(Machete));
		item.name = ("Machete");
		item.size = ImVec2(30, 30);
		break;
	case -1469578201:
		item.texture = texture_cache_byte.get_texture(Longsword, sizeof(Longsword));
		item.name = ("Longsword");
		item.size = ImVec2(30, 30);
		break;
	case -1215753368:
		item.texture = texture_cache_byte.get_texture(Flame_Thrower, sizeof(Flame_Thrower));
		item.name = ("Flame Thrower");
		item.size = ImVec2(30, 30);
		break;
	case 1789825282:
		item.texture = texture_cache_byte.get_texture(Candy_Cane_Club, sizeof(Candy_Cane_Club));
		item.name = ("Candy Cane Club");
		item.size = ImVec2(30, 30);
		break;
	case 1814288539:
		item.texture = texture_cache_byte.get_texture(Bone_Knife, sizeof(Bone_Knife));
		item.name = ("Bone Knife");
		item.size = ImVec2(30, 30);
		break;
	case 1711033574:
		item.texture = texture_cache_byte.get_texture(Bone_Club, sizeof(Bone_Club));
		item.name = ("Bone Club");
		item.size = ImVec2(30, 30);
		break;
	case -2073432256:
		item.texture = texture_cache_byte.get_texture(Skinning_Knife, sizeof(Skinning_Knife));
		item.name = ("Skinning Knife");
		item.size = ImVec2(30, 30);
		break;
	case 1103488722:
		item.texture = texture_cache_byte.get_texture(Snowball_Gun, sizeof(Snowball_Gun));
		item.name = ("Snowball Gun");
		item.size = ImVec2(30, 30);
		break;
	case -1517740219:
		item.texture = texture_cache_byte.get_texture(Speargun, sizeof(Speargun));
		item.name = ("Speargun");
		item.size = ImVec2(30, 30);
		break;
	case -1815301988:
		item.texture = texture_cache_byte.get_texture(Water_Pistol, sizeof(Water_Pistol));
		item.name = ("Water Pistol");
		item.size = ImVec2(30, 30);
		break;
	case 2040726127:
		item.texture = texture_cache_byte.get_texture(Combat_Knife, sizeof(Combat_Knife));
		item.name = ("Combat Knife");
		item.size = ImVec2(30, 30);
		break;
	case -936921910:
		item.texture = texture_cache_byte.get_texture(Flashbang, sizeof(Flashbang));
		item.name = ("Flashbang");
		item.size = ImVec2(30, 30);
		break;
	case 1914691295:
		item.texture = texture_cache_byte.get_texture(Prototype17, sizeof(Prototype17));
		item.name = ("Prototype 17");
		item.size = ImVec2(30, 30);
		break;
	case -194509282:
		item.texture = texture_cache_byte.get_texture(Butcher_Knife, sizeof(Butcher_Knife));
		item.name = ("Butcher Knife");
		item.size = ImVec2(30, 30);
		break;
	case -778367295:
		item.texture = texture_cache_byte.get_texture(L96_Rifle, sizeof(L96_Rifle));
		item.name = ("L96 Rifle");
		item.size = ImVec2(30, 30);
		break;
	case -1966748496:
		item.texture = texture_cache_byte.get_texture(Mace, sizeof(Mace));
		item.name = ("Mace");
		item.size = ImVec2(30, 30);
		break;
	case 1556365900:
		item.texture = texture_cache_byte.get_texture(Molotov_Cocktail, sizeof(Molotov_Cocktail));
		item.name = ("Molotov Cocktail");
		item.size = ImVec2(30, 30);
		break;
	case -1978999529:
		item.texture = texture_cache_byte.get_texture(Salvaged_Cleaver, sizeof(Salvaged_Cleaver));
		item.name = ("Salvaged Cleaver");
		item.size = ImVec2(30, 30);
		break;
	case -363689972:
		item.texture = texture_cache_byte.get_texture(Salvaged_Cleaver, sizeof(Salvaged_Cleaver));
		item.name = ("Snowball");
		item.size = ImVec2(30, 30);
		break;
	case -1262185308:
		item.texture = texture_cache_byte.get_texture(Binoculars, sizeof(Binoculars));
		item.name = ("Binoculars");
		item.size = ImVec2(30, 30);
		break;
	case -1707425764:
		item.texture = texture_cache_byte.get_texture(Fishing_Tackle, sizeof(Fishing_Tackle));
		item.name = ("Fishing Tackle");
		item.size = ImVec2(30, 30);
		break;
	case 999690781:
		item.texture = texture_cache_byte.get_texture(Geiger_Counter, sizeof(Geiger_Counter));
		item.name = ("Geiger Counter");
		item.size = ImVec2(30, 30);
		break;
	case -2001260025:
		item.texture = texture_cache_byte.get_texture(Instant_Camera, sizeof(Instant_Camera));
		item.name = ("Instant Camera");
		item.size = ImVec2(30, 30);
		break;
	case 596469572:
		item.texture = texture_cache_byte.get_texture(RF_Transmitter, sizeof(RF_Transmitter));
		item.name = ("RF Transmitter");
		item.size = ImVec2(30, 30);
		break;
	case -1780802565:
		item.texture = texture_cache_byte.get_texture(Salvaged_Icepick, sizeof(Salvaged_Icepick));
		item.name = ("Salvaged Icepick");
		item.size = ImVec2(30, 30);
		break;
	case -596876839:
		item.texture = texture_cache_byte.get_texture(Spray_Can, sizeof(Spray_Can));
		item.name = ("Spray Can");
		item.size = ImVec2(30, 30);
		break;
	case 1975934948:
		item.texture = texture_cache_byte.get_texture(Survey_Charge, sizeof(Survey_Charge));
		item.name = ("Survey Charge");
		item.size = ImVec2(30, 30);
		break;
	case 1973165031:
		item.texture = texture_cache_byte.get_texture(Birthday_Cake, sizeof(Birthday_Cake));
		item.name = ("Birthday Cake");
		item.size = ImVec2(30, 30);
		break;
	case 304481038:
		item.texture = texture_cache_byte.get_texture(Flare, sizeof(Flare));
		item.name = ("Flare");
		item.size = ImVec2(30, 30);
		break;
	case 200773292:
		item.texture = texture_cache_byte.get_texture(Hammer, sizeof(Hammer));
		item.name = ("Hammer");
		item.size = ImVec2(30, 30);
		break;
	case 1488979457:
		item.texture = texture_cache_byte.get_texture(Jackhammer, sizeof(Jackhammer));
		item.name = ("Jackhammer");
		item.size = ImVec2(30, 30);
		break;
	case -1583967946:
		item.texture = texture_cache_byte.get_texture(Stone_Hatchet, sizeof(Stone_Hatchet));
		item.name = ("Stone Hatchet");
		item.size = ImVec2(30, 30);
		break;
	case -1316706473:
		item.texture = texture_cache_byte.get_texture(Camera, sizeof(Camera));
		item.name = ("Camera");
		item.size = ImVec2(30, 30);
		break;
	case -196667575:
		item.texture = texture_cache_byte.get_texture(Flashlight, sizeof(Flashlight));
		item.name = ("Flashlight");
		item.size = ImVec2(30, 30);
		break;
	case 1569882109:
		item.texture = texture_cache_byte.get_texture(Handmade_Fishing_Rod, sizeof(Handmade_Fishing_Rod));
		item.name = ("Handmade Fishing Rod");
		item.size = ImVec2(30, 30);
		break;
	case 1168856825:
		item.texture = texture_cache_byte.get_texture(Metal_Detector, sizeof(Metal_Detector));
		item.name = ("Metal Detector");
		item.size = ImVec2(30, 30);
		break;
	case -262590403:
		item.texture = texture_cache_byte.get_texture(Salvaged_Axe, sizeof(Salvaged_Axe));
		item.name = ("Salvaged Axe");
		item.size = ImVec2(30, 30);
		break;
	case -1536855921:
		item.texture = texture_cache_byte.get_texture(Shovel, sizeof(Shovel));
		item.name = ("Shovel");
		item.size = ImVec2(30, 30);
		break;
	case 171931394:
		item.texture = texture_cache_byte.get_texture(Stone_Pickaxe, sizeof(Stone_Pickaxe));
		item.name = ("Stone Pickaxe");
		item.size = ImVec2(30, 30);
		break;
	case 795236088:
		item.texture = texture_cache_byte.get_texture(Torch, sizeof(Torch));
		item.name = ("Torch");
		item.size = ImVec2(30, 30);
		break;
	case 1104520648:
		item.texture = texture_cache_byte.get_texture(Chainsaw, sizeof(Chainsaw));
		item.name = ("Chainsaw");
		item.size = ImVec2(30, 30);
		break;
	case 1803831286:
		item.texture = texture_cache_byte.get_texture(Mod_Tool_Gun, sizeof(Mod_Tool_Gun));
		item.name = ("Garry's Mod Tool Gun");
		item.size = ImVec2(30, 30);
		break;
	case -1252059217:
		item.texture = texture_cache_byte.get_texture(Hatchet, sizeof(Hatchet));
		item.name = ("Hatchet");
		item.size = ImVec2(30, 30);
		break;
	case -1302129395:
		item.texture = texture_cache_byte.get_texture(Pickaxe, sizeof(Pickaxe));
		item.name = ("Pickaxe");
		item.size = ImVec2(30, 30);
		break;
	case -1506397857:
		item.texture = texture_cache_byte.get_texture(Salvaged_Hammer, sizeof(Salvaged_Hammer));
		item.name = ("Salvaged Hammer");
		item.size = ImVec2(30, 30);
		break;
	case 1263920163:
		item.texture = texture_cache_byte.get_texture(Smoke_Grenade, sizeof(Smoke_Grenade));
		item.name = ("Smoke Grenade");
		item.size = ImVec2(30, 30);
		break;
	case 1397052267:
		item.texture = texture_cache_byte.get_texture(Supply_Signal, sizeof(Supply_Signal));
		item.name = ("Supply Signal");
		item.size = ImVec2(30, 30);
		break;
	case 1424075905:
		item.texture = texture_cache_byte.get_texture(Water_Bucket, sizeof(Water_Bucket));
		item.name = ("Water Bucket");
		item.size = ImVec2(30, 30);
		break;
	}
	return item;
}
void DrawTexture(ImVec2 pos, ImVec2 size, ImColor color, ImTextureID texture) {
	auto coord = ImVec2(pos.x, pos.y);
	ImVec2 Size_ = ImVec2(size.x, size.y);
	/*if (!(flags & render2::centered_x)) Size_.x = 0;*/

	ImVec2 pos_ = ImVec2(coord.x - (Size_.x / 2), coord.y);

	DrawList->AddImage(texture, pos_, pos_ + size, ImVec2(0, 0), ImVec2(1, 1), color);
}
