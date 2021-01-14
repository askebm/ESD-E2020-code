#ifndef GRAPHICSELEMENT_H
#define GRAPHICSELEMENT_H
#include <SDL2/SDL.h>


class GraphicsElement
{
public:
	virtual void render(SDL_Renderer*) = 0;
	virtual void process(SDL_Event*) = 0;
};

#endif /* GRAPHICSELEMENT_H */
