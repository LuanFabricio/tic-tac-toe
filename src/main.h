#ifndef MAIN_H_
#define MAIN_H_

// CONSTANTS
#define HEIGHT 600
#define WIDTH 800

#define KEY_RIGHT 'd'
#define KEY_LEFT 'a'

#define CENTER_PADDING 150
#define BOARD_MIN_X WIDTH/2-CENTER_PADDING
#define BOARD_MAX_X WIDTH/2+CENTER_PADDING
#define BOARD_MIN_Y HEIGHT/2-CENTER_PADDING
#define BOARD_MAX_Y HEIGHT/2+CENTER_PADDING

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
} Vector2;

// EXTERNAL INTEFACES
extern void init_window(int width, int height, const char* title);
extern int should_close();
extern void draw_rectangle(int x, int y, int width, int height, int color);
extern void draw_line(int x0, int y0, int x1, int y1, int color);
extern void set_game_loop_func(void (*func));
extern void clear_window(int color);
extern void begin_draw();
extern void end_draw();
extern int is_key_pressed(char key);
extern float get_delta_time();
extern float get_mouse_pos_x();
extern float get_mouse_pos_y();

#endif // MAIN_H_
