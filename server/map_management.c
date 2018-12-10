/*
** map_management.c for bomberman in /home/enach/CLionProjects/Bomberman/bm_test/server
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Sun Jul  1 17:37:50 2018
** Last update Sun Jul  1 23:23:51 2018 hochar_n
*/

#include <stdio.h>
#include "server.h"
#include "request.h"
#include "game_info.h"
#include "base_map.h"

int **get_array_map()
{
    static int map[14][15];
    int height;
    int width;

    height = 1;
    for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
        width = 0;
        // largeur
        for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
            SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};

            map[height][width] = draw_map_loop(i, j);
            width++;
        }
        height++;
    }

    return (int **) map;
}

void add_destructible_elements(
    t_game_info *game_info,
    int **map_pointer
)
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

    for (i = 1; i < 14; ++i) {
        for (j = 1; j < 15; ++j) {
            if (game_info->map_destroyable[i][j].exist == 0)
                continue;
            map_destroyable = game_info->map_destroyable[i][j];
            map_destroyable.exist = 1;
            map_pointer[map_destroyable.x_pos][map_destroyable.y_pos] = WALL;
        }
    }
}

void add_bomb_elements(
    t_game_info *game_info,
    int **map_pointer
)
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

    for (i = 1; i < 14; ++i) {
        for (j = 1; j < 15; ++j) {
            if (game_info->map_destroyable[i][j].exist == 0)
                continue;
            map_destroyable = game_info->map_destroyable[i][j];
            if (map_destroyable.bomb == 0
                || (map_destroyable.bomb == 1
                    && game_info->tick_time < map_destroyable.start_explode)
                )
                continue;
            if (map_destroyable.start_explode + 5 == game_info->tick_time) {
                destroy_bomb(game_info, map_pointer, map_destroyable);
                continue;
            }
            trigger_bomb(game_info, map_pointer, map_destroyable);
        }
    }
}

int is_there_a_wall(
    t_game_info *game_info,
    int **map_pointer,
    int x,
    int y
)
{
    int i;
    int j;
    t_map_destroyable map_destroyable;

    if (map_pointer[x][y] == WALL)
        return 1;
    for (i = 1; i < 14; ++i) {
        for (j = 1; j < 15; ++j) {
            if (game_info->map_destroyable[i][j].exist == 0
                || game_info->map_destroyable[i][j].bomb == 1)
                continue;
            map_destroyable = game_info->map_destroyable[i][j];
            if (map_destroyable.y_pos == y && map_destroyable.x_pos == x)
                return 1;
        }
    }

    return 0;
}
