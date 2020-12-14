#include <ESD/gui/Button.hpp>

bool Button::isPressed(){

	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:

			break;

		case SDL_FINGERDOWN:
			break;
		default:
			return false;
	}

}
