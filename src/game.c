#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "render.h"
#include "data.h"

Game_State *init_game_state(void)
{
  Game_State *game = malloc(sizeof *game);

  game->section = FOREST;

  game->lvl = 1;
  game->cur_exp = 0;
  game->need_exp = 73;
  game->total_exp = 0;
  
  int resources[RES_COUNT] = {
      [WOOD_T1] = 0
  };
  memcpy(game->resources, resources, sizeof resources);

  game->is_gathering = 0;
  
  return game;
}

int meet_req(Game_State *game, Res r)
{
  switch (r) {
  case WOOD_T1:
    return 1;
  default:
    return 0;
  }
}

void gather_res(Game_State *game, Res r)
{
  if (!game->is_gathering) {
    if (meet_req(game, r)) {
      game->is_gathering = 1;
      game->gather_res = r;
      clock_gettime(CLOCK_MONOTONIC, &game->gather_start);
    }
  }
}
