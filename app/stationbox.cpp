#include <ESD/driver/GPIO.h>
#include <ESD/stationBox.hpp>
#include <iostream>

#include <cstdlib>
#include <iostream>
#include <array>
#include <mutex>
#include <chrono>

#include <Task/Task.hpp>

#define SAFE_COUT(x) { static std::mutex mtx_cout; mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }
using namespace std::chrono_literals;


// main function for full cashier system.

int main(int argc, char const *argv[])
{

	// main event queue
	std::mutex mtx_events;
	std::queue<Event> events;

	// instantiate task (can be called without name)
	StationBox sb("StationBox", events, mtx_events);

	// start task
	if (not sb.start())
	{
		std::cerr << "Could not start the " << sb.name << " task." << std::endl;
		exit(-1);
	}
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("1")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("2")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("3")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("4")));

while(true){};

	return 0;
}
