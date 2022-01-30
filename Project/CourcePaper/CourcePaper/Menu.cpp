#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include "imgui-SFML.h"

#include "GameSetting.h"

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
        };/*
        if (fullscreenWinow != (getSetting().screenScale ? true : false)) {
            getSetting().screenScale = getSetting().screenScale ? 0 : 1;

            ImGui::SFML::Shutdown();
            saveConfigurate();

            return 3;
        }*/
       /* configurateStruct newData;
        
        setSetting(newData);
        saveConfigurate();*/
       //ImGui::SFML::Shutdown();
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

//Поверхности
enum block {
    empty,  //Пустота   
    grass,  //Земля     0,      64
    stone,  //Камень    64,     64
    water,  //Вода      32,     64

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

class Unit {

private:
    const int TITLE_SIZE = 32;  //Размер одной персонажа
    int x;      //Х координата
    int y;      //Y координата
    int row;    //Номер строки
    int col;    //Номер колонки

    CircleShape g;  //Круг

public:
    //Конструктор
    Unit() {
        x = 0;
        y = 0;

        g.setPosition(x + 16, y + 16);
        g.setRadius(15);
    }
    //Конструктор
    Unit(int x, int y) {
        this->x = x;
        this->y = y;

        g.setPosition(x+16,y+16);
        g.setRadius(15);
        g.setFillColor(Color::Red);
    }

    void setPos(int x, int y) {
        this->x = x * 32;
        this->y = y * 32;

        g.setPosition(this->x, this->y);
        g.setRadius(15);
        g.setFillColor(Color::Red);
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    //Логика
    void update(int moveX, int moveY) {
        g.move(moveX, moveY);
    }

    //Отображение
    void draw(RenderWindow& window) {
        window.draw(g);
    }
};

//Плитка, единица поверхности на поле
class Title {

private:
    const int TITLE_SIZE = 32;  //Размер одной плитки

    int x;      //Х координата
    int y;      //Y координата
    int width;  //Ширина плитки
    int height; //Высота плитки

    block type;         //Тип поверхности
    Texture texture;    //Вырезанная текстура
    Sprite sprite;      //Спрайт поверхности

public:
    //Конструктор по умолчанию
    Title() { }

    //Конструктор по типу поверхности
    Title(block type) {
        initType(type);
    }

    //Деструктор
    ~Title() { }
    
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

    //Установить позицию плитки
    void setPos(int x, int y) {
        this->x =  x * TITLE_SIZE;
        this->y =  y * TITLE_SIZE;
        this->width  = TITLE_SIZE;
        this->height = TITLE_SIZE;
    
        sprite.setPosition(this->x, this->y);
    }

    //Отрисовка плитки на окне
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

};

//Класс, который манипулирует всеми плитками и
//всем игровым процессом
class Map {

private:
    int windowWidth;    //Ширина окна
    int windowHeight;   //Высота окна

    int col;            //Кол. колонок массива
    int row;            //Кол. строк массива

    Title **map;        //Массив карты

    //temp
    Unit player;
    int k;
    //endtemp

public:
    //Конструктор создающий карту col на row
    Map(int col, int row) {
        this->col = col;
        this->row = row;

        map = new Title*[row];
        for(int i = 0; i < row; i++)
            map[i] = new Title[col];

        initArr();
        
        windowWidth = getSetting().windowWidth;
        windowHeight = getSetting().windowHeight;

        player.setPos(col / 2, row / 2);
        k = 0;
    }
    
    //Конструктор, который строит карту по массиву блоков
    Map(block** arr, int col, int row) {
        this->col = col;
        this->row = row;

        map = new Title * [row];
        for (int i = 0; i < row; i++)
            map[i] = new Title[col];

        initArr(arr, row, col);
        
        windowWidth = getSetting().windowWidth;
        windowHeight = getSetting().windowHeight;

        player.setPos(col / 2, row / 2);
        k = 0;
    }

