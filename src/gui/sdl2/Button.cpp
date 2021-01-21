#include <ESD/gui/sdl2/Button.hpp>
#include <iostream>
#include <SDL2/SDL_ttf.h>

#include <ESD/gui/sdl2/Colors.hpp>

Button::Button(const SDL_Rect& r,const SDL_Color& c, const std::string& s, SDL_Renderer* ren,
		void (*callback)(void*),void *data)
	: color(c), rectangle(r), callback(callback), data(data) {

	SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(ren, &(this->rectangle));

	TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans-ExtraLight.ttf",11);
	if (font == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_Surface *surf = TTF_RenderText_Solid(font, s.c_str(), Colors::black);
	if (surf == nullptr){
		std::cout << SDL_GetError() << std::endl;
	}

	this->texture = SDL_CreateTextureFromSurface(ren, surf);
	if (this->texture == nullptr){
		std::cout << SDL_GetError() << std::endl;
	}

	//Clean up
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
}


void Button::render(SDL_Renderer* r){
	SDL_SetRenderDrawColor(r, this->color.r, this->color.g, this->color.b, 255);
	SDL_RenderFillRect(r, &(this->rectangle));
	SDL_Rect dst;
	SDL_QueryTexture(this->texture, NULL, NULL, &(dst.w), &(dst.h));
	dst.x = rectangle.x + (rectangle.w-dst.w)/2;
	dst.y = rectangle.y + (rectangle.h-dst.h)/2;
	SDL_RenderCopy(r,this->texture,NULL,&dst);
}

void Button::process(SDL_Event* event) {
	if (isPressed(event)) {
		callback(data);
	} 
}

#define BETWEEN(s,e,l)  ( ((s)<(e)) && ((e)<(l)) )

bool Button::isPressed(SDL_Event* event){
	switch (event->type) {
		case SDL_MOUSEBUTTONDOWN:
			return ( BETWEEN(rectangle.x, event->button.x, rectangle.x + rectangle.w) &&
					BETWEEN(rectangle.y, event->button.y, rectangle.y + rectangle.h) );

			break;
		case SDL_FINGERDOWN:
			std::cout << "Touch Works" << std::endl;
			break;

		default:
			return false;
	}
	return false;
}

