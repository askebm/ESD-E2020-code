#include <ESD/gui/TouchDisplay.hpp>
#include <iostream>

TouchDisplay::TouchDisplay() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
		std::cout << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow("TouchDisplay",100,100,800,480,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(this->window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
}

TouchDisplay::~TouchDisplay() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
