#ifndef TOUCHDISPLAY_H
#define TOUCHDISPLAY_H

#include <ESD/gui/TouchDisplayBackend.hpp>
#include <ESD/gui/sdl2/Button.hpp>


#include <vector>
#include <SDL2/SDL.h>

class TouchDisplaySDL2 : public TouchDisplayBackend {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<GraphicsElement*> elements;
	

public:
	TouchDisplaySDL2 ();
	~TouchDisplaySDL2 ();

	void process();

	// From interface
	void addModal(const Modal::shr_ptr& m);
	void deployLayout(const Layout::shr_ptr& l);
};

#endif /* TOUCHDISPLAY_H */
