#include <ESD/driver/receiptPrinterDriver.hpp>

ReceiptPrinterDriver::ReceiptPrinterDriver()
{
}
ReceiptPrinterDriver::~ReceiptPrinterDriver()
{
}

int ReceiptPrinterDriver::writeToFile( std::string printer_file, std::string text )
{
    std::ofstream out_file;
    out_file.open( printer_file.c_str() );
    out_file << text;
    out_file.close();

    return 0;
}

int ReceiptPrinterDriver::readFromFile( std::string printer_file, std::string& text )
{
    std::ifstream in_file;
    in_file.open( printer_file.c_str() );
    in_file >> text;
    in_file.close();
    
    return 0;
}


void ReceiptPrinterDriver::configure(std::string printer_file)
{
}

void ReceiptPrinterDriver::cut()
{
}

void ReceiptPrinterDriver::lineFeed()
{
}

void ReceiptPrinterDriver::text(std::string text)
{
}
