#pragma once

#include <vector>
#include <string>
#include <SDL3/SDL_video.h>

class VideoModeMgr
{
private:
	float refresh_rate; // Текущая частота монитора
	SDL_DisplayMode* dm{ nullptr }; // Подобранный режим работы
	bool fullscreen = false; // Активен ли полноэкранный режим
public:
	VideoModeMgr();

	~VideoModeMgr();

	// Определить режим для полного экрана
	bool define_video_mode(int w, int h);

	// Задать режим полного экрана окну
	bool set_video_mode(SDL_Window* w);
};
