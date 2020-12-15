#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <ESD/gui/GraphicsElement.hpp>

class Button : public GraphicsElement
{
private:
	SDL_Rect rectangle;
	struct {
		unsigned char r,g,b,a;
	} color;
public:
	void render(SDL_Renderer* r);
	void process(SDL_Event* e);

	bool isPressed(SDL_Event* event);

	Button();
	~Button();
};

#endif /* BUTTON_H */
