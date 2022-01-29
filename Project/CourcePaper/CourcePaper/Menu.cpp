#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include "imgui-SFML.h"

#include "GameSetting.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>


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

    char** strings;
    int j = 0;
    int k = 0;

    std::vector<sf::VideoMode> tmpArr = sf::VideoMode().getFullscreenModes();
    strings = new char*[tmpArr.size()];
    for (int i = 0; i < tmpArr.size(); i++)
        strings[i] = new char[10];

    char textA[5], textB[5], separator = '*';
    int var = 0;
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
static int val1= getSetting().generaVolume,val2= getSetting().musicVolume,val3= getSetting().soundVolume;
        //Во весь экран
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(getSetting().windowWidth, getSetting().windowHeight));
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);
        if (ImGui::Button(u8"Назад")) {
            configurateStruct newData;
            newData.windowWidth = tmpArr[var].width;
            newData.windowHeight = tmpArr[var].height;
            newData.generaVolume = val1;
            newData.musicVolume = val2;
            newData.soundVolume = val3;
            setSetting(newData);
            saveConfigurate();
            ImGui::SFML::Shutdown();
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
            newData.generaVolume = val1;
            newData.musicVolume = val2;
            newData.soundVolume = val3;
            setSetting(newData);
            saveConfigurate();
            ImGui::SFML::Shutdown();
            return 3;

        }
        
        ImGui::Text(u8"Громкость: \n");
        ImGui::Text(u8"Общая громкость: ");
        ImGui::SliderInt(u8"  ", &val1, 0, 100);
        ImGui::Text(u8"Музыка: ");
        ImGui::SliderInt(u8" ", &val2, 0, 100);
        ImGui::Text(u8"Звуки: ");
        ImGui::SliderInt(u8"   ", &val3, 0, 100);
       /* configurateStruct newData;
        
        setSetting(newData);
        saveConfigurate();*/
       //ImGui::SFML::Shutdown();
        ImGui::End();

        window.clear();
        window.draw(backSprite);
        ImGui::SFML::Render(window);
        window.display();
        ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);  //Позволяет растенуть окно до краёв
    }

    ImGui::SFML::Shutdown();
    return 0;
}

//Поверхности
enum block {
    empty,
    grass,
    stone
};

//Плитка, единица на поле
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
        sprite.setScale(width/32, height/32);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

};

class Map {

private:
    int width;
    int height;
    int titleScale;
    float scalingMap;

    Title **map;

public:
    Map(int width, int height) {
        this->width = width;
        this->height = height;

        titleScale = 100;

        map = new Title*[height];
        for(int i = 0; i < height; i++)
            map[i] = new Title[width];

        initArr();
        //getSetting().windowWidth;
    }
    
    Map(block** arr, int width, int height) {
        this->width = width;
        this->height = height;

        titleScale = 100;

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

    void inc() {
        //if(scalingMap + 0.1 > 1.0)
    }

    void draw(RenderWindow& window) {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                map[i][j].draw(window);
    }

    void update(Event event, RenderWindow& window) {
        if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            //std::cout << "x = " << Mouse::getPosition(window).x << "; y = " << Mouse::getPosition(window).y << ";\n";
        }
    }
};

int gameplay(RenderWindow& window) {
    block bMap[5][5] = {
        {stone,grass,grass,grass,grass},
        {grass,stone,stone,stone,grass},
        {grass,stone,grass,stone,grass},
        {grass,stone,stone,stone,grass},
        {grass,grass,grass,grass,grass}
    };
    
    block** tmpMap = new block*[5];
    for (int i = 0; i < 5; i++)
        tmpMap[i] = new block[5];

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            tmpMap[i][j] = bMap[i][j];

    Map map(tmpMap, 5, 5);

    while (window.isOpen())
    {
    	// Обрабатываем очередь событий в цикле
    	Event event;
    	while (window.pollEvent(event)) {
    		if (event.type == Event::Closed)
    			window.close();
    	}

    	window.clear(Color(Color::Black));
        map.draw(window);
    	window.display();
    }

    return 1;
}