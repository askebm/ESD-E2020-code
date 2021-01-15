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
    
    ReceiptPrinterTask::ReceiptItems receipt;
    
    std::vector<std::string> items;
    std::vector<std::string> quantity;
    std::vector<std::string> item_price;
    std::vector<std::string> line_sum;
    std::string receipt_sum;
    std::string receipt_id;

    items.push_back("Chicken");
    items.push_back("Paper");
    quantity.push_back("2"); //Number of Chickens
    quantity.push_back("10"); //Number of Papers.
    item_price.push_back("24.95"); //Price of one Chicken.
    item_price.push_back("22.99"); //Price of one Paper.
    line_sum.push_back("49.90"); //Sum of Chickes.
    line_sum.push_back("229.90"); //Sum of Papers.
    
    receipt_sum = std::string("279.80"); // Total purchase price.
    receipt_id = std::string("123456789"); // Receipt ID.

    receipt.items = items;
    receipt.quantity = quantity;
    receipt.item_price = item_price;
    receipt.receipt_sum = receipt_sum;
    receipt.receipt_id = receipt_id;
    receipt.line_sum = line_sum;

    auto e = Event(ReceiptPrinterTask::RECEIVED_RECEIPT, receipt);
	task.sendEventToTask(e);

    while (true) 
    {
        std::cout << "Main Running" << std::endl;
        std::this_thread::sleep_for(3s);
    }

    return 0;
}
