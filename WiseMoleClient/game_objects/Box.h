#pragma once

#include "GameObject.h"

class Box : public GameObject
{
private:
	SDL_FRect fr{ 0.0f, 0.0f, 0.0f, 0.0f };
	bool in_place{ false };
public:
	Box();

	void render(SDL_Renderer* renderer);

	void set_position(float x, float y);

	void set_size(float w, float h);

	void move(float diff_x, float diff_y);

	void set_status(bool in_place);
};
