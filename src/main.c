#include "main.h"

#define LINE_PADDING 15
#define LINE_HALF_GAP 50
#define LINE_GAP LINE_HALF_GAP + LINE_HALF_GAP
#define CIRCLE_RADIUS 42

const Line board_lines[] = {
	// Horizontal
	{ .p1 = { .x = BOARD_MIN_X, .y = HEIGHT/2 - LINE_HALF_GAP}, .p2 = { .x = BOARD_MAX_X, .y = HEIGHT/2 - LINE_HALF_GAP } },
	{ .p1 = { .x = BOARD_MIN_X, .y = HEIGHT/2 + LINE_HALF_GAP}, .p2 = { .x = BOARD_MAX_X, .y = HEIGHT/2 + LINE_HALF_GAP } },
	// Vertical
	{ .p1 = { .x = WIDTH/2 - LINE_HALF_GAP, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 - LINE_HALF_GAP, .y = BOARD_MAX_Y } },
	{ .p1 = { .x = WIDTH/2 + LINE_HALF_GAP, .y = BOARD_MIN_Y }, .p2 = { .x = WIDTH/2 + LINE_HALF_GAP, .y = BOARD_MAX_Y } },
};

static int x = 0;
const int LINE_COLOR = 0xff1111ff;
const int BACKGROUND_COLOR = 0xff000000;

static Game game = {0};

char is_valid_char(char c)
{
	return c != -1;
}

char get_winner()
{
	int i;
	for (i = 0; i < 3; i++) {
		// checking lines
		if (is_valid_char(game.board[3*i]) && game.board[3*i] == game.board[3*i+1] && game.board[3*i] == game.board[3*i+2]) {
			return game.board[3*i];
		}

		// checking columns
		if (is_valid_char(game.board[i]) && game.board[i] == game.board[i+3] && game.board[i] == game.board[i+6]) {
			return game.board[i];
		}
	}

	if (is_valid_char(game.board[0]) && game.board[0] == game.board[4] && game.board[0] == game.board[8]) {
		return game.board[0];
	}

	if (is_valid_char(game.board[2]) && game.board[2] == game.board[4] && game.board[2] == game.board[6]) {
		return game.board[2];
	}

	for (i = 0; i < BOARD_SIZE; i++) {
		if (game.board[i] == -1) {
			break;
		}
	}
	if (i == BOARD_SIZE) {
		// Game draw
		return DRAW_VAL;
	}

	// game is not over yet
	return NONE_VAL;
}

int is_valid_board_pos(Vector2 point)
{
	int x_valid = ((int)point.x >= BOARD_MIN_X) && ((int)point.x < BOARD_MAX_X);
	int y_valid = ((int)point.y >= BOARD_MIN_Y) && ((int)point.y < BOARD_MAX_Y);

	return x_valid && y_valid;
}

Vector2i global_to_board(Vector2 global_point)
{
	Vector2i board_point = {0};
	board_point.x = global_point.x;
	board_point.y = global_point.y;

	board_point.x -= BOARD_MIN_X;
	board_point.y -= BOARD_MIN_Y;
	board_point.x /= LINE_GAP;
	board_point.y /= LINE_GAP;

	return board_point;
}

int mouse_to_board(Vector2 mouse)
{

	if (is_valid_board_pos(mouse)) {
		Vector2i bp = global_to_board(mouse);

		return bp.y * BOARD_SIDE +  bp.x;
	}

	return -1;
}

void handle_click(Vector2 mouse)
{
	int board_idx = mouse_to_board(mouse);
	if (board_idx == -1 || game.board[board_idx] != -1) {
		return;
	}

	if (game.is_x_turn) {
		game.board[board_idx] = X_VAL;
	} else {
		game.board[board_idx] = O_VAL;
	}

	game.is_x_turn = !game.is_x_turn;
}

void draw_x(int idx, int color)
{
	int y = idx / BOARD_SIDE;
	int x = idx % BOARD_SIDE;

	draw_line(
		BOARD_MIN_X+LINE_PADDING+x*100,
		BOARD_MIN_Y+LINE_PADDING+y*100,
		BOARD_MIN_X-LINE_PADDING+x*100+100,
		BOARD_MIN_Y-LINE_PADDING+y*100+100,
		color);
	draw_line(
		BOARD_MIN_X-LINE_PADDING+x*100+100,
		BOARD_MIN_Y+LINE_PADDING+y*100,
		BOARD_MIN_X+LINE_PADDING+x*100,
		BOARD_MIN_Y-LINE_PADDING+y*100+100,
		color);
}

void draw_o(int idx, int color)
{
	int y = idx / BOARD_SIDE;
	int x = idx % BOARD_SIDE;

	draw_circle(
		BOARD_MIN_X+x*100+50,
		BOARD_MIN_Y+y*100+50,
		CIRCLE_RADIUS, color);
}

Vector2 get_mouse_pos()
{
	float mouse_x = get_mouse_pos_x();
	float mouse_y = get_mouse_pos_y();

	return  (Vector2){ .x = mouse_x, .y = mouse_y };
}

void init_game()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		game.board[i] = -1;
	}
	game.is_x_turn = 1;
}

void game_loop() {
	Vector2 mouse = get_mouse_pos();
	int board_index = mouse_to_board(mouse);
	char w = get_winner();

	if (is_mouse_clicked() && w == NONE_VAL) {
		handle_click(mouse);
	}

	if (is_key_pressed('r')) {
		init_game();
	}

	begin_draw();

	clear_window(BACKGROUND_COLOR);
	switch (w) {
		case DRAW_VAL:
			draw_text("Draw!", WIDTH / 2 - 32, 15, 32, 0xff888888);
			break;
		case X_VAL:
			draw_text("X wins!", WIDTH / 2 - 32, 15, 32, 0xff888888);
			break;
		case O_VAL:
			draw_text("O wins!", WIDTH / 2 - 32, 15, 32, 0xff888888);
			break;
	}

	if (board_index >= 0 && game.board[board_index] == -1 && w == NONE_VAL) {
		if (game.is_x_turn) {
			draw_x(board_index, 0xff88ff88);
		} else {
			draw_o(board_index, 0xff88ff88);
		}
	}

	for (int i = 0; i < 4; i++) {
		Line l = board_lines[i];
		draw_line(l.p1.x, l.p1.y, l.p2.x, l.p2.y, LINE_COLOR);
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		char current = game.board[i];

		switch (current) {
			case X_VAL:
				draw_x(i, 0xffffffff);
				break;
			case O_VAL:
				draw_o(i, 0xffffffff);
				break;
		}
	}

	end_draw();
}

int main(void)
{
	init_window(800, 600, "Tic-tac-toe");
	init_game();

#ifdef PLATFORM_WEB
	set_game_loop_func(game_loop);
#else
	while(!should_close()) {
		game_loop();
	}
#endif // PLATFORM_WEB

	return 0;
}
