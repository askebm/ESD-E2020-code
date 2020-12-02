#include "include/NumpadTask/NumpadTask.hpp"
#include <fcntl.h>
#include <functional>
#include <mqueue.h>
#include <pthread.h>
#include <thread>

// NumpadDriverTask::NumpadDriverTask() { }

NumpadDriverTask::~NumpadDriverTask() { }

bool NumpadDriverTask::init()
{
	this->npd.init();
}

void NumpadDriverTask::run()
{

	// Retrieve the Event in the queue
	auto event = this->readLatestEvent();

	// if CLEAR is in the queue, flush DATA (flush = set all values to zero)
	if (event->id == Command::CLEAR)
	{
		this->data.fill(-1);
		return;
	}

	// if GET_PIN is in the queue
	if (event->id == Command::GET_PIN)
	{

		// get the following 4 pin inputs
		size_t counter = 0;
		Event* event;

		while (counter < 4)
		{
			auto pin_in = this->npd.getValue();
			if (pin_in != NULL)
			{
				this->data[counter] = pin_in;
				++counter;
			}
		}

		event = new Event(Command::GET_PIN,this->data);
		this->sendEventFromTask(Event(Command::GET_PIN,this->data));
		delete event;
		
		// clear the data object
		this->data.fill(-1);
	}
}
