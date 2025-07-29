#include "player.h"
#include "display.h"
#include "game.h"
#include "input.h"
#include "math.h"
#include "palette.h"
#include "dungeon.h"

static Glyph glyph = glyph(0x01, WHITE, BLACK);

Player player_create(Vec2 spawn) {
	Player p = {0};
	p.position = spawn;
	return p;
}


void player_draw(Player* player) {
	display_putchar(player->position.x, player->position.y, glyph, 10);
}

void player_update(Player* player) {
	Input* input = input_get();
	Vec2 new_pos = vec2_add(player->position, input->delta);

	if (!dungeon_is_solid(&game.dungeon, new_pos.x, new_pos.y)) {
		player->position = new_pos;
		player_fov(player);
	}
}

void player_fov(Player* player) {
	dungeon_update_fov(&game.dungeon, player->position.x, player->position.y, 4);
}
