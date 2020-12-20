#include "CardScannerTask.hpp"
#include <fcntl.h>
#include <functional>
#include <mqueue.h>
#include <pthread.h>
#include <thread>

CardScannerTask::~CardScannerTask() { }

bool CardScannerTask::init()
{
    return  this->USBd.openDevice(device_path);
}

void CardScannerTask::run()
{
    // Retrieve the Event in the queue
    auto event = this->readLatestEvent();

    if (not event)
        return;

    // if GET_CARD_NUMBER is in the queue
    if (event->id == Command::GET_CARD_NUMBER)
    {

        // get the following ? inputs
        size_t counter = 0;
        Event* event;

        while (counter < 4)
        {
            auto barcode_in = this->USBd.getDatafromUSB();
            if (barcode_in != NULL)
            {
                this->data[counter] = barcode_in;
                ++counter;
            }
        }

        event = new Event(Command::GET_CARD_NUMBER,Msg{this->data,4});
        this->sendEventFromTask(Event(Command::GET_CARD_NUMBER,Msg{this->data,4}));
        delete event;

        // clear the data object
        this->data.fill(-1);
    }
}
