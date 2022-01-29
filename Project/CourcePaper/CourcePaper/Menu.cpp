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
    empty,
    grass,
    stone
};

//������, ������� �� ����
class Title {

private:
    int x;
    int y;
    int width;
    int height;

    //temp
    RectangleShape rect;
    //endtemp

    block type;
    Texture texture;
    Sprite sprite;

public:
    Title() {

    }

    Title(block type) {
        this->type = type;
        
        switch (type) {
            case empty: texture.loadFromFile("resource//spriteList.png", IntRect(0,64,32,32)); break;
            case grass: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case stone: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
        }

        sprite.setTexture(texture);
        sprite.setPosition( (float) x, (float) y );
        
    }

    ~Title() {

    }
    
    void initType(block type){
        this->type = type;

        switch (type) {
            case empty: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case grass: texture.loadFromFile("resource//spriteList.png", IntRect(0, 64, 32, 32)); break;
            case stone: texture.loadFromFile("resource//spriteList.png", IntRect(64, 64, 32, 32)); break;
        }
        sprite.setTexture(texture);
    }

    void setRect(IntRect rec) {
        x = rec.left;
        y = rec.top;
        width = rec.width;
        height = rec.height;
    
        sprite.setPosition(x,y);
        sprite.setScale((float)((float)width)/32.0f, (float)((float)height)/ 32.0f);
    }

    void update(RenderWindow& window) {

    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

};

class Map {

private:
    int windowWidth;
    int windowHeight;

    int globalX;
    int globalY;

    int width;
    int height;
    float titleScale;

    Title **map;
    Vector2i mouseData;

public:
    Map(int width, int height) {
        globalX = 50;
        globalY = 150;

        this->width = width;
        this->height = height;

        titleScale = 32.0f;

        map = new Title*[height];
        for(int i = 0; i < height; i++)
            map[i] = new Title[width];

        initArr();
        windowWidth = getSetting().windowWidth;
        windowHeight = getSetting().windowHeight;
    }
    
    Map(block** arr, int width, int height) {
        globalX = 50;
        globalY = 150;

        this->width = width;
        this->height = height;

        titleScale = 32.0f;

        map = new Title * [height];
        for (int i = 0; i < height; i++)
            map[i] = new Title[width];

        initArr(arr, height, width);
        //getSetting().windowWidth;
    }

    ~Map() {
        for (int i = 0; i < height; i++)
            delete[] map[i];
        delete[] map;
    }

    void initArr() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                map[i][j].setRect(IntRect(j * titleScale, i * titleScale, titleScale, titleScale));
                map[i][j].initType(grass);
            }
    }

    void initArr(block** arr, int aHeight, int bWidth) {
        if (aHeight != height || bWidth != width)
            return initArr();

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                map[i][j].setRect(IntRect(j * titleScale, i * titleScale, titleScale, titleScale));
                map[i][j].initType(arr[i][j]);
            }
    }

    void draw(RenderWindow& window) {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                map[i][j].draw(window);
    }

};

void cameraUpdateScroll(Event event, View& v) {

    if (event.type == event.MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0)
            v.zoom(0.9f);
        else
            v.zoom(1.1f);
    }
}

void cameraUpdateMove(Event event, View& v) {
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

    block bMap[5][5];
        

        std::default_random_engine randomEngine(time(NULL));
        std::uniform_int_distribution<int> randomNum(0, 2);

        for (int i = 0; i < 5;) {
            for (int j = 0; j < 5;) {
                int num = randomNum(randomEngine);
                if (num == 0) {
                    bMap[i][j] = grass;
                }
                else
                    bMap[i][j] = stone;
                    j++;
                }
            i++;
        }


    
    
    block** tmpMap = new block*[5];
    for (int i = 0; i < 5; i++)
        tmpMap[i] = new block[5];

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            tmpMap[i][j] = bMap[i][j];

    Map map(tmpMap, 5, 5);

    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("resource//font2.ttf", 36, NULL,
        ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::SFML::UpdateFontTexture();

    Clock deltaClock;

    View camera;
    camera.reset(sf::FloatRect(0, 0, getSetting().windowWidth, getSetting().windowHeight));

    window.setFramerateLimit(60);
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