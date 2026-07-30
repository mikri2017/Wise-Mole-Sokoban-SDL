#include "FontMgr_old.h"

FontMgr_old::FontMgr_old()
{
    scn_indent = 10;
    font_size = 10;
    font_name = "assets/fonts/XoloniumBold.ttf";

    reload_font();

    font_color = {0, 0, 255};
    letter_size_px = 20;
    x_start_left = 0;
    x_start_right = 1366;
}

FontMgr_old::~FontMgr_old()
{
    TTF_CloseFont(font);
}

void FontMgr_old::set_letter_size_in_px(float l_size_px)
{
    if (l_size_px < 0)
        l_size_px = 0;

    letter_size_px = l_size_px;
}

void FontMgr_old::set_font(std::string f_name)
{
    font_name = f_name;
    reload_font();
}

void FontMgr_old::set_font_color(const SDL_Color &f_color)
{
    font_color = f_color;
    reload_font();
}

void FontMgr_old::set_text_xstart_from(float x_left, float x_right)
{
    x_start_left = x_left;
    x_start_right = x_right;
}

void FontMgr_old::set_font_size(float f_size)
{
    font_size = f_size;
    reload_font();
}

void FontMgr_old::render(SDL_Renderer *r, std::string text, float y, float h, FontAlign f_align)
{
    float x;
    float text_width_px = letter_size_px * static_cast<float>(text.length());

    // Настраиваем форматирование текста
    if(f_align == FontAlign::Right) // по правому краю
        x = x_start_right - scn_indent - text_width_px;
    else if(f_align == FontAlign::Centre) // по центру
        x = x_start_left + (x_start_right - x_start_left - text_width_px) / 2;
    else // по левому краю
        x = x_start_left;

    SDL_FRect dstrect = { x, y, text_width_px, h };

    // Русский язык в тексте не поддерживается :(
    // c_str() не проносит нормально русские буквы
    // Заполнение char* русскими буквами и его отдача дает русский язык на экране
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), 0, font_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(r, surface);

    SDL_RenderTexture(r, texture, nullptr, &dstrect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

void FontMgr_old::reload_font()
{
    TTF_CloseFont(font);
    font = TTF_OpenFont(font_name.c_str(), font_size);
    if (!font)
    {
        SDL_Log("Couldn't open TTF font: %s", SDL_GetError());
        return;
    }
}
