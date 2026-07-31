#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class Font
{
private:
    std::string name;
    TTF_Font* font;
public:
    Font(std::string font_path, float font_size);

    ~Font();

    std::string get_name();

    void set_name(std::string font_name);

    float get_size();

    bool set_size(float font_size);

    TTF_FontStyleFlags get_style();

    void set_style(TTF_FontStyleFlags font_style);

    TTF_HorizontalAlignment get_alignment();

    void set_alignment(TTF_HorizontalAlignment h_align);

    TTF_Text* gen_text(TTF_TextEngine* t_eng, std::string text);
};
