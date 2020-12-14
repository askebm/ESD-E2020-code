#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button
{
private:
	SDL_Event* event;

public:

	bool isPressed();

	Button(SDL_Event* event);
	virtual ~Button();
};

#endif /* BUTTON_H */
