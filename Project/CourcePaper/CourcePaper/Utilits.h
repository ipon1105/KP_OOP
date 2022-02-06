#pragma once

#include <SFML/Graphics.hpp>
#include "types.h"

class Utilits
{

private:
	//������ ���� �������� �� ������ �����
	sf::Texture textureMap[157];

	bool finish;	//��������� �������� �������
	int progress;	//�������� �������� ��������

public:
	//������������
	Utilits();
	
	//������ �������� �������
	void startLoad();

	//������ �������� �� ������ (row*(����� ������ �� 0) + col*(����� ������� �� 0))
	sf::Texture& getTexture(const int& num);

	//������ �������� �� ������������ block
	sf::Texture& getTexture(const types& title);

	//������ ��������� ��������
	bool isFinily();

	//������ �������� �������
	int getProgress();
};

