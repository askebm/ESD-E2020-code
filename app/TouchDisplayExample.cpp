#include <ESD/gui/sdl2/TouchDisplaySDL2.hpp>
#include <iostream>

int main(int argc, char *argv[]) {

	TouchDisplaySDL2 disp;

	auto l = Layout::shr_ptr(new Layout() );

	auto r = new Receipt(10);
	auto& receipt = *r;
	receipt.addReceiptLine(12,"Item",12,12);
	receipt.addReceiptLine(12,"Fuit",12,42);

	auto ff = [](){ std::cout << "Callback e1" << std::endl;};
	auto ee1 = new Layout::Element();
	auto& e1 = *ee1;
	e1.callback = ff;
	e1.start_x=5;
	e1.start_y=0;
	e1.end_x=6;
	e1.end_y=1;
	e1.type=Layout::Element::Type::Button;
	e1.text="E1";

	auto rr1 = new Layout::Element();
	auto& r1 = *rr1;
	r1.start_x=0;
	r1.start_y=0;
	r1.end_x=3;
	r1.end_y=5;
	r1.type=Layout::Element::Type::Receipt;
	r1.receipt = &receipt;

	l->addElement(e1);
	l->addElement(r1);

	disp.deployLayout(l);

	ff();

	while (true) {
		disp.process();
	}

	return 0;
}
