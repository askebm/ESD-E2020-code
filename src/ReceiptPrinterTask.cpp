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
        ReceiptFormatter formatter(event->getData<ReceiptItems>());
        std::vector<std::string> formatted_receipt = formatter.formatReceipt();

        printReceipt(formatted_receipt);
    }
}

void ReceiptPrinterTask::printReceipt(std::vector<std::string> formatted_receipt)
{
    for (int i = 0; i < formatted_receipt.size(); ++i) 
    {
        if (m_printer.getPaperStatus()) 
        {
            if (formatted_receipt[i].empty()) 
            {
                //m_printer.lineFeed(1);
                std::cout << std::endl;
            }
            else
            {
                std::cout << formatted_receipt[i] << std::endl;
                //m_printer.printLine(formatted_receipt[i]); 
            }
        }
        else
        {
		    Event *paper_out = new Event(RECIEPT_PRINTER_NO_PAPER, 0);
            
            this->sendEventFromTask(*paper_out);
           
            delete paper_out;
        }
    }

}

		
