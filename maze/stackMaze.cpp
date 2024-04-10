// #include <stdio.h>
// #include <stdlib.h>
#include <iostream>
#define MAX 128
#define ROW 8
#define COL 8

// typedef struct location
struct location
{
    int row; //행 번호 (위, 아래)
    int col; //열 번호 (좌, 우)
};

int mazeRunner(char maze[][COL]);
location* new_location(int* w);
location* push(location* way[],int* w,int row,int col);
void pop(location* way[],int* w);
int dirCheck(char maze[][COL],location* a);
// void finalStep(char maze[][COL],location* a);
void printMaze(char maze[][COL]);

int main()
{
    /*미로 맵 구성*/
    char maze[][COL]=
    {
        0,0,1,0,0,0,0,0,
		0,1,1,0,1,1,1,1,
		0,1,0,0,1,0,0,0,
		0,1,0,1,1,0,1,1,
		0,0,0,0,0,0,0,0,
		1,1,1,0,0,1,1,1,
		1,1,0,0,0,1,0,0,
		0,0,0,1,0,0,0,0,
    }; 
    if(mazeRunner(maze)==0){
        puts("길이 없습니다...");
        return 0;
    }

    printMaze(maze);
    std::cout<<"\n출구를 찾았습니다.\n";
    return 0;
}
/* 미로 찾기 
 * parameter : 미로 배열 
 * return : 정상종료 == 1, 비정상종료 == 0 */
int mazeRunner(char maze[][COL])
{
    /* 지나간 길 저장할 스택(배열)과 저장갯수 */
    static location* way[MAX] = {NULL};
    static int numWay = 0;

    /* 북쪽부터 시계방향으로 돌림 - 최대한 빨리 못찾게 하기 위함 */
    /* 현재 위치 저장 변수 */    
    location* a;
    a = push(way, &numWay, 0, 0); //출발지 생성
    int d = 0; //방향확인 후 return 받을 변수

    while(true){
        /* 메모리 할당에 실패했을 경우 */
        if(a==NULL){
            puts("미로가 이상합니다.");
            return 0;
        }

        /* 출구에 도달하면 정상 종료 */
        else if(a->row == 7 && a->col == 7){
            maze[a->row][a->col]=2; //출구 표시
            return 1;
        }

        /* 동서남북에 길이 있는지 검사 */
        else if((d = dirCheck(maze,a))<4){
            int row = a->row, col = a->col;
            maze[row][col]=3; //지나간 자리 표시
            if(d==0) row--;      //북
            else if(d==1) col++; //동
            else if(d==2) row++; //남
            else if(d==3) col--; //서
            if((a = push(way, &numWay,row,col))==NULL) //신규 좌표 생성
                return 0;
        }

        /* 갈 길이 더 이상 없을 경우 */
        else{
            maze[a->row][a->col]=4; //돌아간 자리 표시
            pop(way,&numWay);
            a = way[numWay-1];
            //numWay는 항상 새로 쓸 위치. 마지막 위치는 numWay-1
        }
        printMaze(maze);
    }
    return 1;
}
/* 스택(배열)에 추가
 * parameter : 위치저장 스택, 저장갯수 포인터, 신규 저장할 row, col
 * return : 정상 == 신규 생성된 주소, 비정상 == NULL */
location* push(location* way[],int* w,int row,int col)
{
    if((way[*w]=new_location(w))==NULL) return NULL;
    way[*w]->row = row;
    way[(*w)++]->col = col;

    return way[(*w)-1];
}
/* 스택(배열)에서 하나 제거
 * parameter : 위치저장 스택, 저장갯수 포인터
 * return : void */
void pop(location* way[],int* w)
{
    /* 신규 시작점까지 없어진 상황이라면 */
    if(*w == 0){
        puts("길이 이상합니다.");
        exit(1);
    }
    /* w는 항상 새로 쓸 위치에 자리하고 있기 때문에 마지막 값은 w-1 */
    free(way[*w-1]);
    way[(*w)-- -1] = NULL;
}
/* 위치 저장 공간 생성
 * parameter : void *
 * return : 정상 == 신규 공간 주소, 비정상 == NULL */
location* new_location(int* w)
{
    /* max에 도달한 경우 NULL값 반환 */
    if(*w == MAX){
        puts("길을 찾지 못했습니다.");
        return NULL;
    }
    location* temp;
    if((temp=(location*)malloc(sizeof(location)))==NULL){
        puts("메모리가 부족합니다.");
        exit(1);
    }
    /* 초기화 */
    temp->row = 0;
    temp->col = 0;

    return temp;
}
/* 동서남북에 길이 있는지 확인
 * parameter : 미로 배열, 확인할 위치값(a)
 * return : 북(0), 동(1), 남(2), 서(3) */
int dirCheck(char maze[][COL],location* a)
{
    /* [북쪽확인] 위에 행이 있고 갈 수 있는 길일 때 */
    if( a->row > 0 && maze[a->row-1][a->col] == 0 ) return 0;
    /* [동쪽확인] 오른쪽에 열이 있고 갈 수 있는 길일 때 */
    else if( a->col+1 < COL && maze[a->row][a->col+1] == 0 ) return 1;
    /* [남쪽확인] 아래쪽에 행이 있고 갈 수 있는 길일 때 */
    else if( a->row+1 < ROW && maze[a->row+1][a->col] == 0 ) return 2;
    /* [서쪽확인] 왼쪽에 행이 있고 갈 수 있는 길일 때 */
    else if( a->col > 0 && maze[a->row][a->col-1] == 0 ) return 3;
    /* 그 외 */
    else return 4;
}
/* 출구 자리 표시 넣어주기
 * parameter : 미로배열, 현재 위치 좌표
 * return : void */
// void finalStep(char maze[][COL],location* a)
// {

// }
/* 미로 출력 */
void printMaze(char maze[][COL])
{
    using namespace std;
    // system("cls");
    cout<<"\n\n";
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            switch(maze[i][j]){
                case 0: //길
                    cout<<"\u2B1A ";
                    break;
                case 1: //벽
                    cout<<"\u2B1B";
                    break;
                case 2: //출구
                    cout<<" \u2B0A";
                    break;
                case 3: //지나간 길
                    cout<<"\u2B1C";
                    break;
                case 4: //돌아간 길
                    cout<<"\u2B6F ";
                    break;
                default:
                    break;
            }
        }
        cout<<endl;
    }
    //하얀 네모 \u2B1C, 검정 네모 \u2B1B, 점선 네모 \u2B1A
}
