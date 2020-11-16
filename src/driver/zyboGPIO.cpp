#include <ESD/driver/zyboGPIO.h>
#include <iostream>

// ZYBO GPIO lib
/**
* Create a GPIO obj controlling pinnumber
*/
zyboGPIO::zyboGPIO(int pinnumber){
    mPinnumber = pinnumber;
}

/**
* Destructing the obj disables the pin in system
*/
zyboGPIO::~zyboGPIO()
{
    this->unExportPin();
}

/**
* Enables the controlled pin in system. Must be called before use;
*/
void zyboGPIO::initialize()
{
    this->exportPin();
}

/**
 * Write to a file, the string value
 */ 
void zyboGPIO::writeToFile(std::string file, std::string value) {
    std::ofstream ofs;
    ofs.open(file, std::ofstream::out | std::ofstream::app);
    ofs << value.c_str();
    ofs.close();
}

/**
* Helper: enables a pin on the system
*/
void zyboGPIO::exportPin()
{
    writeToFile("/sys/class/gpio/export",std::to_string(mPinnumber));
}
/**
* Helper: disables a pin on the system
*/
void zyboGPIO::unExportPin()
{
    writeToFile("/sys/class/gpio/unexport",std::to_string(mPinnumber));
}
/**
* Set pin direction for controlled pin. Possible values ("in"/"out")
*/
void zyboGPIO::setPinDirection(std::string dir)
{
    writeToFile("/sys/class/gpio/gpio"+std::to_string(mPinnumber)+"/direction", dir);
}
/**
* Set pin to high or low depending on value (1/0)
*/
void zyboGPIO::setPin(int val)
{
    writeToFile("/sys/class/gpio/gpio"+std::to_string(mPinnumber)+"/value", std::to_string(val));
}
/**
* Get the value of the controlled pin
*/
int zyboGPIO::getPin()
{
  std::ifstream ifs;

  ifs.open("/sys/class/gpio/gpio"+std::to_string(mPinnumber)+"/value",std::ifstream::in);
  char c = ifs.get();
  int ia = c - '0';
    return ia;

}
