#ifndef PLATFORM_DISPLAY_H
#define PLATFORM_DISPLAY_H

#include <stdint.h>


void begin_frame(uint16_t clear_color);
void draw_char(int x, int y, char g, uint16_t fg, uint16_t bg);
void end_frame();
void send_chunk(int row);
void platform_init_display(void);

#endif // PLATFORM_DISPLAY_H
