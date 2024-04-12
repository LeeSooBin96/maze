/* 미로를 만들어보자 
 * 만들고 출구 찾는 것 까지 고고 */
#include "CMaze.h"

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

int main(void)
{   
    int nSize = 0; //미로 크기
    cout<<"미로의 크기를 입력하세요(1~50) :";
    cin>>nSize;
    while(cin.fail()||nSize<1||nSize>50){ 
        cin.clear();
        while(cin.get()!='\n');
        cout<<"다시 입력해주세요 :";
        cin>>nSize;
    }

    /* 콘솔 창 크기 조절 및 커서 숨기기 */
    char console_size[30];
    sprintf_s(console_size, 30, "mode con cols=%d lines=%d",
        nSize+80, nSize+50);
    system(console_size);
    CursorView(0);

    CMaze maze(nSize); //미로 맵 객체 생성
    maze.makeMaze(); //맵 생성

    return 0;
}   

