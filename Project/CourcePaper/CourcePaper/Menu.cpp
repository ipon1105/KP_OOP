#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include "imgui-SFML.h"

#include "MyView.h"
#include "GameSetting.h"
#include "Game.h"
#include "block.h"
#include "Creater.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <random>

using namespace sf;

bool menuWindow;



int menu(RenderWindow& window) {
    Texture backTexture;
    backTexture.loadFromFile("resource//gm_1.jpg");
    Sprite backSprite(backTexture);

    //Подгонка изображения под разрешение экрана
    backSprite.setScale((float)(((float)getSetting().windowWidth) / (float)(backTexture.getSize().x)), (float)(((float)getSetting().windowHeight) / (float)(backTexture.getSize().y)));
    
    ImGui::SFML::Init(window);

    menuWindow = true;
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 36, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //Во весь экран
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(getSetting().windowWidth, getSetting().windowHeight));
        ImGui::SetNextWindowBgAlpha(0.0f);

        //ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);
        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Играть").x) * 0.5f);
        ImGui::SetCursorPosY(getSetting().windowHeight * 0.4f);
        if (ImGui::Button(u8"Играть")) {
            ImGui::SFML::Shutdown();
            return 4;
        }

        for(int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Песочница").x) * 0.5f);
        if (ImGui::Button(u8"Песочница")) {
            ImGui::SFML::Shutdown();
            return 5;
        }

        for(int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Настройки").x) * 0.5f);
        if (ImGui::Button(u8"Настройки")) {
            ImGui::SFML::Shutdown();
            return 2;
        }

        for (int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Выход").x) * 0.5f);
        if (ImGui::Button(u8"Выход")) {
            window.close();
        }
        ImGui::End();

        window.clear();
        window.draw(backSprite);
        ImGui::SFML::Render(window);
        window.display();
        if(getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
    }

    ImGui::SFML::Shutdown();
    return 0;
}

int setting(RenderWindow& window) {
    Texture backTexture;
    backTexture.loadFromFile("resource//gm_1.jpg");
    Sprite backSprite(backTexture);
  
    //Подгонка изображения под разрешение экрана
    backSprite.setScale((float)(((float)getSetting().windowWidth) / (float)(backTexture.getSize().x)), (float)(((float)getSetting().windowHeight) / (float)(backTexture.getSize().y)));

    ImGui::SFML::Init(window);

    menuWindow = true;
    bool fullscreenWinow = getSetting().screenScale;

    char** strings;
    int j = 0;
    int k = 0;

    std::vector<sf::VideoMode> tmpArr = sf::VideoMode().getFullscreenModes();
    strings = new char*[tmpArr.size()];
    for (int i = 0; i < tmpArr.size(); i++)
        strings[i] = new char[10];

    char textA[5], textB[5], separator = '*';
    int var = 0, varGeneral = getSetting().generaVolume, varMusic = getSetting().musicVolume, varSound = getSetting().soundVolume;
    for (int i = 0; i < tmpArr.size(); i++) {
        if (getSetting().windowWidth == tmpArr[i].width && getSetting().windowHeight == tmpArr[i].height)
            var = i;
        _itoa(tmpArr[i].width, textA, 10);
        _itoa(tmpArr[i].height, textB, 10);
        while(textA[j]){
            strings[i][j] = textA[j];
            j++;
        }
        strings[i][j] = separator; j++;
        while (textB[k]) {
            strings[i][j] = textB[k];
            j++; k++;
        }
        strings[i][j] = '\0';
        j = k = 0;
        
    }

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 36, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        
        //Во весь экран
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(getSetting().windowWidth, getSetting().windowHeight));
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);
        if (ImGui::Button(u8"Назад")) {
            ImGui::SFML::Shutdown();
            saveConfigurate();
            return 1;
        }
        /*
        Проблема разрешения экрана состоит в том, что просто так нельзя изменить разрешение экрана,
        так же необходимо пересоздать окно SFML, что бы всё было корректно
        */
        if (ImGui::Combo(u8" - разрешение экрана", &var, strings, tmpArr.size())) {
            configurateStruct newData;
            newData.windowWidth = tmpArr[var].width;
            newData.windowHeight = tmpArr[var].height;
            setSetting(newData);

            ImGui::SFML::Shutdown();
            return 3;

        }
        
        ImGui::Text(u8"Громкость: \n");
        ImGui::Text(u8"Общая громкость: ");
        if (ImGui::SliderInt(u8"  ", &varGeneral, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        ImGui::Text(u8"Музыка: ");
        if(ImGui::SliderInt(u8" ", &varMusic, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        ImGui::Text(u8"Звуки: ");
        if (ImGui::SliderInt(u8"   ", &varSound, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        
        if (ImGui::Checkbox(u8"Полноэкранный режим", &fullscreenWinow)) {
            configurateStruct tmp;
            tmp.screenScale = (tmp.screenScale) ? 0 : 1;

            setSetting(tmp);
            saveConfigurate();

            ImGui::SFML::Shutdown();

            return 3;
        };

        ImGui::End();

        window.clear();
        window.draw(backSprite);
        ImGui::SFML::Render(window);
        window.display();
        if (getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
    }

    ImGui::SFML::Shutdown();
    return 0;
}
/*
//Плитка, единица поверхности на поле
class MTitle {

private:
    const int TITLE_SIZE = 32;  //Размер одной плитки

    int x;      //Х координата
    int y;      //Y координата
    int width;  //Ширина плитки
    int height; //Высота плитки

    block type;         //Тип поверхности
    Texture texture;    //Вырезанная текстура
    Sprite sprite;      //Спрайт поверхности
    RectangleShape rect;

    bool hitBox;        //Отображение границ
public:
    //Конструктор по умолчанию
    MTitle() { 
        hitBox = false;
        rect.setFillColor(Color::Transparent);
    }

    //Конструктор по типу поверхности
    MTitle(block type) {
        initType(type);
        hitBox = false;
        rect.setFillColor(Color::Transparent);
    }

    //Деструктор
    ~MTitle() { }
    
    //Инициализация плитки с помощью типа поверхности
    void initType(block type){
        this->type = type;

        switch (type) {
            case empty: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case grass: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case stone: texture.loadFromFile("resource//spriteList.png", IntRect(64, 64, 32, 32)); break;
            case stone_grass_left:texture.loadFromFile("resource//spriteList.png", IntRect(0, 128, 32, 32)); break;       //0,        128
            case stone_grass_right:texture.loadFromFile("resource//spriteList.png", IntRect(64, 128, 32, 32)); break;      //64,       128
            case stone_grass_down:texture.loadFromFile("resource//spriteList.png", IntRect(32, 160, 32, 32)); break;       //32,       160
            case stone_grass_up:texture.loadFromFile("resource//spriteList.png", IntRect(32, 96, 32, 32)); break;         //32,       96
            case stone_grass_left_up:texture.loadFromFile("resource//spriteList.png", IntRect(0, 96, 32, 32)); break;   //0,        96
            case stone_grass_left_down:texture.loadFromFile("resource//spriteList.png", IntRect(0, 160, 32, 32)); break;  //0,        160
            case stone_grass_right_up:texture.loadFromFile("resource//spriteList.png", IntRect(64, 96, 32, 32)); break;   //64,       96
            case stone_grass_right_down:texture.loadFromFile("resource//spriteList.png", IntRect(64, 160, 32, 32)); break;//64,       160
        }
        sprite.setTexture(texture);
    }

    block& getType() { return type; }

    //Установить позицию плитки
    void setPos(int x, int y) {
        this->x =  x * TITLE_SIZE;
        this->y =  y * TITLE_SIZE;
        this->width  = TITLE_SIZE;
        this->height = TITLE_SIZE;
    
        sprite.setPosition(this->x, this->y);

        rect.setPosition(this->x, this->y);
        rect.setOutlineColor(Color::Green);
        rect.setOutlineThickness(2);
        rect.setSize(Vector2f(32.f, 32.f));
    }

    //Отображение границ
    void setHitBox(bool hitBox) {
        this->hitBox = hitBox;
    }

    bool getHitBox() {
        return hitBox;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    //Отрисовка плитки на окне
    void draw(RenderWindow& window) {
        window.draw(sprite);

        if (hitBox)
            window.draw(rect);

    }

};

class MyMap {

private:
    int windowWidth;    //Ширина окна
    int windowHeight;   //Высота окна

    int col;            //Кол. колонок массива
    int row;            //Кол. строк массива

    MTitle **map;        //Массив карты

    //temp
    Unit player;
    int k;
    char dataA[5] = "\0";
    char dataB[5] = "\0";
    //endtemp

public:
    //Конструктор создающий карту col на row
    MyMap(int col, int row) {
        this->col = col;
        this->row = row;

        map = new MTitle*[row];
        for(int i = 0; i < row; i++)
            map[i] = new MTitle[col];

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                map[i][j].getType() = empty;
        windowWidth = getSetting().windowWidth;
        windowHeight = getSetting().windowHeight;

        //////////////

        //Генерация карты
        {
            int cStone = 7;
            int cGrass = 7;
            int r = 0, c = 0;
            int i = 0, j = 0;
            bool finish;

            srand(time(0));

            //Генерация cStone количества камня
            for (i = 0; i < cStone; i++)
            {
                r = rand() % row;
                c = rand() % col;

                map[r][c].initType(stone);
            }

            //Генерация cGrass количества камня
            for (i = 0; i < cGrass; i++)
            {
                r = rand() % row;
                c = rand() % col;

                map[r][c].initType(grass);
            }

            finish = false;
            while (1) {
                for (i = 0; i < row; i++) {
                    for (j = 0; j < col; j++) {

                        if (map[i][j].getType() != 0) {

                            if (map[i][j].getType() == shadowGrass || map[i][j].getType() == shadowStone)
                                break; // Возможно нужна замена на continue

                            if (i - 1 >= 0 && map[i - 1][j].getType() == empty)
                                map[i - 1][j].getType() = (map[i][j].getType() == grass) ? shadowGrass : shadowStone;
                            if (i + 1 <= row - 1 && map[i + 1][j].getType() == empty)
                                map[i + 1][j].getType() = (map[i][j].getType() == grass) ? shadowGrass : shadowStone;
                            if (j - 1 >= 0 && map[i][j - 1].getType() == empty)
                                map[i][j - 1].getType() = (map[i][j].getType() == grass) ? shadowGrass : shadowStone;
                            if (j + 1 <= col - 1 && map[i][j + 1].getType() == empty)
                                map[i][j + 1].getType() = (map[i][j].getType() == grass) ? shadowGrass : shadowStone;

                        }
                    }
                }

                for (int kk = 0; kk < row; kk++) {
                    for (int jj = 0; jj < col; jj++) {
                        if (map[kk][jj].getType() == shadowGrass)
                            map[kk][jj].getType() = grass;
                        if (map[kk][jj].getType() == shadowStone)
                            map[kk][jj].getType() = stone;
                    }
                }

                //Проверка на то, что больше делать нечего
                finish = true;
                for (i = 0; i < row; i++)
                    for (j = 0; j < col; j++)
                        if (map[i][j].getType() == 0)
                        {
                            i = row; j = col;
                            finish = false;
                            break;
                        }



                if (finish)
                    break;
            }
            /*
            for (i = 0; i < row; i++)
                for (j = 0; j < col; j++)
                {
                    if (map[i][j].getType() == grass && map[i - 1][j].getType() == stone && map[i][j - 1].getType() == stone && map[i][j + 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_left_up;//лево верх 
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j - 1].getType() == stone && map[i][j + 1].getType() != stone)
                    {
/*лево низ*//*                        map[i][j].getType() = stone_grass_left_down;
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j + 1].getType() == stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_right_down;//право низ                                         
                    }
                    if (map[i][j].getType() == grass && map[i - 1][j].getType() == stone && map[i][j + 1].getType() == stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_right_up;//право верх                                          
                    }
                    if (map[i][j].getType() == grass && map[i - 1][j].getType() == stone && map[i][j + 1].getType() != stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_up;//верх                                                     
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j + 1].getType() != stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_down;//низ                                                     
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() != stone && map[i - 1][j].getType() != stone && map[i][j - 1].getType() == stone)
                    {
                        map[i][j].getType() = stone_grass_left;//лево                                                    
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() != stone && map[i - 1][j].getType() != stone && map[i][j + 1].getType() == stone)
                    {
                        map[i][j].getType() = stone_grass_right;//право
                    }

                }
                
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++) {
                    map[i][j].setPos(j, i);
                }
        }

        //////////////
        
        player.setPos(col / 2, row / 2);
        k = 0;
    }
    
    //Конструктор, который строит карту по массиву блоков
    MyMap(block** arr, int col, int row) {
        this->col = col;
        this->row = row;

        map = new MTitle * [row];
        for (int i = 0; i < row; i++)
            map[i] = new MTitle[col];

        initArr(arr, row, col);
        
        windowWidth = getSetting().windowWidth;
        windowHeight = getSetting().windowHeight;

        player.setPos(col / 2, row / 2);
        k = 0;
    }

    //Деструктор
    ~MyMap() {
        for (int i = 0; i < row; i++)
            delete[] map[i];
        delete[] map;
    }

    //Инициализация всех плиток как плиток земли
    void initArr() {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                map[i][j].initType(grass);
                map[i][j].setPos(j, i);
            }
    }

    //Инициализация всех плиток в счёт переданного массива блоков в виде карты
    void initArr(block** arr, int aHeight, int bWidth) {
        if (aHeight != row || bWidth != col)
            return initArr();

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                map[i][j].initType(arr[i][j]);
                map[i][j].setPos(j, i);
            }
    }

    //Логика
    void update(Event event, RenderWindow& window) {
        if (k++ % 60 == 0) {
            k = 1;

            player.update(-32, 0);
        }

        if (event.type == event.MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2i mousePos = Mouse::getPosition(window);

            (((View)window.getView()).getCenter().x - (getSetting().windowWidth / 2));

            int col = (mousePos.x + (((View)window.getView()).getCenter().x - (getSetting().windowWidth / 2))) / 32;
            int row = (mousePos.y + (((View)window.getView()).getCenter().y - (getSetting().windowHeight / 2))) / 32;

            if (col >= this->col || row >= this->row || col < 0 || row < 0)
                return;

            MTitle temp = map[row][col];
            temp.setHitBox(!temp.getHitBox());
        }
        

    }

    //Отрисовка всех плиток
    void draw(RenderWindow& window) {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                map[i][j].draw(window);

        player.draw(window);
    }

};

*/

int game(sf::RenderWindow& window, Utilits& tool) {

    Game gme(tool);
    gme.run(window);

    return 0;
}

int mapCreater(sf::RenderWindow& window, Utilits& tool) {

    Creater edit(tool);
    edit.run(window);

    return 0;
}