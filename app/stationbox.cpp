#include <ESD/driver/GPIO.h>
#include <BarCodeScannerTask/BarCodeScannerTask.hpp>
#include <NumpadTask/NumpadTask.hpp>
#include <ESD/gui/TouchDisplayBackend.hpp>
#include <DisplayDriverTask/DisplayDriverTask.hpp>
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

#include "../extern/interface_lib/receipt.hpp"


#define SAFE_COUT(x) { static std::mutex mtx_cout; mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }

using namespace std::chrono_literals;

enum STATES { LOCKED, IDLE, SHOPPING, PAYMENT } ;    
namespace LOCKEDstates{
enum LOCKED_SUBSTATES { WAITFORPIN} ;
}
namespace PAYMENTstates{
enum PAYMENT_SUBSTATES {UNDECIDED, WAITFORCARD, WAITFORCASH, WAITFORPIN, WAITFOROK, WAITFORBANK};
}
std::string STATENAME[4] = {"LOCKED" ,"IDLE", "SHOPPING", "PAYMENT"};

//TODO
//
//TOUCH EVENTS
namespace TouchDisplayTask {  

enum Events {
		CARD = 3001,
		CANCEL = 3002,
		EDIT = 3003,
		DONE = 3004,
		OK = 3005,
		START = 3006
	};

};



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
    // Login
     
    std::this_thread::sleep_for(2000ms);
    auto eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::GET_PIN,std::string("1235")));
    std::cout << "[EventGenerator] " << "Sending wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::cout << "[EventGenerator] " << "Sending wrong pin code" << std::endl;
    sendEvent(eptr,v[1].first, v[1].second);
    std::this_thread::sleep_for(2000ms);


    std::cout << "[EventGenerator] " << "Sending correct pin code" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::GET_PIN,std::string("1234")));
    sendEvent(eptr,v[1].first, v[1].second);



    // Barcode scanner

    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);

    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);


    // Payment


    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Press CASH on keypad" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::CASH,NULL));
    sendEvent(eptr,v[1].first, v[1].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Press ENTER on keypad" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::ENTER,NULL));
    sendEvent(eptr,v[1].first, v[1].second);
    

    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "################### NEW TRANSACTION ######################" << std::endl;

    // Barcode scanner 2

    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Barcode scanned" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);


    // Payment

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Press CARD on display" << std::endl; 
    eptr = std::make_shared<Event>(Event(TouchDisplayTask::Events::CARD,NULL));
    sendEvent(eptr,v[1].first, v[1].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Card swiped" << std::endl;
    eptr = std::make_shared<Event>(Event(BarCodeScannerTask::Command::GET_BARCODE,1234123412341324));
    sendEvent(eptr,v[0].first, v[0].second);

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Sending pin code" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::GET_PIN,std::string("1234")));
    sendEvent(eptr,v[1].first, v[1].second);
    

    std::this_thread::sleep_for(300ms);
    std::this_thread::sleep_for(2000ms);
    std::cout << "[EventGenerator] " << "Sending ENTER on keypad" << std::endl;
    eptr = std::make_shared<Event>(Event(NumpadDriverTask::Command::ENTER,std::string("1234")));
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

    // TouchDisplay
	std::mutex mtx_events_touchDisplay;
	std::queue<Event> events_touchDisplay;
    qmp.first = &events_touchDisplay;
    qmp.second = &mtx_events_touchDisplay;
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

    // Event vars
    auto lastEvent = std::make_shared<Event>();
    auto currentEvent = std::make_shared<Event>();

    // Receipt ptr
    std::shared_ptr<Receipt> receipt = std::make_shared<Receipt>();   

    // Start stationbox locked
    STATES sm_State = LOCKED;
PAYMENTstates::PAYMENT_SUBSTATES sm_PAYMENT = PAYMENTstates::PAYMENT_SUBSTATES::UNDECIDED;
    
    while(1){
        // Dont trash CPU
         std::this_thread::sleep_for(20ms);
        // Grab an event if there is any

        lastEvent = currentEvent;
        currentEvent = nextEvent(qmpairs);


        std::cout << "[INFO] State: " << STATENAME[sm_State] << std::endl;
        // State machine
        switch (sm_State) {
            case LOCKED: 
               // Station box is locked  
               // Unmute the keypad task and wait for a pin
                keypadTask.unmute();
                keypadTask.sendEventToTask(Event(NumpadDriverTask::GET_PIN));
                
                 while (!currentEvent)
                 {
                    currentEvent = nextEvent(qmpairs);
                    
                 }

                    // Recived event, check type
                    if (currentEvent->id == NumpadDriverTask::Command::GET_PIN)
                    {
                        // Pin code recieved
                        if ( currentEvent->getData<std::string>() == "1234")
                        {
                            std::cout << "Correct passcode, transition to IDLE" << std::endl;
                            sm_State = STATES::IDLE;
                        }
                        else
                        {
                            std::cout << "Wrong passcode" << std::endl;
                        }
                    }

            break;
        case IDLE:
            // Unmute keypad and barcode scanner to wait for input
            keypadTask.unmute();
            barcodeScannerTask.unmute();

            // Trap and wait for event
            while (!currentEvent)
            {
               currentEvent = nextEvent(qmpairs);
            }

            switch (currentEvent->id) {
                case BarCodeScannerTask::Command::GET_BARCODE:
                    // A barcode have been scanned with the scanner and is avaliable in the event  
                    sm_State = STATES::SHOPPING;
                    std::cout <<  "Addning scanned input to receipt" << std::endl;
                    receipt->addReceiptLine(currentEvent->getData<long  unsigned int>(),10,1 );
                    break;
                case NumpadDriverTask::Command::ENTER:
                    // Enter (D) was pressed on keypad and barcode number is avaliable in the event
                    sm_State = STATES::SHOPPING;
                    // Add the item that caused the move to SHOPPING state 
                    std::cout <<  "Addning Manual input to receipt" << std::endl;
                    receipt->addReceiptLine(currentEvent->getData<long  unsigned int>(),10,1 );
                    break;
            }

        break;        

        case SHOPPING:
            
            // Trap and wait for event
            while (!currentEvent)
            {
               currentEvent = nextEvent(qmpairs);
            }

            switch (currentEvent->id) {
                case BarCodeScannerTask::Command::GET_BARCODE:
                    // A barcode have been scanned with the scanner and is avaliable in the event  
                    std::cout <<  "Adding scanned input to receipt" << std::endl;
                    receipt->addReceiptLine(currentEvent->getData<long  unsigned int>(),10,1 );
                    break;
                case NumpadDriverTask::Command::ENTER:
                    // Enter (D) was pressed on keypad and barcode number is avaliable in the event
                    // Add the item that caused the move to SHOPPING state 
                    std::cout <<  "Adding Manual input to receipt" << std::endl;
                    receipt->addReceiptLine(currentEvent->getData<long  unsigned int>(),10,1 );
                    break;

                case NumpadDriverTask::Command::CASH:
                    // CASH was pressed
                    sm_PAYMENT = PAYMENTstates::PAYMENT_SUBSTATES::WAITFORCASH;   
                    sm_State = STATES::PAYMENT;
                    // Present total to custommer 
                    // TODO Events to show information on customer display
                    
                    break;

                case TouchDisplayTask::Events::CARD:
                    // TOTAL was pressed
                    sm_State = STATES::PAYMENT;
                    sm_PAYMENT = PAYMENTstates::PAYMENT_SUBSTATES::WAITFORCARD;   
                    // Present total to custommer 
                    // TODO Events to show information on customer display
                    
                    break;
            }






        break;

        case PAYMENT:
        
            // Trap and wait for event
            switch (sm_PAYMENT) {
                case PAYMENTstates::PAYMENT_SUBSTATES::WAITFORCASH:
                    std::cout << "CASH selected" << std::endl;
                    currentEvent = nextEvent(qmpairs);

                    while(1){
                    while (!currentEvent)
                    {
                       currentEvent = nextEvent(qmpairs);
                    }
                    if (currentEvent->id == NumpadDriverTask::Command::ENTER)
                    {
                                std::cout << "Cash payment DONE" << std::endl;
                                // Cash is done
                                sm_State = IDLE;
                            break;
                    }
                    }
                    break;
                case PAYMENTstates::PAYMENT_SUBSTATES::WAITFORCARD:
                    std::cout << "CARD selected" << std::endl;
                    while (!currentEvent)
                    {
                       currentEvent = nextEvent(qmpairs);
                    }
                    switch (currentEvent->id) {
                        case BarCodeScannerTask::Command::GET_BARCODE:
                            std::cout << "Got customer card" << std::endl;
                            
                                while(1){

                                   currentEvent = nextEvent(qmpairs);
                                while (!currentEvent)
                                {
                                   currentEvent = nextEvent(qmpairs);
                                }
                                if ( currentEvent->id == NumpadDriverTask::Command::GET_PIN)
                                {
                                    
                                    std::cout << "got pin number" << std::endl;
                                    break;
                                }
                                }

                                while(1){
                                   currentEvent = nextEvent(qmpairs);

                                while (!currentEvent)
                                {
                                   currentEvent = nextEvent(qmpairs);
                                }
                                if ( currentEvent->id == NumpadDriverTask::Command::ENTER)
                                {
                                    std::cout << "Got ENTER, asking bank" << std::endl;
                                    std::this_thread::sleep_for(250ms);
                                    std::cout << "APPROVED" << std::endl;
                                    sm_State = STATES::IDLE;
                                    break;
                                }
                                }
                                
                                



                            break;
                    }

                    
                    break;
            }


        
        break;

            
    }





     



}
	return 0;
}




