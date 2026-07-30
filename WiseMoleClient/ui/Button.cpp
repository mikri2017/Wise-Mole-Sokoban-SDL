#include "Button.h"

Button::~Button()
{
    if (cap_btn)
        delete cap_btn;

    if (font)
        delete font;
}

void Button::init(SDL_Renderer* r)
{
    // Задаем параметры текста
    font = new Font("assets/fonts/XoloniumBold.ttf", 48.0f);

    cap_btn = new Caption(r);
    cap_btn->set_font(font);
    cap_btn->set_font_color(255, 0, 0);
}

void Button::set_caption(std::string caption)
{
    cap_btn->set_caption(caption);
}

void Button::set_position(float x, float y)
{
    btn.x = x;
    btn.y = y;
    cap_btn->set_position(btn.x + 10, btn.y + 5);
}

void Button::set_size(float w, float h)
{
    btn.w = w;
    btn.h = h;
}

bool Button::check_hover(float x, float y) const
{
    if(x >= btn.x && x <= btn.x + btn.w)
    {
        if(y >= btn.y && y <= btn.y + btn.h)
            return true;
    }

    return false;
}

void Button::render(SDL_Renderer *r)
{
    SDL_RenderRect(r, &btn);
    cap_btn->render();
}
