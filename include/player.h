#ifndef PLAYER_H
#define PLAYER_H


#include "math.h"


typedef struct {
	Vec2 position;
} Player;


Player player_create(Vec2 spawn);
void player_draw(Player* player);
void player_update(Player* player);


#endif // PLAYER_H
