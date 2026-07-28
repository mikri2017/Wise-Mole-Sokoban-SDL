#pragma once

#include <iostream>
#include <SDL3/SDL.h>

class FontMgr;

class Button
{
private:
    std::string s_caption;
    SDL_FRect btn;
    FontMgr *font_caption;
    SDL_Color font_color;
    int font_margin_left_right;
    int font_margin_up_dowm;
public:
    Button();

    ~Button();

    void set_caption(std::string caption);

    void set_position(float x, float y);

    void set_size(float w, float h);

    bool check_hover(float x, float y) const;

    void render(SDL_Renderer *r);
};
