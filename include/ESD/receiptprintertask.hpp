#ifndef RECEIPTPRINTERTASK_H
#define RECEIPTPRINTERTASK_H

#include <ESD/driver/receiptPrinterDriver.hpp>

class ReceiptPrinterTask
{
private:
    ReceiptPrinterDriver m_printer;        

public:
    ReceiptPrinterTask();
    ~ReceiptPrinterTask();
    
    bool init();
    void run();

    void printReceipt();

};

#endif /* RECEIPTPRINTERTASK_H */
