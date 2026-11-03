#include "imgui.h"

namespace font
{
	inline ImFont* icomoon = nullptr;
	inline ImFont* lexend_bold = nullptr;
	inline ImFont* lexend_regular = nullptr;
	inline ImFont* lexend_general_bold = nullptr;
	inline ImFont* lexend_general_bold_2 = nullptr;

	inline ImFont* icomoon_widget = nullptr;
	inline ImFont* icomoon_widget2 = nullptr;
}

namespace c
{
	inline ImVec2 menu_pos;
	inline ImVec4 accent = ImColor(112, 110, 215);

	namespace background
	{
		inline ImVec4 filling_top = ImColor(26, 26, 26);
		inline ImVec4 filling = ImColor(20, 20, 20);
		inline ImVec4 stroke = ImColor(18, 18, 18);
		inline ImVec2 size = ImVec2(700, 550);

		inline float rounding = 6;

	}

	namespace elements
	{
		inline ImVec4 mark = ImColor(255, 255, 255);

		inline ImVec4 stroke = ImColor(36, 36, 36);
		inline ImVec4 background = ImColor(26, 26, 26);
		inline ImVec4 background_widget = ImColor(30, 30, 30);

		inline ImVec4 text_active = ImColor(255, 255, 255);
		inline ImVec4 text_hov = ImColor(81, 92, 109);
		inline ImVec4 text = ImColor(153, 153, 153);

		inline float rounding = 5;
	}
	namespace tab
	{
		inline ImVec4 tab_active = ImColor(46, 46, 46);
		inline ImVec4 tab = ImColor(31, 31, 31);
		inline ImVec4 tab_hov = ImColor(38, 38, 38);
		inline ImVec4 border = ImColor(14, 14, 15);
	}

}