#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<skypond.h>
#include <stdarg.h>
#include <macro.h>

static SDL_Window *main_window = nullptr;
static SDL_Renderer *main_renderer = nullptr;
static SDL_Surface *main_surface = nullptr;
static SDL_Texture *main_texture = nullptr;
int main()
{

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_PNG);

	main_window = SDL_CreateWindow("Skpond " VERSION_STR, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	main_renderer = SDL_CreateRenderer(main_window, -1, 
		SDL_RENDERER_SOFTWARE | 0
	);

	main_surface = IMG_Load("../resources/ui/fun2.png");
	main_texture = SDL_CreateTextureFromSurface(main_renderer, main_surface);

	SDL_RenderCopy(main_renderer, main_texture, NULL, NULL);
	SDL_RenderPresent(main_renderer);

	SDL_Delay(50000);

	SDL_DestroyRenderer(main_renderer);
	SDL_FreeSurface(main_surface);
	SDL_DestroyTexture(main_texture);
	SDL_DestroyWindow(main_window);

}