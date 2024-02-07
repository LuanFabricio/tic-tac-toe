#include "main.h"

const Line board_lines[] = {
	// Horizontal
	{ .p1 = { .x = BOARD_MIN_X, .y = (HEIGHT/2) - 100 }, .p2 = { .x = BOARD_MAX_X, .y = (HEIGHT/2) - 100 } },
	{ .p1 = { .x = BOARD_MIN_X, .y = HEIGHT/2 }, 	     .p2 = { .x = BOARD_MAX_X, .y = HEIGHT/2 } 	       },
	{ .p1 = { .x = BOARD_MIN_X, .y = (HEIGHT/2) + 100},  .p2 = { .x = BOARD_MAX_X, .y = (HEIGHT/2) + 100 } },
	// Vertical
	{ .p1 = { .x = WIDTH/2 - 100, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 - 100, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = WIDTH/2, .y = BOARD_MIN_Y }, 	  .p2 = { .x = WIDTH/2, .y = BOARD_MAX_Y } 	 },
	{ .p1 = { .x = WIDTH/2 + 100, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 + 100, .y = BOARD_MAX_Y } },
};

static int x = 0;

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

	clear_window(0xff000000);

	// draw_rectangle(x, 2, 300, 400, 0xffff0000);

	for (int i = 0; i < 6; i++) {
		Line l = board_lines[i];
		draw_line(l.p1.x, l.p1.y, l.p2.x, l.p2.y, 0xff000000);
	}

	draw_rectangle(mouse_x-50, mouse_y-50, 100, 100, 0xff999999);

	end_draw();
}

int main(void)
{
	init_window(800, 600, "Test");

#ifdef PLATFORM_WEB
	set_game_loop_func(draw_loop);
#else
	while(!should_close()) {
		draw_loop();
	}
#endif // PLATFORM_WEB

	return 0;
}
