#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP
#include <SFML/Audio.hpp>;

struct configurateStruct;

int saveConfigurate();			//Сохранить конфигурацию в файл
int loadConfigurate();			//Загрузить конфигурацию из файла
int defaultConfigurate();		//Загрузить конфигурацию по умолчанию

configurateStruct getSetting();					//Вернуть настройки конфигурации
void setSetting(configurateStruct newStruct);	//Установить новые настройки конфигурации
sf::Music& getBackgroundMusic();				//Возвращает объект фоновой музыки

struct configurateStruct {
	int windowWidth;	//Ширина окна
	int windowHeight;	//Высота окна
	int generaVolume;	//Общая громкость
	int musicVolume;	//Громкость музыкы
	int soundVolume;	//Громкость звуков
	int screenScale;	//Полноэкранный режим

	void defaultVars(const configurateStruct& conf) {
		//Разрешение экрана
		this->windowWidth = conf.windowWidth;
		this->windowHeight = conf.windowHeight;

		//Звуки
		this->generaVolume = conf.generaVolume;
		this->musicVolume = conf.musicVolume;
		this->soundVolume = conf.soundVolume;

		//Полноэкранный режим
		this->screenScale = conf.screenScale;
	}

	configurateStruct(const configurateStruct& conf) {
		defaultVars(conf);
	}

	configurateStruct() {
		defaultVars(getSetting());
	}
};
#endif // !GAME_SETTING_HPP
