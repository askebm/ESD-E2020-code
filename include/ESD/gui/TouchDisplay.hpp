#ifndef TOUCHDISPLAY_H
#define TOUCHDISPLAY_H
#include <vector>

#include <SDL2/SDL.h>
#include <ESD/gui/GraphicsElement.hpp>


class TouchDisplay
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<GraphicsElement*> elements;

public:
	void process();
	TouchDisplay();
	~TouchDisplay();
};

#endif /* TOUCHDISPLAY_H */
