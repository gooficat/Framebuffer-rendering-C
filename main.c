#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window;
SDL_Surface *surface;
Uint32 *pixels;

void drawPixel( int x, int y, Uint32 color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        pixels[y * WIDTH + x] = color;
    }
}

Uint32 rgb(int r, int g, int b) {
    return SDL_MapRGB(surface->format, r, g, b);
}

int WinMain(int argc, char *argv[]) {
    if (SDL_VideoInit(NULL) < 0) return -1;
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { SDL_VideoQuit(); return -1; }
    surface = SDL_GetWindowSurface(window);
    if (!surface) { SDL_DestroyWindow(window); SDL_VideoQuit(); return -1; }
    

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) if (event.type == SDL_QUIT) quit = true;


	pixels = (Uint32*)surface->pixels;
	memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));


        drawPixel(0, 0, rgb(255, 0, 255));
        

	SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_VideoQuit();
    return 0;
}

