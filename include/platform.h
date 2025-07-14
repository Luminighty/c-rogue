#ifndef PLATFORM_H
#define PLATFORM_H

#include "input.h"
#include <stdbool.h>

void platform_init();
void platform_destroy();
void platform_render();
bool platform_is_running();
void platform_input(Input* input);

#endif // PLATFORM_H
