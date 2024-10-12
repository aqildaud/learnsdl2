#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

int main(int argc, char* args[])  {
  
  SDL_Window* win = NULL;
  SDL_Renderer* r = NULL;
  SDL_Rect rect = { 0, 0, 10, 10 };
  
  const int s = 10;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("SDL Error: %s\n", SDL_GetError());
  } else {
    win = SDL_CreateWindow("untitled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if  (win == NULL) printf("SDL Error: %s\n", SDL_GetError());
    else {
      r = SDL_CreateRenderer(win, 0, 0);

      SDL_Event e;
      int q = 0;
      while (q == 0) {
        while (SDL_PollEvent(&e))  {
          if  (e.type == SDL_QUIT) q = 1;

          if  (e.type == SDL_KEYDOWN) { 
            if  (e.key.keysym.sym == SDLK_w) {
              rect.y -= s;
            }
            else if  (e.key.keysym.sym == SDLK_s) {
              rect.y += s;
            }
            else if  (e.key.keysym.sym == SDLK_a) {
              rect.x -= s;
            }
            else if  (e.key.keysym.sym == SDLK_d) {
              rect.x += s;
            }
          }
        }

        if (rect.x < 0) rect.x = 0;
        if (rect.x > SCREEN_WIDTH - rect.w) rect.x = SCREEN_WIDTH - rect.w;
        if (rect.y < 0) rect.y = 0;
        if (rect.y > SCREEN_HEIGHT - rect.h) rect.y = SCREEN_HEIGHT - rect.h;

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
        SDL_RenderFillRect(r, &rect);
        SDL_RenderPresent(r);
      }
    }
  }
  
  SDL_DestroyRenderer(r);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
