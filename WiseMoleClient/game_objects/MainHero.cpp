#include "MainHero.h"

MainHero::MainHero()
{
    // Назначаем начальные координаты
    // и размеры героя
    set_position(0, 0);    
    fr.w = get_width();
    fr.h = get_height();

    // И капсулы столкновений
    col_c.set_area(0, 0, get_width(), get_height());
}

void MainHero::render(SDL_Renderer* r)
{
    SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(r, &fr);
}

void MainHero::set_position(float x, float y)
{
    GameObject::set_position(x, y);
    SDL_FPoint p = get_position();
    fr.x = p.x;
    fr.y = p.y;

    col_c.set_area(p.x, p.y, get_width(), get_height());
}

void MainHero::set_size(float w, float h)
{
    GameObject::set_size(w, h);
    fr.w = get_width();
    fr.h = get_height();

    col_c.set_area(fr.x, fr.y, get_width(), get_width());
}

void MainHero::move(float diff_x, float diff_y)
{
    // Перемещаем объект
    GameObject::move(diff_x, diff_y);

    // Обновляем позицию для рисовки
    SDL_FPoint p = get_position();
    fr.x = p.x;
    fr.y = p.y;

    // И расположение капсулы столкновений
    col_c.set_area(fr.x, fr.y, fr.w, fr.h);
}
