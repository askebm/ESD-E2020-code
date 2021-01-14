#include <ESD/stationBox.hpp>




bool StationBox::init() {
    mState = LOCKED; // Initially the station is locked;    


    return true;
}

void StationBox::run() {

    // Grab event from event_in queue
   mCurrentEvent = readLatestEvent();

 
    // State machine
    switch (mState) {
        case LOCKED: 
           // Station box is locked  
           
           // Unmute the keypad task and wait for 4 numbers
           // Only enter statemachine if there is a valid event
            if (mCurrentEvent != nullptr)
            {
                LOCKED_sm();
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


void StationBox::LOCKED_sm() {

    // unmute keypad
    
    static std::string passcode;
    switch (mLockedSubState) {
        case WAITFOR1:
            passcode = ""; 
            if (mCurrentEvent->id == GotPinDigit)
            {
                std::cout << "Got one" << std::endl;
                // got a new number
                passcode += mCurrentEvent->getData<std::string>();
                mLockedSubState = WAITFOR2;
            }
            break;
        case WAITFOR2:
            if (mCurrentEvent->id == GotPinDigit)
            {
                std::cout << "Got two" << std::endl;
                // got a new number
                passcode += mCurrentEvent->getData<std::string>();
                mLockedSubState = WAITFOR3;
            }
            break;
        case WAITFOR3:
            if (mCurrentEvent->id == GotPinDigit)
            {
                std::cout << "Got three" << std::endl;
                // got a new number
                passcode += mCurrentEvent->getData<std::string>();
                mLockedSubState = WAITFOR4;
            }
            break;
        case WAITFOR4:
            if (mCurrentEvent->id == GotPinDigit)
            {
                std::cout << "Got four" << std::endl;
                // got a new number
                passcode += mCurrentEvent->getData<std::string>();
                if(passcode == "1234"){
                    // Correct code - Change to IDLE state
                    std::cout << "Correct passcode - Transition to IDLE state" << std::endl;
                    mState = IDLE;
                }
                // Reset password sub state
                    mLockedSubState = WAITFOR1;
                    // Mute keypad
            }
            break;
    }

    


    
}
