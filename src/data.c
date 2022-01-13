#include "data.h"

const Res_Desc res_table[RES_COUNT] = {
  [WOOD_T1] = {
    // .requires = SKILL_TIER(WOODCHOPPING, 1),
    .duration = 3.0,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(11, 27)
  },
  [WOOD_T2] = {
    // .requires = SKILL_TIER(WOODCHOPPING, 2),
    .duration = 3.6,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(23, 39)
  },
  [WOOD_T3] = {
    // .requires = SKILL_TIER(WOODCHOPPING, 3),
    .duration = 4.1,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(34, 57)
  },
  [LEAF] = {
    // .requires = SKILL_TIER(WOODCHOPPING, 4),
    .duration = 1.9,
    .res_reward = RANGE(1, 3),
    .exp_reward = RANGE(24, 47)
  },
  [APPLE] = {
    // .requires = SKILL_TIER(WOODCHOPPING, 5),
    .duration = 2.7,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(36, 55)
  },

  [STONE_T1] = {
    // .requires = SKILL_TIER(MINING, 1),
    .duration = 3.1,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(12, 28)
  },
  [STONE_T2] = {
    // .requires = SKILL_TIER(MINING, 2),
    .duration = 3.7,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(23, 47)
  },
  [STONE_T3] = {
    // .requires = SKILL_TIER(MINING, 3),
    .duration = 4.2,
    .res_reward = VALUE(1),
    .exp_reward = RANGE(41, 68)
  },
  [COPPER_ORE] = {
    // .requires = SKILL_TIER(MINING, 4),
    .duration = 3.6,
    .res_reward = RANGE(1, 4),
    .exp_reward = RANGE(32, 57)
  },
  [TIN_ORE] = {
    // .requires = SKILL_TIER(MINING, 5),
    .duration = 4.3,
    .res_reward = RANGE(1, 2),
    .exp_reward = RANGE(46, 77)
  },
};
