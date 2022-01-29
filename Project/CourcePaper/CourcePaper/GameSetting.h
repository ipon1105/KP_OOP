#pragma once
#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

struct configurateStruct {
	int windowWidth;	//������ ����
	int windowHeight;	//������ ����
	int generaVolume;	//����� ���������
	int musicVolume;	//��������� ������
	int soundVolume;			//��������� ������
};

int saveConfigurate();			//��������� ������������ � ����
int loadConfigurate();			//��������� ������������ �� �����
int defaultConfigurate();		//��������� ������������ �� ���������

configurateStruct getSetting();					//������� ��������� ������������
void setSetting(configurateStruct newStruct);	//���������� ����� ��������� ������������

#endif // !GAME_SETTING_HPP
