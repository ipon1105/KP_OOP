#pragma once

const int TITLE_SIZE = 32;  //������ ����� ������

//�����������
enum types {
    empty = -1,

    //<!--1-�� ���-->//

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

    //<!--2-�� ���-->//

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

    //<!--3-�� ���-->//

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

    //<!--4-�� ���-->//

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

    //<!--5-�� ���-->//

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
    unit_human_vilager_left_0,
    unit_human_vilager_left_1,

    //<!--6-�� ���-->//

    unit_human_vilager_left_2,
    unit_human_vilager_up_0,
    unit_human_vilager_up_1,
    unit_human_vilager_up_2,
    unit_human_vilager_down_0,
    unit_human_vilager_down_1,
    unit_human_vilager_down_2,
    unit_human_vilager_right_0,
    unit_human_vilager_right_1,
    unit_human_vilager_right_2,
    unit_skeleton_warrior_left_0,
    unit_skeleton_warrior_left_1,
    unit_skeleton_warrior_left_2,
    unit_skeleton_warrior_up_0,
    unit_skeleton_warrior_up_1,

    //<!--7-�� ���-->//

    unit_skeleton_warrior_up_2,
    unit_skeleton_warrior_down_0,
    unit_skeleton_warrior_down_1,
    unit_skeleton_warrior_down_2,
    unit_skeleton_warrior_right_0,
    unit_skeleton_warrior_right_1,
    unit_skeleton_warrior_right_2,
    unit_skeleton_vilager_left_0,
    unit_skeleton_vilager_left_1,
    unit_skeleton_vilager_left_2,
    unit_skeleton_vilager_up_0,
    unit_skeleton_vilager_up_1,
    unit_skeleton_vilager_up_2,
    unit_skeleton_vilager_down_0,
    unit_skeleton_vilager_down_1,

    //<!--8-�� ���-->//

    unit_skeleton_vilager_down_2,
    unit_skeleton_vilager_right_0,
    unit_skeleton_vilager_right_1,
    unit_skeleton_vilager_right_2,
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

    //<!--9-�� ���-->//

    unit_goblin_warrior_right_2,
    unit_goblin_vilager_left_0,
    unit_goblin_vilager_left_1,
    unit_goblin_vilager_left_2,
    unit_goblin_vilager_up_0,
    unit_goblin_vilager_up_1,
    unit_goblin_vilager_up_2,
    unit_goblin_vilager_down_0,
    unit_goblin_vilager_down_1,
    unit_goblin_vilager_down_2,
    unit_goblin_vilager_right_0,
    unit_goblin_vilager_right_1,
    unit_goblin_vilager_right_2,
    unit_russion_warrior_left_0,
    unit_russion_warrior_left_1,

    //<!--10-�� ���-->//

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
    unit_russion_vilager_left_0,
    unit_russion_vilager_left_1,
    unit_russion_vilager_left_2,
    unit_russion_vilager_up_0,
    unit_russion_vilager_up_1,

    //<!--11-�� ���-->//

    unit_russion_vilager_up_2,
    unit_russion_vilager_down_0,
    unit_russion_vilager_down_1,
    unit_russion_vilager_down_2,
    unit_russion_vilager_right_0,
    unit_russion_vilager_right_1,
    unit_russion_vilager_right_2,


    //<!-- temporary floor-->//

    shadowGrass = 200,  //���� �����
    shadowStone         //���� �����

};