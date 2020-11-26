#include <iostream>
#include <ESD/driver/receiptPrinterDriver.hpp>

int main(int argc, char *argv[])
{
    ReceiptPrinterDriver printer;

    printer.configure("");

    std::cout << "Hello World" << std::endl;

    return 0;
}
