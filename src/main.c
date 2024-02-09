#include "main.h"

#define LINE_PADDING 15

const Line board_lines[] = {
	// Horizontal
	// { .p1 = { .x = BOARD_MIN_X, .y = (HEIGHT/2) - 100 }, .p2 = { .x = BOARD_MAX_X, .y = (HEIGHT/2) - 100 } },
	{ .p1 = { .x = BOARD_MIN_X, .y = HEIGHT/2 - 50}, .p2 = { .x = BOARD_MAX_X, .y = HEIGHT/2 - 50 } },
	{ .p1 = { .x = BOARD_MIN_X, .y = HEIGHT/2 + 50}, .p2 = { .x = BOARD_MAX_X, .y = HEIGHT/2 + 50 } },
	// Vertical
	//{ .p1 = { .x = WIDTH/2 - 100, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 - 100, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = WIDTH/2 - 50, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 - 50, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = WIDTH/2 + 50, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 + 50, .y = BOARD_MAX_Y } },
	// Borders
	{ .p1 = { .x = BOARD_MIN_X, .y = BOARD_MIN_Y }, .p2 = { .x = BOARD_MAX_X, .y = BOARD_MIN_Y } },
	{ .p1 = { .x = BOARD_MAX_X, .y = BOARD_MIN_Y }, .p2 = { .x = BOARD_MAX_X, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = BOARD_MAX_X, .y = BOARD_MAX_Y }, .p2 = { .x = BOARD_MIN_X, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = BOARD_MIN_X, .y = BOARD_MAX_Y }, .p2 = { .x = BOARD_MIN_X, .y = BOARD_MIN_Y } },
};

static int x = 0;
const int LINE_COLOR = 0xff1111ff;
const int BACKGROUND_COLOR = 0xff000000;

#define BOARD_SIDE 3
#define BOARD_SIZE BOARD_SIDE * BOARD_SIDE
const char board[BOARD_SIZE] = {0};

void draw_x(int idx)
{
	int y = idx / BOARD_SIDE;
	int x = idx % BOARD_SIDE;

	draw_line(BOARD_MIN_X+LINE_PADDING+x*100    , BOARD_MIN_Y+LINE_PADDING+y*100, BOARD_MIN_X-LINE_PADDING+x*100+100, BOARD_MIN_Y-LINE_PADDING+y*100+100, 0xffffffff);
	draw_line(BOARD_MIN_X-LINE_PADDING+x*100+100, BOARD_MIN_Y+LINE_PADDING+y*100, BOARD_MIN_X+LINE_PADDING+x*100    , BOARD_MIN_Y-LINE_PADDING+y*100+100, 0xffffffff);
}

void draw_loop() {
	float dt = get_delta_time();
	float mouse_x = get_mouse_pos_x();
	float mouse_y = get_mouse_pos_y();
	float speed = 500 * dt;
	if (is_key_pressed(KEY_RIGHT)) {
		x = min(500, x+speed);
	}
	if (is_key_pressed(KEY_LEFT)) {
		x = max(0, x-speed);
	}

	begin_draw();

	clear_window(BACKGROUND_COLOR);

	draw_x(4);

	// draw_rectangle(x, 2, 300, 400, 0xffff0000);

	draw_rectangle(mouse_x-25, mouse_y-25, 50, 50, 0xffffffff);

	for (int i = 0; i < 4; i++) {
		Line l = board_lines[i];
		draw_line(l.p1.x, l.p1.y, l.p2.x, l.p2.y, LINE_COLOR);
	}

	end_draw();
}

int main(void)
{
	init_window(800, 600, "Tic-tac-toe");

#ifdef PLATFORM_WEB
	set_game_loop_func(draw_loop);
#else
	while(!should_close()) {
		draw_loop();
	}
#endif // PLATFORM_WEB

	return 0;
}
