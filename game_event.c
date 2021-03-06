/*
** game_event.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:29:38 2018 MASERA Mathieu
** Last update Wed Jul  4 09:29:40 2018 MASERA Mathieu
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "sdl.h"
#include "request.h"
#include "player.h"
#include "base_map.h"


void *move_player_down(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].y += 6;
  data->players[0].looking = bomber_d;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].y % 18 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_d][data->players[0].index_sprite]), &dest);

return (NULL);
}

void *move_player_up(void *arg) {
  t_data *data = (t_data*)arg;
  data->players[0].looking = bomber_u;
  data->players[0].y -= 6;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].y % 18 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_u][data->players[0].index_sprite]), &dest);

return (NULL);
}

void *move_player_right(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].looking = bomber_r;
  data->players[0].x += 6;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].x % 18 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_r][data->players[0].index_sprite]), &dest);

return (NULL);
}

void *move_player_left(void *arg) {
  t_data *data = (t_data*)arg;

  data->players[0].x -= 6;
  data->players[0].looking = bomber_l;
  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};

  if (data->players[0].x % 18 == 0) {
    if (data->players[0].index_sprite == 3) {
      data->players[0].index_sprite = not_move;
    } else {
      data->players[0].index_sprite++;
    }
  }

  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[bomber_l][data->players[0].index_sprite]), &dest);

return (NULL);
}

void *move_player_stop(void *arg) {
  t_data *data = (t_data*)arg;

  SDL_Rect dest = {data->players[0].x, data->players[0].y, 16 * 3, 24 * 3};
  data->players[0].index_sprite = not_move;
  SDL_RenderCopy(data->renderer, data->texture,
		 &(data->players[0].bomber_sprites[data->players[0].looking][not_move]), &dest);
  return (NULL);
}
