#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#include "types.h"
#include "render.h"
#include "util.h"
#include "data.h"
#include "game.h"
#include "vec.h"

#define COLOR_GREEN "\e[38;5;154m"
#define COLOR_RED "\e[38;5;196m"
#define INVERT_COLOR "\e[7m"
#define RESET_COLOR "\e[0m"

Game_State *game;

void header(void)
{
  printf("\n");
  
  char *lvl_buf = malloc(1024);
  sprintf(lvl_buf, "LVL %d  %s  %d EXP",
	  game->lvl,
	  progress_bar(40, game->cur_exp, game->need_exp),
	  game->total_exp);
  printf("%s%s\n\n", center(strlen(lvl_buf) - 40 * 2), lvl_buf);

  int len = 0;
  for (int sec = 0; sec < SECTION_COUNT; sec++) {
    len += strlen(render_section(sec));
  }
  printf("%s", center(len + SECTION_COUNT - 1));
  for (int sec = 0; sec < SECTION_COUNT; sec++) {
    if (sec == game->section) {
      printf("%s%s%s ", INVERT_COLOR, render_section(sec), RESET_COLOR);
    } else {
      printf("%s ", render_section(sec));
    }
  }
  
  printf("\n\n\n");
}

char *res(Res r)
{
  char *buf = malloc(1024);
  sprintf(buf, "%s%s%s  (You have %d)",
	  meet_req(game, r) ?
	  COLOR_GREEN : COLOR_RED, render_res_desc(r),
	  RESET_COLOR,
          game->resources[r]);
  if (game->is_gathering && game->gather_res == r) {
    sprintf(buf + strlen(buf), "  %s", progress_bar(12, game->gather_elapsed, res_table[r].duration));
  }
  return buf;
}

void update(void)
{
  update_level(game);
  
  if (game->is_gathering) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    game->gather_elapsed = (end.tv_sec - game->gather_start.tv_sec) +
      (end.tv_nsec - game->gather_start.tv_nsec) * 1e-9;

    if (game->gather_elapsed >= res_table[game->gather_res].duration) {
      game->is_gathering = 0;
      Res_Desc desc = res_table[game->gather_res];
      game->cur_exp += parse_reward(desc.exp_reward);
      game->total_exp += parse_reward(desc.exp_reward);
      game->resources[game->gather_res] += parse_reward(desc.res_reward);
    }
  }
}

#define add_res(r) vec_push(v, res(r));

int main(void)
{
  struct termios term;
  init_term(&term);

  game = init_game_state();

  int ix = 0;
  int quit = 0;
  while (!quit) {
    usleep(1e6 * (1.0 / 60));

    update();
    clear();
    header();
    
    vec *v = new_vec();

    switch (game->section) {
    case FOREST:          
      add_res(WOOD_T1);
      add_res(WOOD_T2);
      add_res(WOOD_T3);
      add_res(LEAF);
      add_res(APPLE);
      break;
    case MINES:
      add_res(STONE_T1);
      add_res(STONE_T2);
      add_res(STONE_T3);
      add_res(COPPER_ORE);
      add_res(TIN_ORE);
      break;
    case CRAFT:
      //  Not yet
      break;
    case ITEMS:
      //  Not yet
      break;
    default:
      unreachable(&term, "unknown section in function main");
    }

    for (int i = 0; i < v->count; i++) {
      printf("%*s%s%s\n",
	     30, "",
	     i == ix ? "* " : "  ",
	     v->elems[i]);
    }

    gotoxy(0, term_height() - 3);
    printf("[↑←↓→]   Navigate\n");
    printf("[Z/RET]  Select\n");
    printf("[Q]      Exit\n");
    
    int key = getch();
    switch (key) {
    case 279165: // ↑
      if (ix) {
	ix--;
      } else {
	ix = v->count - 1;
      }
      break;
    case 279166: // ↓
      if (ix + 1 == v->count) {
	ix = 0;
      } else {
	ix++;
      }
      break;
    case 279167: // →
      ix = 0;
      if (game->section + 1 == SECTION_COUNT) {
	game->section = 0;
      } else {
	game->section++;
      }
      break;
    case 279168: // ←
      ix = 0;
      if (game->section) {
	game->section--;
      } else {
	game->section = SECTION_COUNT - 1;
      }
      break;
    case 10: // RET
    case 'z':
      switch (game->section) {
      case FOREST:
	gather_res(game, (Res) ix);
	break;
      case MINES:
	gather_res(game, (Res) ix + FOREST_OFFSET + 1);
	break;
      case CRAFT:
	// Not yet.
	break;
      case ITEMS:
	// Not yet.
	break;
      default:
	unreachable(&term, "unknown section in function main");
      }
      break;
    case 'q':
      quit = 1;
      break;
    default:
      break;
    }
  }
  
  exit_term(&term);
  return 0;
}
