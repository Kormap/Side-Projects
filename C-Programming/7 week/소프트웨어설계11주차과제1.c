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

	/* �Է¹��� m�� �̿��� 1���� m������ ���� n�� �־��ش� */
	for (i = 1; i <= m; i++) {
		n += i;
	}

	/* n�� ���� �̿��� �����Ҵ��� ���ش� */
	A= (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++){
		A[i] = (char*)malloc(sizeof(int)*n);
	}

	/* n�� ���� �̿��� �����Ҵ��� ���ش� */
	B = (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++) {
		B[i] = (char*)malloc(sizeof(int)*n);
	}

	/* n�� ���� �̿��� �����Ҵ��� ���ش�(2n) */
	X = (char*)malloc(sizeof(int*)*(2*n));
	for (i = 0; i<2*n; i++) {
		X[i] = (char*)malloc(sizeof(int)*n);
	}

	/* X[i]�� '0'���� �ʱ�ȭ ���ش� */
	for (i = 0; i < 2*n; i++) {
		X[i] = '0';
	}

	/* �Է¹��� n��ŭ �־���� �ϹǷ�, '0'�� �ش��ϴ� �ƽ�Ű�ڵ忡 +i�� ���� �־��ش� */
	for (i = 0; i < n; i++) {
		A[i] = '0' + i;
	}
	/* �Է¹��� n��ŭ �־���� �ϹǷ�, 'A'�� �ش��ϴ� �ƽ�Ű�ڵ忡 +i�� ���� �־��ش� */
	for (i = 0; i < n; i++) {
		B[i] = 'A' + i;
	}

	/* X[i]�� ���� �־��ش� */
	/* �� 2n���� ���� */
	for (i = 0; i < 2*n;) {
		/* select_A,B�� 1, 2, 3 .. ���������� ���� */
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

	/* A,B,X ���*/
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

	/* �����Ҵ� �޸� ���� */
	free(A);
	free(B);
	free(X);

	return;
}