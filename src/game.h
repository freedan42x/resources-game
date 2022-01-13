#ifndef GAME_H_
#define GAME_H_

#include <time.h>

#include "types.h"

typedef struct
{
  Section section;
  int lvl;
  int cur_exp;
  int need_exp;
  int total_exp;
  int resources[RES_COUNT];
  int is_gathering;
  Res gather_res;
  struct timespec gather_start;
  double gather_elapsed;
} Game_State;

Game_State *init_game_state(void);
int meet_req(Game_State *game, Res r);
void gather_res(Game_State *game, Res r);

#endif // GAME_H_
