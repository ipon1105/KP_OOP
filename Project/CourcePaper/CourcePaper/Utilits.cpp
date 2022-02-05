#include "Utilits.h"

Utilits::Utilits() {
	finish = false;
}

void Utilits::startLoad() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 20; j++){
			textureMap[i][j].loadFromFile("resource//spriteList.png", sf::IntRect(j * 32, i * 32, 32, 32));
			progress = i * 20 + j;
		}

	//Воины от 0 до 3
	for(int i = 0; i < 12; i++){
		unitTexture[0][i].loadFromFile("resource//UnitList//Solider_1.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++){
		unitTexture[1][i].loadFromFile("resource//UnitList//Solider_2.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++){
		unitTexture[2][i].loadFromFile("resource//UnitList//Solider_3.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++){
		unitTexture[3][i].loadFromFile("resource//UnitList//Solider_4.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	
	//Жители от 0 до 3
	for (int i = 0; i < 12; i++){
		unitTexture[4][i].loadFromFile("resource//UnitList//Vilager_1.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++) {
		unitTexture[5][i].loadFromFile("resource//UnitList//Vilager_2.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++) {
		unitTexture[6][i].loadFromFile("resource//UnitList//Vilager_3.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}
	for (int i = 0; i < 12; i++) {
		unitTexture[7][i].loadFromFile("resource//UnitList//Vilager_4.png", sf::IntRect(i / (32 * 3), (i * 32) % (32 * 3), 32, 32));
		progress++;
	}

	finish = true; 
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
		
		//<!-- objects -->//

		case woodRes:	return textureMap[0][4]; break;
		case stoneRes:	return textureMap[1][2]; break;

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

sf::Texture& Utilits::getUnitTexture(const unit_block& title)
{
	switch (title)
	{
		//Воин человек
		case vil0_a1:	return unitTexture[0][0];	break;
		case vil0_a2:	return unitTexture[0][1];	break;
		case vil0_a3:	return unitTexture[0][2];	break;
		case vil0_a4:	return unitTexture[0][3];	break;
		case vil0_a5:	return unitTexture[0][4];	break;
		case vil0_a6:	return unitTexture[0][5];	break;
		case vil0_a7:	return unitTexture[0][6];	break;
		case vil0_a8:	return unitTexture[0][7];	break;
		case vil0_a9:	return unitTexture[0][8];	break;
		case vil0_a10:	return unitTexture[0][9];	break;
		case vil0_a11:	return unitTexture[0][10];	break;
		case vil0_a12:	return unitTexture[0][11];	break;
		
		//Воин скелет
		case vil1_a1:	return unitTexture[1][0];	break;
		case vil1_a2:	return unitTexture[1][1];	break;
		case vil1_a3:	return unitTexture[1][2];	break;
		case vil1_a4:	return unitTexture[1][3];	break;
		case vil1_a5:	return unitTexture[1][4];	break;
		case vil1_a6:	return unitTexture[1][5];	break;
		case vil1_a7:	return unitTexture[1][6];	break;
		case vil1_a8:	return unitTexture[1][7];	break;
		case vil1_a9:	return unitTexture[1][8];	break;
		case vil1_a10:	return unitTexture[1][9];	break;
		case vil1_a11:	return unitTexture[1][10];	break;
		case vil1_a12:	return unitTexture[1][11];	break;
		
		//Воин гоблин
		case vil2_a1:	return unitTexture[2][0];	break;
		case vil2_a2:	return unitTexture[2][1];	break;
		case vil2_a3:	return unitTexture[2][2];	break;
		case vil2_a4:	return unitTexture[2][3];	break;
		case vil2_a5:	return unitTexture[2][4];	break;
		case vil2_a6:	return unitTexture[2][5];	break;
		case vil2_a7:	return unitTexture[2][6];	break;
		case vil2_a8:	return unitTexture[2][7];	break;
		case vil2_a9:	return unitTexture[2][8];	break;
		case vil2_a10:	return unitTexture[2][9];	break;
		case vil2_a11:	return unitTexture[2][10];	break;
		case vil2_a12:	return unitTexture[2][11];	break;
		
		//Воин обидка
		case vil3_a1:	return unitTexture[3][0];	break;
		case vil3_a2:	return unitTexture[3][1];	break;
		case vil3_a3:	return unitTexture[3][2];	break;
		case vil3_a4:	return unitTexture[3][3];	break;
		case vil3_a5:	return unitTexture[3][4];	break;
		case vil3_a6:	return unitTexture[3][5];	break;
		case vil3_a7:	return unitTexture[3][6];	break;
		case vil3_a8:	return unitTexture[3][7];	break;
		case vil3_a9:	return unitTexture[3][8];	break;
		case vil3_a10:	return unitTexture[3][9];	break;
		case vil3_a11:	return unitTexture[3][10];	break;
		case vil3_a12:	return unitTexture[3][11];	break;
		
		//Житель человек
		case vil0_b1:	return unitTexture[4][0];	break;
		case vil0_b2:	return unitTexture[4][1];	break;
		case vil0_b3:	return unitTexture[4][2];	break;
		case vil0_b4:	return unitTexture[4][3];	break;
		case vil0_b5:	return unitTexture[4][4];	break;
		case vil0_b6:	return unitTexture[4][5];	break;
		case vil0_b7:	return unitTexture[4][6];	break;
		case vil0_b8:	return unitTexture[4][7];	break;
		case vil0_b9:	return unitTexture[4][8];	break;
		case vil0_b10:	return unitTexture[4][9];	break;
		case vil0_b11:	return unitTexture[4][10];	break;
		case vil0_b12:	return unitTexture[4][11];	break;
		
		//Житель скелет
		case vil1_b1:	return unitTexture[5][0];	break;
		case vil1_b2:	return unitTexture[5][1];	break;
		case vil1_b3:	return unitTexture[5][2];	break;
		case vil1_b4:	return unitTexture[5][3];	break;
		case vil1_b5:	return unitTexture[5][4];	break;
		case vil1_b6:	return unitTexture[5][5];	break;
		case vil1_b7:	return unitTexture[5][6];	break;
		case vil1_b8:	return unitTexture[5][7];	break;
		case vil1_b9:	return unitTexture[5][8];	break;
		case vil1_b10:	return unitTexture[5][9];	break;
		case vil1_b11:	return unitTexture[5][10];	break;
		case vil1_b12:	return unitTexture[5][11];	break;
		 
		//Житель гоблин
		case vil2_b1:	return unitTexture[6][0];	break;
		case vil2_b2:	return unitTexture[6][1];	break;
		case vil2_b3:	return unitTexture[6][2];	break;
		case vil2_b4:	return unitTexture[6][3];	break;
		case vil2_b5:	return unitTexture[6][4];	break;
		case vil2_b6:	return unitTexture[6][5];	break;
		case vil2_b7:	return unitTexture[6][6];	break;
		case vil2_b8:	return unitTexture[6][7];	break;
		case vil2_b9:	return unitTexture[6][8];	break;
		case vil2_b10:	return unitTexture[6][9];	break;
		case vil2_b11:	return unitTexture[6][10];	break;
		case vil2_b12:	return unitTexture[6][11];	break;
			
		//Житель обидка
		case vil3_b1:	return unitTexture[7][0];	break;
		case vil3_b2:	return unitTexture[7][1];	break;
		case vil3_b3:	return unitTexture[7][2];	break;
		case vil3_b4:	return unitTexture[7][3];	break;
		case vil3_b5:	return unitTexture[7][4];	break;
		case vil3_b6:	return unitTexture[7][5];	break;
		case vil3_b7:	return unitTexture[7][6];	break;
		case vil3_b8:	return unitTexture[7][7];	break;
		case vil3_b9:	return unitTexture[7][8];	break;
		case vil3_b10:	return unitTexture[7][9];	break;
		case vil3_b11:	return unitTexture[7][10];	break;
		case vil3_b12:	return unitTexture[7][11];	break;
	}										  
}											  

bool Utilits::isFinily(){
	return finish;
}

int Utilits::getProgress(){
	return progress;
}

