#include "config.h"
#include "display.h"
#include "input.h"
#include <raylib.h>

static Texture2D ascii;
static RenderTexture2D render_target;
#define color_into_raylib(color) (Color){.r = ((color) >> 16) & 0xFF, .g = ((color) >> 8) & 0xFF, .b = (color) & 0xFF, .a=255 }


void platform_init() {
	InitWindow(TARGET_WINDOW_WIDTH, TARGET_WINDOW_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(60);
	ascii = LoadTexture("assets/pastiche_8x8.png"); 
	render_target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void platform_destroy() {
	CloseWindow();
	UnloadTexture(ascii);
	UnloadRenderTexture(render_target);
}


#define TILE 8
static inline void display_draw() {
	Display* display = display_get();
	display_foreach(x, y) {
		char g = display->glyphs[y][x].glyph;
		int sx = g & 0xF;
		int sy = (g >> 4) & 0xF;

		Color fg = color_into_raylib(display->glyphs[y][x].fg);
		Color bg = color_into_raylib(display->glyphs[y][x].bg);

		Rectangle source = { sx * TILE, sy * TILE, TILE, TILE};
		Rectangle dest = { x * TILE, y * TILE, TILE, TILE};
		DrawRectangleRec(dest, bg);
		DrawTexturePro(
			ascii,
			source,
			dest,
			(Vector2){0},
			0,
			fg
		);
	}
}

static const Rectangle RENDER_SOURCE = {.x = 0, .y = 0, .width = WINDOW_WIDTH, .height = -WINDOW_HEIGHT};
static const Rectangle RENDER_DEST = {.x = 0, .y = 0, .width = TARGET_WINDOW_WIDTH, .height = TARGET_WINDOW_HEIGHT};
void platform_render() {
	BeginDrawing();
	ClearBackground(BLACK);

	BeginTextureMode(render_target);
	display_draw();
	EndTextureMode();

	DrawTexturePro(
		render_target.texture,
		RENDER_SOURCE,
		RENDER_DEST,
		(Vector2){0},
		0,
		WHITE
	);
	EndDrawing();
}


bool platform_is_running() {
	return !WindowShouldClose();
}

void platform_input(Input* input) {
	input->delta.x = IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT);
	input->delta.y = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);
	input->restart = IsKeyDown(KEY_R);
}

