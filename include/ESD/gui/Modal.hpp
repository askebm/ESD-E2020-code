#ifndef MODAL_H
#define MODAL_H

#include <memory>

class Modal {
private:
	

public:
	using shr_ptr = std::shared_ptr<Modal>;
	Modal ();
	~Modal ();
};

#endif /* MODAL_H */
