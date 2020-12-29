#ifndef STATIONBOX_H
#define STATIONBOX_H

#include <memory>
#include <stdio.h>
#include <string>
#include <queue>

#include <Task/Task.hpp>


class StationBox : public Task

{
private:
/*! \enum STATE
 *
 *  States for stationbox
 */
enum STATES { LOCKED, IDLE, SHOPPING, PAYMENT } mState;    
enum LOCKED_SUBSTATES { WAITFOR1, WAITFOR2, WAITFOR3, WAITFOR4  } mLockedSubState = WAITFOR1;


std::shared_ptr<Event> mCurrentEvent;

void LOCKED_sm();







public:
	// must be defined to use Base class constructor
	using Task::Task;
	StationBox() = delete;
	~StationBox() {};

    enum Events { GotPinDigit = 1001 };

    bool init();
    void run();
};

#endif /* STATIONBOX_H */
