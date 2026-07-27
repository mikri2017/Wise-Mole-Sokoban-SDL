#pragma once

#include <iostream>

enum class GRType
{
    GR_IGNORE, // Ничего не делать
    GR_CHG_SCENE, // Изменить сцену
    GR_PREV_SCENE, // Вернуться на предыдущую сцену
    GR_APP_EXIT // Завершить работу программы
};

class GameReaction
{
public:
    GRType gr_type; // Тип реакции
    std::string adv_inf; // Доп. информация
};
