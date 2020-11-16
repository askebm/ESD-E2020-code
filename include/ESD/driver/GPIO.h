#ifndef LIBGPIO_H
#define LIBGPIO_H

#include <string>
#include <fstream>
#include <ESD/driver/zyboGPIO.h>

class GPIO
{
private:

    /*!
     *  Write string to a file descriptor "string"
    */
    int writeToFile(std::string, std::string);
    /**
     *
     *
     */ 
    int readFromFile(std::string, std::string&);


    std::string mPinnumber="";
    zyboGPIO* mCurrentBackingObj = NULL;

public:
    GPIO();
    GPIO(std::string);

    int setPinNumber(int);

    int exportPin();
    int unexportPin();

    int setPinDirection(std::string);

    int setPinValue(std::string);
    int getPinValue(std::string&);

    void set(void);
    void clear(void);
};


#endif /* LIBGPIO_H */
