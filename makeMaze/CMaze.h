#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

/* ��ǥ ���� */
struct location {
	int row;  // ����
	int col;  // �¿�
	location* pre;  // ���� �� ��ġ
};

/* �˻� ������ */
struct findPoint {
	location* loc;	// �˻��� ���� ��ġ (��ǥ)
	findPoint* next;	// ���� �˻��� ���� ��ġ (��ǥ)
};

class CMaze
{
	/* �ʿ��� ��� */
	char* m_pMaze = nullptr; //�̷� ��
	int m_nSize = 0; //�̷� ũ��
	/* �ʿ��� ��� �Լ� */
	void initializeMaze(char* maze, char c);
	bool buildRoad(location** a);
	bool isValidRoad(int x, int y);

	location* createLocation(int row, int col, location* a);
	findPoint* createFind(location* a);
	void removeFind(findPoint** head);
	void bufferPrint(char* maze);
	void mazePrint(int x, int y, char c);
	void gotoxy(int x, int y);
public:
	CMaze(int size);
	~CMaze();

	bool makeMaze(); //�̷� ����
};
