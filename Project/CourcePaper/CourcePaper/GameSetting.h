#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

struct configurateStruct {
	int windowWidth;	//Ширина окна
	int windowHeight;	//Высота окна
	int generaVolume;	//Общая громкость
	int musicVolume;	//Громкость музыкы
	int soundVolume;			//Громкость звуков
};

int saveConfigurate();			//Сохранить конфигурацию в файл
int loadConfigurate();			//Загрузить конфигурацию из файла
int defaultConfigurate();		//Загрузить конфигурацию по умолчанию

configurateStruct getSetting();					//Вернуть настройки конфигурации
void setSetting(configurateStruct newStruct);	//Установить новые настройки конфигурации

#endif // !GAME_SETTING_HPP
