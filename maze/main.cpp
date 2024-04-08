// #include <stdio.h>
// #include <stdlib.h>
#include <iostream>
#define MAX 128
#define ROW 8
#define COL 25

// typedef struct location
struct location
{
    int row; //행 번호 (위, 아래)
    int col; //열 번호 (좌, 우)
};

void main()
{
    /*미로 맵 구성*/
    char maze[][COL]=
    {
        "□□■□□□□□",
		"□■■□■■■■",
		"□■□□■□□□",
		"□■□■■□■■",
		"□□□□□□□□",
		"■■■□□■■■",
		"■■□□□■□□",
		"□□□■□□□□",
    }; //이게 맞나
}
