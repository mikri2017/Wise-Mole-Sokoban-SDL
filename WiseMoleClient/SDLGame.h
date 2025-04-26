#pragma once

#include <SDL3/SDL.h>

class SDLGame
{
private:
	SDL_Window* window {nullptr};
	SDL_Renderer* renderer {nullptr};
	SDL_FRect fr;
public:
	SDLGame(SDL_Window* w, SDL_Renderer* r);

	~SDLGame();

	SDL_AppResult proc_event(void* appstate, SDL_Event* event);

	SDL_AppResult app_iter(void* appstate);
};
