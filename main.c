#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>

typedef struct s_data
{
  SDL_Texture	*texture;
  SDL_Renderer	*renderer;
  SDL_Window	*window;
} t_data;

// in the picture, the size of the square is 16 for a wall block, so i use 48

const int WINDOW_W = 1024;
const int WINDOW_H = 768;
const int PIXEL_SIZE = 48;
const int I_BEGIN = ((1024 - (15 * 48)) / 2 ) / 48;
const int J_BEGIN = (768 - (13 * 48)) / 48;

void *init_window(void * arg);
void *drawPlayer1(void *arg);
void *drawMapModel(void *arg);
void *drawScore(void *arg);
void *drawTimer(void *arg);
void *drawAll(void *arg);

int		main ()
{
  int		quit;
  SDL_Event	event;
  t_data	*data;

  quit = 0;
  data = malloc(sizeof(t_data));
  init_window((void*)data);
  drawAll((void*)data);
  SDL_SetRenderTarget(data->renderer, NULL);
  SDL_RenderPresent(data->renderer);
  SDL_RenderClear(data->renderer);
  while(!quit)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  quit = 1;
	  break;
	case SDL_KEYDOWN:
	  drawAll((void*)data);
	  break;
	} 
      SDL_SetRenderTarget(data->renderer, NULL);
      SDL_RenderClear(data->renderer);
    }
  SDL_DestroyTexture(data->texture);
  SDL_DestroyRenderer(data->renderer);
  SDL_DestroyWindow(data->window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}

void		*init_window(void * arg) {
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*sprite_texture;
  SDL_Surface	*sprites_img;

  t_data *data = (t_data*)arg;
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  window = SDL_CreateWindow(
			    "Bomberman",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    WINDOW_W,
			    WINDOW_H,
			    SDL_WINDOW_SHOWN
			    );  
  if (!window)
    {
      printf("windows not created");
      return (NULL);
    }
  
  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
    {
      SDL_ShowSimpleMessageBox(0, "renderer init error", SDL_GetError(), window);
    }
 
  sprites_img = IMG_Load("bombermanSprite.PNG");
  if (!sprites_img)
    {
      SDL_ShowSimpleMessageBox(0, "img init error", SDL_GetError(), window);
    }

  //we create the image as a texture to insert it in renderer
  sprite_texture = SDL_CreateTextureFromSurface(renderer, sprites_img);
  
  if (!sprite_texture)
    {
      SDL_ShowSimpleMessageBox(0, "texture image init error",
			       SDL_GetError(), window);
    } 
  SDL_FreeSurface(sprites_img);
  SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
  SDL_RenderClear(renderer);
  data->texture = sprite_texture;
  data->renderer = renderer;
  data->window = window;
  /* 
  ** important, use this to apply modification on last textures
  ** placed on the renderer
  */
  SDL_SetRenderTarget(data->renderer, NULL);
  return (NULL);
}

void *drawAll(void *arg)
{
  drawMapModel(arg);
  drawScore(arg);
  drawTimer(arg);
  drawPlayer1(arg);
  return (NULL);
}


void	*drawMapModel(void *arg)
{
  int	i, j, error;
  
  t_data *data = (t_data*)arg;
  error = 0;
  SDL_Rect wall_src_rect = {71, 175, 16, 16};
  SDL_Rect ground_src_rect = {122, 175, 16, 16};
  SDL_Rect ground_showed_rect = {105, 175, 16 ,16};
  for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
    for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
      SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE,
			    PIXEL_SIZE, PIXEL_SIZE};
      if (j == J_BEGIN || j == J_BEGIN + 12 ||
	  i == I_BEGIN || i == I_BEGIN + 14)
	error = SDL_RenderCopy(data->renderer, data->texture ,
			       &wall_src_rect, &dest_rect);
      else if (j == J_BEGIN + 1 ||
	       ( j % 2 != J_BEGIN % 2 && i % 2 == I_BEGIN % 2))
	error = SDL_RenderCopy(data->renderer, data->texture,
			       &ground_showed_rect, &dest_rect);
      else if (i % 2 != I_BEGIN % 2)
	error = SDL_RenderCopy(data->renderer, data->texture,
			       &ground_src_rect, &dest_rect);
      else if (i % 2 == I_BEGIN % 2)
	error = SDL_RenderCopy(data->renderer, data->texture,
			       &wall_src_rect, &dest_rect);
      if (error < 0)
	{
	  SDL_ShowSimpleMessageBox(0, "adding texture in renderer error",
				   SDL_GetError(), data->window);
	  break;
	}
    }
    if (error < 0)
      break;
  }
  if (error < 0)
    return (NULL);
  return ((void*)data);
}


void	*drawScore(void *arg)
{
  int	error;

  error = 0;
  t_data *data = (t_data*) arg;
  SDL_Rect score_panel_rect = {414, 175, 256, 32};
  SDL_Rect dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &score_panel_rect, &dest_rect_score);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Score Tab Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}

void	*drawTimer(void *arg)
{
  int	error;

  error = 0;
  t_data *data = (t_data*) arg;
  SDL_Rect timer_panel_rect = {413, 37, 32, 14};
  SDL_Rect dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};
  SDL_Rect dest_rect_timer = {(WINDOW_W / 2) - ((timer_panel_rect.w / 2) * 5),
			      (dest_rect_score.h / 2) -
			      ((timer_panel_rect.h / 2) * 5),
			      timer_panel_rect.w * 5,
			      timer_panel_rect.h * 5};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &timer_panel_rect, &dest_rect_timer);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Timer Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}

void	*drawPlayer1(void *arg) {
  int	error;

  error = 0;
  t_data *data = (t_data*)arg;
  SDL_Rect bomberman_white = {70, 38, 16, 24};
  SDL_Rect dest_rect = {(I_BEGIN + 1) * 48, ((J_BEGIN + 1) * 48) - 24 ,
			16 * 3, 24 * 3};
  error = SDL_RenderCopy(data->renderer, data->texture,
			 &bomberman_white, &dest_rect);
  if (error < 0)
    SDL_ShowSimpleMessageBox(0, "drawing Player1 Failed",
			     SDL_GetError(), data->window);
  return (NULL);
}
