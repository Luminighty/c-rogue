#include "random.h"
#include <stdlib.h>
#include <time.h>

void random_init() {
	srand(time(NULL));
}

int random_rangei(int min, int max) {
	return min + rand() % (max - min);
}

bool random_bool() {
	return rand() % 2;
}
