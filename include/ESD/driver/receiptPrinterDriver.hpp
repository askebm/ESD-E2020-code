#ifndef RECEIPTPRINTERDRIVER_H
#define RECEIPTPRINTERDRIVER_H

#include <string>
#include <fstream>

class ReceiptPrinterDriver
{
private:
    std::string printer_file_name;

    int writeToFile( std::string printer_file, std::string text );
    int readFromFile( std::string printer_file, std::string& text );

public:
    ReceiptPrinterDriver();
    ~ReceiptPrinterDriver();

    void configure(std::string printer_file);
    void cut();
    void lineFeed();
    void text(std::string text);
};

#endif /* RECEIPTPRINTERDRIVER_H */
