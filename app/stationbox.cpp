#include <ESD/driver/GPIO.h>
#include <ESD/stationBox.hpp>
#include <BarCodeScannerTask/BarCodeScannerTask.hpp>
#include <iostream>

#include <cstdlib>
#include <iostream>
#include <array>
#include <mutex>
#include <chrono>

#include <Task/Task.hpp>

#define SAFE_COUT(x) { static std::mutex mtx_cout; mtx_cout.lock(); std::cout << x; mtx_cout.unlock(); }
using namespace std::chrono_literals;

// main function for full cashier system.

int main(int argc, char const *argv[])
{

    std::vector<Task*> registeredTasks; // All tasks that the system will attempt to start

    

	// stationbox event queue
	std::mutex mtx_events_stationbox;
	std::queue<Event> events_stationbox;
	StationBox sb("StationBox", events_stationbox, mtx_events_stationbox);
    registeredTasks.push_back(&sb);

	// barcodescanner event queue
	std::mutex mtx_events_barcodescanner;
	std::queue<Event> events_barcodescanner;
    BarCodeScannerTask barcodeScannerTask("BarCodeScannerTask", events_barcodescanner, mtx_events_barcodescanner);
    registeredTasks.push_back(&barcodeScannerTask);



    // Start all registered tasks
    for (unsigned int i = 0; i < registeredTasks.size();i++)
    {
        if ( registeredTasks[i]->start() != true)
        {
		    std::cerr << "Could not start the " << registeredTasks[i]->name << " task." << std::endl;
		    exit(-1); // unrecoverable, terminate execution
        }
    }


    // handover operational control
    // Inform stationbox of task handles 
    sb.addInterface(&barcodeScannerTask,StationBox::BarcodeScanner);


    // Testing code
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("1")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("2")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("3")));
    sb.sendEventToTask(Event(StationBox::GotPinDigit,std::string("4")));

while(true){};

	return 0;
}
