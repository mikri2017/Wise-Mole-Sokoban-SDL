#pragma once

#include <SDL3/SDL.h>
#include "CollisionCaps.h"

class GameObject
{
private:
	int hp{ 0 }; // Очки здоровья
	int hp_max{ 0 }; // Максимальное здоровье
	SDL_FPoint pos{ 0, 0 }; // Расположение по оси X и Y
protected:
	CollisionCaps col_c{ CollisionCaps() };
public:
	int get_hp();

	void set_max_hp(int hp_max);

	void add_hp(int hp);

	bool add_damage(int dmg);

	virtual void render() {};

	SDL_FPoint get_position();

	void set_position(float x, float y);

	void move(float diff_x, float diff_y);

	bool check_collision(GameObject game_o);

	bool check_collision(CollisionCaps* cc);

	bool check_inside(CollisionCaps* cc);
};
