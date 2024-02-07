#include "raylib.h"

#define INT_TO_COLOR(color) *(Color*)(&color)

void init_window(int width, int height, const char* title)
{
	InitWindow(width, height, title);
}

int should_close()
{
	return WindowShouldClose();
}

void draw_rectangle(int x, int y, int width, int height, int color)
{
	DrawRectangle(x, y, width, height, INT_TO_COLOR(color));
}

void draw_line(int x0, int y0, int x1, int y1, int color)
{
	DrawLine(x0, y0, x1, y1, INT_TO_COLOR(color));
}

void set_game_loop_func(void (*func));

void clear_window(int color)
{
	ClearBackground(INT_TO_COLOR(color));
}

void begin_draw()
{
	BeginDrawing();
}

void end_draw()
{
	EndDrawing();
}

int is_key_pressed(char key)
{
	return 0;
}

float get_delta_time()
{
	return GetFrameTime();
}

float get_mouse_pos_x()
{
	return GetMouseX();
}

float get_mouse_pos_y()
{
	return GetMouseY();
}
