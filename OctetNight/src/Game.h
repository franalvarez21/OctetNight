#pragma once

#define REAL_MAP_WEIGHT 20
#define REAL_MAP_HEIGHT 14
#define MAX_SQUARE_AMOUNT_WEIGHT 17
#define MAX_SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_AMOUNT_WEIGHT 14
#define SQUARE_AMOUNT_HEIGHT 9
#define SQUARE_SIZE 8
#define GAME_SPEED 5
#define GAME_TIMEOUT_SPEED 2
#define TOOLS_AVAILABLE 5
#define MAX_CAPACITY 9
#define REAL_MAX_CAPACITY 9999
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
};
