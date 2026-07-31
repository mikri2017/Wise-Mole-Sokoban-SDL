#include "BoxPlace.h"

BoxPlace::BoxPlace()
{
    // Назначаем начальные координаты и размеры
    set_position(0, 0);
    fr.w = get_width();
    fr.h = get_height();

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

void BoxPlace::set_size(float w, float h)
{
    GameObject::set_size(w, h);
    fr.w = get_width();
    fr.h = get_height();

    col_c.set_area(fr.x, fr.y, get_width(), get_width());
}

void BoxPlace::move(float diff_x, float diff_y)
{
    // Место под ящик статично
    return;
}
