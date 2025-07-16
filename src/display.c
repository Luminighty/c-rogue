#include "display.h"
#include "palette.h"

static Display display = {0};

static inline int is_on_screen(int x, int y) { 
	return x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT;
}


Display* display_get() {
	return &display;
}


void display_clear() {
	display_foreach(x, y) {
		display.glyphs[y][x].fg = 0;
		display.glyphs[y][x].bg = 0;
		display.z_buffer[y][x] = 0;
		display.is_dirty = true;
	}
}


void display_putchar(int x, int y, Glyph glyph, ZIndex z_index) {
	if (!is_on_screen(x, y))
		return;
	if (z_index != ZINDEX_FORCE && z_index < display.z_buffer[y][x])
		return;
	if (z_index != ZINDEX_FORCE)
		display.z_buffer[y][x] = z_index;
	
	display.glyphs[y][x] = glyph;
	display.is_dirty = true;
}


void display_putstr(int x, int y, const char* message, int fg, int bg, ZIndex z_index) {
	int offset = 0;
	char c;
	while ((c = message[offset]) != '\0') {
		display_putchar(x + offset, y, (Glyph){.glyph=c, .fg=fg, .bg=bg}, z_index);
		offset++;
	}
}

