#pragma once

#include <vector>
#include <string>
#include <SDL3/SDL_video.h>

typedef struct GameVideoModeStr {
	int id;
	std::string mode_name;
};

class VideoModeMgr
{
private:
	std::vector<SDL_DisplayMode> v_modes {};
	bool fullscreen = false;
public:
	VideoModeMgr();

	~VideoModeMgr();

	// Сгенерировать список доступных режимов экрана
	bool reload_modes();

	// Получить доступные режимы
	std::vector<GameVideoModeStr> get_available_modes();

	// Переключиться в выбранные режим работы
	bool set_video_mode(SDL_Window* w, int id);
};
