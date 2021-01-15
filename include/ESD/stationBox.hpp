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


std::shared_ptr<Event> mCurrentEvent;

void LOCKED_sm();


// Interface handles
Task* mBarcodeScannerPtr = nullptr;





public:
	// must be defined to use Base class constructor
	using Task::Task;
	StationBox() = delete;
	~StationBox() {};

    enum Events { GotPinDigit = 1001 };
    enum InterfaceNames {BarcodeScanner};

    bool init();
    void run();


    // Control handover interface
    bool addInterface(Task* taskptr,InterfaceNames ifType);

};

#endif /* STATIONBOX_H */
