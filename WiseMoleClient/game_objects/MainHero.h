#pragma once

#include "GameObject.h"
#include <SDL3/SDL.h>

class MainHero : public GameObject
{
private:
	SDL_FRect fr{ 0.0f, 0.0f, 0.0f, 0.0f };
public:
	MainHero();

	void render(SDL_Renderer* renderer);

	void set_position(float x, float y);

	void move(float diff_x, float diff_y);
};
