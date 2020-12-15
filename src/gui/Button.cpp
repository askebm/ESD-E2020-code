#include <ESD/gui/Button.hpp>
#include <iostream>

Button::Button(){
	this->color = { .r=255, .g=0 ,.b=0,.a=255};
	this->rectangle = { .x=0,.y=0, .w=128,.h=128 };

}

Button::~Button(){

}

void Button::render(SDL_Renderer* r){
	SDL_SetRenderDrawColor(r, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(r, &(this->rectangle));
}

void Button::process(SDL_Event* event) {
	if (isPressed(event)) {
		std::cout << "Is Pressed" << std::endl;
	} else {
		std::cout << "Nothing" << std::endl;
	}
}

#define BETWEEN(s,e,l)  ( ((s)<(e)) && ((e)<(l)) )

bool Button::isPressed(SDL_Event* event){
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			return ( BETWEEN(rectangle.x, event->button.x, rectangle.x + rectangle.w) &&
					BETWEEN(rectangle.y, event->button.y, rectangle.y + rectangle.h) );

			break;
		case SDL_FINGERDOWN:
			std::cout << "Touch Works" << std::endl;
			break;

		default:
			return false;
	}
	return false;
}


