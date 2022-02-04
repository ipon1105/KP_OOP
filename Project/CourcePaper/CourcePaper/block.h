#pragma once

const int BOX_SIZE = 32;  //Размер одной плитки

//Поверхности
enum block {
    empty,  //Пустота   
    grass,  //Земля     0,      64
    stone,  //Камень    64,     64
    water,  //Вода      32,     64

    //<!-- objects -->//

    woodRes,    //Дерево
    stoneRes,   //Камень

    //<!-- stone & grass-->//

    stone_grass_left_up,    //0,        96
    stone_grass_left,       //0,        128
    stone_grass_left_down,  //0,        160
    stone_grass_up,         //32,       96
    stone_grass_right_up,   //64,       96
    stone_grass_right,      //64,       128
    stone_grass_right_down, //64,       160
    stone_grass_down,       //32,       160

    grass_stone_left_up,    //96,       96
    grass_stone_right_up,   //128,      96
    grass_stone_left_down,  //96,       128
    grass_stone_right_down, //128,      128

    grass_stone_x_1,        //96,       160
    grass_stone_x_2,        //128,      160

    //<!-- water & grass-->//

    water_grass_left_up,    //192,      96
    water_grass_left,       //192,      128
    water_grass_left_down,  //192,      160
    water_grass_up,         //224,      96
    water_grass_right_up,   //256,      96
    water_grass_right,      //256,      128
    water_grass_right_down, //256,      160
    water_grass_down,       //224,      160

    grass_water_left_up,    //288,      96
    grass_water_right_up,   //324,      96
    grass_water_left_down,  //288,      128
    grass_water_right_down, //324,      128

    grass_water_x_1,        //288,      160
    grass_water_x_2,        //324,      160

    //<!-- temporary floor-->//

    shadowGrass = 100,  //Тень травы
    shadowStone         //Тень камня

};