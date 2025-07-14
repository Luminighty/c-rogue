#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"


#define ZINDEX_FORCE 0
typedef char ZIndex;


typedef struct {
	char glyph;
	int fg;
	int bg;
} Glyph;

#define glyph(_glyph, _fg, _bg) (Glyph){ .glyph=(_glyph), .fg=(_fg), .bg=(_bg) }


typedef struct {
	Glyph glyphs[SCREEN_HEIGHT][SCREEN_WIDTH];
	ZIndex z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
} Display;

Display* display_get();

void display_clear();
void display_putchar(int x, int y, Glyph glyph, ZIndex z_index);

#define display_foreach(x, y)\
	for(int y = 0; y < SCREEN_HEIGHT; y++)\
	for(int x = 0; x < SCREEN_WIDTH; x++)

#endif // DISPLAY_H
