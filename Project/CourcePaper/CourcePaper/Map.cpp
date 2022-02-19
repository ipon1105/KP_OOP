#include "Map.h"
#include "MyView.h"
#include "GameSetting.h"
#include "PerlinNoise.h"
#include "Base.h"

#include "imgui.h"
#include "imgui-SFML.h"

Map::Map() {

    unitList.push_back(Unit(tool::Surfaces(tool::unit_human_villager_left_0), 1, 1));
    //unitList[0].setGlobalPos(sf::Vector2f(10 * tool::TITLE_SIZE, 10 * tool::TITLE_SIZE));
    //unitList[0].setColor(sf::Color::Red);
}

void Map::initMap(const int& row, const int& col) {
    this->rowCount = row;
    this->colCount = col;


    if(this->map != NULL)
        this->~Map();

    this->map = new Title * [this->rowCount];
    this->moveMap = new tool::MoveSurfaces * [this->rowCount];
    for (int i = 0; i < rowCount; i++){
        this->map[i] = new Title[this->colCount];
        this->moveMap[i] = new tool::MoveSurfaces[this->colCount];
    }
}

Map::Map(const int& row, const int& col) {
    this->colCount = col;
    this->rowCount = row;

    this->map = new Title * [this->rowCount];
    this->moveMap = new tool::MoveSurfaces * [this->rowCount];
    for (int i = 0; i < rowCount; i++) {
        this->map[i] = new Title[this->colCount];
        this->moveMap[i] = new tool::MoveSurfaces[this->colCount];
    }
}

int Map::getRowCount() {
    return this->rowCount;
}
//unitList
int Map::getColCount() {
    return this->colCount;
}

Title** Map::getMap() {
    return this->map;
}

Map::Map(const Map& newMap) {
    this->colCount = newMap.colCount;
    this->rowCount = newMap.rowCount;

    this->map = new Title * [this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        this->map[i] = new Title[this->colCount];
}

void Map::perlinCreate() {
    sf::Uint8* pixel = new sf::Uint8[this->rowCount * this->colCount];

    double biomSize = 0.1;
    int num;

    PerlinNoise noiseMap;
    tool::Surfaces set;
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

            this->moveMap[i][j] = tool::passible;
            if (pixel[num] <= 80){
                set = tool::water;
                this->moveMap[i][j] = tool::unpassible;
            }
            else if (pixel[num] <= 160)
                set = tool::grass;
            else set = tool::stone;

            map[i][j].setType(set);
            map[i][j].setPosition(sf::Vector2i(j,i));
        }
    
    delete[] pixel;
}

tool::Surfaces Map::getTypes(const int& i, const int& j) {
    if (i < 0 || i >= this->rowCount ||
        j < 0 || j >= this->colCount)
        return tool::empty;
    return map[i][j].getType();
}

