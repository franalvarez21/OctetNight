#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <EEPROM.h>

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

#define STARTING_HP 4
#define MIN_HEALTH_ACTION 4
#define FOLLOW_DISTANCE 5
#define ENEMY_SPAWN_PERCENTAGE 10
#define PLANT_SPAWN_PERCENTAGE 5
#define ENEMY_BORDER_SPAWN_LIMIT 3

#define CYCLE_TIME 15
#define HURT_TIME 10
#define ENERGY_TIME 200
#define DIALOG_COOLDOWN 30

#define SEED_1_NUMBER 65
#define SEED_2_NUMBER 76
#define SEED_3_NUMBER 87
#define SEED_4_NUMBER 98
#define SEED_5_NUMBER 103
#define SEED_6_NUMBER 107
#define KEY_NUMBER 110
#define START_ENEMY_NUMBER 120
#define END_ENEMY_NUMBER 197
#define VOID_NUMBER 198
#define EMPTY_NUMBER 199

#define POTION_PRICE 100
#define BASIC_SEED_PACK_PRICE 50
#define MEDIUM_SEED_PACK_PRICE 200
#define SHEEP_PRICE 1000
#define RANDOM_PACK_BENEFITS 3

#define STAGE_MAINMENU 0
#define STAGE_PAUSE 1
#define STAGE_GAME 2
#define STAGE_STOREMENU 3
#define STAGE_GAMEOVER 4

#define SAVE_FILE_ADDRESS (EEPROM_STORAGE_SPACE_START + 64)
#define GAME_ID 111
#define MAX_RANGE 10000

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
  void loadGame(void);
  void saveGame(void);
  void mainMenuTick(void);
  void mainGameTick(void);
  void mainPauseTick(void);
  void mainStoreMenuTick(void);
  void mainGameOverTick(void);
  void changeStage(uint8_t stage);
};
