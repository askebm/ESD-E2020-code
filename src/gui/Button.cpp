#include <ESD/gui/Button.hpp>
#include <iostream>

void Button::render(SDL_Renderer* r){
	SDL_SetRenderDrawColor(r, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(r, &(this->rectangle));
}

#define BETWEEN(s,e,l)  ( ((s)<(e)) && ((e)<(l)) )

bool Button::isPressed(){
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
