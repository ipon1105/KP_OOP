#pragma once

enum state {
	//��������� ������

	idle = 0,	//������ �� ������
	attack,		//�������
	run,		//����
	extract,	//��������
	findRes,	//������ �������
	findEnemy,	//������ ������
	runOut,		//������ �� �����

	//��������� ������
	impassable,	//������������
	passable	//����������
};