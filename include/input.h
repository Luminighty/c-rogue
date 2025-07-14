#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include "math.h"


typedef struct {
	Vec2 delta;

	bool restart;
} Input;

extern Input input;


#endif // INPUT_H
