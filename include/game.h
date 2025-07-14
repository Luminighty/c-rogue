#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "dungeon.h"


typedef struct {
	Player player;
	Dungeon dungeon;
} Game;


extern Game game;

void game_init();
void game_destroy();
void game_update();
void game_draw();


#endif // GAME_H
