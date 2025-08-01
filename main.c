#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIDTH 960
#define HEIGHT 480

SDL_Window* window;
SDL_Surface* surface;

uint32_t* pixels;
bool keys[512];

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return (uint32_t)SDL_MapRGB(surface->format, r, g, b);
}

void pixel(int x, int y, uint32_t color) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
	pixels[y * WIDTH + x] = color;
}

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
		memset(pixels, 0, sizeof(uint32_t) * WIDTH * HEIGHT);

		pixel(100, 100, 0xFFFFFFFF);

		
		SDL_UnlockSurface(surface);
		SDL_UpdateWindowSurface(window);
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}
