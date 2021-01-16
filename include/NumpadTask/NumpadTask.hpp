
/*! \class NumpadDriverTask : public NumpadDriver
 *  \brief Brief class description
 *
 *  Detailed description
 */
#pragma once

#include <driver/NumpadDriver/NumpadDriver.hpp>
#include <Event/Event.hpp>
#include <Task/Task.hpp>
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
		GET_PIN = 1001, 
		CLEAR   = 1002,
		ENTER   = 1003,          // Barcode numbers pressed before this must be in data
        TOTAL   = 1004,
        CANCEL  = 1005,
        CASH    = 1006,
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



