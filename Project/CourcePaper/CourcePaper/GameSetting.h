#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

struct configurateStruct {
	int windowWidth;	//Ширина окна
	int windowHeight;	//Высота окна
	int allSound; //общая громкость
	int Music;// музыка
	int sound;//звуки
};

int saveConfigurate();			//Сохранить конфигурацию в файл
int loadConfigurate();			//Загрузить конфигурацию из файла
int defaultConfigurate();		//Загрузить конфигурацию по умолчанию

configurateStruct getSetting();					//Вернуть настройки конфигурации
void setSetting(configurateStruct newStruct);	//Установить новые настройки конфигурации

#endif // !GAME_SETTING_HPP
