#include "Map.h"
#include "MyView.h"
#include "GameSetting.h"

Map::Map() {

}

void Map::initMap(const int& row, const int& col) {
    this->rowCount = row;
    this->colCount = col;

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

void Map::createMap(const int& stoneCount, const int& grassCount, const int seed) {
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
        //Деление
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
        
        //Выравнивание
        for (int i = 0; i < rowCount; i++) 
            for (int j = 0; j < colCount; j++) {
                if (blockMap[i][j] == shadowGrass)
                    blockMap[i][j] = grass;
                if (blockMap[i][j] == shadowStone)
                    blockMap[i][j] = stone;
            }
        
        //Гранение:


        //Проверка
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

    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++) 
        {
            map[i][j].setType(blockMap[i][j]);
            map[i][j].setOriginPos(sf::Vector2i(j, i));
        }

    for (int i = 0; i < rowCount; i++)
        delete[] blockMap[i];
    delete[] blockMap;
}

void Map::update(const sf::Event& event, sf::RenderWindow& window) {

    if (event.type == event.MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        int col = (mousePos.x + (getCamera().getCenter().x - (getSetting().windowWidth / 2))) / 32;
        int row = (mousePos.y + (getCamera().getCenter().y - (getSetting().windowHeight / 2))) / 32;

        if (col >= this->colCount || row >= this->rowCount || col < 0 || row < 0)
            return;

        map[row][col].setHitBoxing( !map[row][col].getHitBoxing());
    }

    /*
    if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        (((View)window.getView()).getCenter().x - (getSetting().windowWidth / 2));

        int col = (mousePos.x + (((View)window.getView()).getCenter().x - (getSetting().windowWidth / 2))) / 32;
        int row = (mousePos.y + (((View)window.getView()).getCenter().y - (getSetting().windowHeight / 2))) / 32;

        if (col >= this->colCount || row >= this->rowCount || col < 0 || row < 0)
            return;

        Box temp = map[row][col];
        temp.setHitBoxing(!temp.getHitBoxing());
    }
    */

}

void Map::render(sf::RenderWindow& window){
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            this->map[i][j].render(window);
}

 Map::~Map(){
    for (int i = 0; i < this->rowCount; i++)
        delete[] this->map[i];
    delete[] map;
}
 
 Map& Map::operator = (const Map& newMap) {
     Map map(newMap);
     return map;
 }