
#include "Game.h"

#include "utils/Utils.h"
#include "utils/Stats.h"
#include "utils/Effects.h"
#include "utils/Numbers.h"
#include "world/World.h"

#include "menus/Menu.h"
#include "menus/TitleMenu.h"
#include "menus/PauseMenu.h"
#include "menus/StoreMenu.h"

Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);

uint8_t onStage;
uint8_t action;

Utils utils;
Stats stats;
Numbers numbers;
Effects effects;
World world;

TitleMenu titleMenu;
PauseMenu pauseMenu;
StoreMenu storeMenu;

void Game::setup(void)
{
  arduboy.begin();
  arduboy.setFrameRate(15);
  arduboy.initRandomSeed();
  arduboy.systemButtons();
  arduboy.waitNoButtons();

  utils.init(&arduboy);
  restart();
}

void Game::restart(void)
{
  world.reset(&stats);
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
  case 0:
    mainMenuTick();
    break;
  case 1:
    mainPauseTick();
    break;
  case 2:
    mainGameTick();
    break;
  case 3:
    mainStoreMenuTick();
    break;
  }

  utils.tick();
  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  titleMenu.eventDisplay(&utils);
  if (!titleMenu.action(&utils))
  {
    restart();
    onStage = 2;
  }
  effects.displayErrorLine(65, 25, 60);
  effects.displayBistercianBar(0, 2, 10);
  effects.displayBistercianColumn(118, 30, 3);
  effects.displayBistercianColumn(0, 8, 8);
}

void Game::mainPauseTick()
{
  pauseMenu.eventDisplay(&utils, &stats, &numbers);
  switch (pauseMenu.action(&utils))
  {
  case 1:
    onStage = 2;
    break;
  case 2:
    world.newDay(&stats);
    onStage = 2;
    break;
  case 3:
    onStage = 0;
    break;
  default:
    world.completeCanvas();
    break;
  }
}

void Game::mainStoreMenuTick(void)
{
  storeMenu.eventDisplay();
  switch (storeMenu.action(&utils))
  {
  case 1:
    onStage = 2;
    break;
  case 2:
    onStage = 2;
    break;
  }
  world.completeCanvas();
}

void Game::mainGameTick(void)
{
  if (world.canPause() && !world.inAction())
  {
    onStage = 1;
    pauseMenu.refresh();
    world.canvas();
  }
  else
  {
    if (world.action(&utils, &stats) == 2)
    {
      onStage = 3;
      storeMenu.refresh();
    }
    else
    {
      if (utils.cycle == 1)
      {
        world.environmentChange(&utils);
      }
      world.display(&utils, &stats, &effects);
      world.canvas();
    }
  }
}
