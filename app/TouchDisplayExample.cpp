#include <ESD/gui/sdl2/TouchDisplaySDL2.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

	TouchDisplaySDL2 disp;

	while (true) {
		disp.process();
	}

	return 0;
}
