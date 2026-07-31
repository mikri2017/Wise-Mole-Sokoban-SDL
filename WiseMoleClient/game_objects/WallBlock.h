#pragma once

#include "GameObject.h"

class WallBlock : public GameObject
{
private:
    SDL_FRect fr{ 0.0f, 0.0f, 0.0f, 0.0f };
public:
    WallBlock();

    void render(SDL_Renderer* renderer);

    void set_position(float x, float y);

    void set_size(float w, float h);

    void move(float diff_x, float diff_y);
};
