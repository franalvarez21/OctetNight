#pragma once

class World
{
protected:
  uint8_t playerXPosition;
  uint8_t playerYPosition;
  uint8_t playerOrientation;

private:
  uint8_t mapOffsetX;
  uint8_t mapOffsetY;

  bool justPressedLock;
  bool playerXOrientation;

  uint8_t map[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];
  uint8_t map2[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];
  uint8_t currentMap;
  uint8_t currentAction;
  uint8_t currentToolSelected;
  uint8_t currentSeedSelected;
  uint8_t lastArrowUsed;

  uint8_t speedTick;
  uint8_t energyCycle;

public:
  bool isMainMap()
  {
    return currentMap == 0;
  }

  uint8_t mapGet(uint8_t x, uint8_t y)
  {
    if (isMainMap())
    {
      return map[x][y];
    }
    return map2[x][y];
  }

  void mapSet(uint8_t x, uint8_t y, uint8_t value)
  {
    if (isMainMap())
    {
      map[x][y] = value;
    }
    else
    {
      map2[x][y] = value;
    }
  }

  void reset(Stats *stats, Effects *effects)
  {
    changeCurrentMap(0, stats);
    refresh(effects);
    setPlayerPosition(3, 2, 0, 0);
    lastArrowUsed = 0;
  }

  void refresh(Effects *effects)
  {
    effects->refresh();
    speedTick = 0;
    currentAction = 0;
    currentToolSelected = 0;
    currentSeedSelected = 0;
    energyCycle = ENERGY_TIME;
    justPressedLock = true;
    playerOrientation = 1;
    playerXOrientation = true;
  }

  void setPlayerPosition(uint8_t x, uint8_t y, uint8_t xOff, uint8_t yOff)
  {
    playerXPosition = x;
    playerYPosition = y;
    mapOffsetX = xOff;
    mapOffsetY = yOff;
  }

