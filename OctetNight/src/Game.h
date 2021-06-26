#pragma once

#define REAL_MAP_WEIGHT 20
#define REAL_MAP_HEIGHT 14
#define MAX_SQUARE_AMOUNT_WEIGHT 17
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 14
#define SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_SIZE 8
#define TOOLS_AVAILABLE 4
#define SEEDS_AVAILABLE 6
#define MAX_CAPACITY 9
#define REAL_MAX_CAPACITY 9999
#define SHEEP_MAX_AMOUNT 8
#define MIN_HEALTH_ACTION 2

#define CYCLE_TIME 20
#define ENERGY_TIME 200
#define DIALOG_COOLDOWN 30

#define START_ENEMY_NUMBER 39
#define END_ENEMY_NUMBER 64
#define SEED_1_NUMBER 65
#define SEED_2_NUMBER 76
#define SEED_3_NUMBER 87
#define SEED_4_NUMBER 98
#define SEED_5_NUMBER 103
#define SEED_6_NUMBER 107
#define VOID_NUMBER 198
#define EMPTY_NUMBER 199

#define POTION_PRICE 150
#define BASIC_SEED_PACK_PRICE 50
#define MEDIUM_SEED_PACK_PRICE 200
#define SHEEP_PRICE 1000
#define RANDOM_PACK_BENEFITS 4

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
  void mainGameOverTick(void);
  void dialogNotTired(void);
  void dialogNewDay(void);
  void dialogNotAtHome(void);
};
