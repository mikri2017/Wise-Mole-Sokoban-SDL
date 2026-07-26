#include "BoxPlace.h"

BoxPlace::BoxPlace()
{
	// Назначаем начальные координаты и размеры
	set_position(0, 0);
	fr.w = w;
	fr.h = h;

	// Можно проходить сквозь
	col_c.set_area(0, 0, 0, 0);
}

void BoxPlace::render(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 160, 160, 160, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &fr);
}

void BoxPlace::set_position(float x, float y)
{
	GameObject::set_position(x, y);
	SDL_FPoint p = get_position();
	fr.x = p.x;
	fr.y = p.y;
}

void BoxPlace::move(float diff_x, float diff_y)
{
	// Место под ящик статично
	return;
}
