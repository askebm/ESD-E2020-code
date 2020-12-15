#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

class Button
{
private:
	SDL_Event* event;
	SDL_Rect rectangle;
	struct {
		unsigned char r,g,b,a;
	} color;
public:
	void render(SDL_Renderer* r);

	bool isPressed();

	Button(SDL_Event* event);
	virtual ~Button();
};

#endif /* BUTTON_H */
