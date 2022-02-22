#include <tice.h>
#include <graphx.h>
#include <string.h>
#include <time.h>

#define GAME_RES 40

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

int game_looping = 1;

int direction = LEFT;

int game[GAME_RES][GAME_RES];

int snake[1000][3]; // is it there? x, y

int snake_len = 8;
int apple_pos[2];

int score = 0;

int rand_range(int min, int max) {
	srandom(time(0));
	return (random() % (max - min + 1)) + min;
}

void draw_frame() {
	gfx_SetDrawBuffer();
	gfx_FillScreen(0);
	for (int i = 0; i < GAME_RES; i++) {
		for (int ii = 0; ii < GAME_RES; ii++) {
			if (game[i][ii] == 1) {
				gfx_SetColor(127);
			}
			else if (game[i][ii] == 2) {
				gfx_SetColor(237);
			}
			else {
				continue;
			}
			gfx_FillRectangle(LCD_WIDTH / GAME_RES * i, LCD_HEIGHT / GAME_RES * ii, LCD_WIDTH / GAME_RES, LCD_HEIGHT / GAME_RES);
			//usleep(40000);
		}
	}
	
	//gfx_FillRectangle(20, 20, LCD_WIDTH / GAME_RES, LCD_HEIGHT / GAME_RES);
	gfx_BlitBuffer();
}


void generate_frame() {
	memset(game, 0, sizeof(game)); // clear "framebuffer"
	game[apple_pos[0]][apple_pos[1]] = 2;
	for (int i = 0; i < 1000; i++) {
		if (!snake[i][0]) {
			break;
		}
		game[snake[i][1]][snake[i][2]] = 1;
	}
}

void set_apple_pos() {
	// random apple position
	apple_pos[0] = rand_range(2, GAME_RES - 2);
	apple_pos[1] = rand_range(2, GAME_RES - 2);
}
	

void checkinput() {
		sk_key_t key = os_GetCSC();
		switch (key) {
			case sk_Down:
				direction = DOWN;
				break;
			case sk_Up:
				direction = UP;
				break;
			case sk_Left:
				direction = LEFT;
				break;
			case sk_Right:
				direction = RIGHT;
				break;
			case sk_Clear:
				game_looping = 0;
				break;
			default:
				break;	
		}
}

void check_apple_hit() {
	if (snake[0][1] == apple_pos[0] && snake[0][2] == apple_pos[1]) {
		snake_len++;
		score++;
		for (int i = 0; i < 1000; i++) {
			if (!snake[i][0]) {
				snake[i][0] = 1; // give snake extra segment
				break;
			}
		}
		set_apple_pos();
	}
	
	for (int i = 1; i < 1000; i++) {
		if (!snake[i][0]) {
			break;
		}
		if (snake[0][1] == snake[i][1] && snake[0][2] == snake[i][2]) {
			game_looping = 0; // end the game if snake collides with itself
		}
	}
}

void move_snake() {
	int new_snake[1000][3];
	
	new_snake[0][0] = 1;
	new_snake[0][1] = snake[0][1];
	new_snake[0][2] = snake[0][2];
	// move snake in direction
	if (direction == RIGHT) {
		new_snake[0][1] += 1;
	}
	else if (direction == LEFT) {
		new_snake[0][1] -= 1;
	}
	else if (direction == DOWN) {
		new_snake[0][2] += 1;
	}
	else if (direction == UP) {
		new_snake[0][2] -= 1;
	}
	
	// wrap snake
	if (new_snake[0][1] < 0) {
		new_snake[0][1] = GAME_RES;
	}
	if (new_snake[0][1] > GAME_RES) {
		new_snake[0][1] = 0;
	}
	if (new_snake[0][2] == GAME_RES) {
		new_snake[0][2] = 0;
	}
	if (new_snake[0][2] < 0) {
		new_snake[0][2] = GAME_RES - 1;
	}
	
	for (int i = 0; i < 999; i++) {
		if (!snake[i][0]) {
			break;
		}
		new_snake[i + 1][0] = snake[i][0];
		new_snake[i + 1][1] = snake[i][1];
		new_snake[i + 1][2] = snake[i][2];
	}
	
	for (int i = 0; i < 1000; i++) {
		// snake[i][0] = new_snake[i][0];
		snake[i][1] = new_snake[i][1];
		snake[i][2] = new_snake[i][2];
	}
}

void build_snake() {
	for (int i = 0; i < snake_len; i++) {
		snake[i][0] = 1;
		snake[i][1] = GAME_RES / 2 + i;
		snake[i][2] = GAME_RES / 2;
	}
}

int main(void) {
	gfx_Begin();
	build_snake();
	set_apple_pos();
	while (game_looping) {
		checkinput();
		check_apple_hit();
		move_snake();
		generate_frame();
		draw_frame();
		usleep(75000);
		//game_looping++;
	}

	gfx_End();

	return 0;
}
