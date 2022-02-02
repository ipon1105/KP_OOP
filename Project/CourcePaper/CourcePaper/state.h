#pragma once

enum state {
	idle = 0,	//Ничего не делать
	attack,		//Драться
	run,		//Идти
	extract,	//Добывать
	findRes,	//Искать ресурсы
	findEnemy,	//Искать врагов
	runOut		//Бежать от врага
};