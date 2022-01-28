#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

//Список разрешённых разрешений экрана
const int LIST_SCREEN_SIZE[][2] = {
	{ 1920,1080 },
	{ 1680,1050 },
	{ 1400,1050 },
	{ 1280,1024 }
};

struct configurateStruct {
	int windowWidth;	//Ширина окна
	int windowHeight;	//Высота окна
};

int saveConfigurate();			//Сохранить конфигурацию в файл
int loadConfigurate();			//Загрузить конфигурацию из файла
int defaultConfigurate();		//Загрузить конфигурацию по умолчанию

configurateStruct getSetting();					//Вернуть настройки конфигурации
void setSetting(configurateStruct newStruct);	//Установить новые настройки конфигурации

#endif // !GAME_SETTING_HPP
