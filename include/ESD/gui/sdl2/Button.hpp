#ifndef BUTTON_H
#define BUTTON_H

#include <ESD/gui/sdl2/GraphicsElement.hpp>

#include <SDL2/SDL.h>

#include <string>

class Button : public GraphicsElement
{
	private:
		SDL_Rect rectangle;
		SDL_Color color;
		SDL_Texture* texture;
		void (*callback)();
	public:
		void render(SDL_Renderer* r);
		void process(SDL_Event* e);

		bool isPressed(SDL_Event* event);

		// Default for diffrent sizes
		static inline Button* Small(const int& x, const int& y, const SDL_Color& c,SDL_Renderer* ren,
				void (*callback)() = nullptr, const std::string& s = std::string("Small")){
			SDL_Rect r{ .x = x, .y = y , .w = 128, .h=128};
			return new Button(r,c,s,ren);
		}
		static inline Button* Medium(const int& x, const int& y, const SDL_Color& c,SDL_Renderer* ren,
				void (*callback)() = nullptr, std::string s = std::string("Medium")){
			SDL_Rect r{ .x = x, .y = y , .w = 256, .h=128};
			return new Button(r,c,s,ren);
		}
		static inline Button* Big(const int& x, const int& y, const SDL_Color& c, SDL_Renderer* ren,
				void (*callback)() = nullptr, std::string s = std::string("Big")){
			SDL_Rect r{ .x = x, .y = y , .w = 256, .h=256};
			return new Button(r,c,s,ren);
		}

		Button(const SDL_Rect&,const SDL_Color&, const std::string&, SDL_Renderer*, void (*callback)() = nullptr);
		~Button();
};

#endif /* BUTTON_H */
