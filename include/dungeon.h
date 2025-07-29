#ifndef DUNGEON_H
#define DUNGEON_H

#include "config.h"
#include "math.h"

#define MAX_ROOMS 16

typedef enum {
	TILE_FLOOR,
	TILE_WALL,
} Tile;


typedef struct {
	Tile map[SCREEN_HEIGHT][SCREEN_WIDTH];
	Rect rooms[MAX_ROOMS];
	int room_count;
	bool visible[SCREEN_HEIGHT][SCREEN_WIDTH];
	bool discovered[SCREEN_HEIGHT][SCREEN_WIDTH];
} Dungeon;


void dungeon_generate(Dungeon* dungeon);
void dungeon_draw(Dungeon* dungeon);
Tile dungeon_get_tile(Dungeon* dungeon, int x, int y);
bool dungeon_is_solid(Dungeon* dungeon, int x, int y);
void dungeon_update_fov(Dungeon* dungeon, int x, int y, int dist);

#define dungeon_foreach(x, y)\
	for(int y = 0; y < SCREEN_HEIGHT; y++)\
	for(int x = 0; x < SCREEN_WIDTH; x++)

#define room_foreach(dungeon, room_idx)\
	for(int room_idx = 0; room_idx < dungeon->room_count; room_idx++)

#endif // DUNGEON_H
