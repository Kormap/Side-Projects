/*
2014707073 ���ȯ
����Ʈ����� 12���� ����
*/

#include <stdio.h>
#include <stdlib.h>
#include "LiveAndEscape.h"

void main() {
	int box_num = 0;
	int i = 0;

	MAN *man= (MAN*)malloc(sizeof(MAN)*1);

	printf("������ ���� �Է� : ");
	scanf_s("%d", &(man->trap_height));

	printf("���� ������ ���� ������ ���� : ");
	scanf_s("%d", &box_num);

	/* BOX ����ü �����Ҵ� */
	BOX *boxs = (BOX*)malloc(sizeof(BOX)*box_num);

	for (i = 0; i < box_num; i++) {
		boxs[i].height = 0;
		boxs[i].hp = 0;
		boxs[i].time = 0;
	}
	USER_INPUT(boxs,box_num);
	bubble_sort_box(boxs,box_num);
	Escape(man, boxs, box_num);

	/* BOX ����ü �����Ҵ� ���� */
	free(man);
	free(boxs);

	return;
}
