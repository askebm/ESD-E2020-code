#include <ESD/driver/GPIO.h>
#include <BarCodeScannerTask/BarCodeScannerTask.hpp>
#include <NumpadTask/NumpadTask.hpp>
#include <iostream>

#include <cstdlib>
#include <iostream>
#include <array>
#include <memory>
#include <mutex>
#include <chrono>

#include <Task/Task.hpp>
#include <queue>
#include <thread>
#include <unistd.h>

#define SAFE_COUT(x) { static std::mutex mtx_cout; mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }

using namespace std::chrono_literals;

enum STATES { LOCKED, IDLE, SHOPPING, PAYMENT } ;    
enum LOCKED_SUBSTATES { WAITFORPIN} ;



void LOCKED_sm(Event* currentEvent, STATES &sm_State)
{
    LOCKED_SUBSTATES sm_LockedSubState = WAITFORPIN;
    std::string passcode;
    while(1){
        switch(sm_LockedSubState) {
            case WAITFORPIN:
                if (currentEvent->id == NumpadDriverTask::Command::GET_PIN)
                {
                    passcode += currentEvent->getData<std::string>();
                    if(passcode == "1234"){
                        // Correct code - Change to IDLE state
                        SAFE_COUT("Correct passcode - Transition to IDLE state \n");
                        sm_State = STATES::IDLE;
                        return;
                    }
                }
                break;
    }
    }
     
    }


typedef std::pair< std::queue<Event>*, std::mutex*> QMpair;

// main function for full cashier system.


std::shared_ptr<Event> nextEvent( std::vector<QMpair> v )
{
    for (auto& qmp : v)
    {
        auto currentEvent = Task::getEventFromQueue(*qmp.first,*qmp.second); 
        if (currentEvent)
        {
            return currentEvent;
        }

    }
   return nullptr; 
}

void sendEvent(std::shared_ptr<Event> e, std::queue<Event>* q, std::mutex* m)
{
		std::lock_guard<std::mutex> lock(*m);
		q->push(*e);
}

void enviromentAgent( std::vector<QMpair> v)
{
    std::this_thread::sleep_for(1000ms);
    auto eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::GET_PIN,std::string("1235")));
    std::cout << "[Event] " << "Wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::cout << "[Event] " << "Wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::cout << "[Event] " << "Wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::cout << "[Event] " << "Wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::cout << "[Event] " << "Wrong pin code" << std::endl;
    std::this_thread::sleep_for(1000ms);


    std::cout << "[Event] " << "Correct pin code" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::GET_PIN,std::string("1234")));
    sendEvent(eptr,v[1].first, v[1].second);
    
}

int main(int argc, char const *argv[])
{

    std::vector<Task*> registeredTasks; // All tasks that the system will attempt to start
    std::vector<QMpair> qmpairs;


	// barcodescanner event queue
    std::mutex mtx_events_barcodescanner;
	std::queue<Event> events_barcodescanner;
    BarCodeScannerTask barcodeScannerTask("BarCodeScannerTask", events_barcodescanner, mtx_events_barcodescanner);
    registeredTasks.push_back(&barcodeScannerTask);
	QMpair qmp;
    qmp.first = &events_barcodescanner;
    qmp.second = &mtx_events_barcodescanner;
    qmpairs.push_back(qmp);
    


	// keypad event queue
	std::mutex mtx_events_keypad;
	std::queue<Event> events_keypad;
    NumpadDriverTask keypadTask("KeypadTask", events_barcodescanner, mtx_events_barcodescanner);
    registeredTasks.push_back(&keypadTask);
    qmp.first = &events_keypad;
    qmp.second = &mtx_events_keypad;
    qmpairs.push_back(qmp);



    // Start all registered tasks
    /*
    for (unsigned int i = 0; i < registeredTasks.size();i++)
    {
        if ( registeredTasks[i]->start() != true)
        {
		    std::cerr << "Could not start the " << registeredTasks[i]->name << " task." << std::endl;
		    exit(-1); // unrecoverable, terminate execution
        }
    }
*/
    // All Tasks started without error


    // Start Enviroment simulator
    std::thread simAgent(enviromentAgent, qmpairs);


    // Start stationbox locked
    STATES sm_State = LOCKED;
    
    while(1){
        // Dont trash CPU
         std::this_thread::sleep_for(20ms);
        // Grab an event if there is any
        auto currentEvent = nextEvent(qmpairs);


    std::cout << "State: " << sm_State << std::endl;
    // State machine
    switch (sm_State) {
        case LOCKED: 
           // Station box is locked  
           // Unmute the keypad task and wait for a pin
            std::cout << "Here" << std::endl;
            keypadTask.unmute();
            keypadTask.sendEventToTask(Event(NumpadDriverTask::GET_PIN));
            
             while (!currentEvent)
             {
                currentEvent = nextEvent(qmpairs);
                
             }
             std::cout << "Got event" << std::endl;

                // Recived event, check type
                if (currentEvent->id == NumpadDriverTask::Command::GET_PIN)
                {
                    std::cout << "Event is " << NumpadDriverTask::Command::GET_PIN << std::endl;
                    // Pin code recieved
                    if ( currentEvent->getData<std::string>() == "1234")
                    {
                        std::cout << "Correct passcode, transition to IDLE" << std::endl;
                        sm_State = STATES::IDLE;
                        keypadTask.mute();
                    }
                }



            break;
        case IDLE:
            // Unmute keypad and barcode scanner to wait for input
        break;        

        case SHOPPING:

        break;

        case PAYMENT:

        break;

            
    }





     



}
	return 0;
}




