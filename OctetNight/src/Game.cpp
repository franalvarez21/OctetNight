
#include "Game.h"

Arduboy2Base arduboy;
uint8_t onStage;
uint8_t action;

Cycle cycle;
Effects effects;
Stats stats;
Dialogs dialogs;
LevelProgression levelProgression;
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

  cycle.init();
  restart();
}

void Game::restart(void)
{
  world.reset(&stats, &effects);
  levelProgression.reset();
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
  titleMenu.eventDisplay(&cycle);
  switch (titleMenu.action())
  {
  case 1:
    restart();
    changeStage(STAGE_GAME);
    break;
  case 2:
    //TODO: Load game call
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
  default:
    world.completeCanvas();
    break;
  }
}

void Game::mainStoreMenuTick(void)
{
  storeMenu.eventDisplay(&stats);
  switch (storeMenu.action(&stats))
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
    uint8_t action = world.action(&stats, &effects, &levelProgression);

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

      if (cycle.cycle == 1)
      {
        world.environmentChange(&stats);
      }

      world.display(&cycle, &stats, &effects, &levelProgression);
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
