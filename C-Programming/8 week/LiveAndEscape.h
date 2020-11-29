/*
2014707073 김수환
소프트웨어설계 12주차 과제
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct __man {
	int trap_height;
	int p_height; 
	int hp; 
}MAN;

typedef struct __box {
	int time;
	int height;
	int hp;
}BOX;

void bubble_sort_box(BOX *boxs, int box_num);
void Escape(MAN *man, BOX *boxs,int box_num);
void USER_INPUT(BOX *boxs, int box_num);

/**/
void Escape(MAN *man,BOX *boxs,int box_num) {
	int i = 0;
	int CLEAR = 0;
	int OUT = 0;
	int time = 0;
	int total_height = 0;

	man[0].p_height = 0;
	man[0].hp = 10;

	for (i = 0; i < box_num; i++) {
		total_height += boxs[i].height;
	}

	i = 0;
	while (OUT == 0) {
		/* 상자들의 모든 높이를 합쳐도 함정 높이보다 낮을때는 최대한 버티기 위해 상자가 내려올 때마다 먹는다 */
		if (total_height < man[0].trap_height) {
			if (time == boxs[i].time) {
				man[0].hp += boxs[i].hp;
				time++;
				man[0].hp--;
				i++;
			}
			else {
				/* 별 의미 없는 시간이므로 시간은 ++ hp는 --만 해준다 */
				time++;
				man[0].hp--;
			}
			if (man[0].hp <= 0) {
				OUT = 



		}
		else {
			if (man[0].p_height >= man[0].trap_height) {
				CLEAR = 1;
				OUT = 1;
			}
			if (man[0].hp <= 0) {
				OUT = 1;
			}
			/* 상자가 떨어지는 시간일 때 */
			if (time == boxs[i].time) {
				/* 다음 타임까지 HP>0이라면 */
				if (man[0].hp > boxs[i + 1].time - boxs[i].time) {
					man[0].p_height += boxs[i].height;
				}
				/* 다음 타임까지 HP<=0 즉, 죽는다면 */
				else {
					/* 다음 타임까지 HP<0 이지만 지금 상자를 쌓아올려서 탈출 가능하다면 */
					if (man[0].p_height + boxs[i].height >= man[0].trap_height) {
						man[0].p_height += boxs[i].height;
					}
					/* 다음 타임까지 HP<0이고 지금 당장 탈출도 불가능하다면 */
					else {
						/* 상자 안의 물품을 먹는다 */
						man[0].hp += boxs[i].hp;
					}
				}
				i++;
				time++;
				man[0].hp--;
				if (man[0].p_height >= man[0].trap_height) {
					CLEAR = 1;
					OUT = 1;
				}
				if (man[0].hp <= 0) {
					OUT = 1;
				}
			}
			/* 상자가 떨어지지 않는 시간일 때 */
			else {
				/* 별 의미 없는 시간이므로 시간은 ++ hp는 --만 해준다 */
				time++;
				man[0].hp--;
				if (man[0].hp <= 0) {
					OUT = 1;
				}
			}
		}
	}
	
	if (CLEAR) {
		printf("탈출에 성공하였습니다!!!\n");
		printf("탈출시간은 %d입니다!!\n",time-1);
	}
	else {
		printf("탈출에 실패하였습니다!!!\n");
		printf("사망하는데 걸린시간은 %d입니다!!\n", time);
		printf("도달한 높이는 %d입니다!!!",man[0].p_height);
	}

	return;
}

/* BOX 구조체 동적할당만큼 입력 */
void USER_INPUT(BOX *boxs,int box_num) {
	int i = 0;
	for (i = 0; i < box_num; i++) {
		printf("****Box%d****\n", i + 1);
		printf("time      : ");
		scanf_s("%d", &boxs[i].time);
		printf("height    : ");
		scanf_s("%d", &boxs[i].height);
		printf("hp        : ");
		scanf_s("%d", &boxs[i].hp);
	}
}

void bubble_sort_box(BOX *boxs, int box_num) {
	int i = 0, j = 0;
	int time_buffer = 0, hp_buffer = 0, height_buffer = 0;

	/* 시간 순서대로 오름차순 정렬 */
	for (i = 0; i < box_num - 1; i++) {
		for (j = 0; j < box_num - 1; j++) {
			if (boxs[j].time > boxs[j + 1].time) {
				time_buffer = boxs[j].time;
				hp_buffer = boxs[j].hp;
				height_buffer = boxs[j].height;

				boxs[j].time = boxs[j + 1].time;
				boxs[j].hp = boxs[j + 1].hp;
				boxs[j].height = boxs[j + 1].height;

				boxs[j + 1].time = time_buffer;
				boxs[j + 1].hp = hp_buffer;
				boxs[j + 1].height = height_buffer;
			}
		}
	}

	return;
}