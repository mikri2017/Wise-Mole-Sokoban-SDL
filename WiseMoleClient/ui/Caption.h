#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class Caption
{
private:
	std::string text{ "" };
	SDL_FRect area = { 0, 0, 0, 0 };
public:
	std::string get_caption();

	void set_caption(std::string new_text);
};
