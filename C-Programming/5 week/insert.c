/*
2014707073 ���ȯ
����Ʈ����� 7���� ����1
*/

#include <stdio.h>

void insert_sort(int *arr, int *flag);

void main() {
	int arr[10] = { 4,1,2,7,5,3,8,9,10,0 };
	int flag = 0;
	int i = 0;

	printf("1. �������� 0. ��������: ");
	scanf_s("%d", &flag);

	printf("======BEFORE======\n");
	for (i = 0; i<10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	insert_sort(&arr, &flag);

	printf("======AFTER======\n");
	for (i = 0; i<10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return;
}

void insert_sort(int *arr, int *flag) {
	int buffer = 0;
	int i = 0, j = 0;

	if (*flag) { // ��������
		for (i = 0; i<9; i++) {
			j = i;
			while (arr[j]>arr[j + 1]) {
				buffer = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = buffer;
				if (j != 0) {
					j--;
				}
				else {
					j = 0;
				}
			}
		}

	}

	else { // ��������
		for (i = 0; i<9; i++) {
			j = i;
			while (arr[j]<arr[j + 1]) {
				buffer = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = buffer;
				if (j != 0) {
					j--;
				}
				else {
					j = 0;
				}
			}
		}
	}

	return;
}