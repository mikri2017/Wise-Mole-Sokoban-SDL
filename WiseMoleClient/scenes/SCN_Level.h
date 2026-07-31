#pragma once

#include <vector>
#include "Scene.h"
#include "../game_objects/CollisionCaps.h"
#include "../game_objects/MainHero.h"
#include "../game_objects/WallBlock.h"
#include "../game_objects/BoxPlace.h"
#include "../game_objects/Box.h"

class SCN_Level : public Scene
{
private:
    CollisionCaps loc_area; // Допустимая зона пространства

    // Размер блока позволит расположить, максимум
    // 40 объектов по горизонтали и 20 - по вертикали
    const float block_size = 25;

    std::vector<WallBlock> w_blocks{};
    std::vector<BoxPlace> b_places{};
    std::vector<Box> boxes{};

    MainHero hero;
    const float step = 25; // Длина шага персонажа
public:
    SCN_Level();

    void reset();

    GameReaction app_iter(AppState* as);

    GameReaction proc_mouse_motion(AppState* as, float x, float y);

    GameReaction proc_mouse_button_event(AppState* as, SDL_MouseButtonEvent m_btn_event);

    GameReaction proc_keyboard_keydown(AppState* as, SDL_Scancode scancode);

    bool check_collisions_immv(GameObject game_o);

    bool check_collisions_boxes(SoundMgr* snd_mgr, GameObject game_o, float diff_x, float diff_y);

    bool check_for_win();
};