  void clearPlayerPosition()
  {
    switch (currentMap)
    {
    case 0:
      if (lastArrowUsed == 0)
      {
        setPlayerPosition(3, 2, 0, 0);
      }
      else if (lastArrowUsed == 1)
      {
        setPlayerPosition(11, 4, 7, 0);
      }
      break;
    case 1:
      if (lastArrowUsed == 0)
      {
        setPlayerPosition(1, 4, 0, 0);
      }
      else if (lastArrowUsed == 2)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    case 2:
      if (lastArrowUsed == 1)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 3 || lastArrowUsed == 7)
      {
        setPlayerPosition(1, 1, 0, 0);
      }
      else if (lastArrowUsed == 4 || lastArrowUsed == 5)
      {
        setPlayerPosition(11, 1, 7, 0);
      }
      else if (lastArrowUsed == 6)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    case 3:
      if (lastArrowUsed == 5)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 4)
      {
        setPlayerPosition(1, 1, 0, 0);
      }
      else if (lastArrowUsed == 2)
      {
        setPlayerPosition(11, 1, 7, 0);
      }
      else if (lastArrowUsed == 7)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    case 4:
      if (lastArrowUsed == 7)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 2)
      {
        setPlayerPosition(1, 1, 0, 0);
      }
      else if (lastArrowUsed == 3)
      {
        setPlayerPosition(11, 1, 7, 0);
      }
      else if (lastArrowUsed == 5)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    case 5:
      if (lastArrowUsed == 4)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 6)
      {
        setPlayerPosition(11, 4, 7, 6);
      }
      else if (lastArrowUsed == 7)
      {
        setPlayerPosition(1, 4, 0, 6);
      }
      else if (lastArrowUsed == 3)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    case 6:
      if (lastArrowUsed == 2)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 5)
      {
        setPlayerPosition(1, 4, 0, 6);
      }
      else if (lastArrowUsed == 7)
      {
        setPlayerPosition(11, 4, 7, 6);
      }
      break;
    case 7:
      if (lastArrowUsed == 3)
      {
        setPlayerPosition(8, 6, 0, 6);
      }
      else if (lastArrowUsed == 5)
      {
        setPlayerPosition(11, 4, 7, 6);
      }
      else if (lastArrowUsed == 6)
      {
        setPlayerPosition(1, 4, 0, 6);
      }
      else if (lastArrowUsed == 4)
      {
        setPlayerPosition(8, 1, 0, 0);
      }
      break;
    }
  }

  void seedGrowth(uint8_t i, uint8_t j, uint8_t seed_number)
  {
    if (seed_number == SEED_1_NUMBER || seed_number == SEED_2_NUMBER || seed_number == SEED_3_NUMBER)
    {
      if (map[i][j] > seed_number + 2 && map[i][j] < seed_number + 10)
      {
        map[i][j]++;
      }
      else if (map[i][j] > seed_number - 1 && map[i][j] < seed_number + 3)
      {
        map[i][j] = seed_number + 3;
      }
    }
    else if (seed_number == SEED_4_NUMBER)
    {
      if (map[i][j] >= SEED_4_NUMBER && map[i][j] < SEED_5_NUMBER - 1)
      {
        map[i][j]++;
      }
    }
    else if (seed_number == SEED_5_NUMBER)
    {
      if (map[i][j] >= SEED_5_NUMBER && map[i][j] < SEED_6_NUMBER - 1)
      {
        map[i][j]++;
      }
    }
    else if (seed_number == SEED_6_NUMBER)
    {
      if (map[i][j] >= SEED_6_NUMBER && map[i][j] < 109)
      {
        map[i][j]++;
      }
    }
  }

  void clearSheepSpace()
  {
    for (uint8_t i = 11; i < REAL_MAP_WEIGHT - 1; i++)
    {
      for (uint8_t j = 4; j < REAL_MAP_HEIGHT - 1; j++)
      {
        map[i][j] = VOID_NUMBER;
      }
    }
  }

  void spawnSheep(Stats *stats)
  {
    for (uint8_t i = 11, x = 0; i < REAL_MAP_WEIGHT - 1 && x < stats->sheepAmount; i++, x++)
    {
      map[i][5 + rand() % 8] = 20;
      map[i][4 + rand() % 9] = 21;
    }
  }

  void sheepRest()
  {
    for (uint8_t i = 11; i < REAL_MAP_WEIGHT - 1; i++)
    {
      for (uint8_t j = 4; j < REAL_MAP_HEIGHT - 1; j++)
      {
        if (map[i][j] == 23 || map[i][j] == 27)
        {
          map[i][j] = map[i][j] - 2;
        }
      }
    }
  }

  void newDay(Stats *stats, Effects *effects)
  {
    if (isMainMap())
    {
      stats->rest();
      lastArrowUsed = 0;
      refresh(effects);
      clearPlayerPosition();
      sheepRest();
      for (uint8_t i = 0; i < REAL_MAP_WEIGHT - 1; i++)
      {
        for (uint8_t j = 0; j < REAL_MAP_HEIGHT - 1; j++)
        {
          seedGrowth(i, j, SEED_1_NUMBER);
          seedGrowth(i, j, SEED_2_NUMBER);
          seedGrowth(i, j, SEED_3_NUMBER);
          seedGrowth(i, j, SEED_4_NUMBER);
          seedGrowth(i, j, SEED_5_NUMBER);
          seedGrowth(i, j, SEED_6_NUMBER);
        }
      }
    }
  }

  void sheepChange(Utils *utils)
  {
    for (uint8_t i = 10; i < REAL_MAP_WEIGHT - 1; i++)
    {
      for (uint8_t j = 3; j < REAL_MAP_HEIGHT - 1; j++)
      {
        if (map[i][j] == 21 || map[i][j] == 23 || map[i][j] == 25 || map[i][j] == 27)
        {
          switch (rand() % 4)
          {
          case 0:
            if (i - 1 > 10)
            {
              if (map[i][j] == 21 || map[i][j] == 23)
              {
                map[i][j] = map[i][j] + 4;
              }
              moveOthers(i, j, i - 1, j);
            }
            break;
          case 1:
            if (i + 1 < REAL_MAP_WEIGHT - 1)
            {
              if (map[i][j] == 25 || map[i][j] == 27)
              {
                map[i][j] = map[i][j] - 4;
              }
              moveOthers(i, j, i + 1, j);
            }
            break;
          case 2:
            if (j - 1 > 3)
            {
              moveOthers(i, j, i, j - 1);
            }
            break;
          case 3:
            if (j + 1 < REAL_MAP_HEIGHT - 1)
            {
              moveOthers(i, j, i, j + 1);
            }
            break;
          }
        }
      }
    }

    for (uint8_t i = 11; i < REAL_MAP_WEIGHT - 1; i++)
    {
      for (uint8_t j = 4; j < REAL_MAP_HEIGHT - 1; j++)
      {
        if (map[i][j] == 22 || map[i][j] == 24 || map[i][j] == 26 || map[i][j] == 28)
        {
          map[i][j]--;
        }
      }
    }
  }

  bool inAction()
  {
    return (currentAction > 0);
  }

  uint8_t action(Utils *utils, Stats *stats, Effects *effects)
  {
    if (Arduboy2Base::justPressed(A_BUTTON))
    {
      if (currentAction > 0)
      {
        if (currentAction > 2)
        {
          currentSeedSelected = 0;
          currentAction--;
        }
        currentAction--;
        return 1;
      }
    }

    if (Arduboy2Base::justPressed(B_BUTTON))
    {
      if (currentAction == 3)
      {
        return useTool(stats, effects);
      }
      else if (currentAction == 2)
      {
        if (currentToolSelected == 0)
        {
          currentAction++;
        }
        else
        {
          return useTool(stats, effects);
        }
      }
      else if (currentAction == 1)
      {
        if (!(currentToolSelected == 3 && stats->potionsAmount == 0))
        {
          currentAction++;
        }
      }
      else
      {
        currentToolSelected = 0;
        currentSeedSelected = 0;
        currentAction++;
        return 1;
      }
    }

    if (currentAction == 2 && currentToolSelected == 0)
    {
      if (Arduboy2Base::justPressed(UP_BUTTON))
      {
        if (currentSeedSelected > 0)
        {
          currentSeedSelected--;
        }
      }

      if (Arduboy2Base::justPressed(DOWN_BUTTON))
      {
        if (currentSeedSelected < SEEDS_AVAILABLE - 1)
        {
          currentSeedSelected++;
        }
      }
    }
    else if (currentAction == 1)
    {
      if (Arduboy2Base::justPressed(UP_BUTTON))
      {
        if (currentToolSelected > 0)
        {
          currentToolSelected--;
        }
      }

      if (Arduboy2Base::justPressed(DOWN_BUTTON))
      {
        if (currentToolSelected < TOOLS_AVAILABLE - 1)
        {
          currentToolSelected++;
        }
      }
    }
    else
    {
      if (pressed(utils, RIGHT_BUTTON) && !Arduboy2Base::pressed(LEFT_BUTTON))
      {
        playerOrientation = 1;
        if (playerXPosition < SQUARE_AMOUNT_WEIGHT - 2)
        {
          return move(stats, effects, 1, 0);
        }
        else
        {
          if (mapOffsetX + (SQUARE_AMOUNT_WEIGHT - 1) < REAL_MAP_WEIGHT)
          {
            mapOffsetX++;
          }
        }
      }

      if (pressed(utils, LEFT_BUTTON) && !Arduboy2Base::pressed(RIGHT_BUTTON))
      {
        playerOrientation = 3;
        if (playerXPosition > 0)
        {
          return move(stats, effects, -1, 0);
        }
        else
        {
          if (mapOffsetX > 0)
          {
            mapOffsetX--;
          }
        }
      }

      if (pressed(utils, DOWN_BUTTON) && !Arduboy2Base::pressed(UP_BUTTON))
      {
        playerOrientation = 2;
        if (playerYPosition < SQUARE_AMOUNT_HEIGHT - 2)
        {
          return move(stats, effects, 0, 1);
        }
        else
        {
          if (mapOffsetY + (SQUARE_AMOUNT_HEIGHT - 1) < REAL_MAP_HEIGHT)
          {
            mapOffsetY++;
          }
        }
      }

      if (pressed(utils, UP_BUTTON) && !Arduboy2Base::pressed(DOWN_BUTTON))
      {
        playerOrientation = 0;
        if (playerYPosition > 0)
        {
          return move(stats, effects, 0, -1);
        }
        else
        {
          if (mapOffsetY > 0)
          {
            mapOffsetY--;
          }
        }
      }
    }

    if (stats->getHP() < 1)
    {
      return 4;
    }

    return 0;
  }

  void moveOthers(uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    if (mapGet(i, j) == VOID_NUMBER)
    {
      mapSet(i, j, mapGet(x, y) + 1);
      mapSet(x, y, VOID_NUMBER);
    }
  }

  void environmentChange(Utils *utils)
  {
    if (isMainMap() && !(currentAction > 1 && currentToolSelected == 1))
    {
      sheepChange(utils);
    }
  }

  void displayTime(Utils *utils, Stats *stats, Numbers *numbers)
  {
    if (currentAction > 0)
    {
      switch (currentToolSelected)
      {
      case 0:
        if (currentAction > 1)
        {
          switch (currentSeedSelected)
          {
          case 0:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_0, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedOne);
            }
            break;
          case 1:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_1, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedTwo);
            }
            break;
          case 2:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_2, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedThree);
            }
            break;
          case 3:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_3, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedFour);
            }
            break;
          case 4:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_4, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedFive);
            }
            break;
          case 5:
            Arduboy2Base::drawBitmap(106, 2, Mini::seed_5, 20, 20, WHITE);
            if (currentAction > 2)
            {
              numbers->print(102, 23, stats->seedSix);
            }
            break;
          }
        }
        else
        {
          Arduboy2Base::drawBitmap(106, 2, Mini::plant_tool, 20, 20, WHITE);
        }
        break;
      case 1:
        Arduboy2Base::drawBitmap(106, 2, Mini::sheers_tool, 20, 20, WHITE);
        break;
      case 2:
        Arduboy2Base::drawBitmap(106, 2, Mini::sword_tool, 20, 20, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(106, 2, Mini::items_tool, 20, 20, WHITE);
        if (currentAction > 1)
        {
          numbers->print(102, 23, stats->potionsAmount);
        }
        break;
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(106, 2, Mini::clock, 20, 19, WHITE);
    }
  }

  void canvas()
  {
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 4), 0, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 4), SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 3), 0, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 3), SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), 0, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    for (uint8_t y = 1; y < SQUARE_AMOUNT_HEIGHT - 2; y++)
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (SQUARE_AMOUNT_WEIGHT - 1), y * SQUARE_SIZE, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), y * SQUARE_SIZE, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void completeCanvas()
  {
    Arduboy2Base::drawBitmap(0, 0, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), 0, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(0, SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    for (uint8_t x = 1; x < MAX_SQUARE_AMOUNT_WEIGHT - 2; x++)
    {
      Arduboy2Base::drawBitmap(x * SQUARE_SIZE, 0, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      Arduboy2Base::drawBitmap(x * SQUARE_SIZE, SQUARE_SIZE * (MAX_SQUARE_AMOUNT_HEIGHT - 2), Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }

    for (uint8_t y = 1; y < MAX_SQUARE_AMOUNT_HEIGHT - 2; y++)
    {
      Arduboy2Base::drawBitmap(0, y * SQUARE_SIZE, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (MAX_SQUARE_AMOUNT_WEIGHT - 2), y * SQUARE_SIZE, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void display(Utils *utils, Stats *stats, Effects *effects, Numbers *numbers)
  {
    if (playerXPosition + mapOffsetX == 9)
    {
      playerXPosition = 9;
      mapOffsetX = 0;
    }

    if (playerXPosition + mapOffsetX == 10)
    {
      playerXPosition = 3;
      mapOffsetX = 7;
    }

    if (playerYPosition + mapOffsetY == 7)
    {
      playerYPosition = 1;
      mapOffsetY = 6;
    }

    if (playerYPosition + mapOffsetY == 6)
    {
      playerYPosition = 6;
      mapOffsetY = 0;
    }

    displayTime(utils, stats, numbers);
    displayToolAction(utils);
    displayPlayerPointer(utils);
    displayBuilderSelector(utils);
    displayCardOption(utils);
    displayStats(stats);

    for (uint8_t x = mapOffsetX, i = 0; x < SQUARE_AMOUNT_WEIGHT + mapOffsetX - 1; x++, i++)
    {
      for (uint8_t y = mapOffsetY, j = 0; y < SQUARE_AMOUNT_HEIGHT + mapOffsetY - 1; y++, j++)
      {
        displayMaze(utils, stats, effects, x, y, i, j);
      }
    }

    effects->playerAnimationTick(SQUARE_SIZE * (playerXPosition + 1), SQUARE_SIZE * (playerYPosition - 1));

    if (energyCycle > 0)
    {
      energyCycle--;
    }
    else
    {
      if (stats->getEnergy() > MIN_HEALTH_ACTION - 1)
      {
        stats->decEnergy(1);
      }
      energyCycle = ENERGY_TIME;
    }
  }

private:
  bool pressed(Utils *utils, uint8_t button)
  {
    if (justPressedLock)
    {
      if (Arduboy2Base::justPressed(button))
      {
        justPressedLock = false;
        return true;
      }
    }
    else
    {
      if (Arduboy2Base::justPressed(button) || Arduboy2Base::pressed(button) && speedTick == 0)
      {
        speedTick = 2;
        return true;
      }
      else if (Arduboy2Base::pressed(button) && speedTick > 0)
      {
        speedTick--;
      }
    }
    return false;
  }

  void clearMap(Stats *stats)
  {
    uint8_t cell[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];

    if (isMainMap())
    {
      memcpy_P(&cell, &Map::map_0, sizeof(cell));
    }
    else if (currentMap == 1)
    {
      memcpy_P(&cell, &Map::map_1, sizeof(cell));
    }
    else if (currentMap == 2)
    {
      memcpy_P(&cell, &Map::map_2, sizeof(cell));
    }
    else if (currentMap == 3)
    {
      memcpy_P(&cell, &Map::map_3, sizeof(cell));
    }
    else if (currentMap == 4)
    {
      memcpy_P(&cell, &Map::map_4, sizeof(cell));
    }
    else if (currentMap == 5)
    {
      memcpy_P(&cell, &Map::map_5, sizeof(cell));
    }
    else if (currentMap == 6)
    {
      memcpy_P(&cell, &Map::map_6, sizeof(cell));
    }
    else if (currentMap == 7)
    {
      memcpy_P(&cell, &Map::map_7, sizeof(cell));
    }

    for (uint8_t i = 0; i < REAL_MAP_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < REAL_MAP_HEIGHT; j++)
      {
        mapSet(i, j, cell[i][j]);
        if (cell[i][j] == 0) // Trees
        {
          mapSet(i, j, rand() % 3);
        }
        else if (cell[i][j] == 1) // Empty
        {
          mapSet(i, j, VOID_NUMBER);
        }
        else if (cell[i][j] == 2) // Rocks
        {
          mapSet(i, j, 31 + rand() % 3);
        }
        else if (cell[i][j] == 63) // weird block
        {
          mapSet(i, j, 37 + rand() % 3);
        }
      }
    }

    clearSheepSpace();
    spawnSheep(stats);
  }

  bool attackEnemy(uint8_t value)
  {
    switch (playerOrientation)
    {
    case 0:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition), SQUARE_SIZE * (playerYPosition - 1), Common::swing_animation_2, 8, 8, WHITE);
      break;
    case 1:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + 1), SQUARE_SIZE * (playerYPosition), Common::swing_animation_0, 8, 8, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition), SQUARE_SIZE * (playerYPosition + 1), Common::swing_animation_3, 8, 8, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition - 1), SQUARE_SIZE * (playerYPosition), Common::swing_animation_1, 8, 8, WHITE);
      break;
    }
    return value >= START_ENEMY_NUMBER && value <= END_ENEMY_NUMBER;
  }

  void displayPlayerPointer(Utils *utils)
  {
    if (playerOrientation == 1)
    {
      playerXOrientation = true;
      displayPlayerRight(utils);
    }
    else if (playerOrientation == 3)
    {
      playerXOrientation = false;
      displayPlayerLeft(utils);
    }
    else if (playerXOrientation)
    {
      displayPlayerRight(utils);
    }
    else
    {
      displayPlayerLeft(utils);
    }
  }

  void displayPlayerRight(Utils *utils)
  {
    if (utils->halfCycleCheck())
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, (currentToolSelected == 2 && currentAction > 1) ? Common::player_4 : Common::player_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, (currentToolSelected == 2 && currentAction > 1) ? Common::player_5 : Common::player_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayPlayerLeft(Utils *utils)
  {
    if (utils->halfCycleCheck())
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, (currentToolSelected == 2 && currentAction > 1) ? Common::player_6 : Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, (currentToolSelected == 2 && currentAction > 1) ? Common::player_7 : Common::player_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayBuilderSelector(Utils *utils)
  {
    if (currentAction == 0)
    {
      Arduboy2Base::drawBitmap(104, 28, utils->halfCycleCheck() ? Cards::a_1 : Cards::a_2, 24, 8, WHITE);
    }
    else
    {
      switch (currentToolSelected)
      {
      case 0:
        Arduboy2Base::drawBitmap(104, 28, utils->halfCycleCheck() ? Cards::plant_0 : Cards::plant_1, 24, 8, WHITE);
        break;
      case 1:
        Arduboy2Base::drawBitmap(104, 28, utils->halfCycleCheck() ? Cards::sheers_0 : Cards::sheers_1, 24, 8, WHITE);
        break;
      case 2:
        Arduboy2Base::drawBitmap(104, 28, utils->halfCycleCheck() ? Cards::sword_0 : Cards::sword_1, 24, 8, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(104, 28, utils->halfCycleCheck() ? Cards::items_0 : Cards::items_1, 24, 8, WHITE);
        break;
      }
    }
  }

  void displayCardOption(Utils *utils)
  {
    if (currentAction == 1 || (currentAction == 2 && currentToolSelected == 0))
    {
      Arduboy2Base::drawBitmap(104, 21, utils->halfCycleCheck() ? Cards::change_1 : Cards::change_2, 24, 8, WHITE);
    }
    else if (currentAction > 1 && currentToolSelected != 0 && currentToolSelected != 3)
    {
      Arduboy2Base::drawBitmap(104, 21, Cards::use_0, 24, 8, WHITE);
    }
  }

  void displayStats(Stats *stats)
  {
    for (uint8_t i = 0; i < stats->getHP(); i++)
    {
      Arduboy2Base::drawBitmap(108, 54 - (i * 2), Common::bar, 4, 1, WHITE);
    }
    for (uint8_t i = 0; i < stats->getMoney(); i++)
    {
      Arduboy2Base::drawBitmap(114, 54 - (i * 2), Common::bar, 4, 1, WHITE);
    }
    for (uint8_t i = 0; i < stats->getEnergy(); i++)
    {
      Arduboy2Base::drawBitmap(120, 54 - (i * 2), Common::bar, 4, 1, WHITE);
    }
    Arduboy2Base::drawBitmap(104, 55, Cards::stats_1, 24, 8, WHITE);
  }

  void displayMaze(Utils *utils, Stats *stats, Effects *effects, uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    if (!(i == playerXPosition && j == playerYPosition))
    {
      switch (mapGet(x, y))
      {
      case 0:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::tree_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 1:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::tree_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 2:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::tree_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_door_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 4:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_door_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 5:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_tombstone_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 6:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_flag_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 7:
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 2, rand() % 10000);
        break;
      case 8:
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 2, rand() % 10000);
        break;
      case 9:
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 2, rand() % 10000);
        break;
      case 10:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 11:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 12:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_2, SQUARE_SIZE * 2, SQUARE_SIZE * 2, WHITE);
        break;
      case 13:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_home_0, SQUARE_SIZE * 3, SQUARE_SIZE * 2, WHITE);
        break;
      case 14:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::world_store_0, SQUARE_SIZE * 4, SQUARE_SIZE * 3, WHITE);
        break;
      case 15:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_hay, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 16:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_wall, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 17:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_right_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 18:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_top_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 19:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::door_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 20:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, utils->halfCycleCheck() ? Map::natural_hay_0 : Map::natural_hay_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 21:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, utils->halfCycleCheck() ? Mini::sheep_0 : Mini::sheep_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 23:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, utils->halfCycleCheck() ? Mini::sheep_2 : Mini::sheep_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 25:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, utils->halfCycleCheck() ? Mini::sheep_4 : Mini::sheep_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 27:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, utils->halfCycleCheck() ? Mini::sheep_6 : Mini::sheep_7, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 29:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_left_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 30:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_bottom_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 31:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::rock_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 32:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::rock_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 33:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::rock_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 34:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::pillar_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 35:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::pillar_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 36:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::pillar_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 37:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::weird_block_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 3, stats->getRealMoney());
        break;
      case 38:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::weird_block_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 3, stats->getRealMoney());
        break;
      case 39:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::weird_block_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        effects->displayBistercian(SQUARE_SIZE * i + 2, SQUARE_SIZE * j + 3, stats->getRealMoney());
        break;
      case 40:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 41:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 42:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 43:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 44:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 45:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 46:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 47:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_4, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 48:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ruin_wall_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 61:
        // Reserve as store door
        break;
      case 62:
        // Reserve as home door
        break;
      case 63:
        // Reserve as weird blocker
        break;
      case 64:
        // Reserve as blocker
        break;
      // Seed 1
      case SEED_1_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 66:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 67:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 68:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 69:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_4, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 70:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 71:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_6, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 72:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_7, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 73:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_8, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 74:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_9, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 75:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_10, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      // Seed 2
      case SEED_2_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_11, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 77:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_12, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 78:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_13, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 79:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_14, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 80:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_15, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 81:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_16, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 82:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_17, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 83:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_18, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 84:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_19, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 85:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_20, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 86:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_21, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      // Seed 3
      case SEED_3_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_22, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 88:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_23, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 89:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_24, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 90:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_25, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 91:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_26, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 92:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_27, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 93:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_28, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 94:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_29, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 95:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_30, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 96:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_31, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 97:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_32, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      // Seed 4
      case SEED_4_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_33, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 99:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_34, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 100:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_35, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 101:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_36, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 102:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_37, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      // Seed 5
      case SEED_5_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_38, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 104:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_39, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 105:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_40, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 106:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_41, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      // Seed 6
      case SEED_6_NUMBER:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_42, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 108:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_43, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 109:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Seeds::seed_44, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      }
    }
  }

  uint8_t changeCurrentMap(uint8_t number, Stats *stats = NULL)
  {
    currentMap = number;
    if (stats != NULL)
    {
      clearMap(stats);
    }
    clearPlayerPosition();
    return 1;
  }

  uint8_t move(Stats *stats, Effects *effects, const int extX, const int extY)
  {
    uint8_t tempX = playerXPosition + mapOffsetX + extX;
    uint8_t tempY = playerYPosition + mapOffsetY + extY;

    if (playerXPosition + extX >= 0 && playerYPosition + extY >= 0 && playerXPosition + extX < SQUARE_AMOUNT_WEIGHT - 1 && playerYPosition + extY < SQUARE_AMOUNT_HEIGHT - 1)
    {
      uint8_t value = mapGet(tempX, tempY);

      if (value == 61) // Store
      {
        return 2;
      }
      if (value == 62) // Home
      {
        return 3;
      }
      if (value == 6 && currentMap == 1)
      {
        if (playerXPosition + mapOffsetX > 6)
        {
          return 6;
        }
        else
        {
          return 5;
        }
      }

      if (value == SEED_1_NUMBER + 10)
      {
        stats->plusSeedOne();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }
      if (value == SEED_2_NUMBER + 10)
      {
        stats->plusSeedTwo();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }
      if (value == SEED_3_NUMBER + 10)
      {
        stats->plusSeedThree();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }
      if (value == SEED_4_NUMBER + 4)
      {
        stats->plusSeedFour();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }
      if (value == SEED_5_NUMBER + 3)
      {
        stats->plusSeedFive();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }
      if (value == SEED_6_NUMBER + 2)
      {
        stats->plusSeedSix();
        effects->plusAnimation();
        mapSet(tempX, tempY, EMPTY_NUMBER);
      }

      lastArrowUsed = currentMap;
      switch (currentMap)
      {
      case 0:
        if (value == 17)
        {
          return changeCurrentMap(1, stats);
        }
        break;
      case 1:
        if (value == 29)
        {
          return changeCurrentMap(0);
        }
        else if (value == 18)
        {
          return changeCurrentMap(2, stats);
        }
        break;
      case 2:
        if (value == 30)
        {
          return changeCurrentMap(1, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(3, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(4, stats);
        }
        else if (value == 18)
        {
          return changeCurrentMap(6, stats);
        }
        break;
      case 3:
        if (value == 30)
        {
          return changeCurrentMap(5, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(4, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(2, stats);
        }
        else if (value == 18)
        {
          return changeCurrentMap(7, stats);
        }
        break;
      case 4:
        if (value == 30)
        {
          return changeCurrentMap(7, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(2, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(3, stats);
        }
        else if (value == 18)
        {
          return changeCurrentMap(5, stats);
        }
        break;
      case 5:
        if (value == 30)
        {
          return changeCurrentMap(4, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(playerYPosition > 1 ? 7 : 2, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(6, stats);
        }
        else if (value == 18)
        {
          return changeCurrentMap(3, stats);
        }
        break;
      case 6:
        if (value == 30)
        {
          return changeCurrentMap(2, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(5, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(7, stats);
        }
        break;
      case 7:
        if (value == 30)
        {
          return changeCurrentMap(3, stats);
        }
        else if (value == 29)
        {
          return changeCurrentMap(6, stats);
        }
        else if (value == 17)
        {
          return changeCurrentMap(playerYPosition > 1 ? 5 : 2, stats);
        }
        else if (value == 18)
        {
          return changeCurrentMap(4, stats);
        }
        break;
      }

      if (value > 16 && value < 31 || value > SEED_1_NUMBER - 1)
      {
        playerXPosition += extX;
        playerYPosition += extY;
        return 1;
      }
    }
    return 0;
  }

  void displayPlaceIcon(Utils *utils)
  {
    uint8_t x = 1, y = 1;
    switch (playerOrientation)
    {
    case 0:
      y = 0;
      break;
    case 1:
      x = 2;
      break;
    case 2:
      y = 2;
      break;
    case 3:
      x = 0;
      break;
    }

    if (utils->halfCycleCheck())
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + (-1 + x)), SQUARE_SIZE * (playerYPosition + (-1 + y)), Common::available_spot_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + (-1 + x)), SQUARE_SIZE * (playerYPosition + (-1 + y)), Common::available_spot_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  uint8_t useTool(Stats *stats, Effects *effects)
  {
    uint8_t x = 1, y = 1;
    switch (playerOrientation)
    {
    case 0:
      y = 0;
      break;
    case 1:
      x = 2;
      break;
    case 2:
      y = 2;
      break;
    case 3:
      x = 0;
      break;
    }

    uint8_t value = mapGet(playerXPosition + mapOffsetX + (-1 + x), playerYPosition + mapOffsetY + (-1 + y));
    switch (currentToolSelected)
    {
    case 0:
      if (stats->getEnergy() > 0)
      {
        if (isMainMap() && canPlace())
        {
          switch (currentSeedSelected)
          {
          case 0:
            if (stats->seedOne > 0)
            {
              stats->seedOne--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_6_NUMBER;
              stats->decEnergy(1);
            }
            break;
          case 1:
            if (stats->seedTwo > 0)
            {
              stats->seedTwo--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_5_NUMBER;
              stats->decEnergy(1);
            }
            break;
          case 2:
            if (stats->seedThree > 0)
            {
              stats->seedThree--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_4_NUMBER;
              stats->decEnergy(1);
            }
            break;
          case 3:
            if (stats->seedFour > 0)
            {
              stats->seedFour--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_3_NUMBER;
              stats->decEnergy(1);
            }
            break;
          case 4:
            if (stats->seedFive > 0)
            {
              stats->seedFive--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_2_NUMBER;
              stats->decEnergy(1);
            }
            break;
          case 5:
            if (stats->seedSix > 0)
            {
              stats->seedSix--;
              map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = SEED_1_NUMBER;
              stats->decEnergy(1);
            }
            break;
          }
          return 1;
        }
      }
      else
      {
        stats->decHP(1);
        effects->sleepAnimation();
      }
      break;
    case 1:
      if (value == 21 || value == 25)
      {
        mapSet(playerXPosition + mapOffsetX + (-1 + x), playerYPosition + mapOffsetY + (-1 + y), value + 2);
        stats->plusWool();
        effects->plusAnimation();
        return 1;
      }
      break;
    case 2:
      if (attackEnemy(value))
      {
        mapSet(playerXPosition + mapOffsetX + (-1 + x), playerYPosition + mapOffsetY + (-1 + y), VOID_NUMBER);
      }
      break;
    case 3:
      if (stats->potionsAmount > 0 && stats->getHP() < MAX_CAPACITY)
      {
        stats->usePotion();
      }
      break;
    }

    return 0;
  }

  void displayToolAction(Utils *utils)
  {
    if (currentAction == 3 && currentToolSelected == 0 && canPlace())
    {
      displayPlaceIcon(utils);
    }
  }

  bool canPlace()
  {
    switch (playerOrientation)
    {
    case 0:
      if (playerYPosition + mapOffsetY > 0 && mapGet(playerXPosition + mapOffsetX, playerYPosition + mapOffsetY - 1) == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 1:
      if (playerXPosition + mapOffsetX < REAL_MAP_WEIGHT - 1 && mapGet(playerXPosition + mapOffsetX + 1, playerYPosition + mapOffsetY) == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 2:
      if (playerYPosition + mapOffsetY < REAL_MAP_HEIGHT - 1 && mapGet(playerXPosition + mapOffsetX, playerYPosition + mapOffsetY + 1) == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 3:
      if (playerXPosition + mapOffsetX > 0 && mapGet(playerXPosition + mapOffsetX - 1, playerYPosition + mapOffsetY) == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    }

    return false;
  }
};
