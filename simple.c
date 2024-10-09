#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init(SDL_Window** window, SDL_Surface** screenSurface) {
  
  int success = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = 1;
  } else {
   *window = SDL_CreateWindow("my reaction to that information", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) { 
      printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
      success = 1;
    } else {
      *screenSurface = SDL_GetWindowSurface(*window);
    }
  }

  return success;
}

int loadMedia(SDL_Surface** sImage)  {
  // int success = 0;

  *sImage = SDL_LoadBMP("image.bmp");
  if (*sImage == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
    return 1;
  }

  return 0;
}

void q(SDL_Surface *sImage, SDL_Window *window) {
  SDL_FreeSurface(sImage);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *args[]) {
  
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  SDL_Surface* sImage = NULL;
  
  if (init(&window, &screenSurface) != 0) {
    printf("Failed to initialize\n");
  } else {
    if (loadMedia(&sImage) != 0) {
      printf("Failed to load media\n");
    } else {
      if (SDL_BlitSurface(sImage, NULL, screenSurface, NULL) < 0) {
        printf("Unable to blit surface! SDL Error: %s\n", SDL_GetError());
        q(sImage, window);
        return 1;
      }
      if (SDL_UpdateWindowSurface(window) < 0)  {
        printf("Unable to update window surface! SDL Error: %s\n", SDL_GetError());
        q(sImage, window);
        return 1;
      }
      SDL_Event e;
      int quit = 0;
      while (quit == 0) {
        while (SDL_PollEvent(&e)){
          if (e.type == SDL_QUIT) quit = 1;
        }
      }
    }
  }
  
  q(sImage, window);

  return 0;
}
