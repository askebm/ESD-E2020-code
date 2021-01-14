#include <ESD/gui/Layout.hpp>

bool Layout::addElement(const Element& e){
	for (const auto& g : elements) {
		if (overlaps(g,e)) {
			return false;
		}
	}
	elements.push_back(std::move(e));
	return true;
}

bool Layout::overlaps(const Element& e, const Element& g){
	auto f = [](const Element& e1,const Element& e2){
		return (
				( e1.start_x < e2.start_x ) &&
				( e2.start_x < e1.end_x )
				)  || (
					( e1.start_y < e2.start_y ) &&
					( e2.start_y < e1.end_y )
					);
	};
	return (f(e,g) || f(g,e));
}

Layout::Layout (){

}

Layout::~Layout (){

}
