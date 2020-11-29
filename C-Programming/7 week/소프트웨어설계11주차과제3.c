#include <stdio.h>
#include <stdlib.h>

void main() {
	int i = 0, j = 0;
	int n = 0;
	char** mine;
	int count = 0;
	int buffer = 0;

	printf("INPUT SIZE : ");
	scanf("%d", &n);

	/* �Է¹��� [n][n]ũ��� �����Ҵ� */
	mine = (char**)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++)
	{
		mine[i] = (char*)malloc(sizeof(int)*n);
	}

	/* �������� 0,1�� �Է¹��� */
	printf("0 �Ǵ� 1�� �Է��Ͻÿ�\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("INPUT [ %d , %d ] : ",i,j);
			scanf("%d", &mine[i][j]);
		}
	}

	/* 0���� �Է¹��� ������ ������ 1������ ���ڸ�ŭ���� ���� �ٲ��ش� */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			count = 0;
			/* mine[i][j]���� 0�̶�� */
			if (mine[i][j] == 0) { 
				/* �����Ҵ� ���� �迭�� ũ�⸦ ����� �ȵǹǷ� if������ �����ȿ� �������� count�� �ǵ��� �Ѵ� */
				if (i + 1 < n && j + 1 <= n) {
					if (mine[i + 1][j + 1] == 1) count++;
				}
				if (i + 1 < n) {
					if (mine[i + 1][j] == 1) count++;
				}
				if (i + 1 < n && j > 0) {
					if (mine[i + 1][j - 1] == 1) count++;
				}
				if (i  > 0 && j + 1 < n) {
					if (mine[i - 1][j + 1] == 1) count++;
				}
				if (i  > 0) {
					if (mine[i - 1][j] == 1) count++;
				}
				if (i > 0 && j > 0) {
					if (mine[i - 1][j - 1] == 1) count++;
				}
				if (j + 1 < n) {
					if (mine[i][j + 1] == 1) count++;
				}
				if (j > 0) {
					if (mine[i][j - 1] == 1) count++;
				}
				/* count��ŭ�� ���ڸ� mine[i][j]�� �־���� �ϹǷ� char�� mine�� �־��ֱ� ���� '0'+count */
				mine[i][j] = '0' + count;
			}
			
		}
	}

	/* 1�� �Է¹��� ���� *���� �ٲ��ش� */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (mine[i][j] == 1) {
				mine[i][j] = '*';
			}
		}
	}

	/* ���� �迭 ��� */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%c ", mine[i][j]);
		}
		printf("\n");
	}

	/* �����Ҵ� ���� */
	for (i = 0; i < n; i++)
	{
		free(mine[i]);
	}
	free(mine);

	return;
}