#pragma once

#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

enum class FontAlign {
    Right,
    Left,
    Centre
};

class FontMgr_old
{
private:
    TTF_Font* font{ nullptr };
    std::string font_name;
    float font_size{ 0 };
    SDL_Color font_color{ 0, 0, 0, 0 };

    float letter_size_px;
    float scn_indent;
    float x_start_left{ 0 }, x_start_right{ 0 };
public:
    FontMgr_old();

    ~FontMgr_old();

    void set_letter_size_in_px(float l_size_px);

    void set_font(std::string path);

    void set_font_size(float f_size);

    void set_font_color(const SDL_Color &f_color);

    void set_text_xstart_from(float x_left = 0, float x_right = 0);

    void render(SDL_Renderer *r, std::string text, float y, float h, FontAlign f_align);

    void reload_font();
};
