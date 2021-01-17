#include <ESD/ReceiptPrinterTask.hpp>

int main(int argc, char *argv[])
{
    std::mutex mtx_events;
	std::queue<Event> events;
    ReceiptPrinterTask task(events, mtx_events);   
   
    // start task
	if (not task.start())
	{
		std::cerr << "Could not start the " << task.name << " task." << std::endl;
		exit(-1);
	}
    
    int receipt_number = 0;
    
    while (true) 
    {
        ReceiptPrinterTask::ReceiptItems receipt;

        std::cout << "Main Running" << std::endl;
        std::this_thread::sleep_for(3s);
        
        receipt.items.push_back("Pepsi");
        receipt.items.push_back("Pepsi MAX lime flavour");
        receipt.items.push_back("Raspberry Pi Model B 4GB RAM");
        receipt.quantity.push_back("2"); //Number of Pepsies
        receipt.quantity.push_back("10"); //Number of Pepsie MAX's.
        receipt.quantity.push_back("1"); //Number of Raspberry Pis.
        receipt.item_price.push_back("15"); //Price of one Pepsi.
        receipt.item_price.push_back("15"); //Price of one Pepsi Max.
        receipt.item_price.push_back("429"); //Price of one Paper.
        receipt.line_sum.push_back("30"); //Sum of Pepsies.
        receipt.line_sum.push_back("150"); //Sum of Pepsi Max's.
        receipt.line_sum.push_back("429"); //Sum of Raspberry PI's.
        
        receipt.receipt_sum = std::string("609"); // Total purchase price.
        receipt.receipt_id = std::string(std::to_string(receipt_number)); // Receipt ID.

        auto e = Event(ReceiptPrinterTask::RECEIVED_RECEIPT, receipt);
        task.sendEventToTask(e);

        receipt_number++;


        // check for events from tasks (using helper method)
		auto event = ReceiptPrinterTask::getEventFromQueue(events, mtx_events);
		if(not event)
            continue;

        if (*event == ReceiptPrinterTask::RECIEPT_PRINTER_NO_PAPER)
            std::cout << "No more paper in printer." << std::endl;


    }

    return 0;
}
