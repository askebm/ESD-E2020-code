#include <ESD/driver/GPIO.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
	auto led_pin = new GPIO("984");
	led_pin->exportPin();
	led_pin->setPinDirection("out");

	std::cout << "Hello GPIO" << std::endl;

	return 0;
}

