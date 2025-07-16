#include "platform_input.h"

#include "pinout.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"


static adc_oneshot_unit_handle_t adc1_handle;


void platform_init_buttons() {
	adc_oneshot_unit_init_cfg_t init_cfg = {
		.unit_id = ADC_UNIT_1,
	};
	adc_oneshot_new_unit(&init_cfg, &adc1_handle);

	// Configure X and Y channels
	adc_oneshot_chan_cfg_t chan_cfg = {
		.atten = ADC_ATTEN_DB_12,  // Equivalent to old DB_11
		.bitwidth = ADC_BITWIDTH_12,
	};
	ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_AXIS_X, &chan_cfg)); // GPIO 33
	ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_AXIS_Y, &chan_cfg)); // GPIO 32

	uint64_t bit_mask = 1ULL << GPIO_BUTTON;
	gpio_config_t io_conf = {
		.pin_bit_mask = bit_mask,
		.mode = GPIO_MODE_INPUT,
		.pull_up_en = GPIO_PULLUP_ENABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf);
}

int prev_joystick_x;
int prev_joystick_y;
int prev_joystick_btn;

int x, y = 0;

void platform_update_input() {
	int joystick_btn = gpio_get_level(GPIO_BUTTON);
	int x_val, y_val = 0;
	adc_oneshot_read(adc1_handle, ADC_AXIS_X, &x_val);
	adc_oneshot_read(adc1_handle, ADC_AXIS_Y, &y_val);
	int dx = abs(x_val - JOYSTICK_IDLE);
	int dy = abs(y_val - JOYSTICK_IDLE);
	int joystick_x = 0;
	int joystick_y = 0;
	if (dx > JOYSTICK_DEADZONE || dy > JOYSTICK_DEADZONE) {
		if (dx > JOYSTICK_DEADZONE / 2)
			joystick_x = x_val > JOYSTICK_IDLE ? 1 : -1;
		if (dy > JOYSTICK_DEADZONE / 2)
			joystick_y = y_val > JOYSTICK_IDLE ? 1 : -1;
	}
	if (joystick_x != prev_joystick_x)
		y += joystick_x;
	if (joystick_y != prev_joystick_y)
		x += joystick_y;
	prev_joystick_x = joystick_x;
	prev_joystick_y = joystick_y;
	prev_joystick_btn = joystick_btn;
}

