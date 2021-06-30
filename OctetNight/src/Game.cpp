
#include "Game.h"

Arduboy2Base arduboy;
uint8_t onStage;
uint8_t action;
bool saveFile;
byte gameID;

Cycle cycle;
Effects effects;
Stats stats;
Dialogs dialogs;
World world;

TitleMenu titleMenu;
PauseMenu pauseMenu;
StoreMenu storeMenu;
GameOver gameOver;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();
  gameID = GAME_ID;

  saveFile = false;
  if ((EEPROM.read(SAVE_FILE_ADDRESS) == gameID) && (EEPROM.read(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats) + sizeof(uint8_t[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT])) == gameID))
  {
    saveFile = true;
  }

  cycle.init();
  restart();
}

void Game::loadGame(void)
{
  if (saveFile)
  {
    uint8_t map[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];
    EEPROM.get(SAVE_FILE_ADDRESS + sizeof(byte), stats);
    EEPROM.get(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats), map);
    memcpy(&world.map, &map, sizeof(map));
  }
}

void Game::saveGame(void)
{
  saveFile = true;
  EEPROM.put(SAVE_FILE_ADDRESS, gameID);
  EEPROM.put(SAVE_FILE_ADDRESS + sizeof(byte), stats);
  EEPROM.put(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats), world.map);
  EEPROM.put(SAVE_FILE_ADDRESS + sizeof(byte) + sizeof(Stats) + sizeof(uint8_t[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT]), gameID);
}

void Game::restart(void)
{
  world.reset(&stats, &effects);
  dialogs.init();
  stats.init();
  action = 0;
}

void Game::loop(void)
{
  if (!(arduboy.nextFrame()))
  {
    return;
  }

  arduboy.pollButtons();
  arduboy.clear();

  switch (onStage)
  {
  case STAGE_MAINMENU:
    mainMenuTick();
    break;
  case STAGE_PAUSE:
    mainPauseTick();
    break;
  case STAGE_GAME:
    mainGameTick();
    break;
  case STAGE_STOREMENU:
    mainStoreMenuTick();
    break;
  case STAGE_GAMEOVER:
    mainGameOverTick();
    break;
  }

  cycle.tick();
  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  titleMenu.eventDisplay(&cycle, saveFile);
  switch (titleMenu.action(saveFile))
  {
  case 1:
    restart();
    changeStage(STAGE_GAME);
    break;
  case 2:
    restart();
    loadGame();
    changeStage(STAGE_GAME);
    break;
  }
  Effects::displayErrorLine(65, 25, 60);
  effects.displayBistercianColumn(2, 2, 9);
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&stats);
  switch (pauseMenu.action())
  {
  case 1:
    changeStage(STAGE_GAME);
    break;
  case 2:
    if (!world.isMainMap())
    {
      dialogs.displayDialogs(7);
    }
    else if (stats.getEnergy() < MIN_HEALTH_ACTION)
    {
      dialogs.displayDialogs(6);
      world.newDay(&stats, &effects);
    }
    else
    {
      dialogs.displayDialogs(4);
    }
    changeStage(STAGE_GAME);
    break;
  case 3:
    changeStage(STAGE_MAINMENU);
    break;
  case 4:
    restart();
    loadGame();
    changeStage(STAGE_GAME);
    break;
  case 5:
    if (!world.isMainMap())
    {
      dialogs.displayDialogs(7);
    }
    else
    {
      saveGame();
    }
    changeStage(STAGE_GAME);
    break;
  }
  world.completeCanvas();
}

void Game::mainStoreMenuTick(void)
{
  storeMenu.eventDisplay(&stats);
  switch (storeMenu.action(&stats, &world))
  {
  case 1:
    changeStage(STAGE_GAME);
    break;
  case 2:
    dialogs.displayDialogs(1, true);
    break;
  case 3:
    dialogs.displayDialogs(2, true);
    break;
  }
  dialogs.tick();
  world.completeCanvas();
}

void Game::mainGameTick(void)
{
  if (arduboy.justPressed(A_BUTTON) && !world.inAction())
  {
    changeStage(STAGE_PAUSE);
    world.canvas();
  }
  else
  {
    uint8_t action = world.action(&stats, &effects);

    if (action == 4)
    {
      changeStage(STAGE_GAMEOVER);
    }
    else if (action == 3 && stats.getEnergy() < MIN_HEALTH_ACTION)
    {
      dialogs.displayDialogs(6);
      world.newDay(&stats, &effects);
    }
    else if (action == 2)
    {
      changeStage(STAGE_STOREMENU);
    }
    else
    {
      if (action == 3)
      {
        dialogs.displayDialogs(4);
      }
      else if (action == 5)
      {
        dialogs.displayDialogs(3);
      }
      else if (action == 6)
      {
        dialogs.displayDialogs(5);
      }
      else if (action == 7)
      {
        dialogs.displayDialogs(8);
      }

      if (cycle.cycle == 1)
      {
        world.environmentChange(&stats);
      }

      world.display(&cycle, &stats, &effects);
      world.canvas();
      dialogs.tick();
    }
  }
}

void Game::mainGameOverTick(void)
{
  if (gameOver.action())
  {
    changeStage(STAGE_MAINMENU);
  }
  world.completeCanvas();
}

void Game::changeStage(uint8_t stage)
{
  onStage = stage;
  storeMenu.refresh();
  pauseMenu.refresh();
  gameOver.refresh();
}
