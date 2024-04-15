#include "CMaze.h"

/* 생성자 */
/* parameter : 미로 크기 */
CMaze::CMaze(int size)
{
	m_nSize = size;
	m_pMaze = new char[m_nSize*m_nSize]; //맵 생성
	//맵 초기화
	initializeMaze(m_pMaze,1); //1로 초기화
	m_pMaze[0] = 3; m_pMaze[(m_nSize - 1) * (m_nSize + 1)] = 4;//출발점, 도착점 설정
}
/* 파괴자 */
CMaze::~CMaze()
{
	delete[] m_pMaze;
}
/* 미로 맵 초기화 */
/* parameter : 맵 포인터, 초기화 값 */
/* return : void */
void CMaze::initializeMaze(char* maze,char c)
{
	for (int j = 0; j < m_nSize; ++j) {
		for (int i = 0; i < m_nSize; ++i) {
			maze[j * m_nSize + i] = c;
		}
	}
}
/* 미로 맵 생성 */
/* parameter : void */
/* return : 맵 생성 여부 */
bool CMaze::makeMaze()
{
	/* 시작점 */
	location* start = { NULL };
	start = createLocation(0, 0, NULL); //시작점 생성
	if (start == NULL) {
		cout << "시작점 생성 실패! \n";
		exit(1);
	}
	srand(time(NULL));
	
	for (int i = 0; i < 100; ++i)
	{
		if (!buildRoad(&start)&&start->pre!=NULL) { //길 만들기
			//실패하면 특정시점마다 이전 지점으로 돌림ㅊㅊ
			if(i%3==0)
				start = start->pre;
		}
		bufferPrint(m_pMaze); //맵 출력
		cin.get();
	}
	return false;
}
/* 길 만들기 */
/* parameter : 탐색 지점 */
/* return : 길만들기 성공 여부 bool */
bool CMaze::buildRoad(location** a)
{
	int nRow = (*a)->row;
	int nCol = (*a)->col;
	int nDir = rand() % 4; //방향 랜덤 지정
	switch (nDir)
	{
	case 0: //북
		if (isValidRoad(nRow-1,nCol)) { //맵의 끝이 아니고 진입점이 벽일때
			m_pMaze[nCol * m_nSize + nRow - 1] = 0;
			*a = createLocation(nRow - 1, nCol, *a);
			return true;
		}
		break;
	case 1: //동
		if (isValidRoad(nRow, nCol+1)) { //맵의 끝이 아니고 진입점이 벽일때
			m_pMaze[(nCol + 1) * m_nSize + nRow] = 0;
			*a = createLocation(nRow, nCol+1, *a);
			return true;
		}
		break;
	case 2: //남
		if (isValidRoad(nRow + 1, nCol)) { //맵의 끝이 아니고 진입점이 벽일때
			m_pMaze[nCol * m_nSize + nRow + 1] = 0;
			*a = createLocation(nRow+1, nCol, *a);
			return true;
		}
		break;
	case 3: //서
		if (isValidRoad(nRow, nCol-1)) { //맵의 끝이 아니고 진입점이 벽일때
			m_pMaze[(nCol - 1) * m_nSize + nRow] = 0;
			*a = createLocation(nRow, nCol-1, *a);
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
/* 뚫을 수 있는 길인지 확인 */
/* parameter : 뚫고자 하는 좌표값 */
/* return : 뚫을 수 있는지 여부 */
bool CMaze::isValidRoad(int x, int y)
{
	unsigned short ckNum = 0; //벽의 개수 저장
	if (x < 0 || x >= m_nSize || y < 0 || y >= m_nSize) return false; //뚫을 지점이 맵 밖이면
	if (m_pMaze[y * m_nSize + x] == 1) ckNum++; //뚫을 지점이 벽이면
	if (x >= 1 && m_pMaze[y * m_nSize + x - 1] == 1) ckNum++;//북
	if (y < m_nSize && m_pMaze[(y + 1) * m_nSize + x] == 1) ckNum++;//동
	if (x < m_nSize && m_pMaze[y * m_nSize + x + 1] == 1) ckNum++;//남
	if (y >= 1 && m_pMaze[(y - 1) * m_nSize + x] == 1) ckNum++;//서
	
	if (ckNum > 2) return true;
	else return false;
}
/* 신규 location 1개 생성 */
/* parameter : row, col 좌표값, 현재 좌표 */
/* return : 신규 생성된 구조체 주소 */
location* CMaze::createLocation(int row, int col, location* a)
{
	location* temp = new location;
	if (temp == NULL)
		return NULL;
	temp->row = row;
	temp->col = col;
	temp->pre = a;
	return temp;
}
/* 신규 find 1개 생성 */
/* parameter : location* a */
/* return : 신규 생성된 구조체 주소 */
findPoint* CMaze::createFind(location* a)
{
	findPoint* temp = new findPoint;
	if (temp == NULL)
		return NULL;
	temp->loc = a;
	temp->next = NULL;
	return temp;
}
/* find 연결리스트의 가장 앞의 값(head) 삭제 */
/* parameter : find 시작 값 head의 주소 */
/* return : void */
void CMaze::removeFind(findPoint** head)
{
	findPoint* temp = (*head)->next;
	delete (*head);
	*head = temp;
}
/* 버퍼로 받아서 출력 */
/* parameter : 맵 포인터 */
/* retrun : void */
void CMaze::bufferPrint(char* maze)
{
	static char* pFrontBuffer = new char[m_nSize * m_nSize];
	initializeMaze(pFrontBuffer, ' ');

	/* 현재 미로와 front_buffer(이전 미로)에 있는 미로 비교 */
	for (int i = 0; i < m_nSize; ++i)
		for (int j = 0, j2 = 0; j < m_nSize; ++j)
		{
			if (pFrontBuffer[j*m_nSize+i] != maze[j * m_nSize + i])
			{
				mazePrint(i, j2, maze[j*m_nSize+i]);
				// 바뀐 부분 화면에 출력
				pFrontBuffer[j * m_nSize + i] = maze[j * m_nSize + i];
				// 바뀐 부분은 출력 후 front_buffer에 저장
			}
			j2 += 2; 
		}
}
/* 한글자 출력 */
/* prarameter : 좌표 값 x와 y, 바꿀 문자 */
/* return : void */
void CMaze::mazePrint(int x, int y, char c)
{
	gotoxy(10 + y, 5 + x);	// 가운데 출력을 위해 상수를 더해줌
	switch (c)
	{
	case 0: //길
		cout << "□";
		//printf("□");
		break;
	case 1: //벽
		cout << "■";
		//printf("■");
		break;
	case 2: //지나간길
		cout << "▣";
		//printf("▣");
		break;
	case 3: //출발점
		cout << "▩";
		//printf("▩");
		break;
	case 4: //도착점
		cout << "↘";
		//printf("↘");
		break;
	case 5: //최적 경로
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "★";
		//printf("★");
		break;
	}
	gotoxy(10 + m_nSize, 5 + m_nSize); // 출력 후 커서 대기 위치
}
/* 콘솔 출력 좌표 설정 */
/* parameter : x축, y축 */
/* return : void */
void CMaze::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}