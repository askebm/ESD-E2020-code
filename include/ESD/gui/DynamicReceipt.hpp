#ifndef DYNAMICRECEIPT_H
#define DYNAMICRECEIPT_H

#include <vector>

#include <SDL2/SDL_ttf.h>

#include <receipt.hpp>

#include <ESD/gui/GraphicsElement.hpp>


class DynamicReceipt : public GraphicsElement
{
private:
	Receipt* receipt;
	TTF_Font* font;

	SDL_Texture* lineToTexture(const ReceiptLine&, SDL_Renderer*);

public:
	void render(SDL_Renderer* r);
	void process(SDL_Event* e);

	DynamicReceipt(Receipt* r);
	~DynamicReceipt();
};

#endif /* DYNAMICRECEIPT_H */
