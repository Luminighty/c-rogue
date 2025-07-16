#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app.h"
#include "display.h"
#include "pinout.h"
#include "platform_input.h"
#include "platform_display.h"


// TODO: Update to single color param
#define rgb565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))


static inline void render() {
	Display* display = display_get();
	if (!display->is_dirty)
		return;
	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 40; x++) {
			char g = display->glyphs[y][x].glyph;
			draw_char(x * 8, (y % LCD_TRANSFER_ROW_CHARS) * 8, g, 0xFF, 0x0);
		}
		// NOTE: We shouldn't use this many magic variables, but its 1:32 AM, and I want to sleep
		if ((y + 1) % LCD_TRANSFER_ROW_CHARS == 0)
			send_chunk(y - LCD_TRANSFER_ROW_CHARS + 1);
	}
}


void app_main(void) {
	platform_init_display();
	// platform_init_buttons();

	// NOTE: This causes some stack overflow for some reason?
	app_init();
	Display* display = display_get();

	display_putstr(3, 3, "Hello", 0xFF, 0x00, 0);

	display->is_dirty = true;
	while (app_running()) {

		// platform_update_input();
		app_update();

		render();
		display->is_dirty = false;
		vTaskDelay(pdMS_TO_TICKS(33));
	}
	app_destroy();

	// TODO: Implement some low power mode?
}

