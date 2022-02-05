#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP
#include <SFML/Audio.hpp>;

struct configurateStruct;

int saveConfigurate();			//��������� ������������ � ����
int loadConfigurate();			//��������� ������������ �� �����
int defaultConfigurate();		//��������� ������������ �� ���������

configurateStruct getSetting();					//������� ��������� ������������
void setSetting(configurateStruct newStruct);	//���������� ����� ��������� ������������
sf::Music& getBackgroundMusic();				//���������� ������ ������� ������

struct configurateStruct {
	int windowWidth;	//������ ����
	int windowHeight;	//������ ����
	int generaVolume;	//����� ���������
	int musicVolume;	//��������� ������
	int soundVolume;	//��������� ������
	int screenScale;	//������������� �����
	int FPS;			//������ � �������

	void defaultVars(const configurateStruct& conf) {
		//���������� ������
		this->windowWidth = conf.windowWidth;
		this->windowHeight = conf.windowHeight;

		//�����
		this->generaVolume = conf.generaVolume;
		this->musicVolume = conf.musicVolume;
		this->soundVolume = conf.soundVolume;

		//������������� �����
		this->screenScale = conf.screenScale;

		//������ � �������
		this->FPS = conf.FPS;
	}

	configurateStruct(const configurateStruct& conf) {
		defaultVars(conf);
	}

	configurateStruct() {
		defaultVars(getSetting());
	}
};
#endif // !GAME_SETTING_HPP
