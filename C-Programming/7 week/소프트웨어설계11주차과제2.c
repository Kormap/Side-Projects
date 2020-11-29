#include <stdio.h>
#include <stdlib.h>

void main() {
	char* Hello;
	int n = 0, i = 0, j = 0;
	char ch = '0';

	printf("할당하려는 크기 : ");
	scanf("%d", &n);

	/* 할당하려는 크기만큼 동적할당 */
	Hello = (char*)malloc(sizeof(int*)*n);
	for (i = 0; i<n; i++) {
		Hello[i] = (char*)malloc(sizeof(int)*n);
	}


	i = 0;
	/* 버퍼에 \n이 남아있는 것을 방지 */
	while (getchar() != '\n');
	printf("출력하려는 문장 : ");
	/* getchar함수를 이용하여 입력받음 \n이 나올때까지 입력을 받는다 */
	while (ch != '\n') {
		ch = getchar();
		Hello[i] = ch;
		i++;
		j++;
	}

	/* 입력받은 값을 출력 */
	printf("출력확인 : ");
	for (i = 0; i < j; i++) {
		printf("%c",Hello[i]);
	}

	free(Hello);

	return;
}