#ifndef TYPES_H_
#define TYPES_H_

typedef enum
{
  FOREST,
  MINES,
  CRAFT,
  ITEMS,
  SECTION_COUNT
} Section;

typedef enum
{
  WOOD_T1,
  WOOD_T2,
  WOOD_T3,
  LEAF,
  APPLE,

  FOREST_OFFSET,
  
  STONE_T1,
  STONE_T2,
  STONE_T3,
  COPPER_ORE,
  TIN_ORE,
  
  RES_COUNT
} Res;

typedef enum
{
  STICK
} Item;

typedef enum
{
  
} Equipment;

typedef struct
{
  int min;
  int max;
} Range;

typedef enum
{
  REWARD_VALUE,
  REWARD_RANGE
} Reward_Type;

typedef struct
{
  int present;
  Reward_Type type;
  Range range;
  int value;
} Reward;

typedef struct
{
  double duration;
  Reward res_reward;
  Reward exp_reward;
} Res_Desc;

#define VALUE(x) {.present = 1, .type = REWARD_VALUE, .value = x}
#define RANGE(min, max) {.present = 1, .type = REWARD_RANGE, .range = (Range) {min, max}}

#endif // TYPES_H_
