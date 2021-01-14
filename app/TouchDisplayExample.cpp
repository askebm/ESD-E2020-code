#include <ESD/gui/TouchDisplay.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

	TouchDisplay disp;

	while (true) {
		disp.process();
	}

	return 0;
}
