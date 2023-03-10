#include "Func.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

int main() {

	while (true) {
		DrawMap();
		DrawBlock();
		DropBlock();
		BlockToGround();
		RemoveLine();
		InputKey();
	}

	return 0;
}

