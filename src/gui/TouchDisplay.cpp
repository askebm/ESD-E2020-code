#include <ESD/gui/TouchDisplay.hpp>
#include <iostream>

#include <ESD/gui/Button.hpp>

TouchDisplay::TouchDisplay() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
		std::cout << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow("TouchDisplay",0,0,800,480,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(this->window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	auto btn = new Button();
	elements.push_back(btn);


}


void TouchDisplay::process(){
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		for (const auto&	e : this->elements) {
			e->process(&event);
		}
	}

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	for (const auto&	e : this->elements) {
		e->render(this->renderer);
	}
	SDL_RenderPresent(renderer);
}

TouchDisplay::~TouchDisplay() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
