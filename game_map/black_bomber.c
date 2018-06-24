#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <pthread.h>
#include "base_map.h"

void *black_bomber_sprite(void *arg)
{
  t_data *data = (t_data*)arg;
  data->players[0].bomber_sprites[bomber_d][not_move] = init_rect(70, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_d][move_l] = init_rect(52, 66, 16, 24);
    data->players[0].bomber_sprites[bomber_d][transit_move] = init_rect(70, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_d][move_r] = init_rect(88, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_l][not_move] = init_rect(124, 38, 16, 24);
  data->players[0].bomber_sprites[bomber_l][move_l] = init_rect(106, 66, 16, 24);
    data->players[0].bomber_sprites[bomber_l][transit_move] = init_rect(124, 66, 16, 24);

  data->players[0].bomber_sprites[bomber_l][move_r] = init_rect(143, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_r][not_move] = init_rect(179, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_r][move_l] = init_rect(160, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_r][transit_move] = init_rect(179, 66, 16, 24);

  data->players[0].bomber_sprites[bomber_r][move_r] = init_rect(197, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_u][not_move] = init_rect(237, 66, 16, 24);
  data->players[0].bomber_sprites[bomber_u][move_l] = init_rect(219, 66, 16, 24);
    data->players[0].bomber_sprites[bomber_u][transit_move] = init_rect(237, 66, 16, 24);

  data->players[0].bomber_sprites[bomber_u][move_r] = init_rect(255, 66, 16, 24);
   data->players[0].bomber_sprites[die][0] = init_rect(345, 66, 16, 24);
   data->players[0].bomber_sprites[die][1] = init_rect(361, 66, 16, 24);
   data->players[0].bomber_sprites[die][2] = init_rect(395, 66, 16, 24);
  return NULL;
}
