#ifndef MATH_H
#define MATH_H

#include <stdbool.h>

typedef struct {
	int x, y;
} Vec2;

Vec2 vec2_add(Vec2 left, Vec2 right);


typedef struct {
	int x0;
	int x1;
	int y0;
	int y1;
} Rect;

Rect rect_create(int x, int y, int w, int h);
bool rect_intersect(Rect* left, Rect* right);
Vec2 rect_center(Rect* rect);



#endif // MATH_H
