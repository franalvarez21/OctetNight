#pragma once

#define REAL_MAP_WEIGHT 20
#define REAL_MAP_HEIGHT 14
#define MAX_SQUARE_AMOUNT_WEIGHT 17
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 14
#define SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_SIZE 8
#define TOOLS_AVAILABLE 4
#define MAX_CAPACITY 9
#define REAL_MAX_CAPACITY 9999
#define SHEEP_MAX_AMOUNT 5
#define CYCLE_TIME 20

#define START_ENEMY_NUMBER 39
#define END_ENEMY_NUMBER 64
#define SEED_1_NUMBER 65
#define SEED_2_NUMBER 76
#define SEED_3_NUMBER 87
#define VOID_NUMBER 98
#define EMPTY_NUMBER 99

class Game
{
public:
  void setup(void);
  void loop(void);
  void load(void);
  void restart(void);
  void mainMenuTick(void);
  void mainGameTick(void);
  void mainPauseTick(void);
  void mainStoreMenuTick(void);
};
