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

    

    //�������� ����������� ��� ���������� ������
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

        //�� ���� �����
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(getSetting().windowWidth, getSetting().windowHeight));
        ImGui::SetNextWindowBgAlpha(0.0f);

        //ImGui::Begin(u8"������", &menuWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
        ImGui::Begin(u8"������", &menuWindow, ImGuiWindowFlags_NoDecoration);
        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"������").x) * 0.5f);
        ImGui::SetCursorPosY(getSetting().windowHeight * 0.4f);
        if (ImGui::Button(u8"������")) {
            ImGui::SFML::Shutdown();
            return 4;
        }

        for(int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"���������").x) * 0.5f);
        if (ImGui::Button(u8"���������")) {
            ImGui::SFML::Shutdown();
            return 2;
        }

        for (int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"�����").x) * 0.5f);
        if (ImGui::Button(u8"�����")) {
            window.close();
        }
        ImGui::End();

        window.clear();
        window.draw(backSprite);
        ImGui::SFML::Render(window);
        window.display();
        if(getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����
    }

    ImGui::SFML::Shutdown();
    return 0;
}

int setting(RenderWindow& window) {
    Texture backTexture;
    backTexture.loadFromFile("resource//gm_1.jpg");
    Sprite backSprite(backTexture);
  
    //�������� ����������� ��� ���������� ������
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
        
        //�� ���� �����
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(getSetting().windowWidth, getSetting().windowHeight));
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin(u8"������", &menuWindow, ImGuiWindowFlags_NoDecoration);
        if (ImGui::Button(u8"�����")) {
            ImGui::SFML::Shutdown();
            saveConfigurate();
            return 1;
        }
        /*
        �������� ���������� ������ ������� � ���, ��� ������ ��� ������ �������� ���������� ������,
        ��� �� ���������� ����������� ���� SFML, ��� �� �� ���� ���������
        */
        if (ImGui::Combo(u8" - ���������� ������", &var, strings, tmpArr.size())) {
            configurateStruct newData;
            newData.windowWidth = tmpArr[var].width;
            newData.windowHeight = tmpArr[var].height;
            setSetting(newData);

            ImGui::SFML::Shutdown();
            return 3;

        }
        
        ImGui::Text(u8"���������: \n");
        ImGui::Text(u8"����� ���������: ");
        if (ImGui::SliderInt(u8"  ", &varGeneral, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        ImGui::Text(u8"������: ");
        if(ImGui::SliderInt(u8" ", &varMusic, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        ImGui::Text(u8"�����: ");
        if (ImGui::SliderInt(u8"   ", &varSound, 0, 100)) {
            configurateStruct newData;

            newData.generaVolume = varGeneral;
            newData.musicVolume = varMusic;
            newData.soundVolume = varSound;

            setSetting(newData);
            getBackgroundMusic().setVolume(((float)getSetting().musicVolume) * (((float)getSetting().generaVolume) / 100.0f));
        }
        
        if (ImGui::Checkbox(u8"������������� �����", &fullscreenWinow)) {
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
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����
    }

    ImGui::SFML::Shutdown();
    return 0;
}

//�����������
enum block {
    empty,  //�������
    grass,  //�����
    stone,  //������

    shadowGrass = 100,  //���� �����
    shadowStone         //���� �����

};

class Unit {

private:
    const int TITLE_SIZE = 32;  //������ ����� ���������
    int x;      //� ����������
    int y;      //Y ����������
    int row;    //����� ������
    int col;    //����� �������

    CircleShape g;  //����

public:
    //�����������
    Unit() {
        x = 0;
        y = 0;

        g.setPosition(x + 16, y + 16);
        g.setRadius(15);
    }
    //�����������
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

    //������
    void update(int moveX, int moveY) {
        g.move(moveX, moveY);
    }

    //�����������
    void draw(RenderWindow& window) {
        window.draw(g);
    }
};

//������, ������� ����������� �� ����
class Title {

private:
    const int TITLE_SIZE = 32;  //������ ����� ������

    int x;      //� ����������
    int y;      //Y ����������
    int width;  //������ ������
    int height; //������ ������

    block type;         //��� �����������
    Texture texture;    //���������� ��������
    Sprite sprite;      //������ �����������

public:
    //����������� �� ���������
    Title() { }

    //����������� �� ���� �����������
    Title(block type) {
        initType(type);
    }

    //����������
    ~Title() { }
    
    //������������� ������ � ������� ���� �����������
    void initType(block type){
        this->type = type;

        switch (type) {
            case empty: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case grass: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case stone: texture.loadFromFile("resource//spriteList.png", IntRect(64, 64, 32, 32)); break;
        }
        sprite.setTexture(texture);
    }

    //���������� ������� ������
    void setPos(int x, int y) {
        this->x =  x * TITLE_SIZE;
        this->y =  y * TITLE_SIZE;
        this->width  = TITLE_SIZE;
        this->height = TITLE_SIZE;
    
        sprite.setPosition(this->x, this->y);
    }

    //��������� ������ �� ����
    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

};

//�����, ������� ������������ ����� �������� �
//���� ������� ���������
class Map {

private:
    int windowWidth;    //������ ����
    int windowHeight;   //������ ����

    int col;            //���. ������� �������
    int row;            //���. ����� �������

    Title **map;        //������ �����

    //temp
    Unit player;
    int k;
    //endtemp

public:
    //����������� ��������� ����� col �� row
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
    
    //�����������, ������� ������ ����� �� ������� ������
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

    //����������
    ~Map() {
        for (int i = 0; i < row; i++)
            delete[] map[i];
        delete[] map;
    }

    //������������� ���� ������ ��� ������ �����
    void initArr() {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                map[i][j].initType(grass);
                map[i][j].setPos(j, i);
            }
    }

    //������������� ���� ������ � ���� ����������� ������� ������ � ���� �����
    void initArr(block** arr, int aHeight, int bWidth) {
        if (aHeight != row || bWidth != col)
            return initArr();

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                map[i][j].initType(arr[i][j]);
                map[i][j].setPos(j, i);
            }
    }

    //������
    void update() {
        if (k++ % 60 == 0) {
            k = 1;

            player.update(-32,0);
        }
    }

    //��������� ���� ������
    void draw(RenderWindow& window) {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                map[i][j].draw(window);

        player.draw(window);
    }

};

//������� ��� ���� ������
void cameraUpdateScroll(Event event, View& v) {

    if (event.type == event.MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            v.zoom(0.9f);
        else
            v.zoom(1.1f);
    }
}

//������� ��� ����������� ������
void cameraUpdateMove(Event event, View& v) {
    /*
    ������� - ������� ����������� �� �����������
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
    const int col = 30;
    const int row = 30;

    block bMap[row][col] = { empty };
    //��������� �����
    {
        int cStone = 7;
        int cGrass = 7;
        int r = 0, c = 0;
        int i = 0, j = 0;
        bool finish;

        srand(time(0));

        //��������� cStone ���������� �����
        for (i = 0; i < cStone; i++) 
        {
            r = rand() % row;
            c = rand() % col;

            bMap[r][c] = stone;
        }

        //��������� cGrass ���������� �����
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
                            break; // �������� ����� ������ �� continue

                        if (i - 1 >= 0 && bMap[i - 1][j] == empty)
                            bMap[i - 1][j] = (bMap[i][j] == grass) ? shadowGrass : shadowStone;
                        if (i + 1 <= row-1 && bMap[i + 1][j] == empty)
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

            //�������� �� ��, ��� ������ ������ ������
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
    }

    //temp
    /*
    {
        std::default_random_engine randomEngine(time(NULL));
        std::uniform_int_distribution<int> randomNum(0, 2);

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                bMap[i][j] = (randomNum(randomEngine) == 0 ? grass : stone);
    }
    */
    //endtemp

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
    	// ������������ ������� ������� � �����
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
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����
    }

    ImGui::SFML::Shutdown();
    return 0;
}