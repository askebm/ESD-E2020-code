#include <Task/Task.hpp>

Task::Task(std::queue<Event>& events_out, std::mutex& mtx_events_out)
	: events_out(events_out), mtx_events_out(mtx_events_out)
{
	this->is_alive = false;
	this->is_muted = true;
}

Task::~Task()
{
	if (this->is_alive)
		this->kill();
}
Event
Task::get_event(std::queue<Event>& events, std::lock_guard<std::mutex>& lock)
{
	auto event = events.front();
	events.pop();
	lock.~lock_guard();
	return event;
}

bool
Task::start()
{
	// initialize
	if (not this->init())
	{
		std::cerr << "Could not initialize task..." << std::endl;
		return false;
	}

	// start thread
	handle = std::thread([&]()
	{
		while(this->is_alive)
			this->run();
	});
	
	this->is_alive = true;
	this->is_muted = false;

	return true;
}

void
Task::kill(bool force)
{
	std::cout << "Killing task..." << std::endl;

	if (force)
		pthread_cancel(handle.native_handle());

	if (handle.joinable())
	{
		this->is_alive = false;
		handle.join();
		std::cout << "Task was killed." << std::endl;
	}
}

void
Task::mute()
{
	this->is_muted = true;
}

void
Task::unmute()
{
	this->is_muted = false;
}

void
Task::sendEventToTask(const Event& e)
{
	std::lock_guard<std::mutex> lock(mtx_events_in);
	events_in.push(e);
}

void
Task::sendEventFromTask(const Event& e)
{
	if (not this->is_muted)
	{
		std::lock_guard<std::mutex> lock(mtx_events_out);
		this->events_out.push(e);
	}
}

std::shared_ptr<Event>
Task::readLatestEvent()
{
	std::lock_guard<std::mutex> lock(mtx_events_in);

	if (not events_in.empty())
	{
		auto e = this->events_in.front();
		this->events_in.pop();
		return std::make_shared<Event>(e);
	}

	else
		return nullptr;
}