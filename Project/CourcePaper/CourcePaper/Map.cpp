#include "Map.h"

Map::Map() {
    this->colCount = 10;
    this->rowCount = 10;

    map = new Box * [rowCount];
    for (int i = 0; i < rowCount; i++)
        map[i] = new Box[this->colCount];

    //temp
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
        {
            map[i][j].setOriginPos(sf::Vector2i(j, i));
            map[i][j].setType(grass);
        }
    //endtemp
}

Map::Map(const int& row, const int& col) {
    this->colCount = col;
    this->rowCount = row;

    map = new Box*[this->rowCount];
    for (int i = 0; i < this->rowCount; i++)
        map[i] = new Box[this->colCount];

    //temp
    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
        {
            map[i][j].setOriginPos(sf::Vector2i(j,i));
            map[i][j].setType(grass);
        }
    //endtemp
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

    for (int i = 0; i < this->rowCount; i++)
        for (int j = 0; j < this->colCount; j++)
            map[i][j] = newMap.map[i][j];
}

void Map::createMap(const int& stoneCount, const int& grassCount, const int seed = time(0)) {
    srand(seed);

    /*
    Сделать
    */

}

void Map::update(const sf::Event& event) {
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