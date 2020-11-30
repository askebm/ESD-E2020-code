#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <Task/Task.hpp>

std::mutex mtx_cout;
#define SAFE_COUT(x) { mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }


class MyTask final : public Task
{
public:

	// must be defined to use Base class constructor
	using Task::Task;
	MyTask() = delete;
	~MyTask() { /* must be defined */ };

	enum Events
	{
		SOME_EVENT,
		ANOTHER_EVENT,
		ONE_MORE_EVENT
	};

	struct MyDataFormat
	{
		std::string text;
		std::array<double, 2> nums;
	};

protected:

	virtual bool
	init() { return true; };

	virtual void
	run()
	{
		sleep(1);

		static size_t counter = 0;
		SAFE_COUT("[task] doing work... [" << ++counter << "]" << std::endl);

		// check for events
		auto event = this->readLatestEvent();
		if (event and *event == ONE_MORE_EVENT)
			SAFE_COUT("[task] got event: " << event->getData<std::string>() << std::endl);

		// send a random event
		if (counter % 5 == 0)
		{
			auto id = Events(rand() % 2);
			Event* event;

			if (id == SOME_EVENT)
			{
				std::string data = "random number: " + std::to_string(rand() % 100);
				event = new Event(id, data);
			}
			else
			if (id == ANOTHER_EVENT)
			{
				auto data = MyDataFormat{ "Hello", { 3.14, 2.71 } };
				event = new Event(id, data);
			}

			this->sendEventFromTask(*event);
			delete event;
		}
	};
};

int
main(int argc, char const *argv[])
{

	// main event queue
	std::mutex mtx_events;
	std::queue<Event> events;

	// instantiate task
	MyTask task(events, mtx_events);

	// start task
	if (not task.start())
		std::cerr << "Could not start the task." << std::endl;

	// main loop
	while(true)
	{
		static size_t t = 0;
		SAFE_COUT("[main] checking for events... [" << std::to_string(++t) << "]" << std::endl);
		sleep(1);
		
		// send an event to task
		if (t % 4 == 0)
		{
			SAFE_COUT("[main] sending event..." << std::endl);
			auto e = Event(task.ONE_MORE_EVENT, std::string("This is a msg from main!"));
			task.sendEventToTask(e);
		}

		// check for events from tasks
		std::lock_guard<std::mutex> lock(mtx_events);
		if (events.empty())
			continue;

		// handle incoming events (also discards lock)
		auto event = Task::get_event(events, lock);

		// or get event manually from queue
		// auto event = events.front();
		// events.pop();
		// lock.~lock_guard();

		switch (event)
		{

		case MyTask::SOME_EVENT:

			SAFE_COUT("[main] Got SOME_EVENT:" << std::endl);
			SAFE_COUT(event.getData<std::string>() << std::endl);
			break;

		case MyTask::ANOTHER_EVENT:

			SAFE_COUT("[main] Got ANOTHER_EVENT:" << std::endl);
			MyTask::MyDataFormat data;
			data << event;
			SAFE_COUT("[main] MyDataFormat.nums[1] = " << data.nums[1] << std::endl);
			break;
		}

	} // while

	// exit
	return 0;
}
