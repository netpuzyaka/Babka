#include "../../main/visuals/entitylist.h"
static void imgui_render() {
	DrawList = ImGui::GetBackgroundDrawList();

	entitylist();
}