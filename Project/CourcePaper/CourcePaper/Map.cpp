#include "Map.h"
#include "MyView.h"
#include "GameSetting.h"

Map::Map() {

}

void Map::initMap(const int& row, const int& col) {
    this->rowCount = row;
    this->colCount = col;

    unitList.push_back(Unit());
    unitList[0].setOriginPos(sf::Vector2i(4, 3));
    unitList[0].setColor(sf::Color::Red);

    if(map != NULL)
        this->~Map();

    map = new Title * [rowCount];
    for (int i = 0; i < rowCount; i++)
        map[i] = new Title[this->colCount];
        
}

Map::Map(const int& row, const int& col) {
    this->colCount = col;
    this->rowCount = row;

    map = new Title*[this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        map[i] = new Title[this->colCount];
}

int Map::getRowCount() {
    return this->rowCount;
}

int Map::getColCount() {
    return this->colCount;
}

Title** Map::getMap() {
    return map;
}

Map::Map(const Map& newMap) {
    this->colCount = newMap.colCount;
    this->rowCount = newMap.rowCount;

    map = new Title * [this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        map[i] = new Title[this->colCount];
}

void Map::createMap(const int& stoneCount, const int& grassCount, Utilits& tool, const int seed) {
    this->seed = seed;
    srand(seed);

    int r = 0, c = 0;
    types** blockMap = new types*[this->rowCount];
    for (int i = 0; i < rowCount; i++)
        blockMap[i] = new types[this->colCount];
    
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            blockMap[i][j] = empty;

    for (int i = 0; i < stoneCount; i++) {
        r = rand() % rowCount;
        c = rand() % colCount;

        blockMap[r][c] = stone;
    }
    
    for (int i = 0; i < grassCount; i++) {
        r = rand() % rowCount;
        c = rand() % colCount;

        blockMap[r][c] = grass;
    }

    bool gen = true;
    while (gen) {
        //�������
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                if (blockMap[i][j] != 0) {

                    if (blockMap[i][j] == shadowGrass || blockMap[i][j] == shadowStone)
                        break;

                    if (i - 1 >= 0 && blockMap[i - 1][j] == empty)
                        blockMap[i - 1][j] = (blockMap[i][j] == grass) ? shadowGrass : shadowStone;
                    if (i + 1 <= rowCount - 1 && blockMap[i + 1][j] == empty)
                        blockMap[i + 1][j] = (blockMap[i][j]== grass) ? shadowGrass : shadowStone;
                    if (j - 1 >= 0 && blockMap[i][j - 1]== empty)
                        blockMap[i][j - 1] = (blockMap[i][j]== grass) ? shadowGrass : shadowStone;
                    if (j + 1 <= rowCount - 1 && blockMap[i][j + 1] == empty)
                        blockMap[i][j + 1] = (blockMap[i][j] == grass) ? shadowGrass : shadowStone;

                }
            }
        }
        
        //������������
        for (int i = 0; i < rowCount; i++) 
            for (int j = 0; j < colCount; j++) {
                if (blockMap[i][j] == shadowGrass)
                    blockMap[i][j] = grass;
                if (blockMap[i][j] == shadowStone)
                    blockMap[i][j] = stone;
            }

        

        //��������
        gen = false;
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                if (blockMap[i][j] == 0) {
                    gen = true;

                    i = rowCount;
                    j = colCount;
                }
            }
        }
    }


    //��������:

    for (int k = 0; k < rowCount*colCount; k++)
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++) {
                if (((i - 1 >= 0) && (j - 1 >= 0)) && ((i + 1 < rowCount) && (j + 1 < colCount)))
                {
                    if (
                        blockMap[i][j] != stone && (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i - 1][j-1] != stone && blockMap[i+1][j +1] != stone && blockMap[i-1][j + 1] == stone && blockMap[i +1][j - 1] == stone)
                        || (blockMap[i - 1][j - 1] == stone && blockMap[i + 1][j + 1] == stone && blockMap[i - 1][j + 1] != stone && blockMap[i + 1][j - 1] != stone)
                        )
                    {
                        blockMap[i][j] = stone;
                    }
                }
            }
    for (int k = 0; k < rowCount * colCount; k++)
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
            {
                if (blockMap[i][j] != stone) {
                    //������
                    if ((i - 1 >= 0) && (j - 1 >= 0) && (i + 1 <= rowCount - 1) && (j + 1 <= colCount - 1))
                    {

                        if (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                        {
                            blockMap[i][j] = stone;//�������������� ������

                        }
                        else
                            if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] == stone)
                            {
                                blockMap[i][j] = stone;//������������ ������

                            }
                            else
                                if (blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                                {
                                    blockMap[i][j] = stone_grass_left_up;//���� ����
                                }
                                else
                                    if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                                    {
                                        blockMap[i][j] = stone_grass_left_down;//���� ���
                                    }
                                    else
                                        if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                                        {
                                            blockMap[i][j] = stone_grass_right_down;//����� ���
                                        }
                                        else
                                            if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                                            {
                                                blockMap[i][j] = stone_grass_right_up;//����� ����
                                            }
                                            else
                                                if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                                                {
                                                    blockMap[i][j] = stone_grass_up;//����
                                                }
                                                else
                                                    if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                                                    {
                                                        blockMap[i][j] = stone_grass_down;//���
                                                    }
                                                    else
                                                        if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j - 1] == stone)
                                                        {
                                                            blockMap[i][j] = stone_grass_left;//����
                                                        }
                                                        else
                                                            if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone)
                                                            {
                                                                blockMap[i][j] = stone_grass_right;//�����
                                                            }

                    }
                    else

                        if (i - 1 < 0 && j - 1 < 0)//������� ����� ���� �����
                        {
                            if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] != stone)
                            {
                                blockMap[i][j] = stone_grass_down;//���
                            }
                            else
                                if (blockMap[i + 1][j] != stone && blockMap[i][j + 1] == stone)
                                {
                                    blockMap[i][j] = stone_grass_right;//�����
                                }
                                else
                                    //���� ����� ����
                                    if ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down) && ((blockMap[i + 1][j] == stone_grass_left) || (blockMap[i + 1][j] == stone_grass_left_down)))
                                    {
                                        blockMap[i][j] = grass_stone_right_up;
                                    }
                                    else
                                        if (blockMap[i + 1][j] != stone && blockMap[i][j + 1] != stone)
                                        {
                                            blockMap[i][j] = grass;//������ �����
                                        }
                                        else
                                            blockMap[i][j] = stone;
                        }
                        else
                            if ((i - 1 < 0) && (j + 1 > colCount - 1))//���� ������ ����
                            {
                                if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] != stone)
                                {
                                    blockMap[i][j] = stone_grass_down;//���
                                }
                                else
                                    if (blockMap[i + 1][j] != stone && blockMap[i][j - 1] == stone)
                                    {
                                        blockMap[i][j] = stone_grass_left;//����
                                    }
                                    else
                                        if ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down) && ((blockMap[i + 1][j] == stone_grass_left) || (blockMap[i + 1][j] == stone_grass_left_down)))
                                        {
                                            blockMap[i][j] = grass_stone_right_up;
                                        }
                                        else
                                            if (blockMap[i + 1][j] != stone && blockMap[i][j - 1] != stone)
                                            {
                                                blockMap[i][j] = grass;//������ �����
                                            }
                                            else
                                                blockMap[i][j] = stone;
                            }
                            else
                                if (i - 1 < 0)//����
                                {
                                    if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                                    {
                                        blockMap[i][j] = stone_grass_left_down;//���� ���
                                    }
                                    else
                                        if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                                        {
                                            blockMap[i][j] = stone_grass_right_down;//����� ���
                                        }
                                        else
                                            if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] != stone)
                                            {
                                                blockMap[i][j] = stone_grass_down;//���
                                            }
                                            else
                                                if (blockMap[i + 1][j] != stone && blockMap[i][j - 1] == stone)
                                                {
                                                    blockMap[i][j] = stone_grass_left;//����
                                                }
                                                else
                                                    if (blockMap[i + 1][j] != stone && blockMap[i][j + 1] == stone)
                                                    {
                                                        blockMap[i][j] = stone_grass_right;//�����
                                                    }
                                                    else
                                                        if ((blockMap[i + 1][j] == stone_grass_right) || (blockMap[i + 1][j] == stone_grass_right_down) && ((blockMap[i][j + 1] == stone_grass_down) || (blockMap[i][j + 1] == stone_grass_right_down)))
                                                        {
                                                            blockMap[i][j] = grass_stone_left_up;
                                                        }
                                                        else
                                                            if ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down) && ((blockMap[i + 1][j] == stone_grass_left) || (blockMap[i + 1][j] == stone_grass_left_down)))
                                                            {
                                                                blockMap[i][j] = grass_stone_right_up;
                                                            }
                                                            else
                                                                if (blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                                                                {
                                                                    blockMap[i][j] = grass;//������ �����
                                                                }
                                                                else
                                                                    blockMap[i][j] = stone;
                                }
                                else
                                    if (j - 1 < 0 && i + 1 > rowCount - 1)//���� ���
                                    {
                                        if (blockMap[i][j + 1] == stone && blockMap[i - 1][j] != stone)
                                        {
                                            blockMap[i][j] = stone_grass_right;//�����
                                        }
                                        else
                                            if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone)
                                            {
                                                blockMap[i][j] = stone_grass_up;//����
                                            }
                                            else
                                                if ((blockMap[i - 1][j] == stone_grass_left) || (blockMap[i - 1][j] == stone_grass_left_up) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                                                {
                                                    blockMap[i][j] = grass_stone_right_down;
                                                }
                                                else
                                                    if (blockMap[i - 1][j] != stone && blockMap[i][j + 1] != stone)
                                                    {
                                                        blockMap[i][j] = grass;//������ �����
                                                    }
                                                    else
                                                        blockMap[i][j] = stone;
                                    }
                                    else
                                        if (j - 1 < 0)//���� 
                                        {
                                            if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone)
                                            {
                                                blockMap[i][j] = stone_grass_up;//����
                                            }
                                            else
                                                if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] != stone)
                                                {
                                                    blockMap[i][j] = stone_grass_down;//���
                                                }
                                                else
                                                    if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone)
                                                    {
                                                        blockMap[i][j] = stone_grass_right;//�����
                                                    }
                                                    else
                                                        if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] == stone)
                                                        {
                                                            blockMap[i][j] = stone_grass_right_down;//����� ���
                                                        }
                                                        else
                                                            if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone)
                                                            {
                                                                blockMap[i][j] = stone_grass_right_up;//����� ����
                                                            }
                                                            else
                                                                //���� ���� ����
                                                                if ((blockMap[i + 1][j] == stone_grass_right) || (blockMap[i + 1][j] == stone_grass_right_down) && ((blockMap[i][j + 1] == stone_grass_down) || (blockMap[i][j + 1] == stone_grass_right_down)))
                                                                {
                                                                    blockMap[i][j] = grass_stone_left_up;
                                                                }
                                                                else
                                                                    //���� ���� ���
                                                                    if ((blockMap[i - 1][j] == stone_grass_right) || (blockMap[i - 1][j] == stone_grass_right_up) && ((blockMap[i][j + 1] == stone_grass_up) || (blockMap[i][j + 1] == stone_grass_right_up)))
                                                                    {
                                                                        blockMap[i][j] = grass_stone_left_down;
                                                                    }
                                                                    else
                                                                        if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone)
                                                                        {
                                                                            blockMap[i][j] = grass;//������ �����
                                                                        }
                                                                        else
                                                                            blockMap[i][j] = stone;
                                        }
                                        else
                                            if (i + 1 > rowCount - 1 && j + 1 > colCount - 1)//����� ���
                                            {
                                                if (blockMap[i][j - 1] == stone && blockMap[i - 1][j] != stone)
                                                {
                                                    blockMap[i][j] = stone_grass_left;//����
                                                }
                                                else
                                                    if (blockMap[i - 1][j] == stone && blockMap[i][j - 1] != stone)
                                                    {
                                                        blockMap[i][j] = stone_grass_up;//����
                                                    }
                                                    else
                                                        if ((blockMap[i - 1][j] == stone_grass_left) || (blockMap[i - 1][j] == stone_grass_left_up) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                                                        {
                                                            blockMap[i][j] = grass_stone_right_down;
                                                        }
                                                        else
                                                            if (blockMap[i - 1][j] != stone && blockMap[i][j - 1] != stone)
                                                            {
                                                                blockMap[i][j] = grass;//������ �����
                                                            }
                                                            else
                                                                blockMap[i][j] = stone;
                                            }
                                            else
                                                if (i + 1 > rowCount - 1)//���
                                                {
                                                    if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                                                    {
                                                        blockMap[i][j] = stone_grass_up;//����
                                                    }
                                                    else
                                                        if (blockMap[i - 1][j] != stone && blockMap[i][j - 1] == stone)
                                                        {
                                                            blockMap[i][j] = stone_grass_left;//����
                                                        }
                                                        else
                                                            if (blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone)
                                                            {
                                                                blockMap[i][j] = stone_grass_right;//�����
                                                            }
                                                            else
                                                                //���� ����� ���
                                                                if ((blockMap[i - 1][j] == stone_grass_left) || (blockMap[i - 1][j] == stone_grass_left_up) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                                                                {
                                                                    blockMap[i][j] = grass_stone_right_down;
                                                                }
                                                                else
                                                                    //���� ���� ���
                                                                    if ((blockMap[i - 1][j] == stone_grass_right) || (blockMap[i - 1][j] == stone_grass_right_up) && ((blockMap[i][j + 1] == stone_grass_up) || (blockMap[i][j + 1] == stone_grass_right_up)))
                                                                    {
                                                                        blockMap[i][j] = grass_stone_left_down;
                                                                    }
                                                                    else
                                                                        if (blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                                                                        {
                                                                            blockMap[i][j] = stone_grass_left_up;//���� ����
                                                                        }
                                                                        else
                                                                            if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                                                                            {
                                                                                blockMap[i][j] = stone_grass_right_up;//����� ����
                                                                            }
                                                                            else
                                                                                if (blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                                                                                {
                                                                                    blockMap[i][j] = grass;//������ �����
                                                                                }
                                                                                else
                                                                                    blockMap[i][j] = stone;
                                                }
                                                else
                                                    if (j + 1 > colCount - 1)//����� 
                                                    {
                                                        if (blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i + 1][j] != stone)
                                                        {
                                                            blockMap[i][j] = stone_grass_left_up;//���� ����
                                                        }
                                                        else
                                                            if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i - 1][j] != stone)
                                                            {
                                                                blockMap[i][j] = stone_grass_left_down;//���� ���
                                                            }
                                                            else
                                                                if (blockMap[i - 1][j] == stone && blockMap[i][j - 1] != stone)
                                                                {
                                                                    blockMap[i][j] = stone_grass_up;//����
                                                                }
                                                                else
                                                                    if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] != stone)
                                                                    {
                                                                        blockMap[i][j] = stone_grass_down;//���
                                                                    }
                                                                    else
                                                                        if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j - 1] == stone)
                                                                        {
                                                                            blockMap[i][j] = stone_grass_left;//����
                                                                        }
                                                                        else
                                                                            if ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down) && ((blockMap[i + 1][j] == stone_grass_left) || (blockMap[i + 1][j] == stone_grass_left_down)))
                                                                            {
                                                                                blockMap[i][j] = grass_stone_right_up;
                                                                            }
                                                                            else
                                                                                //���� ����� ���
                                                                                if ((blockMap[i - 1][j] == stone_grass_left) || (blockMap[i - 1][j] == stone_grass_left_up) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                                                                                {
                                                                                    blockMap[i][j] = grass_stone_right_down;
                                                                                }
                                                                                else
                                                                                    if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone)
                                                                                    {
                                                                                        blockMap[i][j] = grass;//������ �����
                                                                                    }
                                                                                    else
                                                                                        blockMap[i][j] = stone;
                                                    }

                }
            }
        for (int i = 0; i < rowCount - 1; i++)
            for (int j = 0; j < colCount - 1; j++)
            {
                if (blockMap[i][j] == grass && i - 1 >= 0 && j - 1 >= 0 && i + 1 <= rowCount && j + 1 <= colCount)//�������� grass �� != stone
                {
                    //���� ����� ����
                    if ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down) && ((blockMap[i + 1][j] == stone_grass_left) || (blockMap[i + 1][j] == stone_grass_left_down)))
                    {
                        blockMap[i][j] = grass_stone_right_up;
                    }
                    else
                        //���� ����� ���
                        if ((blockMap[i - 1][j] == stone_grass_left) || (blockMap[i - 1][j] == stone_grass_left_up) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                        {
                            blockMap[i][j] = grass_stone_right_down;
                        }
                        else
                            //���� ���� ����
                            if ((blockMap[i + 1][j] == stone_grass_right) || (blockMap[i + 1][j] == stone_grass_right_down) && ((blockMap[i][j + 1] == stone_grass_down) || (blockMap[i][j + 1] == stone_grass_right_down)))
                            {
                                blockMap[i][j] = grass_stone_left_up;
                            }
                            else
                                //���� ���� ���
                                if ((blockMap[i - 1][j] == stone_grass_right) || (blockMap[i - 1][j] == stone_grass_right_up) && ((blockMap[i][j + 1] == stone_grass_up) || (blockMap[i][j + 1] == stone_grass_right_up)))
                                {
                                    blockMap[i][j] = grass_stone_left_down;
                                }
                }
                
            }
    
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++) 
        {
            map[i][j].setType(blockMap[i][j], tool);
            map[i][j].setPosition(sf::Vector2i(j, i));
        }

    for (int i = 0; i < rowCount; i++)
        delete[] blockMap[i];
    delete[] blockMap;
}

