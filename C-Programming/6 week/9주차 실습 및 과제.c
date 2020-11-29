/*
2014707073 김수환
9주차 소프트웨어설계 실습 및 과제
*/

#include <stdio.h>
#include "automobile.h"
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/*
함수들을 쓰기 위한 include
*/

struct automobile_moving automobile_moving;
struct automobile_coord automobile_coord;
struct obstacle obs;

/*
구조체 선언
*/

void gotoxy(int x, int y);
void user_setting(struct automobile_moving *automobile_moving,struct obstacle *obs);
void draw_map();
void automobile_move(struct automobile_moving *automobile_moving, struct automobile_coord *automobile_coord, struct obstacle *obs);
void draw_obstacle(struct obstacle *obstacle);
void obs_sorting(struct obstacle *obs);

/*
함수 선언
*/

void main() {
	srand((unsigned)time(NULL));
	user_setting(&automobile_moving,&obs);
	system("cls");
	draw_map();
	draw_obstacle(&obs);
	obs_sorting(&obs);
	automobile_move(&automobile_moving,&automobile_coord,&obs);
	
	return;
}
