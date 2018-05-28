#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

int main ()
{
  int		quit = 0;
  SDL_Window	*window;
  SDL_Event	event;
  SDL_Renderer	*renderer;
  SDL_Surface	*sprites_img;
  SDL_Texture	*sprite_texture;
  int		i, j, ibegin, jbegin, error;
  
  const int WINDOW_W = 1024;
  const int WINDOW_H = 768;
  // in the picture, the size of the square is 16 for a wall block, so i use 48
  const int PIXEL_SIZE = 48;
  
  /*
  ** we define where is the first pixel of the texture's image we want to use
  ** and its sizes
  */
  
  SDL_Rect wall_src_rect = {71, 175, 16, 16};
  SDL_Rect ground_src_rect = {122, 175, 16, 16};
  SDL_Rect ground_showed_rect = {105, 175, 16 ,16};
  SDL_Rect score_panel_rect = {414, 175, 256, 32};
  SDL_Rect timer_panel_rect = {413, 37, 32, 14};

  // it helps to know where i begin to draw the squares in the for loop
  ibegin = ((WINDOW_W - (15 * PIXEL_SIZE)) / 2 ) / PIXEL_SIZE;
  jbegin = ((WINDOW_H - (13 * PIXEL_SIZE))) / PIXEL_SIZE;

  error = 0;

  //init sdl
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  
  //init the window
  window = SDL_CreateWindow(
			    "Bomberman",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    WINDOW_W,
			    WINDOW_H,
			    SDL_WINDOW_SHOWN
			    );  
  if (!window) {
    printf("windows not created");
    return 1;
  }
  
  //where the image will be rendered
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer){
    SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
  }
 
  
  sprites_img = IMG_Load("bombermanSprite.PNG");
  if (!sprites_img){
    SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), window);
  }

  //we create the image as a texture to insert it in renderer
  sprite_texture = SDL_CreateTextureFromSurface(renderer, sprites_img);
  
 if (!sprite_texture){
    SDL_ShowSimpleMessageBox(0, "texture image init error", SDL_GetError(), window);
  } 

  SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
  SDL_RenderClear(renderer);


  //place all the squares for the map where it needs to be
  for (j = jbegin; j < jbegin + 13; j++) {
    for (i = ibegin; i < ibegin + 15; i++) {
      SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE,
			    PIXEL_SIZE, PIXEL_SIZE};
      if (j == jbegin || j == jbegin + 12 || i == ibegin || i == ibegin + 14) {
	error = SDL_RenderCopy(renderer, sprite_texture ,
			       &wall_src_rect, &dest_rect);
      } else if (j == jbegin + 1 ||
		 ( j % 2 != jbegin % 2 && i % 2 == ibegin % 2)) {
	error = SDL_RenderCopy(renderer, sprite_texture,
			       &ground_showed_rect, &dest_rect);
      } else if (i % 2 != ibegin % 2) {
	error = SDL_RenderCopy(renderer, sprite_texture,
			       &ground_src_rect, &dest_rect);
      } else if (i % 2 == ibegin % 2) {
	error = SDL_RenderCopy(renderer, sprite_texture,
			       &wall_src_rect, &dest_rect);
      }
      if (error < 0) {
	SDL_ShowSimpleMessageBox(0, "adding texture in renderer error",
				 SDL_GetError(), window);
	break;
      }
    }
    if (error < 0)
      break;
  }

  SDL_Rect dest_rect_score = {0, 0, WINDOW_W , jbegin * PIXEL_SIZE};
  SDL_RenderCopy(renderer, sprite_texture, &score_panel_rect, &dest_rect_score);
  SDL_Rect dest_rect_timer = {(WINDOW_W / 2) - ((timer_panel_rect.w / 2) * 5),
			      (dest_rect_score.h / 2) -
			      ((timer_panel_rect.h / 2) * 5),
			      timer_panel_rect.w * 5,
			      timer_panel_rect.h * 5};
  SDL_RenderCopy(renderer, sprite_texture, &timer_panel_rect, &dest_rect_timer);
  /* 
  ** important, use this to apply modification on last textures
  ** placed on the renderer
  */
  
  SDL_SetRenderTarget(renderer, NULL);

  //SDL_RenderPresent(renderer);
  while(!quit) {
    SDL_WaitEvent(&event);

    switch(event.type)
      {
      case SDL_QUIT:
	quit = 1;
	break;
      }
    
    SDL_RenderPresent(renderer);
  }

 
  SDL_DestroyTexture(sprite_texture);
  SDL_FreeSurface(sprites_img);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
