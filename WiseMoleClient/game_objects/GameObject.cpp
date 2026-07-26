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
	return pos;
}

void GameObject::set_position(float x, float y)
{
	if (x > 0)
		pos.x = x;
	else pos.x = 0;

	if (y > 0)
		pos.y = y;
	else pos.y = 0;
}

void GameObject::move(float diff_x, float diff_y)
{
	pos.x += diff_x;
	if (pos.x < 0)
		pos.x = 0;

	pos.y += diff_y;
	if (pos.y < 0)
		pos.y = 0;
}

bool GameObject::check_collision(GameObject game_o)
{
	return game_o.check_collision(&col_c);
}

bool GameObject::check_collision(CollisionCaps* cc)
{
	return col_c.check_collision(cc);
}

bool GameObject::check_inside(CollisionCaps* cc)
{
	return col_c.check_inside(cc);
}
