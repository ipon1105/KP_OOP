#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

//������ ����������� ���������� ������
const int LIST_SCREEN_SIZE[][2] = {
	{ 1920,1080 },
	{ 1680,1050 },
	{ 1400,1050 },
	{ 1280,1024 }
};

struct configurateStruct {
	int windowWidth;	//������ ����
	int windowHeight;	//������ ����
};

int saveConfigurate();			//��������� ������������ � ����
int loadConfigurate();			//��������� ������������ �� �����
int defaultConfigurate();		//��������� ������������ �� ���������

configurateStruct getSetting();					//������� ��������� ������������
void setSetting(configurateStruct newStruct);	//���������� ����� ��������� ������������

#endif // !GAME_SETTING_HPP
