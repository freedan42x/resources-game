#ifndef UTIL_H_
#define UTIL_H_

#include "types.h"
#include "game.h"
#include "termios.h"

#define MAX_INPUT_SIZE 16
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"

void clear(void);
int rand_range(int min, int max);
char *progress_bar(int width, double cur, double total);
int term_width(void);
int term_height(void);
void gotoxy(int x, int y);
char *center(int len);
int parse_reward(Reward reward);
void update_level(Game_State *game);
void init_term(struct termios *term);
void exit_term(struct termios *term);
void unreachable(struct termios *term, char *msg);
int getch(void);

#endif // UTIL_H_
