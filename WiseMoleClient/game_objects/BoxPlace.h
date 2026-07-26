#pragma once

#include "GameObject.h"
#include <SDL3/SDL.h>

class BoxPlace : public GameObject
{
private:
	float w{ 50.0f }, h{ 50.0f }; // Размеры места под ящики
	SDL_FRect fr{ 0.0f, 0.0f, 0.0f, 0.0f };
public:
	BoxPlace();

	void render(SDL_Renderer* renderer);

	void set_position(float x, float y);

	void move(float diff_x, float diff_y);
};
