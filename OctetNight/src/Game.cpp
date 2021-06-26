
#include "Game.h"

#include "utils/Utils.h"
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

Arduboy2Base arduboy;

uint8_t onStage;
uint8_t action;
uint8_t displayDialog;
uint8_t displayCooldown;

Utils utils;
Stats stats;
Numbers numbers;
Effects effects;
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

  utils.init(&arduboy);
  restart();
}

void Game::restart(void)
{
  world.reset(&stats);
  stats.init();
  action = 0;
  displayDialog = 0;
  displayCooldown = 0;
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
  case 4:
    mainGameOverTick();
    break;
  }

  utils.tick();
  arduboy.display();
}

void Game::mainMenuTick(void)
{
  rand() % analogRead(0);
  titleMenu.eventDisplay(&utils);
  switch (titleMenu.action())
  {
  case 1:
    restart();
    onStage = 2;
    break;
  case 2:
    break;
  }
  effects.displayErrorLine(65, 25, 60);
  effects.displayBistercianColumn(2, 2, 9);
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
    if (stats.getEnergy() < 4)
    {
      dialogNewDay();
    }
    else
    {
      dialogNotTired();
    }
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
  storeMenu.eventDisplay(&stats, &numbers);
  switch (storeMenu.action(&stats, &numbers))
  {
  case 1:
    onStage = 2;
    break;
  case 2:
    dialogs.displayDialogs(1, true);
    break;
  case 3:
    dialogs.displayDialogs(2, true);
    break;
  }
  world.completeCanvas();
}

void Game::mainGameTick(void)
{
  if (arduboy.justPressed(A_BUTTON) && !world.inAction())
  {
    onStage = 1;
    pauseMenu.refresh();
    world.canvas();
  }
  else
  {
    uint8_t action = world.action(&utils, &stats);

    if (action == 4)
    {
      onStage = 4;
      gameOver.refresh();
    }
    else if (action == 3 && stats.getEnergy() < 4)
    {
      dialogNewDay();
    }
    else if (action == 2)
    {
      onStage = 3;
      storeMenu.refresh();
    }
    else
    {
      if (action > 4 && action < 7)
      {
        displayCooldown = DIALOG_COOLDOWN;
      }

      if (action == 3)
      {
        dialogNotTired();
      }
      else if (action == 5)
      {
        displayDialog = 3;
      }
      else if (action == 6)
      {
        displayDialog = 5;
      }

      if (utils.cycle == 1)
      {
        world.environmentChange(&utils);
      }
      world.display(&utils, &stats, &effects, &numbers);
      world.canvas();

      if (displayDialog > 0 && displayCooldown > 0)
      {
        dialogs.displayDialogs(displayDialog);
        displayCooldown--;
      }
      else
      {
        displayDialog = 0;
      }
    }
  }
}

void Game::mainGameOverTick(void)
{
  if (gameOver.action())
  {
    onStage = 0;
  }
  world.completeCanvas();
}

void Game::dialogNotTired()
{
  displayCooldown = DIALOG_COOLDOWN;
  displayDialog = 4;
}

void Game::dialogNewDay()
{
  displayCooldown = DIALOG_COOLDOWN;
  displayDialog = 6;
  world.newDay(&stats);
}
