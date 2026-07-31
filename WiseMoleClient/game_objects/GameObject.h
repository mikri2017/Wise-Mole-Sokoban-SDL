#pragma once

#include <SDL3/SDL.h>
#include "CollisionCaps.h"

class GameObject
{
private:
    int hp{ 0 }; // Очки здоровья
    int hp_max{ 0 }; // Максимальное здоровье

    // Расположение по осям X и Y с размерами
    SDL_FRect fr_area{ 0.0f, 0.0f, 0.0f, 0.0f };
protected:
    CollisionCaps col_c{ CollisionCaps() };
public:
    int get_hp();

    void set_max_hp(int hp_max);

    void add_hp(int hp);

    bool add_damage(int dmg);

    virtual void render() {};

    SDL_FPoint get_position();

    float get_width();

    float get_height();

    void set_position(float x, float y);

    void set_size(float w, float h);

    void move(float diff_x, float diff_y);

    bool check_collision(GameObject game_o);

    bool check_collision(CollisionCaps* cc);

    bool check_inside(GameObject* game_o);

    bool check_inside(CollisionCaps* cc);
};
