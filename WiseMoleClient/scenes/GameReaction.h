#pragma once

#include <iostream>

enum class GRType
{
    Ignore, // Ничего не делать
    ChgScene, // Изменить сцену
    ChgSceneWReset, // Изменить сцену со сбросом
    PrevScene, // Вернуться на предыдущую сцену
    AppExit // Завершить работу программы
};

class GameReaction
{
public:
    GRType gr_type{ GRType::Ignore }; // Тип реакции
    std::string adv_inf{ "" }; // Доп. информация
};
