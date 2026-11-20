#include<stdio.h>

#include<stdlib.h>
#include<windows.h>

#define GAME_WIDTH 25
#define REAL_WIDTH 35
#define HEIGHT 35

#define SCORE_X 52
#define SCORE_Y 5

#define MAX_BULLETS 30

typedef struct {
	int x, y, active;
}Bullet;

void gotoxy(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printPower(int x, int y, int currentScore) {
	gotoxy(x, y);
	printf("POWER : %d", currentScore);
}

int main(void) {
	char map[HEIGHT][REAL_WIDTH];
	char buffer[10000];
	int px = 12, py = 30;
	int score = 0;

	Bullet bullets[MAX_BULLETS] = { 0 };

	gotoxy(0, 0);

	while (1) {
		gotoxy(0, 0);
		if (score < 130) {
		}

		int idx = 0;
		int next_px = px, next_py = py;

		for (int y = 0;y < HEIGHT;y++) {
			for (int x = 0;x < GAME_WIDTH;x++) {
				if (x == 0 || x == GAME_WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
					map[y][x] = '#';
				}
				else {
					map[y][x] = ' ';
				}
			}
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) next_py--;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) next_py++;
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) next_px--;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) next_px++;

		if (GetAsyncKeyState('Z') & 0x8000) {
			for (int i = 0; i < MAX_BULLETS; i++) {
				if (bullets[i].active == 0) {
					bullets[i].x = px;
					bullets[i].y = py;
					bullets[i].active = 1;
					break;
				}
			}
		}

		if (next_px > 0 && next_px < GAME_WIDTH - 1 && next_py > 0 && next_py < HEIGHT - 2) {
			px = next_px;
			py = next_py;
		}

		for (int i = 0;i < MAX_BULLETS;i++) {
			if (bullets[i].active == 1) {
				bullets[i].y--;
				if (bullets[i].y <= 0) {
					bullets[i].active = 0;
				}
			}
		}

		for (int i = 0; i < MAX_BULLETS; i++) {
			if (bullets[i].active == 1) {
				map[bullets[i].y][bullets[i].x] = '|';
			}
		}

		map[py][px] = '@';
		map[py+1][px] = '@';

		for (int y = 0;y < HEIGHT;y++) {
			for (int x = 0;x < GAME_WIDTH;x++) {
				buffer[idx++] = map[y][x];
				buffer[idx++] = ' ';
			}
			buffer[idx++] = '\n';
		}
		buffer[idx] = '\0';

		printf("%s", buffer);

		printPower(SCORE_X, SCORE_Y, score);

		

		Sleep(60);
	}

	return 0;
}

/* 2일차 특징: GetAsyncKeyState() 함수를 활용해 키보드 입력 반환값의 MSB(최상위 비트)가 
1인지 검사하며, 현재 눌림 상태에 따라 바로바로 분기 처리를 하도록 구현했다.*/
