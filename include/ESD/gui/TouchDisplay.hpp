#ifndef TOUCHDISPLAY_H
#define TOUCHDISPLAY_H

#include <SDL2/SDL.h>

class TouchDisplay
{
private:
	SDL_Window* window;

public:
	TouchDisplay();
	virtual ~TouchDisplay();
};

#endif /* TOUCHDISPLAY_H */
