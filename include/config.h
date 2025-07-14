#ifndef CONFIG_H
#define CONFIG_H

// Screen Dimensions based on characters
#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 40
#define SCREEN_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

#define CHR_WIDTH 8
#define CHR_HEIGHT 8

#define CHR_SCALE 3

// Window Dimensions based on pixels
#define WINDOW_WIDTH (CHR_WIDTH * SCREEN_WIDTH)
#define WINDOW_HEIGHT (CHR_HEIGHT * SCREEN_HEIGHT)

// Scaled Window Dimensions
#define TARGET_WINDOW_WIDTH (WINDOW_WIDTH * CHR_SCALE)
#define TARGET_WINDOW_HEIGHT (WINDOW_HEIGHT * CHR_SCALE)
#define WINDOW_TITLE "Rogue"


#endif //  CONFIG_H
