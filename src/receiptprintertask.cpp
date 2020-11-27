#include <ESD/receiptprintertask.hpp>

ReceiptPrinterTask::ReceiptPrinterTask(){ReceiptPrinterTask m_printer;}
ReceiptPrinterTask::~ReceiptPrinterTask(){}
    
bool ReceiptPrinterTask::init()
{
    m_printer.configure(1046, 20497);
    m_printer.initialize(); 

    return true;
}

void ReceiptPrinterTask::run()
{
    //StateMachine here
}

void ReceiptPrinterTask::printReceipt()
{
}


