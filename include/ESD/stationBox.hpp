#ifndef STATIONBOX_H
#define STATIONBOX_H

#include <stdio.h>
#include <string>
#include <queue>


class Event
{
private:    

public:
    Event(){};
    int name;
    int* data;
    int* getData(){return data;}
};



class StationBox
{
private:
/*! \enum STATE
 *
 *  States for stationbox
 */
enum STATES { LOCKED, IDLE, SHOPPING, PAYMENT } mState;    
enum LOCKED_SUBSTATES { WAITFOR1, WAITFOR2, WAITFOR3, WAITFOR4  } mLockedSubState = WAITFOR1;
Event mCurrentEvent;


void LOCKED_sm();






// TEMP 
std::queue<Event> event_in;
std::queue<Event> event_out;
Event readLatestEvent(bool){
    Event event = event_in.front();
    event_in.pop();
    return event;
};

public:
    StationBox();
    int init();
    int run();
     ~StationBox();
};

#endif /* STATIONBOX_H */
