#pragma once

#include <SFML/Graphics.hpp>
#include "block.h"

enum unit_block {
	//���� �������
	vil0_a1,
	vil0_a2,
	vil0_a3,
	vil0_a4,
	vil0_a5,
	vil0_a6,
	vil0_a7,
	vil0_a8,
	vil0_a9,
	vil0_a10,
	vil0_a11,
	vil0_a12,

	//���� ������
	vil1_a1,
	vil1_a2,
	vil1_a3,
	vil1_a4,
	vil1_a5,
	vil1_a6,
	vil1_a7,
	vil1_a8,
	vil1_a9,
	vil1_a10,
	vil1_a11,
	vil1_a12,

	//���� ������
	vil2_a1,
	vil2_a2,
	vil2_a3,
	vil2_a4,
	vil2_a5,
	vil2_a6,
	vil2_a7,
	vil2_a8,
	vil2_a9,
	vil2_a10,
	vil2_a11,
	vil2_a12,

	//���� ������
	vil3_a1,
	vil3_a2,
	vil3_a3,
	vil3_a4,
	vil3_a5,
	vil3_a6,
	vil3_a7,
	vil3_a8,
	vil3_a9,
	vil3_a10,
	vil3_a11,
	vil3_a12,

	//������ �������
	vil0_b1,
	vil0_b2,
	vil0_b3,
	vil0_b4,
	vil0_b5,
	vil0_b6,
	vil0_b7,
	vil0_b8,
	vil0_b9,
	vil0_b10,
	vil0_b11,
	vil0_b12,

	//������ ������
	vil1_b1,
	vil1_b2,
	vil1_b3,
	vil1_b4,
	vil1_b5,
	vil1_b6,
	vil1_b7,
	vil1_b8,
	vil1_b9,
	vil1_b10,
	vil1_b11,
	vil1_b12,

	//������ ������
	vil2_b1,
	vil2_b2,
	vil2_b3,
	vil2_b4,
	vil2_b5,
	vil2_b6,
	vil2_b7,
	vil2_b8,
	vil2_b9,
	vil2_b10,
	vil2_b11,
	vil2_b12,

	//������ ������
	vil3_b1,
	vil3_b2,
	vil3_b3,
	vil3_b4,
	vil3_b5,
	vil3_b6,
	vil3_b7,
	vil3_b8,
	vil3_b9,
	vil3_b10,
	vil3_b11,
	vil3_b12
};

class Utilits
{

private:
	//������ ���� �������� �� ������ �����
	sf::Texture textureMap[9][20];

	//������ ���� ������ �� ������ ������
	sf::Texture unitTexture[8][12];

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

	//������ �������� �� ������������ unit_block
	sf::Texture& getUnitTexture(const unit_block& title);

	//������ ��������� ��������
	bool isFinily();

	//������ �������� �������
	int getProgress();
};

