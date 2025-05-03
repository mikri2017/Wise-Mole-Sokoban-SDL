#include <iostream>
#include "VideoModeMgr.h"

VideoModeMgr::VideoModeMgr()
{

}

VideoModeMgr::~VideoModeMgr()
{

}

bool VideoModeMgr::reload_modes()
{
	// Получаем доступные режимы монитора
	SDL_DisplayMode** dms;

	dms = SDL_GetFullscreenDisplayModes(SDL_GetPrimaryDisplay(), nullptr);
	if (dms == nullptr)
	{
		std::cout << "Something wrong" << std::endl;
		return false;
	}

	// Обходим режимы и сохраняем в контейнер vector
	SDL_DisplayMode dm;

	SDL_DisplayMode** ptr;
	for (ptr = dms; *ptr != nullptr; ptr++) {
		// Заполняем временный режим
		dm.format = (*ptr)->format;
		dm.w = (*ptr)->w;
		dm.h = (*ptr)->h;
		dm.pixel_density = (*ptr)->pixel_density;
		dm.refresh_rate = (*ptr)->refresh_rate;

		v_modes.push_back(dm);
	}

	SDL_free(dms);

	return true;
}

std::vector<GameVideoModeStr> VideoModeMgr::get_available_modes()
{
	GameVideoModeStr m_str;

	std::vector<GameVideoModeStr> gvm_str;

	int id = 0;
	for (auto const& v_mode : v_modes)
	{
		m_str.id = id;
		m_str.mode_name = std::to_string(v_mode.w) + " x "
			+ std::to_string(v_mode.h) + " ("
			+ std::to_string(v_mode.refresh_rate) + " Hz)";

		gvm_str.push_back(m_str);
	}

	return gvm_str;
}

bool VideoModeMgr::set_video_mode(SDL_Window* w, int id)
{
	if (id < v_modes.size())
	{
		// Устанавливаем выбранный режим работы экрана
		SDL_DisplayMode dm = v_modes[id];

		// Назначаем основной экран
		dm.displayID = SDL_GetPrimaryDisplay();

		SDL_SetWindowFullscreenMode(w, &dm);
	}
	else
		return false;

	return true;
}