/*
* ��������� ������� �� ���
if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right)
    {
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                map[i][j].setHitBoxing(false);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        int col = getGlobalMousePos(window).x / 32;
        int row = getGlobalMousePos(window).y / 32;

        if (col >= this->colCount || row >= this->rowCount || col < 0 || row < 0)
            return;

        map[row][col].setHitBoxing( !map[row][col].getHitBoxing());
    }
*/

void Map::update(sf::Event& event, sf::RenderWindow& window) 
{
    //���������� ������
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].update(event, window);
}

void Map::pollUpdate(sf::Event& event, sf::RenderWindow& window)
{

    //����������� ���������� ������
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].pollUpdate(event, window);

    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = getGlobalMousePos(window);

        int col = mousePos.x / 32;
        int row = mousePos.y / 32;

        for (int i = 0; i < this->unitList.size(); i++)
            if (this->unitList[i].getOriginPos().x == col &&
                this->unitList[i].getOriginPos().y == row)
                this->unitList[i].setHitboxing(!this->unitList[i].getHitboxing());
            else
                this->unitList[i].setHitboxing(false);

    }
    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2i mousePos = getGlobalMousePos(window);

        int col = mousePos.x / 32;
        int row = mousePos.y / 32;

        map[row][col].setHitBoxing(!map[row][col].getHitBoxing());

        sf::Vector2i t(col, row);
        this->unitList[0].goToOriginPos(t);

        //for (int i = 0; i < this->unitList.size(); i++)
        //    if (this->unitList[i].getHitboxing()) {
        //    }
    }
}

void Map::render(sf::RenderWindow& window){
    //���������� ������
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            this->map[i][j].render(window);

    //��������� ������
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].render(window);
}

Map::~Map(){
    if (map == NULL)
         return;

    for (int i = 0; i < this->rowCount; i++)
        delete[] this->map[i];
    delete[] map;

}
 
Map& Map::operator = (const Map& newMap) {
    Map map(newMap);
    return map;
}

int Map::getSeed() {
    return this->seed;
}
