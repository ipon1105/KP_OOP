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
	busyState,	//������
	freeState	//�� ������
};