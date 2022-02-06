#include "Map.h"
#include "MyView.h"
#include "GameSetting.h"
#include "PerlinNoise.h"

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

void Map::perlinCreate(Utilits& tool) {
    sf::Uint8* pixel = new sf::Uint8[this->rowCount * this->colCount];

    double biomSize = 0.1;
    int num;

    PerlinNoise noiseMap;
    types set;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            num = ((i * rowCount) + j);
            pixel[num] = noiseMap.noise(j * biomSize, i * biomSize, seed) * 255;
        }

    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            num = i * rowCount + j;

            if (pixel[num] <= 80)
                set = water;
            else if (pixel[num] <= 160)
                set = grass;
            else set = stone;

            map[i][j].setType(set, tool);
            map[i][j].setPosition(sf::Vector2i(j,i));
        }
    
    delete[] pixel;
}

types Map::getTypes(const int& i, const int& j) {
    if (i < 0 || i >= this->rowCount ||
        j < 0 || j >= this->colCount)
        return empty;
    return map[i][j].getType();
}

void Map::faceting(Utilits& tool) {
    types nowType;
    types tmpType;

    int secretNumWater;
    int secretNumStone;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            nowType = map[i][j].getType();
            secretNumWater = secretNumStone = 0;

            secretNumWater += ((tmpType = getTypes(i - 1, j)) == empty ? nowType : tmpType) == water ? 1 : 0;   //вверх water
            secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 1 : 0;                          //вверх stone
            secretNumWater += ((tmpType = getTypes(i, j + 1)) == empty ? nowType : tmpType) == water ? 2 : 0;   //право water
            secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 2 : 0;                          //право stone
            secretNumWater += ((tmpType = getTypes(i + 1, j)) == empty ? nowType : tmpType) == water ? 4 : 0;   //низ water
            secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 4 : 0;                          //низ stone
            secretNumWater += ((tmpType = getTypes(i, j - 1)) == empty ? nowType : tmpType) == water ? 8 : 0;   //лево water
            secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 8 : 0;                          //лево stone

            if(secretNumWater == 10 || secretNumWater == 5 || secretNumWater == 15)
                map[i][j].setType(water, tool);
            if(secretNumStone == 10 || secretNumStone == 5 || secretNumStone == 15)
                map[i][j].setType(stone, tool);
                
        }

    for(int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            nowType = map[i][j].getType();

            if (nowType == grass) {

                secretNumWater = secretNumStone = 0;
                secretNumWater += ((tmpType = getTypes(i - 1, j)) == empty ? nowType : tmpType) == water ? 1 : 0;//вверх
                secretNumWater += ((tmpType = getTypes(i, j + 1)) == empty ? nowType : tmpType) == water ? 2 : 0;//право
                secretNumWater += ((tmpType = getTypes(i + 1, j)) == empty ? nowType : tmpType) == water ? 4 : 0;//низ
                secretNumWater += ((tmpType = getTypes(i, j - 1)) == empty ? nowType : tmpType) == water ? 8 : 0;//лево
                secretNumStone += ((tmpType = getTypes(i - 1, j)) == empty ? nowType : tmpType) == stone ? 1 : 0;//вверх
                secretNumStone += ((tmpType = getTypes(i, j + 1)) == empty ? nowType : tmpType) == stone ? 2 : 0;//право
                secretNumStone += ((tmpType = getTypes(i + 1, j)) == empty ? nowType : tmpType) == stone ? 4 : 0;//низ
                secretNumStone += ((tmpType = getTypes(i, j - 1)) == empty ? nowType : tmpType) == stone ? 8 : 0;//лево

                tmpType = grass;
                switch (secretNumWater) {
                    case 0:
                        if (getTypes(i + 1, j + 1) == water)
                            tmpType = grass_water_left_up;
                        else if(getTypes(i - 1, j + 1) == water)
                            tmpType = grass_water_left_down;
                        if (getTypes(i - 1, j - 1) == water)
                            tmpType = grass_water_right_down;
                        else if(getTypes(i + 1, j - 1) == water)
                            tmpType = grass_water_right_up;
                    break;
                    case 1:     tmpType = water_grass_up;           break;
                    case 2:     tmpType = water_grass_right;        break;
                    case 3:     tmpType = water_grass_right_up;     break;
                    case 4:     tmpType = water_grass_down;         break;
                    case 6:     tmpType = water_grass_right_down;   break;
                    case 8:     tmpType = water_grass_left;         break;
                    case 9:     tmpType = water_grass_left_up;      break;
                    case 12:    tmpType = water_grass_left_down;    break;
                }

                switch (secretNumStone) {
                    case 0:
                        if (getTypes(i + 1, j + 1) == stone)
                            tmpType = grass_stone_left_up;
                        else if (getTypes(i - 1, j + 1) == stone)
                            tmpType = grass_stone_left_down;
                        if (getTypes(i - 1, j - 1) == stone)
                            tmpType = grass_stone_right_down;
                        else if (getTypes(i + 1, j - 1) == stone)
                            tmpType = grass_stone_right_up;
                        break;
                    case 1:     tmpType = stone_grass_up;           break;
                    case 2:     tmpType = stone_grass_right;        break;
                    case 3:     tmpType = stone_grass_right_up;     break;
                    case 4:     tmpType = stone_grass_down;         break;
                    case 6:     tmpType = stone_grass_right_down;   break;
                    case 8:     tmpType = stone_grass_left;         break;
                    case 9:     tmpType = stone_grass_left_up;      break;
                    case 12:    tmpType = stone_grass_left_down;    break;
                }

                if (nowType != tmpType)
                    map[i][j].setType(tmpType, tool);

                continue;
            }
            
        }
}

void Map::createMap(const int& stoneCount, const int& grassCount, Utilits& tool, const int seed) {
    this->seed = seed;
    srand(seed);

    perlinCreate(tool);
    faceting(tool);
   
}

/*
* Обработка нажатия на ПКМ
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
    //обновление юнитов
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].update(event, window);
}

void Map::pollUpdate(sf::Event& event, sf::RenderWindow& window)
{

    //Одноразовое обновление юнитов
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
    //Отрисовать плитки
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            this->map[i][j].render(window);

    //Отрисовка юнитов
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
