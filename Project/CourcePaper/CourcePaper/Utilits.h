#pragma once

#include <SFML/Graphics.hpp>
#include "block.h"

class Utilits
{

private:
	//������ ���� �������� �� ������ �����
	sf::Texture textureMap[9][20];

	bool finish;	//��������� �������� �������
	int progress;	//�������� �������� ��������

public:
	//������������
	Utilits();
	
	//������ �������� �������
	void startLoad();

	//������ �������� �� ������ (row*(����� ������ �� 0) + col*(����� ������� �� 0))
	sf::Texture& getTexture(const int& num);

	//������ �������� �� ������� ������ � �������
	sf::Texture& getTexture(const int& row, const int& col);

	//������ �������� �� ������������ block
	sf::Texture& getTexture(const block& title);

	//������ ��������� ��������
	bool isFinily();

	//������ �������� �������
	int getProgress();
};

