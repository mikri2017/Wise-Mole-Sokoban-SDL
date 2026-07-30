#pragma once

#include "Scene.h"
#include "../ui/FontMgr_old.h"
#include "../ui/Button.h"

class SCN_Congrats : public Scene
{
private:
	SDL_FPoint menuPosition;
	float btn_w, btn_h;
	Button btn_to_main;
public:
	SCN_Congrats();

	void reset();

	GameReaction app_iter(AppState* as);

	GameReaction proc_mouse_motion(AppState* as, float x, float y);

	GameReaction proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event);

	GameReaction proc_keyboard_keydown(AppState* as, SDL_Scancode scancode);
};
