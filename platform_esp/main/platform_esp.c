#include <stdbool.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app.h"
#include "display.h"
#include "palette.h"
#include "pinout.h"
#include "platform_input.h"
#include "platform_display.h"


// NOTE: For some reason the display I have uses rbg?
//#define rgb565(r, g, b) ((((r) & 0xF8) << 8) | (((b) & 0xFC) << 3) | (((g) & 0xF8) >> 3))
#define rgb565(r, g, b) ((((r) & 0xF8) << 8) | (((b) & 0xF8) << 3) | (((g) & 0xFC) >> 2))
#define to_esp_rgb(rgb) rgb565(rgb >> 16, (rgb & 0xFF00) >> 8, rgb & 0xFF)


static inline void render() {
	Display* display = display_get();
	if (!display->is_dirty)
		return;
	for (int y = 0; y < 30; y++) {
		for (int x = 0; x < 40; x++) {
			char g = display->glyphs[y][x].glyph;
			int fg = display->glyphs[y][x].fg;
			int bg = display->glyphs[y][x].bg;
			draw_char(x * 8, 0, g, to_esp_rgb(fg), to_esp_rgb(bg));
		}
		send_chunk(y);
	}
}


void app_main(void) {
	platform_init_display();
	platform_init_buttons();

	// NOTE: This causes some stack overflow for some reason?
	app_init();
	Display* display = display_get();

	display_putstr(3, 3, "Hello", 0xFF, 0x00, 0);
	ESP_LOGI("TEST", "Color: %x", to_esp_rgb(GRAY(0x60)));

	display->is_dirty = true;
	while (app_running()) {
		platform_update_input();
		app_update();

		render();
		display->is_dirty = false;
		vTaskDelay(pdMS_TO_TICKS(33));
	}
	app_destroy();

	// TODO: Implement some low power mode?
}

