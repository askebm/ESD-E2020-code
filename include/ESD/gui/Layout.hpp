#ifndef LAYOUT_H
#define LAYOUT_H

#include <memory>
#include <vector>

class Layout {
public:
	struct Element {
		unsigned int start_x,start_y,end_y,end_x;
		void (*callback)()=nullptr;
		enum Type {Button,Receipt};
		Type type;
	};

	using shr_ptr = std::shared_ptr<Layout>;

private:
	unsigned int width;
	unsigned int height;

	std::vector<Element> elements;
	bool overlaps(const Element&, const Element&);

public:
	bool addElement(const Element& e);


	Layout ();
	~Layout ();
};

#endif /* LAYOUT_H */
