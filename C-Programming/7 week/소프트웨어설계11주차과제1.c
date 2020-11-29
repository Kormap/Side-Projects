#include <stdio.h>
#include <stdlib.h>

void main() {
	char* A;
	char* B;
	char* X;
	int i = 0, j = 0, n = 0, m = 0;
	int ii = 0, iii = 0, k = 0;
	int select_A = 1, select_B = 1;

	printf("INPUT X SIZE : ");
	scanf_s("%d",&m);

	/* 입력받은 m을 이용해 1부터 m까지의 합을 n에 넣어준다 */
	for (i = 1; i <= m; i++) {
		n += i;
	}

	/* n의 값을 이용해 동적할당을 해준다 */
	A= (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++){
		A[i] = (char*)malloc(sizeof(int)*n);
	}

	/* n의 값을 이용해 동적할당을 해준다 */
	B = (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++) {
		B[i] = (char*)malloc(sizeof(int)*n);
	}

	/* n의 값을 이용해 동적할당을 해준다(2n) */
	X = (char*)malloc(sizeof(int*)*(2*n));
	for (i = 0; i<2*n; i++) {
		X[i] = (char*)malloc(sizeof(int)*n);
	}

	/* X[i]를 '0'으로 초기화 해준다 */
	for (i = 0; i < 2*n; i++) {
		X[i] = '0';
	}

	/* 입력받은 n만큼 넣어줘야 하므로, '0'에 해당하는 아스키코드에 +i로 값을 넣어준다 */
	for (i = 0; i < n; i++) {
		A[i] = '0' + i;
	}
	/* 입력받은 n만큼 넣어줘야 하므로, 'A'에 해당하는 아스키코드에 +i로 값을 넣어준다 */
	for (i = 0; i < n; i++) {
		B[i] = 'A' + i;
	}

	/* X[i]에 값을 넣어준다 */
	/* 총 2n번을 돈다 */
	for (i = 0; i < 2*n;) {
		/* select_A,B가 1, 2, 3 .. 순차적으로 증가 */
		for (ii = 0; ii < select_A; ii++) {
			X[i] = A[j];
			j++;
			i++;
		}
		select_A++;

		for (iii = 0; iii < select_B; iii++) {
			X[i] = B[k];
			k++;
			i++;
		}
		select_B++;
	}

	/* A,B,X 출력*/
	printf("A = { ");
	for (i = 0; i < n; i++) {
		printf("%c ", A[i]);
	}
	printf(" }\n");

	printf("B = { ");
	for (i = 0; i < n; i++) {
		printf("%c ", B[i]);
	}
	printf(" }\n");

	printf("X = { ");
	for (i = 0; i < 2*n; i++) {
		printf("%c ",X[i]);
	}
	printf(" }\n");

	/* 동적할당 메모리 해제 */
	free(A);
	free(B);
	free(X);

	return;
}