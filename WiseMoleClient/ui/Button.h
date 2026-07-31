#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "../ui/Caption.h"

class Font;

class Button
{
private:
    SDL_FRect btn{ 0.0f, 0.0f, 0.0f, 0.0f };
    Caption* cap_btn{ nullptr };
public:
    ~Button();

    void set_font(Font* new_font);

    void set_font_color(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);

    void set_caption(std::string caption);

    void set_position(float x, float y);

    void set_size(float w, float h);

    bool check_hover(float x, float y) const;

    void render(SDL_Renderer *r);
};
