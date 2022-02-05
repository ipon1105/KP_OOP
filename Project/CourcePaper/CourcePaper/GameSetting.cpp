#include "GameSetting.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>;
#include <fstream>

//��� ����� ������������
const char config[] = "config.txt";

//���� ������������
configurateStruct confSetting;

//������� ������
sf::Music backgroundMusic;

int saveConfigurate() {
	std::ofstream outData(config);

	if (!outData)
		return 1;

	//���������� ������
	outData << confSetting.windowWidth	<< '\n';
	outData << confSetting.windowHeight	<<'\n';

	//�����
	outData << confSetting.generaVolume << '\n';
	outData << confSetting.musicVolume	<< '\n';
	outData << confSetting.soundVolume	<< '\n';

	//������������� �����
	outData << confSetting.screenScale;

	//������ � �������
	outData << confSetting.FPS;
	
	return 0;
}

int defaultConfigurate() {
	sf::VideoMode tmp = sf::VideoMode().getDesktopMode();

	//���������� ������
	confSetting.windowWidth = tmp.width;
	confSetting.windowHeight = tmp.height;

	//�����
	confSetting.generaVolume = 100;
	confSetting.musicVolume = 100;
	confSetting.soundVolume = 100;

	//������������� �����
	confSetting.screenScale = 1;

	//������ � �������
	confSetting.FPS = 60;

	return (saveConfigurate()) ? 1 : 0;
}

int loadConfigurate() {
	std::ifstream inData(config);

	if (!inData)
		return (defaultConfigurate()) ? 1 : -1;

	//���������� ������
	inData >> confSetting.windowWidth;
	inData >> confSetting.windowHeight;

	//�����
	inData >> confSetting.generaVolume;
	inData >> confSetting.musicVolume;
	inData >> confSetting.soundVolume;

	//������������� �����
	inData >> confSetting.screenScale;

	//������ � �������
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