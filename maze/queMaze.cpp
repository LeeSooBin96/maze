/* 큐 구조_미로 찾기 참고: https://codevang.tistory.com/52 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SIZE 15
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 40

typedef struct l location;
typedef struct f find;

/* 좌표 저장 */
struct l {
	int row;  // 상하
	int col;  // 좌우
	location* pre;  // 이전 길 위치
};

/* 검색 기준점 */
struct f {
	location* loc;	// 검색할 기준 위치 (좌표)
	find* next;	// 다음 검색할 기준 위치 (좌표)
};
int make_maze(char maze[][SIZE], char* read_file);
void maze_print(int j, int i, char c);
int maze_runner(char maze[][SIZE]);
location* create_location(int row, int col, location* a);
find* create_find(location* a);
void remove_find(find** head);
int dir_checker(char maze[][SIZE], int row, int col);
int all_around_checker(char maze[][SIZE], location* a, find** tail);
void final_step(char maze[][SIZE], find* tail);
void gotoxy(int x, int y);
void buffer_print(char maze[][SIZE]);
void CursorView(char hide);

int main()
{
	/* 콘솔 창 크기 조절 및 커서 숨기기 */
	char console_size[30];
	sprintf(console_size, "mode con cols=%d lines=%d",
		CONSOLE_WIDTH, CONSOLE_HEIGHT);
	system(console_size);
	CursorView(0);

	/*미로 그림 만들기(파일에서 가져오기) */
	char maze[SIZE][SIZE] = { 0 };
	make_maze(maze, "maze.txt");
	maze_runner(maze); //길 찾기
}
/* 미로 찾기 
 * parameter : 미로 배열 
 * return : 정상종료 == 1, 비정상종료 == 0 
 * 이제 이 함수를 채워야 한다 */
int maze_runner(char maze[][SIZE])
{
    /* 현재 위치 저장 변수 */    
    location* a;
    a = create_location(0, 0, a); //출발지 생성
    //검색 기준점 생성
    find* f;
    f = create_find(a);
    
    //차근차근 작성해보자
    printf("%d\n",all_around_checker(maze,a,&f->next));
    // a=f->next->loc;
    // printf("%d  %d\n",a->row,a->col);
    // a=f->next->next->loc;
    // printf("%d  %d\n",a->row,a->col);
    
    // remove_find(&f);
    // printf("%d\n",all_around_checker(maze,a,&f));

    // printf("%d\n",all_around_checker(maze,a,&f));

    // while(true){

    // }
}
/* 길인지 확인
 * parameter : 미로 배열, 확인할 위치값 row, col
 * return : 길이면 0 아니면 1 
 * 이 함수도 채워야 한다 */
