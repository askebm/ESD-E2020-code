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
	MyTask task("MyTask", events, mtx_events);

	// start task
	if (not task.start())
	{
		std::cerr << "Could not start the " << task.name << " task." << std::endl;
		exit(-1);
	}

	// mute task to ignore incoming events from task
	// task.mute();

	// kill the task if you really don't like it (even force it with a bool)
	// task.kill(true);

	// main loop
	while(true)
	{
		static size_t t = 0;
		SAFE_COUT("[main] checking for events... [" << std::to_string(++t) << "]" << std::endl);
		
		std::this_thread::sleep_for(1s);
		
		// send an event to task
		if (t % 4 == 0)
		{
			SAFE_COUT("[main] sending event..." << std::endl);
			auto e = Event(MyTask::ONE_MORE_EVENT, std::string("This is a msg from main!"));
			task.sendEventToTask(e);
		}

		// check for events from tasks (using helper method)
		auto event = Task::getEventFromQueue(events, mtx_events);
		if (not event)
			continue;

		// check for events from tasks (manual, but gives obj instead of ptr)
		// std::lock_guard<std::mutex> lock(mtx_events);
		// if (events.empty())
		// 	continue;
		// auto event = events.front();
		// events.pop();
		// lock.~lock_guard();

		// handle incoming events
		switch (*event)
		{

		case MyTask::SOME_EVENT:

			SAFE_COUT("[main] Got SOME_EVENT:" << std::endl);
			SAFE_COUT(event->getData<std::string>() << std::endl);
			break;

		case MyTask::ANOTHER_EVENT:

			SAFE_COUT("[main] Got ANOTHER_EVENT:" << std::endl);
			MyTask::MyDataFormat data;
			data << *event;
			SAFE_COUT("[main] MyDataFormat.nums[1] = " << data.nums[1] << std::endl);
			break;
		}

	} // while

	// exit program
	return 0;
}
