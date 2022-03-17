#include "GameSetting.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>;
#include <fstream>

//Имя файла конфигурации
const char config[] = "config.txt";

//Файл конфигурации
configurateStruct confSetting;

//Фоновая музыка
sf::Music backgroundMusic;

int saveConfigurate() {
	std::ofstream outData(config);

	if (!outData)
		return 1;

	//Разрешение экрана
	outData << confSetting.windowWidth	<< '\n';
	outData << confSetting.windowHeight	<<'\n';

	//Звуки
	outData << confSetting.generaVolume << '\n';
	outData << confSetting.musicVolume	<< '\n';
	outData << confSetting.soundVolume	<< '\n';

	//Полноэкранный режим
	outData << confSetting.screenScale << '\n';

	//Кадров в секунду
	outData << confSetting.FPS;
	
	return 0;
}

int defaultConfigurate() {
	sf::VideoMode tmp = sf::VideoMode().getDesktopMode();

	//Разрешение экрана
	confSetting.windowWidth = tmp.width;
	confSetting.windowHeight = tmp.height;

	//Звуки
	confSetting.generaVolume = 100;
	confSetting.musicVolume = 100;
	confSetting.soundVolume = 100;

	//Полноэкранный режим
	confSetting.screenScale = 1;

	//Кадров в секунду
	confSetting.FPS = 60;

	return (saveConfigurate()) ? 1 : 0;
}

int loadConfigurate() {
	std::ifstream inData(config);

	if (!inData)
		return (defaultConfigurate()) ? 1 : -1;

	//Разрешение экрана
	inData >> confSetting.windowWidth;
	inData >> confSetting.windowHeight;

	//Звуки
	inData >> confSetting.generaVolume;
	inData >> confSetting.musicVolume;
	inData >> confSetting.soundVolume;

	//Полноэкранный режим
	inData >> confSetting.screenScale;

	//Кадров в секунду
	inData >> confSetting.FPS;

	return 0;
}

configurateStruct getSetting() {
	return confSetting;
}

void setSetting(configurateStruct newStruct) {
	confSetting = newStruct;
}

sf::Music& getBackgroundMusic() {
	return backgroundMusic;
}