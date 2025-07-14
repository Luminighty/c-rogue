#include "config.h"
#include "game.h"
#include "platform.h"
#include "input.h"
#include "random.h"


int main() {
	random_init();
	game_init();

	platform_init();
	while (platform_is_running()) {
		platform_input(&input);

		game_update();
		game_draw();

		platform_render();
	}
	platform_destroy();

	game_destroy();

	return 0;
}
