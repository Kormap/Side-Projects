#include <stdio.h>
#include <stdlib.h>

void main() {
	char* Hello;
	int n = 0, i = 0, j = 0;
	char ch = '0';

	printf("�Ҵ��Ϸ��� ũ�� : ");
	scanf("%d", &n);

	/* �Ҵ��Ϸ��� ũ�⸸ŭ �����Ҵ� */
	Hello = (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++) {
		Hello[i] = (char*)malloc(sizeof(int)*n);
	}


	i = 0;
	/* ���ۿ� \n�� �����ִ� ���� ���� */
	while (getchar() != '\n');
	printf("����Ϸ��� ���� : ");
	/* getchar�Լ��� �̿��Ͽ� �Է¹��� \n�� ���ö����� �Է��� �޴´� */
	while (ch != '\n') {
		ch = getchar();
		Hello[i] = ch;
		i++;
		j++;
	}

	/* �Է¹��� ���� ��� */
	printf("���Ȯ�� : ");
	for (i = 0; i < j; i++) {
		printf("%c",Hello[i]);
	}

	free(Hello);

	return;
}