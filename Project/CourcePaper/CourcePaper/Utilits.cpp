#include "Utilits.h"

Utilits::Utilits() {
	progress = 0;
	finish = false;
}

void Utilits::startLoad() {
	//�������� ������ 3-�� �����
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 15; j++)
			textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(j * 32, i * 32, 32, 32));
	
	for(int j = 0; j < 13; j++)
		textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(j * 32, 96, 32, 32));
	

	textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(384, 128, 96, 96));
	textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(384, 224, 64, 64));
	textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(448, 224, 32, 64));

	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 12; j++)
			textureMap[progress++].loadFromFile("resource//spriteList.png", sf::IntRect(j * 32, i * 32 + 128, 32, 32));
		

	finish = true; 
}

sf::Texture& Utilits::getTexture(const int& num) {
	if (num >= 157 || num < 0)
		return textureMap[0];
	return textureMap[num];
}	

sf::Texture& Utilits::getTexture(const types& title) {
	if (title == empty || title >= shadowGrass)
		return textureMap[water];
	return textureMap[title];
}

bool Utilits::isFinily(){
	return finish;
}

int Utilits::getProgress(){
	return progress;
}

