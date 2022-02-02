#include "Utilits.h"

Utilits::Utilits() {

	for(int i = 0; i < 9; i++)
		for (int j = 0; j < 20; j++)
			textureMap[i][j].loadFromFile("resource//spriteList.png", sf::IntRect(j * 32, i*32, 32, 32));


}

sf::Texture& Utilits::getTexture(const int& num) {
	if (num >= 180 || num < 0)
		return textureMap[0][6];

	return textureMap[num / 20][num % 20];
}

sf::Texture& Utilits::getTexture(const int& row, const int& col) {
	if (row >= 9 || row < 0 || col >= 20 || col < 0)
		return textureMap[0][6];

	return textureMap[row][col];
}

sf::Texture& Utilits::getTexture(const block& title) {

	switch (title) {
		case empty: return textureMap[0][6]; break;
		case grass: return textureMap[2][0]; break;
		case stone: return textureMap[2][2]; break;
		case water: return textureMap[2][1]; break;

		//<!-- stone & grass-->//

		case stone_grass_left_up:		return textureMap[3][0]; break;
		case stone_grass_left:			return textureMap[4][0]; break;
		case stone_grass_left_down:		return textureMap[5][0]; break;
		case stone_grass_up:			return textureMap[3][1]; break;
		case stone_grass_right_up:		return textureMap[3][2]; break;
		case stone_grass_right:			return textureMap[4][2]; break;
		case stone_grass_right_down:	return textureMap[5][2]; break;
		case stone_grass_down:			return textureMap[5][1]; break;

		case grass_stone_left_up:		return textureMap[3][3]; break;
		case grass_stone_right_up:		return textureMap[3][4]; break;
		case grass_stone_left_down:		return textureMap[4][3]; break;
		case grass_stone_right_down:	return textureMap[4][4]; break;

		case grass_stone_x_1:			return textureMap[5][3]; break;
		case grass_stone_x_2:			return textureMap[5][4]; break;

		//<!-- water & grass-->//

		case water_grass_left_up:		return textureMap[3][5]; break;
		case water_grass_left:			return textureMap[4][5]; break;
		case water_grass_left_down:		return textureMap[5][5]; break;
		case water_grass_up:			return textureMap[3][6]; break;
		case water_grass_right_up:		return textureMap[3][7]; break;
		case water_grass_right:			return textureMap[4][7]; break;
		case water_grass_right_down:	return textureMap[5][7]; break;
		case water_grass_down:			return textureMap[5][6]; break;

		case grass_water_left_up:		return textureMap[3][8]; break;
		case grass_water_right_up:		return textureMap[3][9]; break;
		case grass_water_left_down:		return textureMap[4][8]; break;
		case grass_water_right_down:	return textureMap[4][9]; break;

		case grass_water_x_1:			return textureMap[5][8]; break;
		case grass_water_x_2:			return textureMap[5][9]; break;
	}

	return textureMap[0][6];
}