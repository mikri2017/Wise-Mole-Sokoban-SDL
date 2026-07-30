#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>

Font::Font(std::string font_path, float font_size)
{
	// Создаем шрифт
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font)
		SDL_Log("Font open error [%s]", font_path.c_str());
}

Font::~Font()
{
	if (font)
		TTF_CloseFont(font);
}

std::string Font::get_name()
{
	return name;
}

void Font::set_name(std::string font_name)
{
	name = font_name;
}

float Font::get_size()
{
	float font_size = TTF_GetFontSize(font);
	if (font_size == 0.0f)
	{
		SDL_Log("Error on getting font size: %s", SDL_GetError());
		return 0.0f;
	}

	return font_size;
}

bool Font::set_size(float font_size)
{
	if (!TTF_SetFontSize(font, font_size))
	{
		SDL_Log("Error on set size of font: %s", SDL_GetError());
		return false;
	}

	return true;
}

TTF_FontStyleFlags Font::get_style()
{
	return TTF_GetFontStyle(font);
}

void Font::set_style(TTF_FontStyleFlags font_style)
{
	TTF_SetFontStyle(font, font_style);
}

TTF_HorizontalAlignment Font::get_alignment()
{
	return TTF_GetFontWrapAlignment(font);
}

void Font::set_alignment(TTF_HorizontalAlignment h_align)
{
	TTF_SetFontWrapAlignment(font, h_align);
}

TTF_Text* Font::gen_text(TTF_TextEngine* t_eng, std::string text)
{
	return TTF_CreateText(t_eng, font, text.c_str(), 0);
}
