
/*! \class NumpadDriverTask : public NumpadDriver
 *  \brief Brief class description
 *
 *  Detailed description
 */
#pragma once

#include "include/driver/NumpadDriver/NumpadDriver.hpp"
#include "Event.hpp"
#include "include/Task/Task.hpp"
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>

class NumpadDriverTask : public Task
{
public:

	// Types.
	using Task::Task;
	using DATA = std::array<int,4>;

	enum Command
	{
		GET_PIN = 1, 
		CLEAR   = 2
	};

	// Messages.
	struct Msg 
	{
		DATA data;
	};

	// Methods.
	NumpadDriverTask() = delete;
	~NumpadDriverTask();

	virtual void run() override;
	virtual bool init() override;

protected:

	// Attributes.
	NumpadDriver       npd;
	DATA               data;

};



