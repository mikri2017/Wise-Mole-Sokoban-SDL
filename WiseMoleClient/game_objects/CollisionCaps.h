#pragma once

#include <SDL3/SDL.h>

class CollisionCaps
{
private:
	SDL_FRect area;
public:
	SDL_FRect get_area();

	void set_area(float x, float y, float w, float h);

	bool check_collision(CollisionCaps* cc);

	bool check_collision(SDL_FRect area_ch);

	bool check_inside(CollisionCaps* cc);

	bool check_inside(SDL_FRect area_ch);
};
