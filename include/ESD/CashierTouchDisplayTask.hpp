#ifndef CASHIERTOUCHDISPLAYTASK_H
#define CASHIERTOUCHDISPLAYTASK_H

#include <Task/Task.hpp>


class CashierTouchDisplayTask final : public Task
{
private:

protected:
	bool init() override;
	void run() override;

public:
	using Task::Task;

	enum Event {

	};

};

#endif /* CASHIERTOUCHDISPLAYTASK_H */
