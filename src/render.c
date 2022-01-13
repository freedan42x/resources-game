#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "render.h"
#include "types.h"
#include "data.h"

char *render_section(Section section)
{
  switch (section) {
  case FOREST:
    return "[Forest]";
  case MINES:
    return "[Mines]";
  case CRAFT:
    return "[Craft]";
  case ITEMS:
    return "[Items]";
  default:
    fprintf(stderr, "render_section: Unreachable");
    exit(1);
  }
}

char *render_reward(Reward reward)
{
  char *buf = malloc(256);
  switch (reward.type) {
  case REWARD_VALUE:
    sprintf(buf, "%d", reward.value);
    return buf;
  case REWARD_RANGE:
    sprintf(buf, "%d~%d", reward.range.min, reward.range.max);
    return buf;
  default:
    fprintf(stderr, "render_reward: Unreachable");
    exit(1);
  }
}

char *render_res_type(Res res)
{
  switch (res) {

  case WOOD_T1:
    return "Wood T1";
  case WOOD_T2:
    return "Wood T2";
  case WOOD_T3:
    return "Wood T3";
  case LEAF:
    return "Leaf";
  case APPLE:
    return "Apple";

  case STONE_T1:
    return "Stone T1";
  case STONE_T2:
    return "Stone T2";
  case STONE_T3:
    return "Stone T3";
  case COPPER_ORE:
    return "Copper Ore";
  case TIN_ORE:
    return "Tin Ore";
    
  default:
    fprintf(stderr, "render_res_type: Unreachable");
    exit(1);
  }
}

char *render_res_desc(Res res)
{
  char *buf = malloc(1024);
  const Res_Desc desc = res_table[res];

  sprintf(buf, "%s%*s[+%s%*s%s EXP]",
	  render_res_type(res),
	  12 - (int) strlen(render_res_type(res)), "",
	  render_reward(desc.res_reward),
	  5 - (int) strlen(render_reward(desc.res_reward)), "",
	  render_reward(desc.exp_reward));
  return buf;
}
