#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include "imgui-SFML.h"

#include "MyView.h"
#include "GameSetting.h"
#include "Game.h"
#include "block.h"

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
/*
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
class MTitle {

private:
    const int TITLE_SIZE = 32;  //������ ����� ������

    int x;      //� ����������
    int y;      //Y ����������
    int width;  //������ ������
    int height; //������ ������

    block type;         //��� �����������
    Texture texture;    //���������� ��������
    Sprite sprite;      //������ �����������
    RectangleShape rect;

    bool hitBox;        //����������� ������
public:
    //����������� �� ���������
    MTitle() { 
        hitBox = false;
        rect.setFillColor(Color::Transparent);
    }

    //����������� �� ���� �����������
    MTitle(block type) {
        initType(type);
        hitBox = false;
        rect.setFillColor(Color::Transparent);
    }

    //����������
    ~MTitle() { }
    
    //������������� ������ � ������� ���� �����������
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

    //���������� ������� ������
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

    //����������� ������
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

    //��������� ������ �� ����
    void draw(RenderWindow& window) {
        window.draw(sprite);

        if (hitBox)
            window.draw(rect);

    }

};

class MyMap {

private:
    int windowWidth;    //������ ����
    int windowHeight;   //������ ����

    int col;            //���. ������� �������
    int row;            //���. ����� �������

    MTitle **map;        //������ �����

    //temp
    Unit player;
    int k;
    char dataA[5] = "\0";
    char dataB[5] = "\0";
    //endtemp

public:
    //����������� ��������� ����� col �� row
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

                map[r][c].initType(stone);
            }

            //��������� cGrass ���������� �����
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
                                break; // �������� ����� ������ �� continue

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

                //�������� �� ��, ��� ������ ������ ������
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
                        map[i][j].getType() = stone_grass_left_up;//���� ���� 
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j - 1].getType() == stone && map[i][j + 1].getType() != stone)
                    {
/*���� ���*//*                        map[i][j].getType() = stone_grass_left_down;
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j + 1].getType() == stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_right_down;//����� ���                                         
                    }
                    if (map[i][j].getType() == grass && map[i - 1][j].getType() == stone && map[i][j + 1].getType() == stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_right_up;//����� ����                                          
                    }
                    if (map[i][j].getType() == grass && map[i - 1][j].getType() == stone && map[i][j + 1].getType() != stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_up;//����                                                     
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() == stone && map[i][j + 1].getType() != stone && map[i][j - 1].getType() != stone)
                    {
                        map[i][j].getType() = stone_grass_down;//���                                                     
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() != stone && map[i - 1][j].getType() != stone && map[i][j - 1].getType() == stone)
                    {
                        map[i][j].getType() = stone_grass_left;//����                                                    
                    }
                    if (map[i][j].getType() == grass && map[i + 1][j].getType() != stone && map[i - 1][j].getType() != stone && map[i][j + 1].getType() == stone)
                    {
                        map[i][j].getType() = stone_grass_right;//�����
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
    
    //�����������, ������� ������ ����� �� ������� ������
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

    //����������
    ~MyMap() {
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

    //��������� ���� ������
    void draw(RenderWindow& window) {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                map[i][j].draw(window);

        player.draw(window);
    }

};

int gameplay(RenderWindow& window) {
    const int col = 40;
    const int row = 40;

    char
        cenX[5] = "\0", cenY[5] = "\0",
        posX[5] = "\0", posY[5] = "\0",
        posCol[5] = "\0", posRow[5] = "\0",
        winWid2[5] = "\0", winHei2[5] = "\0",
        posWidth[5] = "\0", posHeight[5] = "\0";
   
    MyMap map(row, col);

    ImGui::SFML::Init(window, false);////////////////////////////////////////////
    ImGuiIO& io = ImGui::GetIO();////////////////////////////////////////////
    io.Fonts->Clear();////////////////////////////////////////////
    io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 22, NULL,////////////////////////////////////////////
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());////////////////////////////////////////////
    ImGui::SFML::UpdateFontTexture();////////////////////////////////////////////
    ImGuiStyle oldStyle = ImGui::GetStyle();////////////////////////////////////////////

    oldStyle.Colors[2] = ImVec4(0.48, 0.23, 0.16, 1.0f);////////////////////////////////////////////
    //oldStyle.Colors[8] = ImVec4(0.98, 0.43, 0.26, 0.0f);
    //oldStyle.Colors[9] = ImVec4(0.98, 0.43, 0.26, 0.0f);

    oldStyle.Alpha = 0.0f;////////////////////////////////////////////
    //ImGui::SetNextWindowBgAlpha(0.1f);

    Clock deltaClock;////////////////////////////////////////////

    getCamera() = window.getView();

    //camera.reset(sf::FloatRect(0, 0, getSetting().windowWidth, getSetting().windowHeight));

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
    	// ������������ ������� ������� � �����
    	Event event;
    	while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

    		if (event.type == Event::Closed)
    			window.close();

            cameraUpdateZoom(event);
    	}
        cameraUpdateMove(event);

        ImGui::SFML::Update(window, deltaClock.restart());////////////////////////////////////////////
        window.setView(camera);
        window.clear(Color(Color::Black));
        
        map.draw(window);

        ImGui::SetNextWindowBgAlpha(0.2f);////////////////////////////////////////////
        ImGui::Begin(u8"����������");////////////////////////////////////////////

        //��������� ���������� �� ����������� ����
        {
            Vector2i mousePos = Mouse::getPosition(window);
            
            {
                ImGui::BeginGroup();
                //�����
                {
                    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"�����:").x) * 0.5f);
                    ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"�����:");

                    ImGui::Text(u8"X = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(mousePos.x, posX, 10));
                    ImGui::SameLine();

                    ImGui::Text(u8"; Y = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(mousePos.y, posY, 10));
                    ImGui::Spacing();
                }
                
                //������� ������ �� �����
                {
                    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"������� ������:").x) * 0.5f);
                    ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"������� ������:");

                    ImGui::Text(u8"������ = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(mousePos.y / 32, posRow, 10));
                    ImGui::SameLine();

                    ImGui::Text(u8"; ������� = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(mousePos.x / 32, posCol, 10));
                    ImGui::Spacing();
                }

                //���������� � ����
                {
                    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"���:").x) * 0.5f);
                    ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"���:");

                    ImGui::Text(u8"������ = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(((View)window.getView()).getSize().x, posWidth, 10));
                    ImGui::SameLine();

                    ImGui::Text(u8"; ������ = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(((View)window.getView()).getSize().y, posHeight, 10));

                    ImGui::Text(u8"�����X = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(((View)window.getView()).getCenter().x, cenX, 10));
                    ImGui::SameLine();

                    ImGui::Text(u8"; �����Y = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(((View)window.getView()).getCenter().y, cenY, 10));
                    ImGui::Spacing();
                }

                //�������� ������
                {
                    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"�����:").x) * 0.5f);
                    ImGui::TextColored(ImVec4(0.8, 0.8, 0.8, 1.0), u8"�����:");

                    ImGui::Text(u8"windowWidth / 2 = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(getSetting().windowWidth / 2,winWid2,10));

                    ImGui::Text(u8"windowHeight / 2 = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(getSetting().windowHeight / 2, winWid2, 10));

                    int col = (mousePos.x + (((View)window.getView()).getCenter().x - (getSetting().windowWidth / 2)));
                    int row = (mousePos.y + (((View)window.getView()).getCenter().y - (getSetting().windowHeight / 2)));

                    ImGui::Text(u8"mousePos.x + (windowWidth / 2) = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(col, winWid2, 10));

                    ImGui::Text(u8"mousePos.y + (windowHeight / 2) = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(row, winWid2, 10));

                    col = (mousePos.x + (((View)window.getView()).getCenter().x - (((View)window.getView()).getSize().x / 2) * 1.1f));
                    row = (mousePos.y + (((View)window.getView()).getCenter().y - (((View)window.getView()).getSize().y / 2) * 1.1f));

                    ImGui::Text(u8"mousePos.x + (view.windowWidth / 2) = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(col, winWid2, 10));

                    ImGui::Text(u8"mousePos.y + (view.windowHeight / 2) = ");
                    ImGui::SameLine();

                    ImGui::Text(_itoa(row, winWid2, 10));



                }

                ImGui::EndGroup();
                //ImGui::Text(u8"�����");
            }
        }////////////////////////////////////////////

        ImGui::End();////////////////////////////////////////////

        ImGui::SFML::Render(window);////////////////////////////////////////////
        window.display();
        
        if (getSetting().screenScale)
            ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //��������� ��������� ���� �� ����
    }

    ImGui::SFML::Shutdown();
    return 0;
}
*/

int test(sf::RenderWindow& window) {

    Game gme;
    gme.run(window);

    return 0;
}