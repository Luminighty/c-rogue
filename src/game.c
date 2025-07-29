#include "game.h"
#include "display.h"
#include "dungeon.h"
#include "input.h"


Game game = {0};


void game_init() {
	dungeon_generate(&game.dungeon);

	Vec2 start = rect_center(&game.dungeon.rooms[0]);
	game.player = player_create(start);
	player_fov(&game.player);
}


void game_destroy() {
}


void game_update() {
	Input* input = input_get();
	player_update(&game.player);
	if (input->restart) {
		game_destroy();
		game_init();
	}
}


void game_draw() {
	display_clear();
	dungeon_draw(&game.dungeon);
	player_draw(&game.player);
}

