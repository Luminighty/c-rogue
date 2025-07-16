#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "math.h"


typedef struct {
	Vec2 delta;
	bool restart;
} Input;


Input* input_get();


#endif // INPUT_H
