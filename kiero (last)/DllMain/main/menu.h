int page = 0;    int active_tab = 0;    float anim_childs = 1.f;
DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha;
const char* flags_type[] = { "Sleeper", "Wounded", "SafeZone","Teammate" };
static const char* hitmaterial[] = { ("Default"),  ("Glass"),("Water"),("Wood"),("Metal") };
const char* ignoring_type[] = { "Sleeper", "Wounded" };
const char* bone_target_aimbot[] = { "Head", "Body","Random Main","Random All" };
const char* predicttype[] = { "Default", "Beta" };
const char* manip_radius[] = { "Hard", "Default" };
const char* hammer_spam[] = { "On player", "LocalPlayer" };
const char* fast_speed[] = { "Fast", "Default" };
const char* hitsound_style[] = { "Roblox", "Minecraft","Crystal" };
const char* fb_speed[] = { "Fast", "Default" };
const char* ignoring_type_aimbot[] = { "Sleeper", "Wounded","Npc","Teammate" };
static const char* modelstate_pos[]{"On Ladder","On Ground","Ducked","Sleeping"};
static const char* font_[]{ "Cunia","Segue","Roboto"};
static const char* box_style[]{"Default","Cornered"};
static const char* hand_chams_type[]{ "Gold", "Trippy", "Glitch"};
static const char* chams_render_mode[3]{ "All", "Only hands", "Only Weapon" };
const char* cheat_name = "Kiero Hook";
const char* developer =  __DATE__;
const char* role = "Beta";
void watermark() {
    ImGuiStyle* style = &ImGui::GetStyle();
    ImGui::PushFont(font::lexend_bold);
    const float cheat_name_size = ImGui::CalcTextSize(cheat_name).x;
    const float developer_size = ImGui::CalcTextSize(developer).x;
    const float role_size = ImGui::CalcTextSize(role).x;
    const float bar_size = ImGui::CalcTextSize("|").x;

    const float ibar_size = cheat_name_size + bar_size + developer_size + bar_size + role_size + bar_size + developer_size  - 15;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - (ibar_size  + 15), 15));
    ImGui::SetNextWindowSize(ImVec2(ibar_size,45));

    ImGui::Begin("info-bar", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
    {
        const ImVec2& pos = ImGui::GetWindowPos(), spacing = style->ItemSpacing, region = ImGui::GetContentRegionMax();
        ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + region, ImGui::GetColorU32(c::background::filling), c::elements::rounding);
        ImGui::GetBackgroundDrawList()->AddRect(pos, pos + region, ImGui::GetColorU32(c::background::stroke), c::elements::rounding);
        const char* info_set[3] = { cheat_name, developer, role };
        ImGui::SetCursorPos(ImVec2(spacing.x, (45 - ImGui::CalcTextSize(developer).y) / 2));
        ImGui::BeginGroup();
        {
            for (int i = 0; i < ARRAYSIZE(info_set); i++) {
                ImGui::TextColored(i < 1 ? ImColor(ImGui::GetColorU32(c::accent)) : ImColor(ImGui::GetColorU32(c::elements::text)), info_set[i]);
                ImGui::SameLine();
                if (ARRAYSIZE(info_set) != i)
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "|");
                    ImGui::SameLine();
                }
            }
        }
        ImGui::EndGroup();
    }
    ImGui::End();

    ImGui::PopFont();
}

void tabs()
{
    ImGui::SetCursorPos(ImVec2(10, 60));
    ImGui::BeginGroup();
    std::vector<std::vector<std::string>> tab_columns = {
        { "c", "f", "b", "o", "e" },
        { "Aimbot", "Weapons", "Visuals", "Misc", "Configs" },
    };
    for (int i = 0; i < tab_columns[0].size(); ++i) {

        if (edited::Tab(page == i, tab_columns[0][i].c_str(), tab_columns[1][i].c_str(), ImVec2(50, 50))) {
            page = i;
        }

    }
    ImGui::EndGroup();
}

