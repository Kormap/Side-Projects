/*
2014707073 김수환
소프트웨어설계 7주차 과제2
*/

#include <stdio.h>

int selection_sort();

void main() {
	int arr[10] = { 4,1,2,7,5,3,8,9,10,0 };
	int flag = 0;
	int i = 0;
	int num_of_operate = 0;

	printf("======BEFORE======\n");
	for (i = 0; i<10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	printf("1. 오름차순 0. 내림차순: ");
	scanf_s("%d", &flag);

	num_of_operate = selection_sort(&arr, &flag);

	printf("\n");
	printf("Number of operate: %d\n", num_of_operate);
	printf("======AFTER======\n");
	for (i = 0; i<10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return;
}

int selection_sort(int *arr, int *flag) {
	int i = 0, j = 0;
	int min = 0, max = 0, buffer = 0;
	int coordinate = 0;
	int count = 0;
	int num_operate = 0;

	if (*flag) {     // 오름차순
		for (i = 0; i<9; i++) {
			count = 0;
			min = arr[i];
			for (j = i; j<9; j++) {
				num_operate++;
				if (min>arr[j + 1]) {
					min = arr[j + 1];
					coordinate = j + 1;
					count++;
				}
			}
			if (count) {
				buffer = arr[i];
				arr[i] = min;
				arr[coordinate] = buffer;
			}
		}
	}

	else {
		for (i = 0; i<9; i++) {
			count = 0;
			max = arr[i];
			for (j = i; j<9; j++) {
				num_operate++;
				if (max<arr[j + 1]) {
					max = arr[j + 1];
					coordinate = j + 1;
					count++;
				}
			}
			if (count) {
				buffer = arr[i];
				arr[i] = max;
				arr[coordinate] = buffer;
			}
		}
	}

	return num_operate;
}