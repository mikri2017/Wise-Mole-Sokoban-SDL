#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Font.h"

class Caption
{
private:
    SDL_FRect area{ 0, 0, 0, 0 };
    TTF_TextEngine* t_eng{ nullptr };
    TTF_Text* txt{ nullptr };
    Font* font{ nullptr };
    SDL_Color font_c{ 0, 0, 0, SDL_ALPHA_OPAQUE };

    std::string text{ "" };

    bool need_update{ true };

    void update_txt(SDL_Renderer *r);
public:
    Caption(Font* new_font);

    ~Caption();

    std::string get_caption();

    void set_caption(std::string new_text);

    void set_font(Font* new_font);

    void set_font_color(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);

    void set_position(float x, float y);

    void set_width(float w);

    void set_height(float h);

    void render(SDL_Renderer *r);
};
