#include <ESD/driver/GPIO.h>
#include <iostream>
#include <string>

// GPIO adapter class

/**
 *  Create a GPIO obj without a pinnumber. This requires a call to setPinNumber(int) before further use.
 */ 
GPIO::GPIO()
{
   // We do not have a pinNumber, Do nothing 
}

/**
 * Create a GPIO object controlling pinnumber
 */
GPIO::GPIO(std::string pinnumber)
{
   
   mPinnumber = pinnumber;

   // We have a pinNumber, instansiate backingObj
   mCurrentBackingObj = new zyboGPIO(stoi(mPinnumber)); 
   mCurrentBackingObj->initialize();
}

/**
 * Set pinnumber for the object to control
 */
int GPIO::setPinNumber(int pinnumber)
{
    // (re)/define pin // Deconstructor is called when old obj goes out of scope
    mCurrentBackingObj = new zyboGPIO(stoi(mPinnumber)); 
    mCurrentBackingObj->initialize();
    return 0;
}

/**
 * Enable the linux subsystem pin
 */
int GPIO::exportPin()
{
    if (!mCurrentBackingObj)
    {
        mCurrentBackingObj->initialize();
    }
    else if (mPinnumber != "")
   {
        mCurrentBackingObj = new zyboGPIO(stoi(mPinnumber)); 
    }
    else
    {
        return -1;
    }
    return 0;
}

/**
 * Disable the linux subsystem pin
 */
int GPIO::unexportPin()
{
    mCurrentBackingObj = NULL;
    return 0;
}

/**
 * Set the controlled pin to the integer value of 'str'
 */ 
int GPIO::setPinValue(std::string str)
{
    mCurrentBackingObj->setPin(stoi(str));
}

/**
 * Get the controlled pin value as a string
 */ 
int GPIO::getPinValue(std::string &str)
{
    str = std::to_string(mCurrentBackingObj->getPin());
    return 0;
}

/**
 * Set the controlled pin direction. Possible values are "in" / "out"
 */ 
int GPIO::setPinDirection(std::string str)
{
    mCurrentBackingObj->setPinDirection(str);
    return 0;
}

/**
 * Set the controlled pin value to high
 */
void GPIO::set()
{
    setPinValue("1");
}

/**
 * Set the controlled pin value to low
 */
void GPIO::clear()
{
    setPinValue("0");
}


