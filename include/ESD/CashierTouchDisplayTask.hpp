#ifndef CASHIERTOUCHDISPLAYTASK_H
#define CASHIERTOUCHDISPLAYTASK_H

#include <Task/Task.hpp>
#include <Event/Event.hpp>
#include <receipt.hpp>
#include <ESD/gui/Layout.hpp>
#include <ESD/gui/TouchDisplayBackend.hpp>


class CashierTouchDisplayTask final : public Task
{
public:
	using Task::Task;
	CashierTouchDisplayTask () = delete;
	~CashierTouchDisplayTask () {};

private:
	std::vector<Layout*> templates;
	TouchDisplayBackend* display;

protected:
	bool init() override;
	void run() override;
	Receipt* receipt;

public:
	struct receipt_data {
		Receipt* receipt;
	};

	enum Events : int {
		CARD=0,
		CANCEL,
		EDIT,
		DONE,
		OK,
		START,
		SCAN,
		NONE,
	};

	enum States {
		NO_TRANSACTION = 0,
		TRANSACTION,
		EDIT_RECIPE,
		CARD_TRANSACTION
	};


protected:
	States state = NO_TRANSACTION;


};

#endif /* CASHIERTOUCHDISPLAYTASK_H */
