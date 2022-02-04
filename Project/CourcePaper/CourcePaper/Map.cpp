#include "Map.h"
#include "MyView.h"
#include "GameSetting.h"

Map::Map() {

}

void Map::initMap(const int& row, const int& col) {
    this->rowCount = row;
    this->colCount = col;

    this->~Map();

    map = new Box * [rowCount];
    for (int i = 0; i < rowCount; i++)
        map[i] = new Box[this->colCount];
        
}

Map::Map(const int& row, const int& col) {
    this->colCount = col;
    this->rowCount = row;

    map = new Box*[this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        map[i] = new Box[this->colCount];

    this->tmp[0] = this->tmp[1] = 0;
}

int Map::getRowCount() {
    return this->rowCount;
}

int Map::getColCount() {
    return this->colCount;
}

Box** Map::getMap() {
    return map;
}

Map::Map(const Map& newMap) {
    this->colCount = newMap.colCount;
    this->rowCount = newMap.rowCount;

    map = new Box * [this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        map[i] = new Box[this->colCount];
}

void Map::createMap(const int& stoneCount, const int& grassCount, Utilits& tool, const int seed) {
    this->seed = seed;
    srand(seed);

    int r = 0, c = 0;
    block** blockMap = new block*[this->rowCount];
    for (int i = 0; i < rowCount; i++)
        blockMap[i] = new block[this->colCount];
    
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
        //ƒеление
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
        
        //¬ыравнивание
        for (int i = 0; i < rowCount; i++) 
            for (int j = 0; j < colCount; j++) {
                if (blockMap[i][j] == shadowGrass)
                    blockMap[i][j] = grass;
                if (blockMap[i][j] == shadowStone)
                    blockMap[i][j] = stone;
            }

        for (int i = 1; i < rowCount - 1; i++)
            for (int j = 1; j < colCount - 1; j++) {
                if (((i - 1 >= 0) && (j - 1 >= 0)) || ((i + 1 < rowCount - 1) && (j + 1 < colCount - 1)))
                {
                    if (
                        blockMap[i][j] == grass && (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        || (blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] == stone)
                        )
                    {
                        blockMap[i][j] = stone;
                    }

                }
            }

        //ѕроверка
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


    //√ранение:

    for (int i = 0; i < rowCount-1; i++)
        for (int j = 0; j < colCount-1; j++)
        {
            if ((blockMap[i][j] == grass) && (i - 1 >= 0) && (j - 1 >= 0) && (i + 1 <= rowCount) && (j + 1 <= colCount))
            {
            
                if (blockMap[i + 1][j] == stone && blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                {
                    blockMap[i - 1][j] = stone_grass_up;//горизонтальна€ полоса
                    blockMap[i + 1][j] = stone_grass_down;
                }
                else
                if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] == stone)
                {
                    blockMap[i][j - 1] = stone_grass_left;//вертикальна€ полоса
                    blockMap[i][j + 1] = stone_grass_right;
                }
                else
                if ( blockMap[i - 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                {
                    blockMap[i][j] = stone_grass_left_up;//лево верх
                }
                else
                if (blockMap[i + 1][j] == stone && blockMap[i][j - 1] == stone && blockMap[i][j + 1] != stone)
                {
                    blockMap[i][j] = stone_grass_left_down;//лево низ
                }
                else
                if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                {
                    blockMap[i][j] = stone_grass_right_down;//право низ
                }
                else
                if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] == stone && blockMap[i][j - 1] != stone)
                {
                    blockMap[i][j] = stone_grass_right_up;//право
                }
                else
                if (blockMap[i - 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                {
                    blockMap[i][j] = stone_grass_up;//верх
                }
                else
                if (blockMap[i + 1][j] == stone && blockMap[i][j + 1] != stone && blockMap[i][j - 1] != stone)
                {
                    blockMap[i][j] = stone_grass_down;//низ
                }
                else
                if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j - 1] == stone)
                {
                    blockMap[i][j] = stone_grass_left;//лево
                }
                else
                if (blockMap[i + 1][j] != stone && blockMap[i - 1][j] != stone && blockMap[i][j + 1] == stone)
                {
                    blockMap[i][j] = stone_grass_right;//право
                }
               
            }
        }


    for (int i = 0; i < rowCount-1; i++)
        for (int j = 0; j < colCount-1; j++)
        {
            if (i - 1 >= 0 && j - 1 >= 0 && i + 1 <= rowCount && j + 1 <= colCount)
            {
                //угол право верх
                if (blockMap[i][j] == grass && ((blockMap[i][j - 1] == stone_grass_down) || (blockMap[i][j - 1] == stone_grass_left_down)) && ((blockMap[i + 1][j] == stone_grass_left) ||  (blockMap[i + 1][j] == stone_grass_left_down)))
                {
                    blockMap[i][j] = grass_stone_right_up;
                }
                //угол право низ
                if (blockMap[i][j] == grass && ((blockMap[i - 1][j] == stone_grass_left)  || (blockMap[i - 1][j] == stone_grass_left_up)) && ((blockMap[i][j - 1] == stone_grass_up) || (blockMap[i][j - 1] == stone_grass_left_up)))
                {
                    blockMap[i][j] = grass_stone_right_down;
                }
                //угол лево верх
                if (blockMap[i][j] == grass && ((blockMap[i + 1][j] == stone_grass_right) || (blockMap[i + 1][j] == stone_grass_right_down)) && ((blockMap[i][j + 1] == stone_grass_down) || (blockMap[i][j + 1] == stone_grass_right_down)))
                {
                    blockMap[i][j] = grass_stone_left_up;
                }
                //угол лево низ
                if (blockMap[i][j] == grass && ((blockMap[i - 1][j] == stone_grass_right) || (blockMap[i - 1][j] == stone_grass_right_up)) && ((blockMap[i][j + 1] == stone_grass_up) || (blockMap[i][j + 1] == stone_grass_right_up)))
                {
                    blockMap[i][j] = grass_stone_left_down;
                }
            }
        }


    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++) 
        {
            map[i][j].setType(blockMap[i][j], tool);
            map[i][j].setOriginPos(sf::Vector2i(j, i));
        }

    for (int i = 0; i < rowCount; i++)
        delete[] blockMap[i];
    delete[] blockMap;
}

void Map::update(const sf::Event& event, sf::RenderWindow& window) {

    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Right)
    {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        map[tmp[0]][tmp[1]].setHitBoxing(false);

        int col = getGlobalMousePos(window).x / 32;
        int row = getGlobalMousePos(window).y / 32;

        tmp[0] = row;
        tmp[1] = col;

        if (col >= this->colCount || row >= this->rowCount || col < 0 || row < 0)
            return;

        map[row][col].setHitBoxing( !map[row][col].getHitBoxing());
    }
}

void Map::render(sf::RenderWindow& window){
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            this->map[i][j].render(window);
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