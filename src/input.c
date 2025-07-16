#include "input.h"

static Input input = {0};

Input* input_get() {
	return &input;
}
