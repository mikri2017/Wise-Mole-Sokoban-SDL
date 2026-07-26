#include "GameObject.h"

int GameObject::get_hp()
{
	return hp;
}

void GameObject::set_max_hp(int hp_max)
{
	if (hp > 0)
		hp = hp_max;
	else hp = 0;
}

void GameObject::add_hp(int hp_cure)
{
	if (hp_cure < 0) // Метод лечит, а не калечит
		return;

	// Восстанавливаем объект
	hp += hp_cure;
	if (hp < hp_max)
		hp = hp_max;
}

bool GameObject::add_damage(int dmg)
{
	// Вернет true, если объект еще цел/жив
	hp -= dmg;
	if (hp < 0)
	{
		hp = 0;
		return false;
	}

	return true;
}

SDL_FPoint GameObject::get_position()
{
	return {fr_area.x, fr_area.y};
}

float GameObject::get_width()
{
	return fr_area.w;
}

float GameObject::get_height()
{
	return fr_area.h;
}

void GameObject::set_position(float x, float y)
{
	if (x > 0)
		fr_area.x = x;
	else fr_area.x = 0;

	if (y > 0)
		fr_area.y = y;
	else fr_area.y = 0;
}

void GameObject::set_size(float w, float h)
{
	if (w >= 0)
		fr_area.w = w;
	else fr_area.w = 0;

	if (h >= 0)
		fr_area.h = h;
	else fr_area.h = 0;
}

void GameObject::move(float diff_x, float diff_y)
{
	fr_area.x += diff_x;
	if (fr_area.x < 0)
		fr_area.x = 0;

	fr_area.y += diff_y;
	if (fr_area.y < 0)
		fr_area.y = 0;
}

bool GameObject::check_collision(GameObject game_o)
{
	return game_o.check_collision(&col_c);
}

bool GameObject::check_collision(CollisionCaps* cc)
{
	return col_c.check_collision(cc);
}

bool GameObject::check_inside(GameObject* game_o)
{
	// Проверка, что переданный объект внутри текущего

	SDL_FPoint pos_go = game_o->get_position();

	if (fr_area.x >= pos_go.x && fr_area.y >= pos_go.y &&
		fr_area.x + fr_area.w <= pos_go.x + game_o->get_width() &&
		fr_area.y + fr_area.h <= pos_go.y + game_o->get_height())
	{
		return true;
	}

	return false;
}

bool GameObject::check_inside(CollisionCaps* cc)
{
	SDL_FRect cc_area = cc->get_area();

	if (fr_area.x >= cc_area.x && fr_area.y >= cc_area.y &&
		fr_area.x + fr_area.w <= cc_area.x + cc_area.w &&
		fr_area.y + fr_area.h <= cc_area.y + cc_area.h)
	{
		return true;
	}

	return false;
}
