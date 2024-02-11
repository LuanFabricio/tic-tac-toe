#include "raylib.h"
#include <stdarg.h>
#include <stdio.h>

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

void draw_circle(int center_x, int center_y, float radius, int color)
{
	DrawCircleLines(center_x, center_y, radius, INT_TO_COLOR(color));
}

void draw_text(const char *text, int x, int y, int font_size, int color)
{
	DrawText(text, x, y, font_size, INT_TO_COLOR(color));
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
	if (key >= 65 && key <= 90) {
		return IsKeyPressed(key);
	}

	if (key >= 97 && key <= 122) {
		return IsKeyPressed(key-32);
	}

	return 0;
}

int is_mouse_clicked()
{
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
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

void game_log (const char *__restrict format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
