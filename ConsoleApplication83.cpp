#include "pramougol.h"
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

int main() {
	system("color 10");
	Pramougol obj = Pramougol(CENTER);
	for (int i = 0; i < 40; ++i) {
		obj.UpdateDirection(LEFT_POZITION);
		obj.View();
	}
	for (int i = 0; i < 40; ++i) {
		obj.UpdateDirection(RIGHT_POZITION);
		obj.View();
	}
}