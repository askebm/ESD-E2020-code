#include <ESD/CashierTouchDisplayTask.hpp>
#include <random>


int main(int argc, char *argv[])
{
	// main event queue
	std::mutex mtx_events;
	std::queue<Event> events;

	CashierTouchDisplayTask task("CashierHMI",events,mtx_events);

	// start task
	if (not task.start())
	{
		std::cerr << "Could not start the " << task.name << " task." << std::endl;
		exit(-1);
	}

	auto running = true;

	using EVENTS = CashierTouchDisplayTask::Events;

	std::array<std::string,7> event_selection;
	event_selection[0]="CARD";
	event_selection[1]="CANCEL";
	event_selection[2]="EDIT";
	event_selection[3]="DONE";
	event_selection[4]="OK";
	event_selection[5]="START";
	event_selection[6]="SCAN";

	std::array<std::string,4> items{"Potato","Bread","Battery","Fruit"};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> item_dist(0,3);
	std::uniform_int_distribution<> amount_dist(0,100);
	std::uniform_int_distribution<> price_dist(0,100);

	int response;
	while (running) {
		std::cout << "Send Event to Task" << std::endl;
		for (int i = 0; i < event_selection.size(); ++i) {
			std::cout << i << ".\t" << event_selection[i] << std::endl;
		}
		std::cout << "7. quit" << std::endl;

		std::cin >> response;

		Event* event = nullptr;
		Receipt* receipt = nullptr;

		switch (response) {
			case 7:
				running = false;
				break;
			case 6://SCAN
				if (receipt != nullptr) {
					auto item_id = item_dist(gen);
					auto item_name = items[item_id];
					auto amount = amount_dist(gen);
					auto price = price_dist(gen);
					receipt->addReceiptLine(item_id,item_name,price,amount);
				}
				event = new Event(EVENTS::SCAN);
				break;
			case 5://START
				{
				receipt = new Receipt(80);
				CashierTouchDisplayTask::receipt_data data{receipt};
				event = new Event(EVENTS::START,data);
				task.sendEventToTask(*event);
				}
				break;
			case 4://OK
				event = new Event(EVENTS::OK);
				break;
			case 3://DONE
				event = new Event(EVENTS::DONE);
				break;
			case 2://EDIT
				event = new Event(EVENTS::EDIT);
				break;
			case 1://CANCEL
				event = new Event(EVENTS::CANCEL);
				delete receipt;
				break;
			case 0://CARD
				event = new Event(EVENTS::CARD);
				break;
			default: 
				std::cout << response << " is not an option" << std::endl;
		}

		if (event != nullptr) {
			task.sendEventToTask(*event);
			delete event;
		}
	}
	
	return 0;
}
