#ifndef TOUCHDISPLAYBACKEND_H
#define TOUCHDISPLAYBACKEND_H

#include <ESD/gui/Modal.hpp>
#include <ESD/gui/Layout.hpp>
#include <iostream>

class TouchDisplayBackend
{

public:
	virtual void addModal(const Modal::shr_ptr& m) =0;
	virtual void deployLayout(const Layout::shr_ptr& l) =0;
	virtual void deployLayout(Layout* l) =0;
	virtual void process() =0;

	enum Signals {
		NONE = -1,
		START = 0,
		CANCEL,
		CARD_TRANSACTION,
		RECEIPT_LINE,
		EDIT,
		NEW_AMOUNT,
		DONE,
	};

	const auto inline getSignal() { auto tmp = signal; signal = NONE; return tmp; };
	const auto inline setSignal(Signals s) { signal = s;};
	const auto inline getAmount() { return amount; };
	const auto inline setAmount(int a) { amount = a; };

protected:
	Signals signal = NONE;
	int amount = -1;
};

#endif /* TOUCHDISPLAYBACKEND_H */
