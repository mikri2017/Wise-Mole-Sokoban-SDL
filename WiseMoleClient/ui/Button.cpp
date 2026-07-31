#include "Button.h"

Button::~Button()
{
    if (cap_btn)
        delete cap_btn;
}

void Button::set_font(Font *new_font)
{
    if (!cap_btn)
        cap_btn = new Caption(new_font);
    else cap_btn->set_font(new_font);
}

void Button::set_font_color(int r, int g, int b, int a)
{
    if (cap_btn)
        cap_btn->set_font_color(r, g, b, a);
}

void Button::set_caption(std::string caption)
{
    if (cap_btn)
        cap_btn->set_caption(caption);
}

void Button::set_position(float x, float y)
{
    btn.x = x;
    btn.y = y;

    if (cap_btn)
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

    if (cap_btn)
        cap_btn->render(r);
}
