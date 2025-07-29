#ifndef FOV_H
#define FOV_H

#include <stdbool.h>


void fov_2d(
	int x, int y, int max_distance,
	bool (*is_opaque)(int, int, void*), 
	void (*on_visible)(int, int, void*), 
	void* data
);


#endif // FOV_H
