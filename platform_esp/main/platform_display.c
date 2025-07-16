#include "platform_display.h"
#include "pinout.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_types.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_lcd_ili9341.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "driver/gpio.h"

extern const uint8_t font_bitmap[16 * 16][8];

static uint16_t framebuffer[LCD_WIDTH * LCD_TRANSFER_ROWS];
static esp_lcd_panel_handle_t panel;

#define rgb565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))


void platform_init_display(void) {
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << PIN_NUM_BK_LIGHT
    };
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_SCLK,
        .mosi_io_num = PIN_NUM_MOSI,
        // .miso_io_num = PIN_NUM_MISO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_TRANSFER_ROWS * LCD_WIDTH * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_NUM_LCD_DC,
        .cs_gpio_num = PIN_NUM_LCD_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = LCD_CMD_BITS,
        .lcd_param_bits = LCD_PARAM_BITS,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_LCD_RST,
        .rgb_endian = LCD_RGB_ENDIAN_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel, true));

    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel, true));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel, true, true));

    gpio_set_level(PIN_NUM_BK_LIGHT, 1);
}


void begin_frame(uint16_t clear_color) {
}


void draw_char(int x, int y, char g, uint16_t fg, uint16_t bg) {
	for (int row = 0; row < 8; ++row) {
		uint8_t bits = font_bitmap[(uint8_t)g][row];
		int py = y + row;
		for (int col = 0; col < 8; ++col) {
			bool pixel = bits & (0b1 << col);
			int px = x + col;
			framebuffer[py * LCD_WIDTH + px] = pixel ? fg : bg;
		}
	}
}

void send_chunk(int row) {
	esp_lcd_panel_draw_bitmap(
		panel, 
		0, row * 8,
		LCD_WIDTH, (row + LCD_TRANSFER_ROW_CHARS) * 8,
		framebuffer
	);
}

