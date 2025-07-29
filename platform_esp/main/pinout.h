#ifndef PINOUT_H
#define PINOUT_H

#define LCD_HOST  SPI2_HOST

#define LCD_TRANSFER_ROWS      8
#define LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define LCD_BK_LIGHT_ON_LEVEL  1
#define LCD_BK_LIGHT_OFF_LEVEL !LCD_BK_LIGHT_ON_LEVEL
#define PIN_NUM_SCLK           18
#define PIN_NUM_MOSI           23
#define PIN_NUM_MISO           21
#define PIN_NUM_LCD_DC         13
#define PIN_NUM_LCD_RST        4
#define PIN_NUM_LCD_CS         5
#define PIN_NUM_BK_LIGHT       2
#define PIN_NUM_TOUCH_CS       15

#define LCD_HEIGHT             240
#define LCD_WIDTH              320

#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

// number of display lines in each draw buffer
#define LVGL_DRAW_BUF_LINES    20
#define LVGL_TICK_PERIOD_MS    2
#define LVGL_TASK_MAX_DELAY_MS 500
#define LVGL_TASK_MIN_DELAY_MS 1000 / CONFIG_FREERTOS_HZ
#define LVGL_TASK_STACK_SIZE   (4 * 1024)
#define LVGL_TASK_PRIORITY     2

#define GPIO_AXIS_X		33
#define GPIO_AXIS_Y		32
#define ADC_AXIS_X		ADC_CHANNEL_5
#define ADC_AXIS_Y		ADC_CHANNEL_4
#define GPIO_BUTTON		25
#define JOYSTICK_MAX		4095
#define JOYSTICK_IDLE		(4095 / 2)
#define JOYSTICK_DEADZONE	(3 * JOYSTICK_IDLE / 4)
#define ADC_BUFFER_SIZE		1024

#endif // PINOUT_H
