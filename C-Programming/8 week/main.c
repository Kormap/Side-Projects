/*
2014707073 김수환
소프트웨어설계 12주차 과제
*/

#include <stdio.h>
#include <stdlib.h>
#include "LiveAndEscape.h"

void main() {
	int box_num = 0;
	int i = 0;

	MAN *man= (MAN*)malloc(sizeof(MAN)*1);

	printf("함정의 높이 입력 : ");
	scanf_s("%d", &(man->trap_height));

	printf("함정 속으로 넣을 상자의 개수 : ");
	scanf_s("%d", &box_num);

	/* BOX 구조체 동적할당 */
	BOX *boxs = (BOX*)malloc(sizeof(BOX)*box_num);

	for (i = 0; i < box_num; i++) {
		boxs[i].height = 0;
		boxs[i].hp = 0;
		boxs[i].time = 0;
	}
	USER_INPUT(boxs,box_num);
	bubble_sort_box(boxs,box_num);
	Escape(man, boxs, box_num);

	/* BOX 구조체 동적할당 해제 */
	free(man);
	free(boxs);

	return;
}
