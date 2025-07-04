#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 960
#define HEIGHT 480

SDL_Window* window;
SDL_Surface* surface;

uint32_t* pixels;
bool keys[512];

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	pixels = (uint32_t*)surface->pixels;
	
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				keys[e.key.keysym.sym] = true;
			}
			else if (e.type == SDL_KEYUP) {
				keys[e.key.keysym.sym] = false;
			}
		}
		SDL_LockSurface(surface);
		
		
		SDL_UnlockSurface(surface);
		SDL_UpdateWindowSurface(window);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}
