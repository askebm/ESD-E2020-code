#include <ESD/stationBox.hpp>


/*! \brief Brief function description here
 *
 *  Detailed description
 *
 * \return Return parameter description
 */
StationBox::StationBox() {
    
}
 StationBox::~StationBox() {
    
}



/*! \brief Station box init function
 */
int StationBox::init() {
    mState = LOCKED; // Initially the station is locked;    


    return 0;
}

/*! \brief run() is continually  called during operation by super thread
 *
 */
int StationBox::run() {

    // Grab event from event_in queue
    mCurrentEvent = readLatestEvent(true);
 
    // State machine
    switch (mState) {
        case LOCKED: 
           // Station box is locked  
           // Unmute the keypad task and wait for 4 numbers
           LOCKED_sm();
            break;
        case IDLE:
            // Unmute keypad and barcode scanner


            
    }



}


void StationBox::LOCKED_sm() {

    // unmute keypad
    
    static std::string passcode;
    switch (mLockedSubState) {
        case WAITFOR1:
            passcode = ""; 
            if (mCurrentEvent.name == 1000)
            {
                // got a new number
                mLockedSubState = WAITFOR2;
            }
            break;
        case WAITFOR2:
            if (mCurrentEvent.name == 1000)
            {
                // got a new number
                mLockedSubState = WAITFOR3;
            }
            break;
        case WAITFOR3:
            if (mCurrentEvent.name == 1000)
            {
                // got a new number
                mLockedSubState = WAITFOR4;
            }
            break;
        case WAITFOR4:
            if (mCurrentEvent.name == 1000)
            {
                // got a new number
                if(passcode == "1234"){
                    // Correct code - Change to IDLE state
                    mState = IDLE;
                }
                // Reset password sub state
                    mLockedSubState = WAITFOR1;
                    // Mute keypad
            }
            break;
    }

    


    
}
