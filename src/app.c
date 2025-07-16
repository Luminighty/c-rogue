#include "app.h"

#include "game.h"
#include "random.h"


void app_init() {
	random_init();
	game_init();
}


void app_update() {
	game_update();
	game_draw();
}


void app_destroy() {
	game_destroy();
}


bool app_running() {
	return true;
}

