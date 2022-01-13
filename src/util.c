#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

#include "util.h"

void clear(void)
{
  printf("\e[1;1H\e[2J");
}

int rand_range(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}

char *progress_bar(int width, double cur, double total)
{
  char *buf = malloc(1024);
  char *bar_buf = malloc(1024);

  int prog_width = cur * width / total;
  for (int i = 0; i < width; i++) {
    strcat(bar_buf, (i < prog_width) ? "█" : "░");
  }
  sprintf(buf, "%s", bar_buf);

  return buf;
}

static struct winsize w;

int term_width(void)
{
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

int term_height(void)
{
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row; 
}

void gotoxy(int x, int y)
{
  printf("\033[%d;%dH", y, x);
}

char *center(int len)
{
  char *buf = malloc(1024);
  sprintf(buf, "%*s", (term_width() - len) / 2, "");
  return buf;
}

int parse_reward(Reward reward)
{
  if (!reward.present) {
    return 0;
  }
  switch (reward.type) {
  case REWARD_VALUE:
    return reward.value;
  case REWARD_RANGE:
    return rand_range(reward.range.min, reward.range.max);
  default:
    fprintf(stderr, "parse_reward: Unreachable");
    exit(1);
  }
}

void update_level(Game_State *game)
{
  while (game->cur_exp >= game->need_exp) {
    game->cur_exp -= game->need_exp;
    game->lvl++;
    game->need_exp = game->need_exp + pow(game->need_exp, 3.0 / 4.0) + log2(game->need_exp) + game->lvl;
  }
}

void init_term(struct termios *term)
{
  srand(time(NULL));
  printf(HIDE_CURSOR);
  
  tcgetattr(STDIN_FILENO, term);

  struct termios new_term;
  memcpy(&new_term, term, sizeof new_term);
  new_term.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void exit_term(struct termios *term)
{
  printf(SHOW_CURSOR);
  tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void unreachable(struct termios *term, char *msg)
{
  fprintf(stderr, "%s", msg);
  exit_term(term);
  exit(1);
}

int kbhit() {
  setbuf(stdin, NULL);
  int bytes;
  ioctl(STDIN_FILENO, FIONREAD, &bytes);

  return bytes;
}

int getch(void) {
  int c = 0;

  struct termios org_opts, new_opts;

  tcgetattr(STDIN_FILENO, &org_opts);
  
  memcpy(&new_opts, &org_opts, sizeof new_opts);
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

  if (kbhit()) {
    c = getchar();
    if (c == 27) {
      int d = getchar();
      int e = getchar();
      c = c * 10000 + d * 100 + e;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  }

  return c;
}
