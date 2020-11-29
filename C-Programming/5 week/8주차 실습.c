/*
2014707073 김수환
8주차 실습1
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
/*
밑에 함수들을 쓰기위한 include와 밑에 함수들 선언
*/
void gotoxy(int x, int y);
void draw_map();
void run_game();

void main() {
	draw_map(); // race를 할 map을 그려준다.
	run_game(); // 
	return;
}

void draw_map() {
	int i = 1;

	printf("======RUN GAME======\n");
	for (i = 1; i < 30; i += 2) {
		gotoxy(i, 1); printf("■");
		gotoxy(i, 5); printf("□");
		gotoxy(i, 9); printf("■");
	}
/*
Gotoxy를 이용해서 맵을 그려준다.
y좌표 1 5 9에 맵을 그리므로,
그 가운데인 3 7이 run을 하는 좌표가 된다.
*/
}

void run_game() {
	int i = 1, j = 1;
	char key;

	while (1) {
		_kbhit(); // 제가 쓰는 visual studio 2015 에서는 _kbhit라 이렇게 씀
		key = _getch();
		if (key=='a') {
			gotoxy(i, 3); // i를 if문에서 1씩 증가시켜줌으로써 움직여줌
			Sleep(200); // 움직임을 조금씩 끊어주기 위해 Sleep을 씀
			printf("★");
                         gotoxy(i-1,3); // 그전에 있던
                         printf(“ ”); // ★을 지워줌
			i++;
		}
		else if (key == 'd') {
			gotoxy(j, 7);
			Sleep(200);
			printf("☆");
gotoxy(j-1,3);
                         printf(“ ”);
			j++;
		}
			
/*
I나 j가 30에 다다르면, 게임이 끝난 것이므로 
if문으로 i와 j가 30이 될 경우를 나눠줘서
먼저 system(“cls”)로 기존의 화면을 지워주고, 누가 이겼는지를 표시해준다.
그리고 system(“pause”);로 진행 후 return;한다
*/
		if (i == 30) {
			system("cls"); 
			printf("★ WINNER!!\n");
			system("pause");
			return;
		}
		else if (j == 30) {
			system("cls");
			printf("☆ WINNER!!\n");
			system("pause");
			return;
		}
	}
}

void gotoxy(int x, int y) { // gotoxy의 정의
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
