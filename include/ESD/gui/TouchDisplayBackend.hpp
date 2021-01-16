#ifndef TOUCHDISPLAYBACKEND_H
#define TOUCHDISPLAYBACKEND_H

#include <ESD/gui/Modal.hpp>
#include <ESD/gui/Layout.hpp>

class TouchDisplayBackend
{
public:
	virtual void addModal(const Modal::shr_ptr& m) =0;
	virtual void deployLayout(const Layout::shr_ptr& l) =0;
};

#endif /* TOUCHDISPLAYBACKEND_H */
