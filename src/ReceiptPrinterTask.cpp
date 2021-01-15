#include <ESD/ReceiptPrinterTask.hpp>

ReceiptPrinterTask::~ReceiptPrinterTask(){}
    
bool ReceiptPrinterTask::init() 
{
    std::cout << "init" << std::endl;
    m_printer.configure(1046, 20497);
    m_printer.initialize(); 
    
    std::this_thread::sleep_for(1s);
    return true;
}

void ReceiptPrinterTask::run()
{
    auto event = this->readLatestEvent(); 
    if(event && *event == Printer::RECEIVED_RECEIPT)
    {
        //Format
        printReceipt(event->getData<ReceiptItems>());
    }

    std::this_thread::sleep_for(2s);
}

void ReceiptPrinterTask::printReceipt(ReceiptItems receivedReceipt)
{
    std::cout << "Printing Receipt" << std::endl;
    
    for (int i = 0; i < receivedReceipt.items.size(); ++i)
    {
        std::cout << receivedReceipt.items.at(i) << " , " << receivedReceipt.quantity.at(i) << " , " 
            << receivedReceipt.item_price.at(i) << " , " << receivedReceipt.line_sum.at(i) << " , " << std::endl;    
    }
    std::cout << "Total: " << receivedReceipt.receipt_sum << std::endl;
    std::cout << "Receipt ID: " << receivedReceipt.receipt_id << std::endl;
}


