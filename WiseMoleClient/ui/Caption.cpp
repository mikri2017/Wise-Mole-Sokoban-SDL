#include "Caption.h"

void Caption::update_txt(SDL_Renderer *r)
{
    if (!t_eng)
    {
        // Первый рендер
        t_eng = TTF_CreateRendererTextEngine(r);
    }

    if (txt)
        TTF_DestroyText(txt);

    txt = font->gen_text(t_eng, text);

    TTF_SetTextColor(txt, font_c.r, font_c.g, font_c.b, font_c.a);

    need_update = false;
}

Caption::Caption(Font* new_font)
{
    set_font(new_font);
}

Caption::~Caption()
{
    // Font не трогаем, потому что внешний

    if (txt)
        TTF_DestroyText(txt);

    if (t_eng)
        TTF_DestroyRendererTextEngine(t_eng);
}

std::string Caption::get_caption()
{
    return text;
}

void Caption::set_caption(std::string new_text)
{
    text = new_text;
    need_update = true;
}

void Caption::set_font(Font* new_font)
{
    if (new_font)
    {
        font = new_font;
        need_update = true;
    }
}

void Caption::set_font_color(int r, int g, int b, int a)
{
    if (r < 0)
        r = 0;
    else font_c.r = r;

    if (g < 0)
        g = 0;
    else font_c.g = g;

    if (b < 0)
        b = 0;
    else font_c.b = b;

    if (a < 0)
        a = SDL_ALPHA_OPAQUE;
    else font_c.a = a;

    need_update = true;
}

void Caption::set_position(float x, float y)
{
    if (x < 0)
        area.x = 0;
    else area.x = x;

    if (y < 0)
        area.y = 0;
    else area.y = y;
}

void Caption::set_width(float w)
{
    if (w < 0)
        area.w = 0;
    else area.w = w;
}

void Caption::set_height(float h)
{
    if (h < 0)
        area.h = 0;
    else area.h = h;
}

void Caption::render(SDL_Renderer *r)
{
    if (need_update)
        update_txt(r);

    if (!TTF_DrawRendererText(txt, area.x, area.y))
        SDL_Log("Error with drawing text %s", SDL_GetError());
}
