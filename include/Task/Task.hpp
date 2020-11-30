#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <memory>

#include <Event/Event.hpp>

class Task
{
private:

	std::thread handle;
	std::string name = "";

	std::atomic<bool> is_alive;
	std::atomic<bool> is_muted;

	std::mutex mtx_events_in;
	std::queue<Event> events_in;

	std::mutex& mtx_events_out;
	std::queue<Event>& events_out;

protected:

	virtual bool
	init() = 0;

	virtual void
	run() = 0;
	
	void
	sendEventFromTask(const Event& e);

	std::shared_ptr<Event>
	readLatestEvent();

public:

	Task() = delete;
	Task(std::queue<Event>& events_out, std::mutex& mtx_events_out);
	virtual ~Task();

	bool
	start();

	void
	kill(bool force = false);

	void
	mute();

	void
	unmute();

	void
	sendEventToTask(const Event& e);
	
	static Event
	get_event(std::queue<Event>& events, std::lock_guard<std::mutex>& lock);

};