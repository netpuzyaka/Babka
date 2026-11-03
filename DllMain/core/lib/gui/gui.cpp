#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <vector>
#include <string>
#include <d3d11.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx11tex.h"
#include <functional>
#include <animations.hpp>
#include "managers/FontManager.hpp"
#include "managers/ImageManager.hpp"
#include "compbuilder/CompBuilder.hpp"
#include "managers/WidgetsManager.hpp"
#include "managers/StyleManager.hpp"
#include "fonts.h"
#include "unicodes.hpp"
#include "managers/TabsManager.hpp"
#include "managers/ChildManager.hpp"
#include "managers/PopupManager.hpp"
#include "managers/SearchManager.hpp"

#include <gui.hpp>

#pragma comment(lib, "freetype64.lib")

using namespace ImGui;

#include "managers/NotifyManager.hpp"
#include "../../menu.h"

void GUI::initialize( ID3D11Device* device ) {
	size = ImVec2{ 750, 500 };

	GImGui->IO.IniFilename = "";

	StyleManager::get( ).Styles( );
	StyleManager::get( ).Colors( );

	fonts.resize( fonts_size );

	fonts.at( font ).setup( b_font, sizeof( b_font ),
		{ 14, 12 },
		GetIO( ).Fonts->GetGlyphRangesCyrillic( ) );

	fonts.at(esp_font).setup(b_font_hellhit, sizeof(b_font_hellhit),
		{ 15, 14, 13, 12 },
		GetIO().Fonts->GetGlyphRangesCyrillic());

	const static ImWchar icons_ranges[] = { 0x1 + 16000, 0x1 + 17170, 0 };
	fonts.at( icons ).setup( glyphter, sizeof( glyphter ),
		{ 14, 12 },
		icons_ranges );


	init_begins();
}

void GUI::draw( ) {
	static bool bools[100];
	static int ints[100];
	static bool multicombo_values[4];
	static float col[100][4];
	static char buf[16];

	SetNextWindowSize( size );
	Begin( "GUI", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus );
	{
		BeginChild( "navbar", { 180, 0 }, 0, ImGuiWindowFlags_NoBackground );
		{
			SetCursorPos( { 14, 14 } );
			PushStyleColor( ImGuiCol_FrameBg, GetColorU32( ImGuiCol_FrameBg, 0.f ) );
			PushStyleVar( ImGuiStyleVar_FrameBorderSize, 1 );
			PushItemFlag( ImGuiItemFlags_NoNav, true );
			if ( WidgetsManager::get( ).TextField( "##search", SearchManager::get( ).search_buf, sizeof( SearchManager::get( ).search_buf ), { GetWindowWidth( ) - 28, 0 }, "Search...", i_search_md ) ) {
				SearchManager::get( ).update( );
			}
			PopItemFlag( );
			PopStyleVar( );
			PopStyleColor( );
			WidgetsManager::get( ).Separator( );
			SetCursorPosX( 14 );
			TabsManager::get( ).render_tabs( 8 );

			GetWindowDrawList( )->AddRectFilled( GetWindowPos( ) + ImVec2{ GetWindowWidth( ) - 1, 0 }, GetWindowPos( ) + GetWindowSize( ), GetColorU32( ImGuiCol_Border ) );

		}
		EndChild( );

		SameLine( 0, 0 );

		if ( strlen( SearchManager::get( ).search_buf ) > 0 || SearchManager::get( ).get_anim( ) > 0.05f ) PushStyleVar( ImGuiStyleVar_WindowPadding, { 14, 14 } );
		BeginChild( "main", { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );
		{
			if ( strlen( SearchManager::get( ).search_buf ) > 0 || SearchManager::get( ).get_anim( ) > 0.05f ) PopStyleVar( );

			ChildManager::get( ).smoothscroll( );

			if ( strlen( SearchManager::get( ).search_buf ) == 0 && SearchManager::get( ).get_anim( ) < 0.05f ) {
				TabsManager::get( ).render_subtabs( 20 );

				auto window = GetCurrentWindow( );

				PushStyleVar( ImGuiStyleVar_Alpha, GImGui->Style.Alpha * TabsManager::get( ).get_anim( ) * GImGui->Style.Alpha );
				PushStyleVar( ImGuiStyleVar_WindowPadding, { 14, 14 } );
				BeginChild( "content", { 0, 0 }, ImGuiChildFlags_AlwaysUseWindowPadding, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );
				{
					TabsManager::get( ).draw_page( window );
				}
				EndChild( );
				PopStyleVar( 2 );
			} else {
				SearchManager::get( ).draw( );
			}
		}
		EndChild( );
		
		PopupManager::get( ).handle( );
	}
	End( );

	NotifyManager::get( ).draw( );
}