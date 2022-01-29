#include "GameSetting.h"

#include <SFML/Graphics.hpp>
#include <fstream>

//Имя файла конфигурации
const char config[] = "config.txt";

//Файл конфигурации
configurateStruct confSetting;

int saveConfigurate() {
	std::ofstream outData(config);

	if (!outData)
		return 1;

	outData << confSetting.windowWidth << '\n';
	outData << confSetting.windowHeight<<'\n';
	outData << confSetting.generaVolume << '\n';
	outData << confSetting.musicVolume << '\n';
	outData << confSetting.soundVolume;
	return 0;
}

int defaultConfigurate() {
	sf::VideoMode tmp = sf::VideoMode().getDesktopMode();
	confSetting.windowWidth = tmp.width;
	confSetting.windowHeight = tmp.height;

	return (saveConfigurate()) ? 1 : 0;
}

int loadConfigurate() {
	std::ifstream inData(config);

	if (!inData)
		return (defaultConfigurate()) ? 1 : -1;

	inData >> confSetting.windowWidth;
	inData >> confSetting.windowHeight;
	inData >> confSetting.generaVolume;
	inData >> confSetting.musicVolume;
	inData >> confSetting.soundVolume;

	return 0;
}

configurateStruct getSetting() {
	return confSetting;
}

void setSetting(configurateStruct newStruct) {
	confSetting = newStruct;
	return (void)0;
}