int dir_checker(char maze[][SIZE], int row, int col)
{
    if(maze[row][col]==48) return 0; //길이면
    return 1;
}
/* 미로 만들기(파일에서 가져오기) */ 
/* parameter : 미로배열, 파일 이름 */
/* return : 정상 == 1, 비정상 == 0 */
int make_maze(char maze[][SIZE], char* read_file)
{
	FILE* read = NULL;
	// errno_t err;
	// err = 
    read = fopen(read_file, "r");
	if (read == NULL)
		return 0;

	/* 파일에서 읽어서 tab 없애서 배열에 넣어줌 */
	char c;
	int i = 0;
	int j = 0;
	while ((c = fgetc(read)) != EOF)
	{
		if (c != '\t' && c != '\n' && j < SIZE)
			maze[i][j++] = c;
		else if (c == '\n' && i < SIZE)
		{
			i++;
			j = 0;
		}
	}
	fclose(read);
	return 1;
}
/* 신규 location 1개 생성 */
/* parameter : row, col 좌표값, 현재 좌표 */
/* return : 신규 생성된 구조체 주소 */
location* create_location(int row, int col, location* a)
{
	location* temp = (location*)malloc(sizeof(location));
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
find* create_find(location* a)
{
	find* temp = (find*)malloc(sizeof(find));
	if (temp == NULL)
		return NULL;
	temp->loc = a;
	temp->next = NULL;
	return temp;
}
/* find 연결리스트의 가장 앞의 값(head) 삭제 */
/* parameter : find 시작 값 head의 주소 */
/* return : void */
void remove_find(find** head)
{
	find* temp = (*head)->next;
	free(*head);
	*head = temp;
}
/* argument로 제공된 현재 좌표의 동서남북 길 확인 후 좌표 생성 */
/* parameter : 현재좌표, find의 마지막 값(tail)의 주소 */
/* return : 새로운 길의 좌표를 생성한 갯수, 종료지점 도달 시 == -1*/
int all_around_checker(char maze[][SIZE], location* a, find** tail)
{
	/* 현재 좌표 기준 동서남북 좌표 생성 */
	int dir[4][2] = { {a->row, a->col + 1}, {a->row, a->col - 1},
		{a->row + 1, a->col}, {a->row - 1, a->col} };
	int count = 0; // 길이 있어서 실제 좌표를 생성한 횟수

	/* 현재 좌표 기준 동서남북 길 확인 */
	for (int i = 0; i < 4; ++i)
	{
		location* temp_location;
		find* temp_find;

		/* 해당 방향이 미로의 마지막 지점이라면 체크하지 않음 */
		if (i == 0 && a->col == SIZE - 1)
			continue;
		else if (i == 1 && a->col == 0)
			continue;
		else if (i == 2 && a->row == SIZE - 1)
			continue;
		else if (i == 3 && a->row == 0)
			continue;

		/* 해당 방향이 길이라면 */
		if (dir_checker(maze, dir[i][0], dir[i][1]) == 0)
		{
			temp_location = create_location(dir[i][0], dir[i][1], a);
			// 신규 좌표점 생성
			temp_find = create_find(temp_location);  // find 포인터 생성
			(*tail)->next = temp_find;  // 기존 연결리스트에 붙여줌
			*tail = temp_find;  // tail값도 바꿔줌
			count++;  // 생성된 좌표 카운트

			/* 지나간 길 표시 (출구일경우 다르게) */
			if (dir[i][0] == SIZE - 1 && dir[i][1] == SIZE - 1)
			{
				maze[dir[i][0]][dir[i][1]] = 52;
				return -1;
			}
			maze[dir[i][0]][dir[i][1]] = 50;
		}
	}
	return count;
}
/* 출구를 찾으면 최단거리 길을 표시해줌 */
/* parameter : 미로배열, tail */
/* return : void */
void final_step(char maze[][SIZE], find* tail)
{
	location* p;
	p = tail->loc;
	// 마지막 출구는 ↘로 남아있도록 제일 마지막 전점부터 시작함
	// 출발지도 그대로 남아있도록 제일 처음 이후점에서 끝냄
	while (p->pre->pre != NULL)
	{
		p = p->pre;
		maze[p->row][p->col] = 53;
		buffer_print(maze);
		Sleep(100);
	}
}
/* 콘솔 출력 좌표 설정 */
/* parameter : x축, y축 */
/* return : void */
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/* 커서 숨기기 */
/* parameter : 숨기기 : 0, 보이기 : 1*/
/* return : void */
void CursorView(char hide)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = hide;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
/* 버퍼로 받아서 출력 */
/* parameter : 미로배열 */
/* return : void */
void buffer_print(char maze[][SIZE])
{
	static char front_buffer[SIZE][SIZE] = { ' ' };

	/* 현재 미로와 front_buffer(이전 미로)에 있는 미로 비교 */
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0, j2 = 0; j < SIZE; ++j)
		{
			if (front_buffer[i][j] != maze[i][j])
			{
				maze_print(j2, i, maze[i][j]);
				// 바뀐 부분 화면에 출력
				front_buffer[i][j] = maze[i][j];
				// 바뀐 부분은 출력 후 front_buffer에 저장
			}
			j2 += 2;
		}
}
/* 한글자 출력 */
/* prarameter : 좌표 값, 바꿀 문자 */
/* return : void */
void maze_print(int j, int i, char c)
{
	gotoxy(10 + j, 5 + i);	// 가운데 출력을 위해 상수를 더해줌
	switch (c)
	{
	case 48: //길
		// printf("\u2B1A ");
        printf("0");
		break;
	case 49: //벽
		// printf("\u2B1B");
        printf("1");
		break;
	case 50: //지나간길
		// printf("\u2B1C");
        printf("2");
		break;
	case 51: //출발점
		// printf("\u25A9");
        printf("3");
		break;
	case 52: //도착점
		// printf(" \u2B0A");
        printf("4");
		break;
	case 53: //최적 경로
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		// printf("\u2B50");
        printf("5");
		break;
	}
	gotoxy(10 + SIZE, 5 + SIZE); // 출력 후 커서 대기 위치
}