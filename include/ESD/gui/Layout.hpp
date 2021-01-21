#ifndef LAYOUT_H
#define LAYOUT_H

#include <memory>
#include <vector>
#include <string>
#include <receipt.hpp>
#include <functional>

class Layout {
public:
	struct Element {
		unsigned int start_x,start_y,end_y,end_x;
		void (*callback)(void*)=nullptr;
		std::string text;
		enum Type {Button,Receipt};
		Type type;
		class Receipt* receipt;
		void* data;
	};


	using shr_ptr = std::shared_ptr<Layout>;

private:
	unsigned int width;
	unsigned int height;

	std::vector<Element> elements;
	bool overlaps(const Element&, const Element&);

public:

	const auto inline getWidth(){return width;}; 
	const auto inline getHeight(){return height;}; 


	bool addElement(const Element& e);
	const inline std::vector<Element>& getElements(){ return elements; }


	Layout (int w=10,int h=6);
	~Layout ();
};

#endif /* LAYOUT_H */
