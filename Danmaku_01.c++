#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 30
#define HEIGHT 30
#define BUFFER_SIZE (HEIGHT * (WIDTH * 2 + 1) + 1)
#define MAX_BULLETS 30

typedef struct {
    int x, y;
    int active;
} Bullet;

int main(void) {
    char map[HEIGHT][WIDTH];
    char screen_buffer[BUFFER_SIZE];
    int px = 15, py = 20;

    Bullet bullets[MAX_BULLETS] = { 0 };

    printf("\033[2J\033[?25l");

    while (1) {
        int next_x = px;
        int next_y = py;

        if (_kbhit()) {
            int ch = _getch();
            if (ch == 'q') break;
            if (ch == 'w') next_y--;
            if (ch == 's') next_y++;
            if (ch == 'a') next_x--;
            if (ch == 'd') next_x++;

            if (ch == ' ') {
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (bullets[i].active == 0) {
                        bullets[i].x = px;
                        bullets[i].y = py - 1;
                        bullets[i].active = 1;
                        break;
                    }
                }
            }
        }

        if (next_x > 0 && next_x < WIDTH - 1 && next_y > 0 && next_y < HEIGHT - 1) {
            px = next_x;
            py = next_y;
        }

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active == 1) {
                bullets[i].y--;

                if (bullets[i].y <= 0) {
                    bullets[i].active = 0;
                }
            }
        }

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                    map[y][x] = '#';
                }
                else {
                    map[y][x] = '.';
                }
            }
        }

        map[py][px] = '@';

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active == 1) {
                map[bullets[i].y][bullets[i].x] = '|';
            }
        }

        int idx = 0;
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                screen_buffer[idx++] = map[y][x];
                screen_buffer[idx++] = ' ';
            }
            screen_buffer[idx++] = '\n';
        }
        screen_buffer[idx] = '\0';

        printf("\033[H%s", screen_buffer);
        Sleep(30);
    }

    printf("\033[?25h");
    return 0;
}
