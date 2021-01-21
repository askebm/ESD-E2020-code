#include <ESD/CashierTouchDisplayTask.hpp>
#include <ESD/gui/sdl2/TouchDisplaySDL2.hpp>

#include <chrono>
#include <thread>

void printSignal(TouchDisplayBackend::Signals s){
	using Signals = TouchDisplayBackend::Signals;
	switch (s) {
		case Signals::CANCEL:
			std::cout << "Signal: CANCEL" << std::endl;
			break;
		case Signals::START:
			std::cout << "Signal: START" << std::endl;
			break;
		case Signals::CARD_TRANSACTION:
			std::cout << "Signal: CARD_TRANSACTION" << std::endl;
			break;
		case Signals::RECEIPT_LINE:
			std::cout << "Signal: RECEIPT_LINE" << std::endl;
			break;
		case Signals::EDIT:
			std::cout << "Signal: EDIT" << std::endl;
			break;
		case Signals::NEW_AMOUNT:
			std::cout << "Signal: NEW_AMOUNT" << std::endl;
			break;
		case Signals::DONE:
			std::cout << "Signal: DONE" << std::endl;
			break;
		default:
			;
	}
};

void printEvent(int e){
	using Events = CashierTouchDisplayTask::Events;
	switch (e) {
		case Events::CANCEL:
			std::cout << "Event: CANCEL" << std::endl;
			break;
		case Events::CARD:
			std::cout << "Event: CARD" << std::endl;
			break;
		case Events::DONE:
			std::cout << "Event: DONE" << std::endl;
			break;
		case Events::EDIT :
			std::cout << "Event: EDIT" << std::endl;
			break;
		case Events::OK:
			std::cout << "Event: OK" << std::endl;
			break;
		case Events::SCAN:
			std::cout << "Event: SCAN" << std::endl;
			break;
		case Events::START:
			std::cout << "Event: START" << std::endl;
			break;
		default:
			;
	}
};

bool CashierTouchDisplayTask::init() {
	display = new TouchDisplaySDL2();
	if (!display) {
		return false;
	}

	//Generate Layouts
	using Signals = TouchDisplayBackend::Signals;
	// NO transaction
	auto l = new Layout();
	{
		Layout::Element btn;
		btn.callback = [](void* d) -> void {
			TouchDisplayBackend* dis = static_cast<TouchDisplayBackend*>(d);
			dis->setSignal(Signals::START);
		};
		btn.data = static_cast<void*>(display);
		btn.end_x = 10;
		btn.end_y = 6;
		btn.start_x = 7;
		btn.start_y = 4;
		btn.type = Layout::Element::Type::Button;
		btn.text = "START";
		l->addElement(btn);
	}
	templates.push_back(l);
	// Transaction
	auto trans = new Layout();
	{
		Layout::Element edit;
		edit.callback = [](void* d) -> void {
			TouchDisplayBackend* dis = static_cast<TouchDisplayBackend*>(d);
			dis->setSignal(Signals::EDIT);
		};
		edit.data = static_cast<void*>(display);
		edit.end_x = 10;
		edit.end_y = 4;
		edit.start_x = 8;
		edit.start_y = 3;
		edit.type = Layout::Element::Type::Button;
		edit.text = "EDIT";
		trans->addElement(edit);
	}
	{
		Layout::Element card;
		card.callback = [](void* d) -> void {
			TouchDisplayBackend* dis = static_cast<TouchDisplayBackend*>(d);
			dis->setSignal(Signals::CARD_TRANSACTION);
		};
		card.data = static_cast<void*>(display);
		card.end_x = 10;
		card.end_y = 5;
		card.start_x = 8;
		card.start_y = 4;
		card.type = Layout::Element::Type::Button;
		card.text = "CARD";
		trans->addElement(card);
	}
	{
		Layout::Element cancel;
		cancel.callback = [](void* d) -> void {
			TouchDisplayBackend* dis = static_cast<TouchDisplayBackend*>(d);
			dis->setSignal(Signals::CANCEL);
		};
		cancel.data = static_cast<void*>(display);
		cancel.end_x = 10;
		cancel.end_y = 6;
		cancel.start_x = 8;
		cancel.start_y = 5;
		cancel.type = Layout::Element::Type::Button;
		cancel.text = "CANCEL";
		trans->addElement(cancel);
	}

	templates.push_back(trans);
	templates.push_back(trans);
	templates.push_back(trans);

	display->deployLayout(l);

	return true;
}

void CashierTouchDisplayTask::run() {

	using Signals = TouchDisplayBackend::Signals;

	auto changeState = [&](States s){
					this->state = s;
					this->display->deployLayout(templates[s]);
					std::cout << "Changing state to: ";
					switch (s) {
						case TRANSACTION:
							std::cout << "TRANSACTION";
							break;
						case NO_TRANSACTION:
							std::cout << "NO_TRANSACTION";
							break;
						case EDIT_RECIPE:
							std::cout << "EDIT_RECEIPT";
							break;
						case CARD_TRANSACTION:
							std::cout << "CARD_TRANSACTION";
							break;
						default:
							;
					}
					std::cout << std::endl;
	};

	auto event_in = this->readLatestEvent();
	auto signal = display->getSignal();
	Event* event_out = nullptr;
	auto event_id = -1;
	if (event_in) {
		event_id = event_in->id;
	}

	printSignal(signal);
	printEvent(event_id);


	switch (this->state) {
		case TRANSACTION:
			switch (event_id) {
				case CANCEL:
					changeState(NO_TRANSACTION);
					break;
				case EDIT:
					changeState(EDIT_RECIPE);
					break;
				case CARD:
					changeState(CARD_TRANSACTION);
					break;
				case SCAN:
					//TODO
					break;
				default:
					;
			}
			switch (signal) {
				case Signals::CANCEL:
					event_out = new Event(Events::CANCEL);
					break;
				case Signals::CARD_TRANSACTION:
					event_out = new Event(Events::CARD);
					break;
				case Signals::EDIT:
					changeState(States::EDIT_RECIPE);
					break;
				default:
					;
			}
			break;
		case EDIT_RECIPE:
			switch (event_id) {
				case DONE:
					changeState(TRANSACTION);
					break;
				default:
					;
			}
			switch (signal) {
				case Signals::NEW_AMOUNT:
					//TODO
					break;
				case Signals::CANCEL:
					changeState(TRANSACTION);
					break;
				default:
					;
			}
			break;
		case CARD_TRANSACTION:
			switch (event_id) {
				case CANCEL:
				case OK:
					changeState(NO_TRANSACTION);
					break;
				default:
					;
			}
			switch (signal) {
				case Signals::CANCEL:
					event_out = new Event(Events::CANCEL);
					break;
				default:
					;
			}
			break;
		case NO_TRANSACTION:
			switch (event_id) {
				case START:
					changeState(TRANSACTION);
					break;
				case SCAN:

					break;
				default:
					;
			}
			switch (signal) {
				case Signals::START:
					event_out = new Event(Events::START);
					break;
				default:
					;
			}
			break;
		default:
			;
	}
	display->process();

	if (event_out != nullptr) {
		this->sendEventFromTask(*event_out);
		delete event_out;
	}

	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(5ms);
	}


}
