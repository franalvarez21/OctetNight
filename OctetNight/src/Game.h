#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>

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
#define MIN_HEALTH_ACTION 4

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
#define KEY_NUMBER 110
#define VOID_NUMBER 198
#define EMPTY_NUMBER 199

#define POTION_PRICE 150
#define BASIC_SEED_PACK_PRICE 50
#define MEDIUM_SEED_PACK_PRICE 200
#define SHEEP_PRICE 1000
#define RANDOM_PACK_BENEFITS 4

#define STAGE_MAINMENU 0
#define STAGE_PAUSE 1
#define STAGE_GAME 2
#define STAGE_STOREMENU 3
#define STAGE_GAMEOVER 4

#include "utils/const/Map.h"
#include "utils/const/Common.h"
#include "utils/const/Mini.h"
#include "utils/const/Lines.h"
#include "utils/const/Title.h"
#include "utils/const/Cards.h"
#include "utils/const/Seeds.h"
#include "utils/const/Hub.h"
#include "utils/const/Digits.h"

#include "utils/Cycle.h"
#include "utils/Stats.h"
#include "utils/Effects.h"
#include "utils/Numbers.h"
#include "utils/Dialogs.h"
#include "utils/LevelProgression.h"
#include "world/World.h"

#include "menus/Menu.h"
#include "menus/TitleMenu.h"
#include "menus/PauseMenu.h"
#include "menus/StoreMenu.h"
#include "menus/GameOver.h"

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
  void changeStage(uint8_t stage);
};
