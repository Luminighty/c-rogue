#include "dungeon.h"
#include "config.h"
#include "display.h"
#include "math.h"
#include "palette.h"
#include "random.h"
#include <assert.h>
#include <stdio.h>


static inline Glyph tile_glyph(Tile t) {
	switch (t) {
	case TILE_WALL: return glyph('#', GREEN, BLACK);
	case TILE_FLOOR: return glyph('.', GRAY(0x22), BLACK);
	default: assert(0); return glyph('?', RED, BLUE);
	}
}


void dungeon_draw(Dungeon* dungeon) {
	dungeon_foreach(x, y) {
		Tile t = dungeon->map[y][x];
		Glyph g = tile_glyph(t);
		display_putchar(x, y, g, ZINDEX_FORCE);
	}
}


Tile dungeon_get_tile(Dungeon* dungeon, int x, int y) {
	return dungeon->map[y][x];
}

bool dungeon_is_solid(Dungeon* dungeon, int x, int y) {
	switch (dungeon_get_tile(dungeon, x, y)) {
	case TILE_WALL:
		return true;
	default:
		return false;
	}
}


// ========== ================== ========== 
// ========== DUNGEON GENERATION ========== 
// ========== ================== ========== 

inline static void map_set(Dungeon* dungeon, int x, int y, Tile tile) {
	assert(x >= 0 && x < SCREEN_WIDTH);
	assert(y >= 0 && y < SCREEN_HEIGHT);
	dungeon->map[y][x] = tile;
}

#define for_line(x, y, from_x, from_y, condition, step)\
	for (int (y) = (from_y), (x) = (from_x); (condition); (step))

#define for_rect(x, y, from_x, from_y, to_x, to_y)\
	for (int (y) = (from_y); (y) < (to_y); (y)++)\
	for (int (x) = (from_x); (x) < (to_x); (x)++)

inline static void apply_vertical_tunnel(Dungeon* dungeon, int y0, int y1, int x) {
	int min_y = y0 < y1 ? y0 : y1;
	int max_y = y0 > y1 ? y0 : y1;
	for (int y = min_y; y <= max_y; y++)
		map_set(dungeon, x, y, TILE_FLOOR);
}

inline static void apply_horizontal_tunnel(Dungeon* dungeon, int x0, int x1, int y) {
	int min_x = x0 < x1 ? x0 : x1;
	int max_x = x0 > x1 ? x0 : x1;
	for (int x = min_x; x <= max_x; x++)
		map_set(dungeon, x, y, TILE_FLOOR);
}

static void room_try_add(Dungeon* dungeon) {
	static const int MIN_SIZE = 6;
	static const int MAX_SIZE = 10;

	int w = random_rangei(MIN_SIZE, MAX_SIZE);
	int h = random_rangei(MIN_SIZE, MAX_SIZE);
	int x = random_rangei(1, SCREEN_WIDTH - w - 1) - 1;
	int y = random_rangei(1, SCREEN_HEIGHT - h - 1) - 1;
	Rect room = rect_create(x, y, w, h);
	bool is_valid_spot = true;
	room_foreach(dungeon, room_idx) {
		bool intersects = rect_intersect(&room, &dungeon->rooms[room_idx]);
		if (intersects) {
			is_valid_spot = false;
			break;
		}
	}
	if (!is_valid_spot)
		return;
	for_rect(x, y, room.x0 + 1, room.y0 + 1, room.x1, room.y1)
		map_set(dungeon, x, y, TILE_FLOOR);

	if (dungeon->room_count > 0) {
		Vec2 new = rect_center(&room);
		Vec2 prev = rect_center(&dungeon->rooms[dungeon->room_count - 1]);

		if (random_bool()) {
			apply_horizontal_tunnel(dungeon, prev.x, new.x, prev.y);
			apply_vertical_tunnel(dungeon, prev.y, new.y, new.x);
		} else {
			apply_vertical_tunnel(dungeon, prev.y, new.y, prev.x);
			apply_horizontal_tunnel(dungeon, prev.x, new.x, new.y);
		}
	}

	dungeon->rooms[dungeon->room_count++] = room;
}

Dungeon dungeon_generate() {
	Dungeon dungeon = {0};
	for_rect(x, y, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) map_set(&dungeon, x, y, TILE_WALL);

	for (int i = 0; i < MAX_ROOMS; i++)
		room_try_add(&dungeon);

	// DEBUG: To ensure we generate all rooms.
	// while(dungeon.room_count < MAX_ROOMS)
	// 	room_try_add(&dungeon);

	return dungeon;
}

