#include "math.h"

Vec2 vec2_add(Vec2 left, Vec2 right) {
	return (Vec2){.x=left.x+right.x, .y=left.y+right.y};

}

Rect rect_create(int x, int y, int w, int h) {
	return (Rect){.x0 = x, .x1 = x + w, .y0 = y, .y1 = y + h};
}

bool rect_intersect(Rect* left, Rect* right) {
	return left->x0 <= right->x1 &&
		left->x1 >= right->x0 &&
		left->y0 <= right->y1 &&
		left->y1 >= right->y0
	;
}

Vec2 rect_center(Rect* rect) {
	return (Vec2){
		.x = (rect->x0 + rect->x1) / 2,
		.y = (rect->y0 + rect->y1) / 2,
	};
}

