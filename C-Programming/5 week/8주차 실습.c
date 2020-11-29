/*
2014707073 ���ȯ
8���� �ǽ�1
*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
/*
�ؿ� �Լ����� �������� include�� �ؿ� �Լ��� ����
*/
void gotoxy(int x, int y);
void draw_map();
void run_game();

void main() {
	draw_map(); // race�� �� map�� �׷��ش�.
	run_game(); // 
	return;
}

void draw_map() {
	int i = 1;

	printf("======RUN GAME======\n");
	for (i = 1; i < 30; i += 2) {
		gotoxy(i, 1); printf("��");
		gotoxy(i, 5); printf("��");
		gotoxy(i, 9); printf("��");
	}
/*
Gotoxy�� �̿��ؼ� ���� �׷��ش�.
y��ǥ 1 5 9�� ���� �׸��Ƿ�,
�� ����� 3 7�� run�� �ϴ� ��ǥ�� �ȴ�.
*/
}

void run_game() {
	int i = 1, j = 1;
	char key;

	while (1) {
		_kbhit(); // ���� ���� visual studio 2015 ������ _kbhit�� �̷��� ��
		key = _getch();
		if (key=='a') {
			gotoxy(i, 3); // i�� if������ 1�� �������������ν� ��������
			Sleep(200); // �������� ���ݾ� �����ֱ� ���� Sleep�� ��
			printf("��");
                         gotoxy(i-1,3); // ������ �ִ�
                         printf(�� ��); // ���� ������
			i++;
		}
		else if (key == 'd') {
			gotoxy(j, 7);
			Sleep(200);
			printf("��");
gotoxy(j-1,3);
                         printf(�� ��);
			j++;
		}
			
/*
I�� j�� 30�� �ٴٸ���, ������ ���� ���̹Ƿ� 
if������ i�� j�� 30�� �� ��츦 �����༭
���� system(��cls��)�� ������ ȭ���� �����ְ�, ���� �̰������ ǥ�����ش�.
�׸��� system(��pause��);�� ���� �� return;�Ѵ�
*/
		if (i == 30) {
			system("cls"); 
			printf("�� WINNER!!\n");
			system("pause");
			return;
		}
		else if (j == 30) {
			system("cls");
			printf("�� WINNER!!\n");
			system("pause");
			return;
		}
	}
}

void gotoxy(int x, int y) { // gotoxy�� ����
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