    //Деструктор
    ~Map() {
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
    void update() {
        if (k++ % 60 == 0) {
            k = 1;

            player.update(-32,0);
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

//Функция для зума камеры
void cameraUpdateScroll(Event event, View& v) {

    if (event.type == event.MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            v.zoom(0.9f);
        else
            v.zoom(1.1f);
    }
}

//Функция для перемещения камеры
void cameraUpdateMove(Event event, View& v) {
    /*
    Пометка - сделать зависимость от приблежения
    */
    const int speed = 5;

    if (Keyboard::isKeyPressed(Keyboard::Left))
        v.move(-speed, 0);
    if (Keyboard::isKeyPressed(Keyboard::Right))
        v.move(speed, 0);
    if (Keyboard::isKeyPressed(Keyboard::Down))
        v.move(0, speed);
    if (Keyboard::isKeyPressed(Keyboard::Up))
        v.move(0, -speed);
}


int gameplay(RenderWindow& window) {
    const int col = 40;
    const int row = 40;

    block bMap[row][col] = { empty };
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

            bMap[r][c] = stone;
        }

        //Генерация cGrass количества камня
        for (i = 0; i < cGrass; i++)
        {
            r = rand() % row;
            c = rand() % col;

            bMap[r][c] = grass;
        }

        finish = false;
        while (1) {
            for (i = 0; i < row; i++) {
                for (j = 0; j < col; j++) {

                    if (bMap[i][j] != 0) {

                        if (bMap[i][j] == shadowGrass || bMap[i][j] == shadowStone)
                            break; // Возможно нужна замена на continue

                        if (i - 1 >= 0 && bMap[i - 1][j] == empty)
                            bMap[i - 1][j] = (bMap[i][j] == grass) ? shadowGrass : shadowStone;
                        if (i + 1 <= row - 1 && bMap[i + 1][j] == empty)
                            bMap[i + 1][j] = (bMap[i][j] == grass) ? shadowGrass : shadowStone;
                        if (j - 1 >= 0 && bMap[i][j - 1] == empty)
                            bMap[i][j - 1] = (bMap[i][j] == grass) ? shadowGrass : shadowStone;
                        if (j + 1 <= col - 1 && bMap[i][j + 1] == empty)
                            bMap[i][j + 1] = (bMap[i][j] == grass) ? shadowGrass : shadowStone;

                    }
                }
            }

            for (int kk = 0; kk < row; kk++) {
                for (int jj = 0; jj < col; jj++) {
                    if (bMap[kk][jj] == shadowGrass)
                        bMap[kk][jj] = grass;
                    if (bMap[kk][jj] == shadowStone)
                        bMap[kk][jj] = stone;
                }
            }

            //Проверка на то, что больше делать нечего
            finish = true;
            for (i = 0; i < row; i++)
                for (j = 0; j < col; j++)
                    if (bMap[i][j] == 0)
                    {
                        i = row; j = col;
                        finish = false;
                        break;
                    }



            if (finish)
                break;
        }
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
            {
                if (bMap[i][j] == grass && bMap[i - 1][j] == stone && bMap[i][j - 1] == stone && bMap[i][j + 1] != stone)
                {
                    bMap[i][j] = stone_grass_left_up;//лево верх 
                }
                if (bMap[i][j] == grass && bMap[i + 1][j] == stone && bMap[i][j - 1] == stone && bMap[i][j + 1] != stone)
                {
                    bMap[i][j] = stone_grass_left_down;//лево низ
                }
                if (bMap[i][j] == grass && bMap[i + 1][j] == stone && bMap[i][j + 1] == stone && bMap[i][j - 1] != stone)
                {
                    bMap[i][j] = stone_grass_right_down;//право низ
                }
                if (bMap[i][j] == grass && bMap[i - 1][j] == stone && bMap[i][j + 1] == stone && bMap[i][j - 1] != stone)
                {
                    bMap[i][j] = stone_grass_right_up;//право верх
                }
                if (bMap[i][j] == grass && bMap[i - 1][j] == stone && bMap[i][j + 1] != stone && bMap[i][j - 1] != stone)
                {
                    bMap[i][j] = stone_grass_up;//верх
                }
                if (bMap[i][j] == grass && bMap[i + 1][j] == stone && bMap[i][j + 1] != stone && bMap[i][j - 1] != stone)
                {
                    bMap[i][j] = stone_grass_down;//низ
                }
                if (bMap[i][j] == grass && bMap[i + 1][j] != stone && bMap[i-1][j] != stone && bMap[i][j - 1] == stone)
                {
                    bMap[i][j] = stone_grass_left;//лево
                }
                if (bMap[i][j] == grass && bMap[i + 1][j] != stone && bMap[i-1][j] != stone && bMap[i][j + 1] == stone)
                {
                    bMap[i][j] = stone_grass_right;//право
                }

            }

    }

    block** tmpMap = new block*[row];
    for (int i = 0; i < row; i++)
        tmpMap[i] = new block[col];

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            tmpMap[i][j] = bMap[i][j];

    Map map(tmpMap, row, col);

    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 36, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;

    View camera;
    camera.reset(sf::FloatRect(0, 0, getSetting().windowWidth, getSetting().windowHeight));

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
    	// Обрабатываем очередь событий в цикле
    	Event event;
    	while (window.pollEvent(event)) {

    		if (event.type == Event::Closed)
    			window.close();

            cameraUpdateScroll(event, camera);
    	}
        cameraUpdateMove(event, camera);
        map.update();
        ImGui::SFML::Update(window, deltaClock.restart());
        window.setView(camera);
        window.clear(Color(Color::Black));
        map.draw(window);
        ImGui::SFML::Render(window);
    	window.display();
        if (getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
    }

    ImGui::SFML::Shutdown();
    return 0;
}