/*
2014707073 ���ȯ
9���� ����Ʈ����� �ǽ� �� ����
*/

#include <stdio.h>
#include "automobile.h"
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/*
�Լ����� ���� ���� include
*/

struct automobile_moving automobile_moving;
struct automobile_coord automobile_coord;
struct obstacle obs;

/*
����ü ����
*/

void gotoxy(int x, int y);
void user_setting(struct automobile_moving *automobile_moving,struct obstacle *obs);
void draw_map();
void automobile_move(struct automobile_moving *automobile_moving, struct automobile_coord *automobile_coord, struct obstacle *obs);
void draw_obstacle(struct obstacle *obstacle);
void obs_sorting(struct obstacle *obs);

/*
�Լ� ����
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
