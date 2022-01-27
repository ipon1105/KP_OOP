#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include "imgui-SFML.h"

#include "GameSetting.h"

#include <SFML/Graphics.hpp>

using namespace sf;

bool menuWindow;

int menu(RenderWindow& window) {
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

        //ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);
        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Играть").x) * 0.5f);
        ImGui::SetCursorPosY(getSetting().windowHeight * 0.4f);
        if (ImGui::Button(u8"Играть")) {
            
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
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

int setting(RenderWindow& window) {
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
    for (int i = 0; i < tmpArr.size(); i++) {
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
    int var = 0;

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

        ImGui::Begin(u8"Начало", &menuWindow, ImGuiWindowFlags_NoDecoration);
        if (ImGui::Button(u8"Назад")) {
            ImGui::SFML::Shutdown();
            return 1;
        }
        ImGui::Text(u8"Разрешение экрана: ");
        if (ImGui::Combo(u8"Разрешение экрана: ", &var, strings, tmpArr.size())) {
            configurateStruct newData;
            newData.windowWidth = tmpArr[var].width;
            newData.windowHeight = tmpArr[var].height;
            setSetting(newData);
        }
        
        
        
        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Играть").x) * 0.5f);
        ImGui::SetCursorPosY(getSetting().windowHeight * 0.4f);
        if (ImGui::Button(u8"Играть")) {

        }

        for (int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Настройки").x) * 0.5f);
        if (ImGui::Button(u8"Настройки")) {

        }

        for (int i = 0; i < 3; i++)
            ImGui::Spacing();

        ImGui::SetCursorPosX((getSetting().windowWidth - ImGui::CalcTextSize(u8"Выход").x) * 0.5f);
        if (ImGui::Button(u8"Выход")) {
            window.close();
        }
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}