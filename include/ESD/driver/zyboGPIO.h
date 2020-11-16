#ifndef LIBzyboGPIO_H
#define LIBzyboGPIO_H

#include <string>
#include <fstream>

class zyboGPIO {
    private:
        void writeToFile(std::string file, std::string value);
        int mPinnumber;
        void exportPin();
        void unExportPin();

    public:
        zyboGPIO(int pinnumber);
        ~zyboGPIO();

        void initialize();
        void setPin(int val);
        void setPinDirection(std::string);
        int getPin();

};

#endif /* LIBzyboGPIO_H */
