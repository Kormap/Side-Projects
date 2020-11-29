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

	/* 입력방은 [n][n]크기로 동적할당 */
	mine = (char**)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++)
	{
		mine[i] = (char*)malloc(sizeof(int)*n);
	}

	/* 유저에게 0,1을 입력받음 */
	printf("0 또는 1로 입력하시오\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("INPUT [ %d , %d ] : ",i,j);
			scanf("%d", &mine[i][j]);
		}
	}

	/* 0으로 입력받은 곳에서 주위의 1값들의 숫자만큼으로 값을 바꿔준다 */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			count = 0;
			/* mine[i][j]값이 0이라면 */
			if (mine[i][j] == 0) { 
				/* 동적할당 받은 배열의 크기를 벗어나면 안되므로 if문으로 범위안에 있을때만 count가 되도록 한다 */
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
				/* count만큼의 숫자를 mine[i][j]에 넣어줘야 하므로 char인 mine에 넣어주기 위해 '0'+count */
				mine[i][j] = '0' + count;
			}
			
		}
	}

	/* 1을 입력받은 곳에 *으로 바꿔준다 */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (mine[i][j] == 1) {
				mine[i][j] = '*';
			}
		}
	}

	/* 최종 배열 출력 */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%c ", mine[i][j]);
		}
		printf("\n");
	}

	/* 동적할당 해제 */
	for (i = 0; i < n; i++)
	{
		free(mine[i]);
	}
	free(mine);

	return;
}