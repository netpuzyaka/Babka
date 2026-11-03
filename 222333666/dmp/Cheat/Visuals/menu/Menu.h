#include <vector>
#include <algorithm>
#include <windows.h>
#include <urlmon.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <Wininet.h>
#pragma comment(lib, "wininet.lib")
using namespace std;
string replaceAll(string subject, const string& search,
    const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

//string CheckLink(string URL) {
//    HINTERNET interwebs = InternetOpenA( ("Mozilla/5.0"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
//    HINTERNET urlFile;
//    string rtn;
//    if (interwebs) {
//        urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
//        if (urlFile) {
//            char buffer[2000];
//            DWORD bytesRead;
//            do {
//                InternetReadFile(urlFile, buffer, 2000, &bytesRead);
//                rtn.append(buffer, bytesRead);
//                memset(buffer, 0, 2000);
//            } while (bytesRead);
//            InternetCloseHandle(interwebs);
//            InternetCloseHandle(urlFile);
//            string p = replaceAll(rtn, "|n", "\r\n");
//            return p;
//        }
//    }
//    InternetCloseHandle(interwebs);
//    string p = replaceAll(rtn, "|n", "\r\n");
//    return p;
//}
#pragma comment(lib, "urlmon.lib")
namespace Gui {
    static ImVec2					Size = { 550 , 416 };
    int                             SidebarSize = 46;
    int                             SidebarId = 0;
}

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA2 ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

#define get_keycode_name(vk, name)\
switch (vk) {\
case VK_CONTROL: name = "control"; break;\
case VK_SHIFT: name = "shift"; break;\
case VK_LSHIFT: name = "shift"; break;\
case VK_MENU: name = "alt"; break;\
case VK_TAB: name = "tab"; break;\
case VK_LBUTTON: name = "mouse 1"; break;\
case VK_RBUTTON: name = "mouse 2"; break;\
case VK_MBUTTON: name = "mouse 3"; break;\
case VK_XBUTTON1: name = "mouse 4"; break;\
case VK_XBUTTON2: name = "mouse 5"; break;\
case VK_PRIOR: name = "page up"; break;\
case VK_NEXT: name = "page down"; break;\
case VK_END: name = "end"; break;\
case VK_HOME: name = "home"; break;\
case VK_LEFT: name = "left arrow"; break;\
case VK_UP: name = "up arrow"; break;\
case VK_RIGHT: name = "right arrow"; break;\
case VK_DOWN: name = "down arrow"; break;\
case VK_INSERT: name = "insert"; break;\
case VK_DELETE: name = "delete"; break;\
case 'A': name = "a"; break;\
case 'B': name = "b"; break;\
case 'C': name = "c"; break;\
case 'D': name = "d"; break;\
case 'E': name = "e"; break;\
case 'F': name = "f"; break;\
case 'G': name = "g"; break;\
case 'H': name = "h"; break;\
case 'I': name = "i"; break;\
case 'J': name = "j"; break;\
case 'K': name = "k"; break;\
case 'L': name = "l"; break;\
case 'M': name = "m"; break;\
case 'N': name = "n"; break;\
case 'O': name = "o"; break;\
case 'P': name = "p"; break;\
case 'Q': name = "q"; break;\
case 'R': name = "r"; break;\
case 'S': name = "s"; break;\
case 'T': name = "t"; break;\
case 'U': name = "u"; break;\
case 'V': name = "v"; break;\
case 'W': name = "w"; break;\
case 'X': name = "x"; break;\
case 'Y': name = "y"; break;\
case 'Z': name = "z"; break;\
case VK_NUMPAD0: name = "numpad 0"; break;\
case VK_NUMPAD1: name = "numpad 1"; break;\
case VK_NUMPAD2: name = "numpad 2"; break;\
case VK_NUMPAD3: name = "numpad 3"; break;\
case VK_NUMPAD4: name = "numpad 4"; break;\
case VK_NUMPAD5: name = "numpad 5"; break;\
case VK_NUMPAD6: name = "numpad 6"; break;\
case VK_NUMPAD7: name = "numpad 7"; break;\
case VK_NUMPAD8: name = "numpad 8"; break;\
case VK_NUMPAD9: name = "numpad 9"; break;\
case VK_F1: name = "F1"; break;\
case VK_F2: name = "F2"; break;\
case VK_F3: name = "F3"; break;\
case VK_F4: name = "F4"; break;\
case VK_F5: name = "F5"; break;\
case VK_F6: name = "F6"; break;\
case VK_F7: name = "F7"; break;\
case VK_F8: name = "F8"; break;\
case VK_F9: name = "F9"; break;\
case VK_F10: name = "F10"; break;\
case VK_F11: name = "F11"; break;\
case VK_F12: name = "F12"; break;\
default: name = "unknown";\
}


static bool IsKeyPressedMap(ImGuiKey key, bool repeat = true)
{
    const int key_index = GImGui->IO.KeyMap[key];
    return (key_index >= 0) ? ImGui::IsKeyPressed((ImGuiKey)key_index, repeat) : false;
}
bool Hotkey_(const char* label, int* k, const ImVec2& size_arg)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    const ImGuiStyle& style = g.Style;

    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y);
    const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, -2.0f), window->DC.CursorPos + size - ImVec2(0, 2));
    const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

    ImGui::ItemSize(total_bb);
    if (!ImGui::ItemAdd(total_bb, id))
        return false;

    const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);

    const bool hovered = ImGui::ItemHoverable(frame_bb, id);

    if (hovered) {
        ImGui::SetHoveredID(id);
        g.MouseCursor = ImGuiMouseCursor_TextInput;
    }

    const bool user_clicked = hovered && io.MouseClicked[0];

    if (focus_requested || user_clicked) {
        if (g.ActiveId != id) {
            // Start edition
            memset(io.MouseDown, 0, sizeof(io.MouseDown));
            memset(io.KeysDown, 0, sizeof(io.KeysDown));
            *k = 0;
        }
        ImGui::SetActiveID(id, window);
        ImGui::FocusWindow(window);
    }
    else if (io.MouseClicked[0]) {
        // Release focus when we click outside
        if (g.ActiveId == id)
            ImGui::ClearActiveID();
    }

    bool value_changed = false;
    int key = *k;

    if (g.ActiveId == id) {
        for (auto i = 0; i <= 6; i++) {
            if (io.MouseDown[i] || GetAsyncKeyState(VK_XBUTTON1) || GetAsyncKeyState(VK_XBUTTON2)) {
                switch (i) {
                case 0:
                    key = VK_LBUTTON;
                    break;
                case 1:
                    key = VK_RBUTTON;
                    break;
                case 2:
                    key = VK_MBUTTON;
                    break;
                }
                if (GetAsyncKeyState(VK_XBUTTON2))
                    key = VK_XBUTTON2;
                if (GetAsyncKeyState(VK_XBUTTON1))
                    key = VK_XBUTTON1;

                value_changed = true;
                ImGui::ClearActiveID();
            }
        }
        if (!value_changed) {
            for (auto i = VK_BACK; i <= VK_RMENU; i++) {
                if (io.KeysDown[i]) {
                    key = i;
                    value_changed = true;
                    ImGui::ClearActiveID();
                }
            }
        }

        if (IsKeyPressedMap(ImGuiKey_Escape, false)) {
            *k = 0;
            ImGui::ClearActiveID();
        }
        else {
            *k = key;
        }
    }

    // Render
    // Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

    const char* buf_display = "None";

    if (*k != 0 && g.ActiveId != id) {
        const char* key_name;
        get_keycode_name(*k, buf_display);
    }
    else if (g.ActiveId == id) {
        buf_display = "Press";
    }
    auto text_size = ImGui::CalcTextSize(buf_display).x;

    const ImU32 col = ImGui::GetColorU32((user_clicked && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    ImGui::RenderNavHighlight(frame_bb, id);
    ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, col, false, 2);
    window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(1.f, 1.f, 1.f, 0.07f * style.Alpha), 2);


    const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
    ImVec2 render_pos = frame_bb.Min;
    ImGui::RenderTextClipped(frame_bb.Min, frame_bb.Max, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
    //RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
    //draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

    if (label_size.x > 0)
        ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y), label);

    return value_changed;
}
string update_logs =  ("");
ImVec4 WinBgCol = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void net_menu() {

    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiWindowFlags main_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    ImGui::SetNextWindowPos({ (GetSystemMetrics(SM_CXSCREEN) / 2) - (Gui::Size.x / 2) , (GetSystemMetrics(SM_CYSCREEN) / 2) - (Gui::Size.y / 2) }, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSizeConstraints(Gui::Size, ImVec2(vars::stuff::ScreenWidth, vars::stuff::ScreenHeight));
    vector < const char* > modelstae = {  ("None"), ("OnLadder"),   ("OnGround"), ("Ducked"), ("Sleeping") };
    vector < const char* > items = {  ("Head"),  ("Chest"), ("Body"),  ("Legs"),  ("Feet") };
    vector < const char* > autoshoot_type = {  ("Silent"),  ("Default") };
    vector < const char* > desync_autoshoot_type = {  ("Always"), ("Desync") };
    vector < const char* > font_type_ = {  ("Default"), ("Pixel") };
    vector < const char* > fakelagtype = {  ("Disable"), ("Default"), ("Experimental") };
    vector < const char* > bttype = {  ("Type 1"), ("Type 2"), ("Type 3"), ("Type 4") };
    vector < const char* > btttype = {  ("First"), ("Second") };
    vector < const char* > doubletaptype = {  ("Disable"), ("Default"), ("Automatic") };

    vector < const char* > hitbox_type = {  ("None"),   ("Body"), ("Head"), ("Randomize All"), ("Head/Body") };
    vector < const char* > hitmaterial_c = {  ("Default"),   ("Glass"), ("Water(UnregB)"), ("Wood"), ("Metal"), ("Sand"), ("Grass"), ("Rock"), ("Concrete"), ("Forest"), ("Cloth"), ("Generic"), ("Null") };
    vector < const char* > geasture_s = {  ("None"),   ("Clap"), ("Friendly"), ("Thumbsdown"), ("Thumbsup"), ("Ok"), ("Point"), ("Shrug") , ("Victory") , ("Wave")  };
    vector < const char* > boxtype = {  ("Default"),   ("Cornered"), ("3D") };
    vector < const char* > spheretype = {  ("Shpere"),   ("Gizmo"), ("Box") };
    vector < const char* > sphetype = {  ("Shpere"),   ("Gizmo"), ("Box") };
    vector < const char* > killtype = {  ("Chill"),   ("Chillllllll"), ("Chillasd") };
    vector < const char* > healthbarstyle = {  ("Left"),   ("Bottom"), ("Right") };

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin( ("Window::WindowName"), nullptr, main_window_flags);
    ImGui::PopStyleVar(); 
    {  
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + Gui::SidebarSize, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y), ImGui::GetColorU32(ImGuiCol_ChildBg), style.WindowRounding, ImDrawFlags_RoundCornersLeft); // Sidebar 
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + Gui::SidebarSize + style.WindowBorderSize, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y), ImGui::GetColorU32(ImGuiCol_WindowBg), style.WindowRounding, ImDrawFlags_RoundCornersRight); // Main Panel 
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y), IM_COL32(0, 0, 0, 255), style.WindowRounding, 0, style.WindowBorderSize); // BorderShadows 
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(ImGui::GetWindowPos().x + style.WindowBorderSize, ImGui::GetWindowPos().y + style.WindowBorderSize), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x - style.WindowBorderSize, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y - style.WindowBorderSize), ImGui::GetColorU32(ImGuiCol_Border), style.WindowRounding, 0, style.WindowBorderSize); // Border 
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x + Gui::SidebarSize, ImGui::GetWindowPos().y + style.WindowBorderSize * 2), ImVec2(ImGui::GetWindowPos().x + Gui::SidebarSize, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y - (style.WindowBorderSize * 2)), ImGui::GetColorU32(ImGuiCol_Border), style.WindowBorderSize); // Side border line 
        { 
            ImGui::BeginChild(("sidebar"), ImVec2(Gui::SidebarSize + style.WindowBorderSize * 2, 0), true, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar); 
            auto SidebarButtonSize = ImVec2(ImGui::GetWindowSize().x - style.WindowPadding.x * 2, ImGui::GetWindowSize().x - style.WindowPadding.x * 2); 
            {
                static bool siderbar_popups = false;
                ImAdd->NavigationRadioIcon(ICON_FA_USER,  ("Player"), SidebarButtonSize, 1, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_CROSSHAIRS,  ("Weapons"), SidebarButtonSize, 2, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_EYE,  ("Visuals"), SidebarButtonSize, 3, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_EARTH_EUROPE,  ("World"), SidebarButtonSize, 4, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_EARTH_ASIA,  ("World "), SidebarButtonSize, 5, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_LAPTOP_CODE,  ("Developer"), SidebarButtonSize, 6, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_ARROWS_ROTATE,  ("Updates"), SidebarButtonSize, 7, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
                ImAdd->NavigationRadioIcon(ICON_FA_GEAR,  ("Settings"), SidebarButtonSize, 8, &Gui::SidebarId, siderbar_popups);
                ImGui::Separator();
            }
            ImGui::EndChild();
            ImGui::SameLine(Gui::SidebarSize - style.WindowBorderSize);
    
            ImGui::BeginChild( ("content"), ImVec2(0, 0), true, ImGuiWindowFlags_NoBackground);
            {
                auto visualsgroupsizing = ImVec2(((ImGui::GetWindowSize().x / 2) - (style.WindowPadding.x * (2 + 1)) / 2), ((ImGui::GetWindowSize().y / 2) - (style.WindowPadding.y * (2 + 1)) / 2));
                auto playergroupsizing = ImVec2(((ImGui::GetWindowSize().x / 2) - (style.WindowPadding.x * (2 + 1)) / 2), 0);
                auto weaponsgroupsizing = ImVec2(((ImGui::GetWindowSize().x / 2) - (style.WindowPadding.x * (2 + 1)) / 2), ((ImGui::GetWindowSize().y / 2) - (style.WindowPadding.y * (2 + 1)) / 2));

                switch (Gui::SidebarId)
                {
                case 0:
                    ImGui::Text( ("Skyline.one"));
                    break;
                case 1:

                    ImGui::BeginChild( ("player1"), playergroupsizing, true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Player Assistance")), ImGui::EndMenuBar();
                        {
                            auto playerbuttonsgroup = ImVec2(((ImGui::GetWindowSize().x / 2) - (style.WindowPadding.x * (2 + 1)) / 2), 0);
                            ImGui::SliderFloat( ("Fov"), &vars::misc::fov, 30.f, 130.f);
                            Hotkey_( ("Zoom"), &vars::keys::zoom, ImVec2(70, 18));

                            ImGui::Combo( ("Geasture"), &vars::misc::gesture, geasture_s.data(), geasture_s.size());

                            ImGrp->ToggleButton( ("Instant Loot"), &vars::misc::fast_loot);
                            ImGrp->ToggleButton( ("visded"), &vars::visuals::visded);
                            if (vars::visuals::visded) {
                                ImGui::Combo(("Allkillefect Style"), &vars::visuals::Allkillefect, killtype.data(), killtype.size());
                            }
                            ImGrp->ToggleButton( ("Auto Med"), &vars::misc::faster_healing);
                            ImGui::Checkbox( ("Auto pidoras"), &vars::misc::faster_healing);
                            ImGrp->ToggleButton( ("BetterJump"), &vars::misc::better_jump);
                            ImGrp->ToggleButton( ("Spiderman"), &vars::misc::spiderman);
                            ImGrp->ToggleButton( ("Auto Farm"), &vars::misc::auto_farm);
                            if (vars::misc::auto_farm) {
                                ImGrp->ToggleButton( ("Auto Farm Ore"), &vars::misc::auto_farm_ore);
                                ImGrp->ToggleButton( ("Auto Farm Tree"), &vars::misc::auto_farm_tree);
                            }
                            ImGrp->ToggleButton( ("Auto Pick Up"), &vars::misc::auto_pickup);
                            ImGrp->ToggleButton( ("Bhop"), &vars::misc::bhop);
                            if (vars::misc::bhop)
                                Hotkey_( ("Key Bhop"), &vars::keys::bhop, ImVec2(0, 0));
                            ImGrp->ToggleButton( ("Interactive Debug"), &vars::misc::interactive_debug);
                            if (vars::misc::interactive_debug)
                                Hotkey_( ("Key Interactibe Debug"), &vars::keys::debugging, ImVec2(0, 0));
                            ImGrp->ToggleButton( ("Teloport To Player"), &vars::misc::TeloportTopPlayer);
                            if (vars::misc::TeloportTopPlayer)
                                Hotkey_( ("Key Teleport"), &vars::keys::TeleportTopPlayer, ImVec2(0, 0));
                            ImGui::Checkbox(("Hit Marker"), &vars::misc::hitmarker); ImGui::ColorEdit4(("Hit Marker Col"), (float*)&vars::colors::marker, NO_ALPHA);
                            ImGui::SameLine(ImGui::GetWindowWidth() - 33); ImGui::ColorEdit4( ("Hit Marker Color"), (float*)&vars::colors::hitmarker, NO_ALPHA);
                            ImGui::Checkbox( ("Damage Marker"), &vars::misc::damagemarker);
                            ImGui::SameLine(ImGui::GetWindowWidth() - 33); ImGui::ColorEdit4( ("Damage Marker Color"), (float*)&vars::colors::damagemarker, NO_ALPHA);

                        }
                    }
                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("player2"), ImVec2(playergroupsizing.x, 210), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Player Modifications")), ImGui::EndMenuBar();
                        {

                            ImGui::Combo( ("State"), &vars::misc::modelstate, modelstae.data(), modelstae.size());
                            ImGui::Combo( ("Fake Lag"), &vars::misc::fakelag, fakelagtype.data(), fakelagtype.size());

                            ImGrp->ToggleButton( ("IgnoreColision"), &vars::misc::jesus);
                            ImGrp->ToggleButton( ("FakeAdmin"), &vars::misc::fakeadmin);
                            ImGrp->ToggleButton( ("Omni-Sprint"), &vars::misc::omnidirectional_sprinting); ImGui::SameLine(); Hotkey_( (" "), &vars::keys::speedkey, ImVec2(70, 18));
                            ImGrp->ToggleButton( ("No Fall Damage"), &vars::misc::no_fall);
                            ImGrp->ToggleButton( ("Fly Hack Stopper"), &vars::misc::fly_auto_stopper);

                            ImGrp->ToggleButton( ("Suicide"), &vars::misc::suicide);
                            if (vars::misc::suicide)
                                Hotkey_( ("key"), &vars::keys::suicide,ImVec2(0,0));

                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("player3"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Indicators")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Crosshair"), &vars::misc::crosshair);
                            ImGrp->ToggleButton( ("Target Belt"), &vars::players::TargetBelt);

                            ImGrp->ToggleButton( ("Flyhack Indicator"), &vars::misc::flyhack_indicator);
                            ImGrp->ToggleButton( ("Reload Indicator"), &vars::misc::reload_indicator);
                            ImGrp->ToggleButton( ("Manipulator Indicator"), &vars::misc::manipulator_indicator);
                            ImGrp->ToggleButton( ("Target Info"), &vars::misc::TargetInfo);
                            ImGrp->ToggleButton( ("Bullet Tracer"), &vars::debug::bullettracer);
                            if (vars::debug::bullettracer)
                            {
                                ImGui::Combo( ("Bullet Tracer Type"), &vars::stuff::bttype, bttype.data(), bttype.size());
                            }
                            ImGrp->ToggleButton(("Bullettar Tracer"), &vars::debug::bullettartracer);
                            if (vars::debug::bullettartracer)
                            {
                                ImGui::Combo(("Bulletra Tracer Type"), &vars::stuff::bttype, btttype.data(), btttype.size());
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    break;
                case 2:


                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("weapons1"), ImVec2(weaponsgroupsizing.x, 240), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Aim Assistance")), ImGui::EndMenuBar();
                        {
                            // Range
                            ImGui::Combo( ("HitBox"), &vars::combat::hitbox, hitbox_type.data(), hitbox_type.size());
                            ImGrp->ToggleButton( ("Magi Bullet On Helicopter"), &vars::combat::always_heli_rotor);
                            ImGrp->ToggleButton( ("pSilent"), &vars::combat::psilent);
                            if (vars::combat::psilent) {
                                ImGrp->ToggleButton( ("Autoshoot"), &vars::combat::autoshoot);
                                if (vars::combat::autoshoot) {
                                    ImGui::Combo( ("Fire Type"), &vars::combat::autoshoot_type, autoshoot_type.data(), autoshoot_type.size());
                                }
                            }
                            ImGrp->ToggleButton(("Test"), &vars::weapons::test);
                            ImGrp->ToggleButton(("Test2"), &vars::weapons::test2);
                            ImGrp->ToggleButton(("Visual prj"), &vars::weapons::scale);
                            if (vars::weapons::scale) {
                                ImGui::SliderFloat("Visual y", &vars::weapons::bullet_sizey, 1.f, 100.f, "%.2f");
                                ImGui::SliderFloat(("Visual x"), &vars::weapons::bullet_sizex, 1.f, 100.f, "%.2f");
                                ImGui::SliderFloat(("Visual z"), &vars::weapons::bullet_sizez, 1.f, 100.f, "%.2f");
                            }
                            ImGrp->ToggleButton( ("Manipulator"), &vars::combat::manipulator, []() {
                                ImGrp->ToggleButton( ("Hit Hluyha"), &vars::combat::hitscan);
                                ImGrp->ToggleButton( ("shot AtBt"), &vars::combat::Manipulator_shot_atBt);
                                ImGrp->ToggleButton( ("shot AtÅÅBt"), &vars::combat::m_check_bullet_tp);
                                ImGrp->ToggleButton( ("Show Radius"), &vars::combat::ManipulatorRadios);
                                ImGrp->ToggleButton( ("Draw R"), &vars::combat::draw_manip_radius);
                                ImGrp->ToggleButton( ("Radius Type 1"), &vars::combat::mpvis);
                                ImGrp->ToggleButton( ("Radius Type 2"), &vars::combat::vismp);

                 
                                });  Hotkey_(("Manipulator k"), &vars::keys::manipulated_key, ImVec2(70, 18));
                            ImGrp->ToggleButton( ("Silent Melee"), &vars::combat::silent_melee);
                            ImGrp->ToggleButton(("InstaXui"), &vars::combat::instakill);
                            Hotkey_(("InstaXui k"), &vars::keys::instakill, ImVec2(70, 19));
                            ImGrp->ToggleButton( ("STW"), &vars::combat::stw);
                            ImGrp->ToggleButton( ("Reflect"), &vars::combat::tree_reflect);
                            ImGrp->ToggleButton( ("Double Tap"), &vars::combat::doubletap);
                            if (vars::combat::doubletap)
                            ImGui::Combo( ("Double Type"), &vars::combat::doubletaptype, doubletaptype.data(), doubletaptype.size());

                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("weapons2"), ImVec2(weaponsgroupsizing.x, 0), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Aim Filters")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Visualize Targeting Fov"), &vars::combat::visualize_fov);
                            ImGui::SliderFloat("Targeting Fov", &vars::combat::fov, 20.f, 1000.f, "%.2f");
                            //size_font

                            ImGrp->ToggleButton( ("Ignore NPC's"), &vars::combat::ignore_npc);
                            ImGrp->ToggleButton( ("Ignore Teammates"), &vars::combat::ignore_team);
                            ImGrp->ToggleButton( ("Ignore Sleeping"), &vars::combat::ignore_sleepers);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginChild( ("weapons3"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Combat Assistance")), ImGui::EndMenuBar();
                        {
                            ImGui::Combo( ("Hit Material"), &vars::misc::hitmaterial, hitmaterial_c.data(), hitmaterial_c.size());
                            ImGrp->ToggleButton(("Hit Sphere"), &vars::misc::hitmarker);
                            if (vars::misc::hitmarker) {
                                ImGui::SliderFloat(("Duration"), &vars::misc::hitmarker_duration, 0.f, 10.f);
                                ImGui::ColorEdit4(("Radius Color"), (float*)&vars::colors::marker, NO_ALPHA);
                            }
                            ImGrp->ToggleButton( ("No Recoil"), &vars::weapons::no_recoil);
                            if (vars::weapons::no_recoil) {
                                ImGui::SliderFloat( ("Recoil"), &vars::weapons::recoil_control, 0.f, 100.f);
                            }
                            ImGrp->ToggleButton( ("No Spread"), &vars::weapons::no_spread);
                            ImGrp->ToggleButton( ("No Sway"), &vars::weapons::no_sway);
                            ImGrp->ToggleButton( ("Force Automatic"), &vars::weapons::automatic);
                            ImGrp->ToggleButton( ("Insta Compound Bow"), &vars::weapons::compound);
                            ImGrp->ToggleButton( ("Minicopter Aim"), &vars::weapons::minicopter_aim);
                            ImGrp->ToggleButton( ("No Bobing"), &vars::visuals::No_bobing);
                            ImGrp->ToggleButton( ("Thick Bullets"), &vars::weapons::thick_bullet);
                            ImGrp->ToggleButton( ("Bullet Teleport"), &vars::combat::bullet_tp, []() {
                            ImGrp->ToggleButton( ("Extendet For Mounted"), &vars::combat::ExtentForMoutend);
                            ImGrp->ToggleButton( ("Show BTP"), &vars::visuals::onan);
                            ImGrp->ToggleButton( ("GRAD BTP"), &vars::combat::BulletTeleportGradient);
                            if (vars::combat::BulletTeleportGradient) {
                                ImGui::ColorEdit4( ("Radius Color"), (float*)&vars::colors::one_color, NO_ALPHA2);
                            }
                            //  ImGui::ColorEdit4( ("Show Distance Bullet Active"), (float*)&vars::colors::BulletTp_color, NO_ALPHA);
                                });
                            ImGui::Combo( ("BTP Style"), &vars::visuals::ponan, sphetype.data(), sphetype.size());
                            ImGrp->ToggleButton( ("Rapid Fire"), &vars::weapons::rapidfire);

                            ImGrp->ToggleButton( ("Faster Bullets"), &vars::weapons::fast_bullets);
                            ImGrp->ToggleButton( ("Pidor Bullets"), &vars::weapons::low_velocity);
                            Hotkey_( (""), &vars::keys::low_velocity_key, ImVec2(70, 18));
                            ImGrp->ToggleButton( ("Pierce Materials"), &vars::weapons::penetrate);
                            ImGrp->ToggleButton( ("Instat eoka"), &vars::weapons::eokatap);
                            ImGrp->ToggleButton( ("Auto Reload"), &vars::combat::autoreload);
                            ImGrp->ToggleButton( ("Can Always Shoot"), &vars::misc::can_attack);
                        }
                    }
                    ImGui::EndChild();
                    break;
                case 3:

                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals1"), ImVec2(visualsgroupsizing.x, 240), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Player ESP")), ImGui::EndMenuBar();
                        {

                            ImGrp->ToggleButton( ("Name"), &vars::players::name, []() {
                                

                                ImGrp->ToggleButton( ("Outline"), &vars::players::name_::outline);
                                });
                            ImGrp->ToggleButton( ("Box"), &vars::players::box, []() {
                                ImGrp->ToggleButton( ("Outline"), &vars::players::box_::outline);
                                });
              
                            ImGrp->ToggleButton( ("Skeleton"), &vars::players::skeleton, []() {
                                ImGrp->ToggleButton( ("Outline"), &vars::players::skeleton_::outline);
                                });
                            ImGrp->ToggleButton( ("Distance"), &vars::players::distance);
                            ImGrp->ToggleButton( ("Healthbar"), &vars::players::healthbar);
                            ImGrp->ToggleButton( ("Weapon "), &vars::players::weapon, []() {

                                ImGrp->ToggleButton( ("Outline"), &vars::players::weapon_::outline);
                                });
                            ImGrp->ToggleButton( ("Weapon Icon"), &vars::players::WeaponIcon, []() {
                                ImGrp->ToggleButton( ("Disable Weapon Name"), &vars::players::DisableWeaponName);
                                });
                            ImGrp->ToggleButton( ("OOF Indicators"), &vars::players::oof_arrows);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals2"), ImVec2(visualsgroupsizing.x, 0), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("ESP Settings")), ImGui::EndMenuBar();
                        {
                            if (vars::players::box)
                                ImGui::Combo( ("Box Style"), &vars::players::boxstyle, boxtype.data(), boxtype.size());
                            if (vars::players::healthbar)
                                ImGui::Combo( ("HealthBar Style"), &vars::players::healthbarstyle, healthbarstyle.data(), healthbarstyle.size());

                            ImGrp->ToggleButton( ("Ignore Sleepers"), &vars::players::sleeperignore);
                            ImGrp->ToggleButton( ("Target Tracers"), &vars::players::targetline);
                            ImGui::ColorEdit4( ("Esp Color"), (float*)&vars::visible::box_color, NO_ALPHA2);
                            ImGui::ColorEdit4( ("Npc Color"), (float*)&vars::colors::npc_box_color , NO_ALPHA2);
                            ImGui::ColorEdit4( ("Target Color"), (float*)&vars::colors::target_color, NO_ALPHA2);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals3"), ImVec2(visualsgroupsizing.x, 210), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Npc ESP")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Name "), &vars::npc::name);
                            ImGrp->ToggleButton( ("Box "), &vars::npc::box);
                            ImGrp->ToggleButton( ("Skeleton "), &vars::npc::skeleton);
                            ImGrp->ToggleButton( ("Distance "), &vars::npc::distance);
                            ImGrp->ToggleButton( ("Healthbar "), &vars::npc::healthbar);
                            ImGrp->ToggleButton( ("Weapon "), &vars::npc::weapon);
                            ImGrp->ToggleButton( ("Weapon Icon "), &vars::npc::WeaponIcon, []() {
                                ImGrp->ToggleButton( ("Disable Weapon Name "), &vars::npc::DisableWeaponName);
                                });
                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals4"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Visuals")), ImGui::EndMenuBar();
                        {
                            ImGui::Checkbox( ("Bright Ambient"), &vars::misc::bright_ambient);
                            ImGui::SameLine(ImGui::GetWindowWidth() - 33); ImGui::ColorEdit4( ("Ambient Color"), (float*)&vars::colors::ambient_color, NO_ALPHA);
                            ImGrp->CheckboxSliderFloat(("Sky Color"), ("##Intensivity"), &vars::visuals::skycolor, &vars::misc::intensivity, 0.f, 36.f);
                            ImGrp->CheckboxSliderFloat(("Stars"), ("##Intens"), &vars::misc::night_stars, &vars::misc::stars, 0.f, 100.f);
                            ImGui::SameLine(ImGui::GetWindowWidth() - 10); ImGui::ColorEdit4( ("Sky Color"), (float*)&vars::colors::sky_color, NO_ALPHA);
                            ImGui::Checkbox( ("Colision Sphera"), &vars::misc::sphere);
                            if (vars::misc::sphere)
                                ImGui::Combo( ("Sphera Style"), &vars::misc::Sphera, spheretype.data(), spheretype.size());
                            ImGui::SameLine(ImGui::GetWindowWidth() - 33); ImGui::ColorEdit4( ("Sphera Color"), (float*)&vars::colors::colsphere, NO_ALPHA);
                            ImGrp->CheckboxSliderFloat( ("Custom Time"),  ("##Time"), &vars::misc::custom_time, &vars::misc::time, 0.f, 12.f);

                            ImGrp->CheckboxSliderFloat( ("Aspect Ratio"),  ("##aspectratio"), &vars::misc::AspectRatio, &vars::misc::ratio, 0.2f, 2.0f);
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    break;
                case 4:

                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals1"), ImVec2(visualsgroupsizing.x, 240), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Crate")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Chinook Crates"), &vars::visuals::crates::chinook);
                            ImGrp->ToggleButton( ("Airdrops"), &vars::visuals::crates::supply);
                            ImGrp->ToggleButton( ("Heli Crates"), &vars::visuals::crates::heli);
                            ImGrp->ToggleButton( ("Bradley Crates"), &vars::visuals::crates::bradley);
                            ImGrp->ToggleButton( ("Military Crates"), &vars::visuals::crates::military);
                            ImGrp->ToggleButton( ("Elite Crates"), &vars::visuals::crates::elite);
                            if (vars::visuals::crates::supply || vars::visuals::crates::bradley || vars::visuals::crates::heli || vars::visuals::crates::military || vars::visuals::crates::elite) {
                                ImGui::SliderFloat( ("Crate ESP Distance"), &vars::visuals::crates::draw_distance, 5.f, 3000.f);
                                ImGrp->ToggleButton( ("Show Distance "), &vars::visuals::crates::show_distance);
                            }

                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals2"), ImVec2(visualsgroupsizing.x, 0), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Vehicle")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Patrol Heli"), &vars::visuals::patrol_heli);
                            ImGrp->ToggleButton( ("Minicopters"), &vars::visuals::vehicles::minicopter);
                            ImGrp->ToggleButton( ("Scrap Helis"), &vars::visuals::vehicles::scrapheli);
                            ImGrp->ToggleButton( ("Boats"), &vars::visuals::vehicles::boat);
                            ImGrp->ToggleButton( ("RHIB's"), &vars::visuals::vehicles::rhib);
                            if (vars::visuals::vehicles::minicopter || vars::visuals::vehicles::scrapheli || vars::visuals::vehicles::boat || vars::visuals::vehicles::rhib) {
                                ImGui::SliderFloat( ("Vehicle ESP Distance"), &vars::visuals::vehicles::draw_distance, 5.f, 3000.f);
                                ImGrp->ToggleButton( ("Show Distance  "), &vars::visuals::vehicles::show_distance);
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals3"), ImVec2(visualsgroupsizing.x, 210), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Ore")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Stone"), &vars::ores::stone);
                            ImGrp->ToggleButton( ("Sulfur"), &vars::ores::sulfur);
                            ImGrp->ToggleButton( ("Metal"), &vars::ores::metal);
                            if (vars::ores::sulfur || vars::ores::stone || vars::ores::metal) {
                                ImGui::SliderFloat( ("Ore ESP Distance"), &vars::ores::draw_distance, 5.f, 400.f);
                                ImGrp->ToggleButton( ("Show Collectables"), &vars::ores::show_collectables);
                                ImGrp->ToggleButton( ("Show Distance"), &vars::ores::show_distance);
                            }

                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals4"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Animals")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Bears"), &vars::visuals::animals::bear);
                            ImGrp->ToggleButton( ("Pigs"), &vars::visuals::animals::pig);
                            ImGrp->ToggleButton( ("Wolfs"), &vars::visuals::animals::wolf);
                            ImGrp->ToggleButton( ("Horses"), &vars::visuals::animals::deer);
                            ImGrp->ToggleButton( ("Chickens"), &vars::visuals::animals::chicken);
                            if (vars::visuals::animals::bear || vars::visuals::animals::pig || vars::visuals::animals::wolf || vars::visuals::animals::deer || vars::visuals::animals::chicken) {
                                ImGui::SliderFloat( ("Animal ESP Distance"), &vars::visuals::animals::draw_distance, 5.f, 400.f);
                                ImGrp->ToggleButton( ("Show Distance      "), &vars::visuals::animals::show_distance);
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    break;
                case 5:

                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals1"), ImVec2(visualsgroupsizing.x, 240), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Turrets")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Auto Turrets"), &vars::visuals::turrets::auto_turret);
                            ImGrp->ToggleButton( ("Flame Turrets"), &vars::visuals::turrets::flame_turret);
                            ImGrp->ToggleButton( ("Shotgun Traps"), &vars::visuals::turrets::shotgun_turret);
                            ImGrp->ToggleButton( ("SAM Sites"), &vars::visuals::turrets::sam_site);
                            ImGrp->ToggleButton( ("Landmines"), &vars::visuals::turrets::landmine);
                            ImGrp->ToggleButton( ("Beartraps"), &vars::visuals::turrets::bear_trap);
                            if (vars::visuals::turrets::auto_turret || vars::visuals::turrets::flame_turret || vars::visuals::turrets::shotgun_turret || vars::visuals::turrets::landmine || vars::visuals::turrets::bear_trap) {
                                ImGui::SliderFloat( ("Trap ESP Distance"), &vars::visuals::turrets::draw_distance, 5.f, 400.f);
                                ImGrp->ToggleButton( ("Show Distance   "), &vars::visuals::turrets::show_distance);
                            }


                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals2"), ImVec2(visualsgroupsizing.x, 0), true);
                    {

                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals3"), ImVec2(visualsgroupsizing.x, 210), true, ImGuiWindowFlags_MenuBar);
                    {

                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Other")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Tool Cupboards"), &vars::visuals::base::tc);
                            ImGrp->ToggleButton( ("Sleeping Bags"), &vars::visuals::base::sleeping_bag);
                            ImGrp->ToggleButton( ("Beds"), &vars::visuals::base::bed);
                            ImGrp->ToggleButton( ("Boxes"), &vars::visuals::base::boxes);
                            if (vars::visuals::base::tc || vars::visuals::base::sleeping_bag || vars::visuals::base::bed || vars::visuals::base::boxes) {
                                ImGui::SliderFloat( ("Base ESP Distance"), &vars::visuals::base::draw_distance, 5.f, 400.f);
                                ImGrp->ToggleButton( ("Show Distance     "), &vars::visuals::base::show_distance);
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::BeginChild( ("visuals4"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Misc")), ImGui::EndMenuBar();
                        {
                            ImGrp->ToggleButton( ("Hemp"), &vars::visuals::other::hemp);
                            ImGrp->ToggleButton( ("Corpses"), &vars::visuals::other::corpse);
                            ImGrp->ToggleButton( ("Dropped Items"), &vars::visuals::other::dropped_items);

                            ImGrp->ToggleButton( ("Stashes"), &vars::visuals::other::stash);
                            if (vars::visuals::other::corpse || vars::visuals::other::stash || vars::visuals::other::hemp || vars::visuals::other::dropped_items) {
                                ImGui::SliderFloat( ("ESP Distance"), &vars::visuals::other::draw_distance, 5.f, 400.f);
                                ImGrp->ToggleButton( ("Show Distance    "), &vars::visuals::other::show_distance);
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    break;
                case 6:

                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals3"), ImVec2(playergroupsizing.x, 0), true, ImGuiWindowFlags_MenuBar);
                    {

                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Debug ")), ImGui::EndMenuBar();
                        {
                            ImGui::Checkbox( ("Enable Debug"), &vars::debug::debug);
       
                            ImGui::Checkbox( ("Target Debug"), &vars::debug::debug);
                            ImGui::Checkbox( ("Player List"), &vars::debug::espdebug);


                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginChild( ("weapons3"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Debug 2")), ImGui::EndMenuBar();
                        {
                        

                        }
                    }
                    ImGui::EndChild();
                    break;
                case 7:
                    //if (update_logs == "")
                     //   update_logs = CheckLink( ("https://raw.githubusercontent.com/Kors1337/Skyline-2/main/updatelog")).c_str();
                    ImGui::Text( ("discord.gg/6bmWhnVzR"));
                    break;
                case 8:
                    static char config_name[64] = u8"\0";

                    ImGui::BeginGroup();
                    ImGui::BeginChild( ("visuals3"), ImVec2(playergroupsizing.x,0), true, ImGuiWindowFlags_MenuBar);
                    {

                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("List")), ImGui::EndMenuBar();
                        {
                            if (ImGui::BeginListBox( ("##aa"), ImGui::GetWindowSize() - ImVec2(20,35)))
                            {
                                for (auto cfg : config.GetConfigList())
                                    if (ImGui::Selectable(cfg.c_str(), cfg == vars::stuff::selected_cfg))
                                        vars::stuff::selected_cfg = cfg;

                                ImGui::EndListBox();
                            }
                        }
                    }
                    ImGui::EndChild();
                    ImGui::EndGroup();
                    ImGui::SameLine();
                    ImGui::BeginChild( ("weapons3"), ImVec2(), true, ImGuiWindowFlags_MenuBar);
                    {
                        if (ImGui::BeginMenuBar()) ImGui::TextUnformatted( ("Settings")), ImGui::EndMenuBar();
                        {
                            ImGui::InputText( ("Config Name"), config_name, sizeof(config_name));
                            if (ImGui::Button( ("Save"), ImVec2(0, 0))) {
                                config.Save(vars::stuff::selected_cfg.c_str());
                            }
                            ImGui::SameLine();
                            if (ImGui::Button( ("Load"), ImVec2(0, 0))) {
                                config.Load(vars::stuff::selected_cfg.c_str());
                            }
                            if (ImGui::Button( ("Create"), ImVec2(0, 0))) {
                                vars::stuff::selected_cfg = config_name;
                                config.Create();
                            }
                            ImGui::SameLine();

                            if (ImGui::Button( ("Remove"), ImVec2(0, 0))) {
                                config.Remove(vars::stuff::selected_cfg.c_str());
                            }
                            ImGui::SameLine();

                            if (ImGui::Button( ("Reload"), ImVec2(0, 0))) {
                                config.Load("");
                                config.Load(vars::stuff::selected_cfg.c_str());
                            }
                            if (ImGui::Button( ("Unload Cheat"))) {
                                vars::stuff::Panic = true;
                            }
                            ImGui::Combo( ("Esp Font"), &vars::stuff::font, font_type_.data(), font_type_.size());
                          //  ImGui::SliderFloat( ("Size Font"), &vars::stuff::size_font, 10.f, 20.f);

                        }
                    }
                    ImGui::EndChild();
                    break;
                }

            }
            ImGui::EndChild();

        }
    }
    ImGui::End();
}