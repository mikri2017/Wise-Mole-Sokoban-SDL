#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "../ui/Font.h"
#include "../ui/Caption.h"

class Button
{
private:
    SDL_FRect btn{ 0.0f, 0.0f, 0.0f, 0.0f };
    Font* font{ nullptr };
    Caption* cap_btn{ nullptr };
public:
    ~Button();

    void init(SDL_Renderer* r);

    void set_caption(std::string caption);

    void set_position(float x, float y);

    void set_size(float w, float h);

    bool check_hover(float x, float y) const;

    void render(SDL_Renderer *r);
};
