#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

/* 좌표 저장 */
struct location {
	int row;  // 상하
	int col;  // 좌우
	location* pre;  // 이전 길 위치
};

/* 검색 기준점 */
struct findPoint {
	location* loc;	// 검색할 기준 위치 (좌표)
	findPoint* next;	// 다음 검색할 기준 위치 (좌표)
};

class CMaze
{
	/* 필요한 멤버 */
	char* m_pMaze = nullptr; //미로 맵
	int m_nSize = 0; //미로 크기
	/* 필요한 멤버 함수 */
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

	bool makeMaze(); //미로 생성
};
