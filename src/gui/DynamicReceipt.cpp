#include <ESD/gui/DynamicReceipt.hpp>
#include <iostream>
#include <ESD/gui/Colors.hpp>
#include <cstdlib>

DynamicReceipt::DynamicReceipt(Receipt* r) : receipt(r) {
	this->font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans-ExtraLight.ttf",11);
	if (font == nullptr) {
		std::cout << SDL_GetError() << std::endl;
	}

}

DynamicReceipt::~DynamicReceipt(){
	TTF_CloseFont(this->font);
}


void DynamicReceipt::render(SDL_Renderer* r){
	auto& color = Colors::black;
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
	SDL_Rect rect{0,0,400,480};
	SDL_RenderFillRect(r, &rect);
	SDL_Rect dst{0,0,0,0};
	auto lines = receipt->getReceiptLines();
	for (const auto& line : lines) {
		auto tex = lineToTexture(line,r);
		SDL_QueryTexture(tex, NULL, NULL, &(dst.w), &(dst.h));
		SDL_RenderCopy(r,tex,NULL,&dst);
		dst.y+= dst.h+2;
	}
}


void DynamicReceipt::process(SDL_Event* e){

}

SDL_Texture* DynamicReceipt::lineToTexture(const ReceiptLine& line, SDL_Renderer* r){
	auto generateTex = [&](const std::string& s){
		auto surf = TTF_RenderText_Solid(this->font,s.c_str(),Colors::black);
		auto tex = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		return tex;
	};

	auto quantity_tex = generateTex(std::to_string(line.quantity));
	auto total_price_tex = generateTex(std::to_string(line.total_price));
	auto price_tex = generateTex(std::to_string(line.price));
	auto name_tex = generateTex(line.name);

	// Create resulting texture and set as render target
	auto result = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 25);
	SDL_SetRenderTarget(r, result);
	SDL_SetRenderDrawColor(r, 255, 255, 255, 0);
	SDL_RenderClear(r);


	SDL_Rect rect{0,0,0,0};

	SDL_QueryTexture(price_tex,NULL,NULL,&(rect.w),&(rect.h));
	SDL_RenderCopy(r,price_tex,NULL,&rect);

	rect.y += rect.h;
	SDL_QueryTexture(name_tex,NULL,NULL,&(rect.w),&(rect.h));
	SDL_RenderCopy(r,name_tex,NULL,&rect);

	SDL_QueryTexture(total_price_tex,NULL,NULL,&(rect.w),&(rect.h));
	rect.y = 0;
	rect.x = 400 - rect.w;
	SDL_RenderCopy(r,total_price_tex,NULL,&rect);

	SDL_QueryTexture(quantity_tex,NULL,NULL,&(rect.w),&(rect.h));
	rect.x -= rect.w + 20;
	SDL_RenderCopy(r,quantity_tex,NULL,&rect);

	SDL_DestroyTexture(name_tex);
	SDL_DestroyTexture(total_price_tex);
	SDL_DestroyTexture(price_tex);
	SDL_DestroyTexture(quantity_tex);

	// Reset renderer
	SDL_SetRenderTarget(r, NULL);
	return result;
}	
