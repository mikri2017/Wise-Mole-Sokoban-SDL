#pragma once

#include "GameObject.h"

class WallBlock : public GameObject
{
private:
	float w{ 50.0f }, h{ 50.0f }; // Размеры блока стены
	SDL_FRect fr{ 0.0f, 0.0f, 0.0f, 0.0f };
public:
	WallBlock();

	void render(SDL_Renderer* renderer);

	void set_position(float x, float y);

	void move(float diff_x, float diff_y);
};
