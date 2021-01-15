#include <ESD/stationBox.hpp>




bool StationBox::init() {
    mState = LOCKED; // Initially the station is locked;    


    return true;
}

void StationBox::run() {

    // Grab event from event_in queue
   mCurrentEvent = readLatestEvent();

 
   

}


void StationBox::LOCKED_sm() {


    
}

bool StationBox::addInterface(Task* taskptr, InterfaceNames ifType)
{
    switch (ifType) {
        case InterfaceNames::BarcodeScanner:
            mBarcodeScannerPtr = taskptr;  
            return true;
            break;
    }
    return false;
}
