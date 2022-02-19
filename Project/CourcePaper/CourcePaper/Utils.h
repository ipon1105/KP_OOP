#pragma once

#include <SFML/Graphics.hpp>

namespace tool {

    static const int TITLE_SIZE = 32;           //Размер одной плитки
    static const int OUTLINE_THICKNESS = 2;     //Ширина выделения
    static int fps;

    //Поверхности
    static enum Surfaces {
        empty = -1,

        //<!--1-ый ряд-->//

        water_grass_left_up,
        water_grass_up,
        water_grass_right_up,
        grass_water_left_up,
        grass_water_right_up,
        stone_grass_left_up,
        stone_grass_up,
        stone_grass_right_up,
        grass_stone_left_up,
        grass_stone_right_up,
        water_stone_left_up,
        water_stone_up,
        water_stone_right_up,
        stone_water_left_up,
        stone_water_right_up,

        //<!--2-ой ряд-->//

        water_grass_left,
        water_grass_mid,
        water_grass_right,
        grass_water_left_down,
        grass_water_right_down,
        stone_grass_left,
        stone_grass_mid,
        stone_grass_right,
        grass_stone_left_down,
        grass_stone_right_down,
        water_stone_left,
        water_stone_mid,
        water_stone_right,
        stone_water_left_down,
        stone_water_right_down,

        //<!--3-ий ряд-->//

        water_grass_left_down,
        water_grass_down,
        water_grass_right_down,
        water_grass_x_1,
        water_grass_x_2,
        stone_grass_left_down,
        stone_grass_down,
        stone_grass_right_down,
        stone_grass_x_1,
        stone_grass_x_2,
        water_stone_left_down,
        water_stone_down,
        water_stone_right_down,
        water_stone_x_1,
        water_stone_x_2,

        //<!--4-ый ряд-->//

        grass,
        water,
        stone,
        wall_down_right,
        wall_left_right,
        wall_up_down,
        wall_left_down,
        wall_up_right,
        wall_left_up,
        wall_A,
        wall_B,
        woodRes,
        stoneRes,
        base,
        home,

        //<!--5-ый ряд-->//

        tree,
        unit_human_warrior_left_0,
        unit_human_warrior_left_1,
        unit_human_warrior_left_2,
        unit_human_warrior_up_0,
        unit_human_warrior_up_1,
        unit_human_warrior_up_2,
        unit_human_warrior_down_0,
        unit_human_warrior_down_1,
        unit_human_warrior_down_2,
        unit_human_warrior_right_0,
        unit_human_warrior_right_1,
        unit_human_warrior_right_2,
        unit_human_villager_left_0,
        unit_human_villager_left_1,

        //<!--6-ой ряд-->//

        unit_human_villager_left_2,
        unit_human_villager_up_0,
        unit_human_villager_up_1,
        unit_human_villager_up_2,
        unit_human_villager_down_0,
        unit_human_villager_down_1,
        unit_human_villager_down_2,
        unit_human_villager_right_0,
        unit_human_villager_right_1,
        unit_human_villager_right_2,
        unit_skeleton_warrior_left_0,
        unit_skeleton_warrior_left_1,
        unit_skeleton_warrior_left_2,
        unit_skeleton_warrior_up_0,
        unit_skeleton_warrior_up_1,

        //<!--7-ой ряд-->//

        unit_skeleton_warrior_up_2,
        unit_skeleton_warrior_down_0,
        unit_skeleton_warrior_down_1,
        unit_skeleton_warrior_down_2,
        unit_skeleton_warrior_right_0,
        unit_skeleton_warrior_right_1,
        unit_skeleton_warrior_right_2,
        unit_skeleton_villager_left_0,
        unit_skeleton_villager_left_1,
        unit_skeleton_villager_left_2,
        unit_skeleton_villager_up_0,
        unit_skeleton_villager_up_1,
        unit_skeleton_villager_up_2,
        unit_skeleton_villager_down_0,
        unit_skeleton_villager_down_1,

        //<!--8-ой ряд-->//

        unit_skeleton_villager_down_2,
        unit_skeleton_villager_right_0,
        unit_skeleton_villager_right_1,
        unit_skeleton_villager_right_2,
        unit_goblin_warrior_left_0,
        unit_goblin_warrior_left_1,
        unit_goblin_warrior_left_2,
        unit_goblin_warrior_up_0,
        unit_goblin_warrior_up_1,
        unit_goblin_warrior_up_2,
        unit_goblin_warrior_down_0,
        unit_goblin_warrior_down_1,
        unit_goblin_warrior_down_2,
        unit_goblin_warrior_right_0,
        unit_goblin_warrior_right_1,

        //<!--9-ый ряд-->//

        unit_goblin_warrior_right_2,
        unit_goblin_villager_left_0,
        unit_goblin_villager_left_1,
        unit_goblin_villager_left_2,
        unit_goblin_villager_up_0,
        unit_goblin_villager_up_1,
        unit_goblin_villager_up_2,
        unit_goblin_villager_down_0,
        unit_goblin_villager_down_1,
        unit_goblin_villager_down_2,
        unit_goblin_villager_right_0,
        unit_goblin_villager_right_1,
        unit_goblin_villager_right_2,
        unit_russion_warrior_left_0,
        unit_russion_warrior_left_1,

        //<!--10-ый ряд-->//

        unit_russion_warrior_left_2,
        unit_russion_warrior_up_0,
        unit_russion_warrior_up_1,
        unit_russion_warrior_up_2,
        unit_russion_warrior_down_0,
        unit_russion_warrior_down_1,
        unit_russion_warrior_down_2,
        unit_russion_warrior_right_0,
        unit_russion_warrior_right_1,
        unit_russion_warrior_right_2,
        unit_russion_villager_left_0,
        unit_russion_villager_left_1,
        unit_russion_villager_left_2,
        unit_russion_villager_up_0,
        unit_russion_villager_up_1,

        //<!--11-ый ряд-->//

        unit_russion_villager_up_2,
        unit_russion_villager_down_0,
        unit_russion_villager_down_1,
        unit_russion_villager_down_2,
        unit_russion_villager_right_0,
        unit_russion_villager_right_1,
        unit_russion_villager_right_2,


        //<!-- temporary floor-->//

        shadowGrass = 200,  //Тень травы
        shadowStone         //Тень камня

    };

    //Стороны
    static enum Side {
        up,
        right,
        down,
        left
    };

    //Можно ходить или нет
    static enum MoveSurfaces {
        unpassible = 0,
        passible = 1
    };

    class Utils
    {
    public:
        //Конструкторы
        Utils();

        //Начать загрузку текстур 
        static void startLoad();

        //Вернёт текстуру по номеру (row*(номер строки от 0) + col*(номер столбца от 0))
        static sf::Texture& getTexture(const int& num);

        //Вернёт текстуру по перечислению block
        static sf::Texture& getTexture(const Surfaces& title);

        //Вернёт результат загрузки
        static bool isFinily();

        //Вернёт прогресс процеса
        static int getProgress();
    };
}


