#include <ESD/gui/sdl2/TouchDisplaySDL2.hpp>
#include <ESD/gui/sdl2/DynamicReceipt.hpp>
#include <ESD/gui/sdl2/Colors.hpp>

#include <iostream>
#include <SDL2/SDL_ttf.h>


TouchDisplaySDL2::TouchDisplaySDL2 (int w, int h) :
width(w), height(h){
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
		std::cout << SDL_GetError() << std::endl;
	}
	window = SDL_CreateWindow("TouchDisplay",0,0,width,height,SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(this->window,-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}
	if (TTF_Init() != 0){
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

//	auto rec  = new Receipt;
//	DynamicReceipt* drec = new DynamicReceipt(rec);
//
//	rec->addReceiptLine(100,"Test",22,3);
//	elements.push_back(drec);
//
//	rec->addReceiptLine(101,"Test2",22,3);
//	elements.push_back(drec);
//
//	auto btn = Button::Small(400,0,Colors::amber,renderer);
//	elements.push_back(btn);
//	btn = Button::Small(400,128,Colors::antique_ruby,renderer);
//	elements.push_back(btn);
}

void  TouchDisplaySDL2::process (){
	// Handle Events
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		for (const auto&	e : this->elements) {
			e->process(&event);
		}
	}
	render();
}

void TouchDisplaySDL2::render(){
	// Render result
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	for (const auto&	e : this->elements) {
		e->render(this->renderer);
	}
	SDL_RenderPresent(renderer);
}


TouchDisplaySDL2::~TouchDisplaySDL2 (){

}
void TouchDisplaySDL2::addModal(const Modal::shr_ptr& m){

}

void TouchDisplaySDL2::clear(){
	// Clear old layout
	for (GraphicsElement* e : elements) {
		delete(e);
	}
	if (elements.size() != 0) {
		elements.erase(elements.begin());
		
	}
}

GraphicsElement* TouchDisplaySDL2::elementToSDL(const Layout::Element& e,const double& scale_x,const double& scale_y){
	using Type = Layout::Element::Type;

	GraphicsElement* e_sdl = nullptr;
	SDL_Rect rect{
		.x = static_cast<int>(e.start_x*scale_x),
			.y=static_cast<int>(e.start_y*scale_y), 
			.w=static_cast<int>( (e.end_y - e.start_y)*scale_y ),
			.h=static_cast<int>( (e.end_x - e.start_x)*scale_x )
	};


	switch (e.type) {
		case Type::Button:
			{
				auto btn = new Button(rect,Colors::red,e.text,renderer,e.callback);
				e_sdl = btn;
			}
			break;
		case Type::Receipt:
			{
				auto rcp = new DynamicReceipt(e.receipt,rect);
				e_sdl = rcp;
			}
			break;
		default: 
			break;
	}
	return e_sdl;
}


void TouchDisplaySDL2::deployLayout(const Layout::shr_ptr& l){
	clear();
	auto& basic_elements = l->getElements();

	double scale_x = double(width)/l->getWidth();
	double scale_y = double(height)/l->getHeight();

	for (const auto& be : basic_elements) {
		elements.push_back(elementToSDL(be,scale_x,scale_y));
	}
	render();
}


