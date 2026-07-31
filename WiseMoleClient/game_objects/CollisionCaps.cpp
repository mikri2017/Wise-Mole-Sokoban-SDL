#include "CollisionCaps.h"

SDL_FRect CollisionCaps::get_area()
{
    return { area.x, area.y, area.w, area.h };
}

void CollisionCaps::set_area(float x, float y, float w, float h)
{
    if (x > 0)
        area.x = x;
    else area.x = 0;

    if (y > 0)
        area.y = y;
    else area.y = 0;

    if (w > 0)
        area.w = w;
    else area.w = 0;

    if (h > 0)
        area.h = h;
    else area.h = 0;
}

bool CollisionCaps::check_collision(CollisionCaps * cc)
{
    return cc->check_collision(area);
}

bool CollisionCaps::check_collision(SDL_FRect area_ch)
{
    // Проверка, что мы пересекаемся с объектом
    if (area.x < area_ch.x + area_ch.w &&
        area.x + area.w > area_ch.x &&
        area.y < area_ch.y + area_ch.h &&
        area.y + area.h > area_ch.y)
    {
        return true;
    }

    return false;
}
