#ifndef MAIN_H_
#define MAIN_H_

// CONSTANTS
#define HEIGHT 600
#define WIDTH 800

#define KEY_RIGHT 'd'
#define KEY_LEFT 'a'

#define X_VAL 0
#define O_VAL 1
#define DRAW_VAL -1
#define NONE_VAL -2

#define CENTER_PADDING 150
#define BOARD_MIN_X WIDTH/2-CENTER_PADDING
#define BOARD_MAX_X WIDTH/2+CENTER_PADDING
#define BOARD_MIN_Y HEIGHT/2-CENTER_PADDING
#define BOARD_MAX_Y HEIGHT/2+CENTER_PADDING

#define BOARD_SIDE 3
#define BOARD_SIZE BOARD_SIDE * BOARD_SIDE

// UTILS
static int max(int x1, int x2)
{
	return x1 > x2 ? x1 : x2;
}

static int min(int x1, int x2)
{
	return x1 > x2 ? x2 : x1;
}

// TYPEDEFS
typedef struct {
	int x, y;
} Point;

typedef struct {
	Point p1, p2;
} Line;

typedef struct {
	float x, y;
}Vector2;

typedef struct {
	int x, y;
} Vector2i;

typedef struct {
	char board[BOARD_SIZE];
	char is_x_turn;
} Game;

// EXTERNAL INTEFACES
extern void init_window(int width, int height, const char* title);
extern int should_close();
extern void draw_rectangle(int x, int y, int width, int height, int color);
extern void draw_line(int x0, int y0, int x1, int y1, int color);
extern void draw_circle(int center_x, int center_y, float radius, int color);
extern void draw_text(const char *text, int x, int y, int font_size, int color);
extern int mesure_text(const char *text, int font_size);
extern void set_game_loop_func(void (*func));
extern void clear_window(int color);
extern void begin_draw();
extern void end_draw();
extern int is_key_pressed(char key);
extern int is_mouse_clicked();
extern float get_delta_time();
extern float get_mouse_pos_x();
extern float get_mouse_pos_y();
extern void game_log (const char *__restrict __format, ...);

#endif // MAIN_H_