static float tab_alpha = 0.f;
void decoration(const ImVec2& region)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(settings::screen_size.x, settings::screen_size.y), ImColor(0.f, 0.f, 0.f,  50.f / 255));
   
    ImGuiStyle* style = &ImGui::GetStyle();
    const ImVec2& pos = ImGui::GetWindowPos();
  
    const ImVec2& spacing = style->ItemSpacing;

    style->WindowPadding = ImVec2(0, 0);
    style->WindowBorderSize = 0.f;
    style->ItemSpacing = ImVec2(10.f, 10.f);

    tab_alpha = ImLerp(tab_alpha, (page == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
    if (tab_alpha < 0.01f ) active_tab = page;
    c::menu_pos = pos;
    auto text_size = font::lexend_general_bold_2->CalcTextSizeA(34.f, FLT_MAX, 0, ("KH"));
    ImGui::GetWindowDrawList()->AddRectFilled(pos, pos + c::background::size, ImGui::GetColorU32(c::background::filling), c::background::rounding);
    ImGui::GetWindowDrawList()->AddRectFilled(pos, pos + ImVec2(70, c::background::size.y), ImGui::GetColorU32(c::background::filling_top), c::background::rounding, ImDrawFlags_RoundCornersLeft);

    ImGui::GetWindowDrawList()->AddRectFilled(pos + ImVec2(70, 0), pos + ImVec2(72, c::background::size.y), ImGui::GetColorU32(c::background::stroke));
    ImGui::GetWindowDrawList()->AddText(font::lexend_general_bold_2, 34.f, pos + ImVec2(70 / 2 - text_size.x / 2, 50 / 2 - text_size.y / 2), ImGui::GetColorU32({ c::accent }), ("KH"));
}

void menu()
{
    static float accent[4] = { 114 / 255.f, 109 / 255.f, 173 / 255.f, 1.f };
    edited::Particles_init();
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(c::background::size);
    ImGui::Begin("menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);
    {
        ImGuiStyle* style = &ImGui::GetStyle();
        style->WindowPadding = ImVec2(0, 0);
        style->ItemSpacing = ImVec2(10, 10);
        style->WindowBorderSize = 0;
        style->ScrollbarSize = 8.f;
        const ImVec2& region = ImGui::GetContentRegionMax();
        decoration(region );
        tabs();
 
        c::accent = { color[0], color[1], color[2], 1.f };

        ImGui::SetCursorPos(ImVec2(80, 5 - (tab_alpha * 5)));
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);
        {
            if (active_tab == 0)
            {
                edited::BeginChild("##Container0", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Psilent");
                    edited::Checkbox(("Perfect silent"), ("Redirect bullet to target") ,&settings::combat::psilent);
                    if (settings::combat::psilent) {
                        edited::Combo("Prediction", ("The predict type"), &settings::misc::predict_type, predicttype, IM_ARRAYSIZE(predicttype));
                    }
                    edited::Checkbox(("Draw fov"), ("Draws the radius of the silent"), &settings::combat::visualize_fov);
                    edited::ColorEdit4("Fov Color", "Changing the color of the radius", settings::combat::fov_color, picker_flags);
                    edited::SliderInt((("Fov value")), ("Changing the silent radius"), &settings::combat::fov, 20, 2000, "%d%");
                    edited::Combo("Bone", ("Where will the silent shoot"), &settings::combat::bones_target, bone_target_aimbot, IM_ARRAYSIZE(bone_target_aimbot));
                    edited::MultiCombo("Ignoring", ("Ignoring players"), settings::combat::ignore_players_type, ignoring_type_aimbot, IM_ARRAYSIZE(ignoring_type_aimbot));
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Exploits");
                    edited::Checkbox(("Bullet teleport"), ("Shoot at radius 2.6 and hit"), &settings::weapons::bullet_tp);
                    if (settings::weapons::bullet_tp)
                    {
                        edited::Checkbox("Target Behind Wall", ("Shoots to bullet teleport radius"), &settings::combat::hit_scan);
                        edited::Checkbox(("Show radius"), ("Drawing the bullet teleport radius"), &settings::weapons::show_radius);
                    }
                    edited::Checkbox(("STW"), ("Shoot Throw Wall - redirect bullets through walls to closest point on target"), &settings::weapons::stw);
                    edited::Checkbox(("Manipulator"), ("Desync eye position: server sees your eyes at a manipulated offset, so bullets legally originate from it. Works in combo with BulletTP/STW/hitscan while the key is held"), &settings::combat::manipulator);
                    edited::Keybind(("Manipulator key"), ("Hold this key to activate the manipulator desync"), &settings::misc::manipulator_key);
                }

                edited::EndChild();

                ImGui::SameLine(0, 0);

                edited::BeginChild("##Container1", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Other");
                    edited::Checkbox(("Silent Reload"), ("Auto reload on weapons"), &settings::combat::autoreload);
                    edited::Checkbox(("Auto Shoot"), ("Auto shoots to target"), &settings::combat::powershoot);
                    if (settings::combat::powershoot)
                    {
                        edited::Keybind("Auto Shoot key", ("Key to auto shoot"), &settings::combat::powershoot_key);
                        edited::SliderFloat("Bullets Counter", ("How many bullet will shot"), &settings::combat::bullet_counter, 1, 3, "%.0f");
                    }
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Visual Effect");
                    edited::Combo(("Hit Effect"),"The effect of the hit", & settings::misc::hitmaterial, hitmaterial, IM_ARRAYSIZE(hitmaterial));
                    edited::Checkbox(("Hammer spam"), ("Spams with hammer"), &settings::misc::hammer_spam);
                    if (settings::misc::hammer_spam) {
                        edited::Combo(("Spam Mode"), ("Where you will spam"), &settings::misc::spam_mode, hammer_spam, IM_ARRAYSIZE(hammer_spam));
                        edited::Keybind(("Hammer Spam key"), ("The button for using the hammer spam"), &settings::misc::spam_key);
                    }

                }
                edited::EndChild();
            }
            else if (active_tab == 1)
            {
                edited::BeginChild("##Container0", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Main");
                    edited::Checkbox(("Recoil control") ,"Recoil of the weapon", &settings::weapons::no_recoil);
                    if (settings::weapons::no_recoil) {
                        edited::SliderInt(("Recoil"),"Adjusting the recoil", &settings::weapons::recoil_control, 0, 100);
                    }
                    edited::Checkbox(("No spread"), "Spread of the weapon", &settings::weapons::no_spread);
                    if (settings::weapons::no_spread)
                    {
                        edited::SliderInt((("Spread")), "Adjusting the Spread", &settings::weapons::no_spread_value, 0, 100);
                    }
                    edited::Checkbox(("No sway"),"Disabling sight swing", &settings::weapons::no_sway);
                    edited::Checkbox(("Instant eoka"),"Instant eoka", &settings::weapons::eokatap);
                    edited::Checkbox(("Automatic"),"Automatic weapons", &settings::weapons::automatic);
                    edited::Checkbox(("Rapid fire"), "Do the weapon faster", &settings::combat::rapid_fire);
                }
                edited::EndChild();

                ImGui::SameLine(0, 0);

                edited::BeginChild("##Container1", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Other");
                    edited::Checkbox(("Fast bullet"),"Speeding up the bullet speed", &settings::weapons::fast_bullets);
                    edited::Checkbox(("Penetrate"), "Shoot through some objects", &settings::weapons::penetrate);
                    edited::Checkbox(("Insta charge compound"), "Fast bowstring pulling", &settings::weapons::compound);
                    edited::Checkbox(("Can Hold Items"),"Hold a weapon while sitting", &settings::weapons::minicopter_aim);
                    edited::Checkbox(("Jump shoot"),"Jump shooting", &settings::misc::can_attack);
                    edited::Checkbox(("Fast bow"), "Skips the bow reload time", &settings::weapons::fastbow);
                }
                edited::EndChild();
            }
            else if (active_tab == 2)
            {
                edited::BeginChild("##Container0", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Player");
                    edited::Checkbox("Name","Rendering the player's name", &settings::visual::name);
                    edited::Checkbox("Distance","Rendering the player's distance", &settings::visual::distance);
                    edited::Checkbox("Box", "Rendering the player's box", &settings::visual::box);
                    if (settings::visual::box)
                    {
                        edited::Combo(("Box Style"), "Changing the box style", &settings::visual::boxstyle, box_style, IM_ARRAYSIZE(box_style));
                    }
                    edited::Checkbox("Spike", "Render on player spike", &settings::visual::fillbox);
                    edited::Checkbox("Looking direction", "Line of looking on player", &settings::visual::lookingdirection);
                    edited::Checkbox("Weapon", "Rendering the player's weapon", &settings::visual::weapon);
                    edited::Checkbox("Target tracer", "Draw line to target", &settings::visual::target_trasers);
                    edited::Checkbox("Off arrows", "Render arrows on screen", &settings::visual::off_arrors);
                    edited::MultiCombo("Show flags","Draw flags on the player", settings::visual::flags_players, flags_type, IM_ARRAYSIZE(flags_type));
                    edited::MultiCombo("Ignoring","Ignore having selected flag", settings::visual::ignore_players_type, ignoring_type, IM_ARRAYSIZE(ignoring_type));
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "World");
                    edited::Checkbox(("Dropped Items"),"Rendering an object`s", &settings::visuals::other::dropped_items);
                    edited::Checkbox(("Hemp"), "Rendering an object`s", &settings::visuals::other::hemp);
                    edited::Checkbox(("Corpses"), "Rendering an object`s", &settings::visuals::other::corpse);
                    edited::Checkbox(("Bodybags"), "Rendering an object`s", &settings::visuals::other::bodybag);
                    edited::Checkbox(("Stashes"), "Rendering an object`s", &settings::visuals::other::stash);
                    if (settings::visuals::other::corpse || settings::visuals::other::stash || settings::visuals::other::hemp || settings::visuals::other::dropped_items) {
                        edited::SliderFloat(("Important ESP Distance"),"Maximum distance", &settings::visuals::other::draw_distance, 5.f, 400.f, "%.0f");
                        edited::Checkbox(("Show Distance    "), "Show the distance", &settings::visuals::other::show_distance);
                    }
                    edited::Checkbox(("Stone"), "Rendering an object`s", &settings::ores::stone);
                    edited::Checkbox(("Sulfur"), "Rendering an object`s", &settings::ores::sulfur);
                    edited::Checkbox(("Metal"), "Rendering an object`s", &settings::ores::metal);
                    if (settings::ores::sulfur || settings::ores::stone || settings::ores::metal) {
                        edited::SliderFloat(("Ores ESP Distance"), "Maximum distance", &settings::ores::draw_distance, 5.f, 400.f, "%.0f");
                        edited::Checkbox(("Show Collectables"),"Show the selected ones", &settings::ores::show_collectables);
                        edited::Checkbox(("Show Distance"), "Show the distance", &settings::ores::show_distance);
                    }
                   edited::Checkbox(("Chinook Crates"), "Rendering an object`s", &settings::visuals::crates::chinook);
                   edited::Checkbox(("Airdrops"), "Rendering an object`s", &settings::visuals::crates::supply);
                   edited::Checkbox(("Heli Box"), "Rendering an object`s", &settings::visuals::crates::heli);
                   edited::Checkbox(("Bradley Box"), "Rendering an object`s", &settings::visuals::crates::bradley);
                   edited::Checkbox(("Military Box"), "Rendering an object`s", &settings::visuals::crates::military);
                   edited::Checkbox(("Elite Box"), "Rendering an object`s", &settings::visuals::crates::elite);
                    if (settings::visuals::crates::supply || settings::visuals::crates::bradley || settings::visuals::crates::heli || settings::visuals::crates::military || settings::visuals::crates::elite) {
                        edited::SliderFloat(("Crates ESP Distance"), "Maximum distance", &settings::visuals::crates::draw_distance, 5.f, 3000.f, "%.0f");
                        edited::Checkbox(("Show Distance "), "Show the distance", &settings::visuals::crates::show_distance);
                    }
                }
                edited::EndChild();

                ImGui::SameLine(0, 0);

                edited::BeginChild("##Container1", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Player Colors");
                    edited::ColorEdit4("Name Color","Name Color Change", settings::visual::name_color, picker_flags);
                    edited::ColorEdit4("Box Color", "Box Color Change", settings::visual::box_color, picker_flags);
                    edited::ColorEdit4("Looking direction Color","Looking direction Color Change", settings::visual::Lookingdirection_color, picker_flags);
                    edited::ColorEdit4("Weapon Color", "Weapon Color Change", settings::visual::weapon_color, picker_flags);
                    edited::ColorEdit4("Off arrows Color", "Off arrows Color Change", settings::visual::off_color, picker_flags);
                    edited::ColorEdit4("Target player Color", "Target player Color Change", settings::visual::target_trasers_color, picker_flags);
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Npc");
                    edited::Checkbox("Name", "Rendering the npc's name", &settings::npc::name);
                    edited::Checkbox("Distance", "Rendering the npc's distance", &settings::npc::distance);
                    edited::Checkbox("Box", "Rendering the npc's box", &settings::npc::box);
                    if (settings::npc::box)
                    {
                        edited::Combo(("Box Style"), "Changing the box style", &settings::npc::boxstyle, box_style, IM_ARRAYSIZE(box_style));
                    }
                    edited::Checkbox("Weapon", "Rendering the npc's weapon", &settings::npc::weapon);
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "World");
                    edited::Checkbox(("Bears"), "Rendering an object`s", &settings::visuals::animals::bear);
                    edited::Checkbox(("Boars"), "Rendering an object`s", &settings::visuals::animals::pig);
                    edited::Checkbox(("Wolfs"), "Rendering an object`s", &settings::visuals::animals::wolf);
                    edited::Checkbox(("Horses"), "Rendering an object`s", &settings::visuals::animals::deer);
                    edited::Checkbox(("Chickens"), "Rendering an object`s", &settings::visuals::animals::chicken);
                    if (settings::visuals::animals::bear || settings::visuals::animals::pig || settings::visuals::animals::wolf || settings::visuals::animals::deer || settings::visuals::animals::chicken) {
                        edited::SliderFloat("Animals ESP Distance", "Maximum distance", &settings::visuals::animals::draw_distance, 5.f, 400.f, "%.0f");
                        edited::Checkbox(("Show Distance      "), "Show the distance", &settings::visuals::animals::show_distance);
                    }
                    edited::Checkbox(("Tool Cupboards"), "Rendering an object`s", &settings::visuals::base::tc);
                    edited::Checkbox(("Sleeping Bags"), "Rendering an object`s", &settings::visuals::base::sleeping_bag);
                    edited::Checkbox(("Beds"), "Rendering an object`s", &settings::visuals::base::bed);
                    edited::Checkbox(("Boxes"), "Rendering an object`s", &settings::visuals::base::boxes);
                    if (settings::visuals::base::tc || settings::visuals::base::sleeping_bag || settings::visuals::base::bed || settings::visuals::base::boxes) {
                        edited::SliderFloat(("Base ESP Distance"), "Maximum distance", &settings::visuals::base::draw_distance, 5.f, 400.f, "%.0f");
                        edited::Checkbox(("Show Distance     "), "Show the distance", &settings::visuals::base::show_distance);
                    }
                    edited::Checkbox(("Auto Turrets"), "Rendering an object`s", &settings::visuals::turrets::auto_turret);
                    edited::Checkbox(("Flame Turrets"), "Rendering an object`s", &settings::visuals::turrets::flame_turret);
                    edited::Checkbox(("Shotgun Traps"), "Rendering an object`s", &settings::visuals::turrets::shotgun_turret);
                    edited::Checkbox(("SAM Sites"), "Rendering an object`s", &settings::visuals::turrets::sam_site);
                    edited::Checkbox(("Landmines"), "Rendering an object`s", &settings::visuals::turrets::landmine);
                    edited::Checkbox(("Beartraps"), "Rendering an object`s", &settings::visuals::turrets::bear_trap);
                    if (settings::visuals::turrets::auto_turret || settings::visuals::turrets::flame_turret || settings::visuals::turrets::shotgun_turret || settings::visuals::turrets::landmine || settings::visuals::turrets::bear_trap) {
                        edited::SliderFloat(("Traps ESP Distance"), "Maximum distance", &settings::visuals::turrets::draw_distance, 5.f, 400.f, "%.0f");
                        edited::Checkbox(("Show Distance   "), "Show the distance", &settings::visuals::turrets::show_distance);
                    }
                }
                edited::EndChild();
            }
            else if (active_tab == 3)
            {
               edited::BeginChild("##Container0", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
               {
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Main");
                   edited::Checkbox("Fake admin","Gives some admin functions", &settings::misc::fakeadmin);
                   edited::Checkbox("Fast loot", "Fast looting", &settings::misc::fast_loot);
                   edited::Checkbox(("Suicide"),"Fast suicide", &settings::misc::mass_suicide);
                   if (settings::misc::mass_suicide)
                   {
                       edited::Keybind("Suicide key","Key to suicide", &settings::misc::mass_suicide_key);
                   }
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Other");
                   edited::Checkbox("Silent loot stash","Opening the stashes without digging", &settings::misc::stesh_finder);
                   if (settings::misc::stesh_finder)
                   {
                       edited::Keybind("Silent loot stash key","The button for using the silent loot stash", &settings::misc::stesh_finder_key);
                   }
                   edited::Checkbox(("Custom modelstate"), "Changing the modelstate", &settings::misc::ModelState);
                   if (settings::misc::ModelState)
                   {
                       edited::Combo("Modelstate","Modelstate styles", &settings::misc::modelstate, modelstate_pos, IM_ARRAYSIZE(modelstate_pos));
                   }
                   edited::Checkbox("Spiderman", "Climbing on walls", &settings::misc::spiderman);
                   edited::Checkbox("Omni-Sprint", "Auto shift", &settings::misc::omnidirectional_sprinting);
                   edited::Checkbox("Walk on water","Walking on water", &settings::misc::walkonwater);
                   edited::Checkbox(("Fly Stopper"),"Does not give a kick for flyhack", &settings::misc::fly_auto_stop);
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Player");
                   edited::Checkbox("Chams","Watch on your hands", &settings::visuals::chams::hand_chams);
                   if (settings::visuals::chams::hand_chams)
                   {
                       edited::Combo(("Chams Type"),"Chams style", &settings::visuals::chams::hand_chams_type, hand_chams_type, IM_ARRAYSIZE(hand_chams_type), 7);
                       edited::Combo(("Render Mode"),"What will the champs work on", &settings::visuals::chams::chams_render_mode, chams_render_mode, IM_ARRAYSIZE(chams_render_mode), 3);
                   }
                   edited::Checkbox(("Hitsound"),"Sound when hit", &settings::misc::custom_hitsound);
                   if (settings::misc::custom_hitsound)
                   {
                       edited::Combo(("Sound"),"Sound type", &settings::misc::hitsound_style, hitsound_style, IM_ARRAYSIZE(hitsound_style));
                   }
                   edited::Checkbox(("Ambient"),"Highlighting the world", &settings::misc::bright_ambient);
                   edited::Checkbox(("Weapon spam"),"Weapon spammer", &settings::misc::weapon_spam);
                   if (settings::misc::weapon_spam)
                   {
                       edited::Keybind("Spam key", "The button for using the spam", &settings::misc::weapon_spam_key);
                   }
                   edited::Checkbox(("Mie Changer"),"Changing the world", &settings::misc::mie_changer);
                   if (settings::misc::mie_changer) {
                       edited::SliderFloat(("Mie Amount"),"Changing the world size", &settings::misc::mie, 1.f, 100.f);
                   }
                   edited::Checkbox(("Rayleigh Changer"), "Changing the world", &settings::misc::rayleigh_changer);
                   if (settings::misc::rayleigh_changer) {
                       edited::SliderFloat(("Rayleigh Amount"), "Changing the world size", &settings::misc::rayleigh, 1.f, 100.f);
                   }
                   edited::Checkbox(("Brightness Changer"), "Changing the world", &settings::misc::brightness_changer);
                   if (settings::misc::brightness_changer) {
                       edited::SliderFloat(("Brightness Amount"), "Changing the world size", &settings::misc::brightness, 1.f, 50.f);
                   }
                   edited::Checkbox(("No rain & snowfall"), "Changing the world", &settings::misc::no_rain);
               }
               edited::EndChild();

               ImGui::SameLine(0, 0);

               edited::BeginChild("##Container1", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
               {
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Other");
                   edited::Checkbox(("Interactive Debug"),"objects on/off through walls", &settings::misc::interactive_debug);
                   if (settings::misc::interactive_debug)
                   {
                       edited::Keybind(("Debug Key"), "The button for using the debug", &settings::misc::debugging);
                   }
                   edited::Checkbox(("Infinity Jump"), "Endless jumps", &settings::misc::inf_jump);
                   edited::Checkbox(("SpeedHack"), "Increase Player Speed", &settings::misc::speedhack);
                   if (settings::misc::speedhack) {

                       edited::Keybind("SpeedHack key", "Key to speedhack", &settings::misc::speedhackbind);
                   }
                   edited::Checkbox(("Auto pick up"), "Auto lifting of objects", &settings::misc::auto_pickup);
                   edited::Checkbox(("Anti aim"), "The player's twister", &settings::misc::anti_aim);
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Player");
                   edited::Checkbox("Custom fov","Changing the player's fov", &settings::misc::fov);
                   if (settings::misc::fov)
                   {
                       edited::SliderInt("Fov scale","Changing the size of the fov", &settings::misc::fov_scale, 30, 120);
                       edited::Keybind("Zoom key", "The button for using the zoom", &settings::misc::zoom_key);
                   }
                   edited::Checkbox(("Aspect Ratio"), "Changing the player's aspect", &settings::misc::aspect_ratio);
                   if (settings::misc::aspect_ratio)
                   {
                       edited::SliderFloat("Aspect Ratio scale", "Change the ratio of screen", &settings::misc::aspect_ratio_value, 0.2f, 2.0f);
                   }
                   edited::Checkbox("Movement Line", "The line behind the player", &settings::misc::movement_line);
                   edited::Checkbox("Bullet tracers", "The line behind the bullet", &settings::misc::bullet_tracers);
                   ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Indicators");
                   edited::Checkbox(("Fly indicator"),"Flyhack indicator", &settings::misc::flyhack_indicator);
                   edited::Checkbox(("Reload indicator"), "Reload indicator", &settings::misc::reload_coldown);
                   edited::Checkbox(("Target name"), "Target name", &settings::combat::target_name);
               }
              edited::EndChild();
            }
            else if (active_tab == 4)
            {
                edited::BeginChild("##Container0", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Config List");
                    std::vector<std::string> files;
                    config_manager::read_directory(("C:/Kiero/"), files);
                    for (auto cfg : config.GetConfigList())
                    {
                        if (edited::Selectable(cfg.c_str(), cfg == settings::selected_cfg))
                        {
                            settings::selected_cfg = cfg;
                        }
                    }
                    static bool creating = false;
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Config");
                    if (edited::Button(("Save"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                        config.Save();
                    }
                    if (edited::Button(("Load"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                        config.Load();
                    }
                    if (!creating)
                    {
                        if (edited::Button(("Create"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                            creating = true;
                        }

                    }
                    else
                    {
                        ImGui::InputTextEx("v", "Config name", settings::ConfigName, 65, ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40), NULL);
                        if (edited::Button(("Apply"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                            creating = false;
                            config.Create();
                        }
                    }
                    if (edited::Button(("Remove"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                        config.Remove();
                    }
                    if (edited::Button(("Open folder"), ImVec2((c::background::size.x - 80) / 2, 40))) {
                        system("start C:\\kiero");
                    }
                }
                edited::EndChild();
                ImGui::SameLine(0, 0);

                edited::BeginChild("##Container1", ImVec2((c::background::size.x - 80) / 2, c::background::size.y - 5), NULL);
                {
                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::elements::text)), "Menu");
                    edited::Checkbox("Watermark", "Off/On watermark", &settings::menu::watermark);
                    edited::ColorEdit4("Accented Color", "Setting the main color of the menu.", color, picker_flags);
                    edited::Combo(("Font Style"), "Font style", &settings::misc::font, font_, IM_ARRAYSIZE(font_), 2);
                }
                edited::EndChild();
            }
        }
        ImGui::PopStyleVar();
    }

    ImGui::End();
}