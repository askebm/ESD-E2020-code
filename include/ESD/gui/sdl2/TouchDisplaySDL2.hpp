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

	int width,height;
	

public:
	TouchDisplaySDL2 (int w=800,int=480);
	~TouchDisplaySDL2 ();

	void render();
	void process();
	void clear();

	GraphicsElement* elementToSDL(const Layout::Element&,const double&,const double&);

	// From interface
	void addModal(const Modal::shr_ptr& m);
	void deployLayout(const Layout::shr_ptr& l);
};

#endif /* TOUCHDISPLAY_H */