void Map::faceting() {
    using namespace tool;
    tool::Surfaces nowType;
    tool::Surfaces tmpType;

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

            if(secretNumWater == 10 || secretNumWater == 5 || secretNumWater == 15|| (getTypes(i + 1, j - 1) == water && getTypes(i - 1, j + 1) == water)  || (getTypes(i - 1, j - 1)==water &&getTypes(i + 1, j + 1)==water))
                map[i][j].setType(water);
            if(secretNumStone == 10 || secretNumStone == 5 || secretNumStone == 15 || (getTypes(i + 1, j - 1) == stone && getTypes(i - 1, j + 1) == stone) || (getTypes(i - 1, j - 1) == stone && getTypes(i + 1, j + 1) == stone))
                map[i][j].setType(stone);
            switch (secretNumStone) {
                case 14: case 13: case 11: case 7:
                    map[i][j].setType(stone);
                break;
            }
            switch (secretNumWater) {
                case 14: case 13: case 11: case 7:
                    map[i][j].setType(water);
                break;
            }
                
        }

    for(int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
        {
            nowType = map[i][j].getType();

            if (nowType == grass) {

                secretNumWater = secretNumStone = 0;
                secretNumWater += ((tmpType = getTypes(i - 1, j)) == empty ? nowType : tmpType) == water ? 1 : 0;   //вверх water
                secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 1 : 0;                          //вверх stone
                secretNumWater += ((tmpType = getTypes(i, j + 1)) == empty ? nowType : tmpType) == water ? 2 : 0;   //право water
                secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 2 : 0;                          //право stone
                secretNumWater += ((tmpType = getTypes(i + 1, j)) == empty ? nowType : tmpType) == water ? 4 : 0;   //низ water
                secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 4 : 0;                          //низ stone
                secretNumWater += ((tmpType = getTypes(i, j - 1)) == empty ? nowType : tmpType) == water ? 8 : 0;   //лево water
                secretNumStone += (tmpType == empty ? nowType : tmpType) == stone ? 8 : 0;                          //лево stone

                tmpType = grass;
                switch (secretNumWater) {
                    case 1:     tmpType = water_grass_up;           break;
                    case 2:     tmpType = water_grass_right;        break;
                    case 3:     tmpType = water_grass_right_up;     break;
                    case 4:     tmpType = water_grass_down;         break;
                    case 6:     tmpType = water_grass_right_down;   break;
                    case 8:     tmpType = water_grass_left;         break;
                    case 9:     tmpType = water_grass_left_up;      break;
                    case 12:    tmpType = water_grass_left_down;    break;
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
                }

                switch (secretNumStone) {
                    case 1:     tmpType = stone_grass_up;           break;
                    case 2:     tmpType = stone_grass_right;        break;
                    case 3:     tmpType = stone_grass_right_up;     break;
                    case 4:     tmpType = stone_grass_down;         break;
                    case 6:     tmpType = stone_grass_right_down;   break;
                    case 8:     tmpType = stone_grass_left;         break;
                    case 9:     tmpType = stone_grass_left_up;      break;
                    case 12:    tmpType = stone_grass_left_down;    break;
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
                }

                if (nowType != tmpType)
                    map[i][j].setType(tmpType);

                continue;
            }
            
        }
}

void Map::moveMapUpdate()
{
    for(int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
        {
            moveMap[i][j] = (map[i][j].getType() == tool::water 
                ? tool::unpassible : tool::passible);

        }

    for (int i = 0; i < unitList.size(); i++)
        moveMap[unitList[i].getTitlePos().y][unitList[i].getTitlePos().x] = tool::unpassible;
}

void Map::createMap(const int& stoneCount, const int& grassCount, const int seed) {
    this->seed = seed;
    srand(seed);

    perlinCreate();
    faceting();
    objectsList.push_back(Objects(tool::base));
    objectsList[0].setTitlePos(sf::Vector2i(7, 7));
   
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
       unitList[i].update(event, window, moveMap);
    

    //Обновление объектов
    for (int i = 0; i < objectsList.size(); i++){
        objectsList[i].startInfo(window);
        if (objectsList[i].getHitBoxing() && objectsList[i].getType() == tool::base) {
            ImGui::Text(u8"Меню создания:");
            ImGui::Image(sf::Sprite(tool::Utils::getTexture(tool::unit_human_warrior_left_0)));
            ImGui::SameLine();
            ImGui::Image(sf::Sprite(tool::Utils::getTexture(tool::unit_human_warrior_left_1)));
        }
        objectsList[i].stopInfo(window);
        objectsList[i].update(window, event);
    }
}

void Map::pollUpdate(sf::Event& event, sf::RenderWindow& window)
{
    //Одноразовое обновление юнитов
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].poll_update(event, window);

    //Одноразовое обновление юнитов
    for (int i = 0; i < objectsList.size(); i++)
        objectsList[i].pollUpdate(window, event);
}

void Map::render(sf::RenderWindow& window){
    //Отрисовать плитки
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            this->map[i][j].render(window);

    //Отрисовка юнитов
    for (int i = 0; i < unitList.size(); i++)
        unitList[i].render(window);

    //Отрисовка объектов
    for (int i = 0; i < objectsList.size(); i++)
        objectsList[i].render(window);
}

Map::~Map(){
    if (map == NULL)
         return;

    for (int i = 0; i < this->rowCount; i++)
        delete[] this->map[i];
    delete[] map;
    for (int i = 0; i < this->rowCount; i++)
        delete[] this->moveMap[i];
    delete[] moveMap;

}
 
Map& Map::operator = (const Map& newMap) {
    Map map(newMap);
    return map;
}

int Map::getSeed() {
    return this->seed;
}
