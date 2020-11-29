/*
2014707073 ���ȯ
����Ʈ����� 12���� ����
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
		/* ���ڵ��� ��� ���̸� ���ĵ� ���� ���̺��� �������� �ִ��� ��Ƽ�� ���� ���ڰ� ������ ������ �Դ´� */
		if (total_height < man[0].trap_height) {
			if (time == boxs[i].time) {
				man[0].hp += boxs[i].hp;
				time++;
				man[0].hp--;
				i++;
			}
			else {
				/* �� �ǹ� ���� �ð��̹Ƿ� �ð��� ++ hp�� --�� ���ش� */
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
			/* ���ڰ� �������� �ð��� �� */
			if (time == boxs[i].time) {
				/* ���� Ÿ�ӱ��� HP>0�̶�� */
				if (man[0].hp > boxs[i + 1].time - boxs[i].time) {
					man[0].p_height += boxs[i].height;
				}
				/* ���� Ÿ�ӱ��� HP<=0 ��, �״´ٸ� */
				else {
					/* ���� Ÿ�ӱ��� HP<0 ������ ���� ���ڸ� �׾ƿ÷��� Ż�� �����ϴٸ� */
					if (man[0].p_height + boxs[i].height >= man[0].trap_height) {
						man[0].p_height += boxs[i].height;
					}
					/* ���� Ÿ�ӱ��� HP<0�̰� ���� ���� Ż�⵵ �Ұ����ϴٸ� */
					else {
						/* ���� ���� ��ǰ�� �Դ´� */
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
			/* ���ڰ� �������� �ʴ� �ð��� �� */
			else {
				/* �� �ǹ� ���� �ð��̹Ƿ� �ð��� ++ hp�� --�� ���ش� */
				time++;
				man[0].hp--;
				if (man[0].hp <= 0) {
					OUT = 1;
				}
			}
		}
	}
	
	if (CLEAR) {
		printf("Ż�⿡ �����Ͽ����ϴ�!!!\n");
		printf("Ż��ð��� %d�Դϴ�!!\n",time-1);
	}
	else {
		printf("Ż�⿡ �����Ͽ����ϴ�!!!\n");
		printf("����ϴµ� �ɸ��ð��� %d�Դϴ�!!\n", time);
		printf("������ ���̴� %d�Դϴ�!!!",man[0].p_height);
	}

	return;
}

/* BOX ����ü �����Ҵ縸ŭ �Է� */
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

	/* �ð� ������� �������� ���� */
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