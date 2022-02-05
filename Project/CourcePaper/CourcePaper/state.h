#pragma once

enum state {
	//Состояние юнитов

	idle = 0,	//Ничего не делать
	attack,		//Драться
	run,		//Идти
	extract,	//Добывать
	findRes,	//Искать ресурсы
	findEnemy,	//Искать врагов
	runOut,		//Бежать от врага

	//Состояние плиток
	busyState,	//Занята
	freeState	//Не занята
};