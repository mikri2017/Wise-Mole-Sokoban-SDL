#include "Button.h"
#include "FontMgr.h"

Button::Button()
{
    btn.x = 0;
    btn.y = 0;
    btn.w = 0;
    btn.h = 0;
    s_caption = "";

    // Задаем параметры текста
    font_color = {255, 0, 0};
    font_margin_left_right = 10;
    font_margin_up_dowm = 5;

    font_caption = new FontMgr();
    font_caption->set_font("assets/fonts/XoloniumBold.ttf");
    font_caption->set_font_size(48);
    font_caption->set_font_color(font_color);
    font_caption->set_letter_size_in_px(22);
}

Button::~Button()
{
    delete font_caption;
}

void Button::set_caption(std::string caption)
{
    s_caption = caption;
}

void Button::set_position(float x, float y)
{
    btn.x = x;
    btn.y = y;
}

void Button::set_size(float w, float h)
{
    btn.w = w;
    btn.h = h;
    font_caption->set_text_xstart_from(btn.x + font_margin_left_right, btn.x + btn.w - font_margin_left_right);
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
    font_caption->render(r, s_caption, btn.y, btn.h - font_margin_up_dowm, FontAlign::Centre);
}
