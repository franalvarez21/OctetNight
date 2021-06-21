#pragma once

class World
{
protected:
  uint8_t mapOffsetX;
  uint8_t mapOffsetY;
  uint8_t map[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];
  uint8_t playerXPosition;
  uint8_t playerYPosition;
  uint8_t playerOrientation;
  bool playerXOrientation;
  uint8_t currentAction;
  uint8_t speedTick;
  uint8_t currentToolSelected;
  bool justPressedLock;
  uint8_t plusAnimation;

public:
  void refresh()
  {
    speedTick = 0;
    currentAction = 0;
    currentToolSelected = 0;
    plusAnimation = 0;
    reset();
  }

  void seedGrowth(uint8_t i, uint8_t j, uint8_t seed_number)
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

  void newDay(Stats *stats)
  {
    stats->rest();
    currentAction = 0;
    currentToolSelected = 0;
    clearPlayerPosition();
    sheepRest();
    for (uint8_t i = 0; i < REAL_MAP_WEIGHT - 1; i++)
    {
      for (uint8_t j = 0; j < REAL_MAP_HEIGHT - 1; j++)
      {
        seedGrowth(i, j, SEED_1_NUMBER);
        seedGrowth(i, j, SEED_2_NUMBER);
        seedGrowth(i, j, SEED_3_NUMBER);
      }
    }
  }

  bool inAction()
  {
    return (currentAction > 0);
  }

  uint8_t action(Utils *utils, Stats *stats)
  {
    if (Arduboy2Base::justPressed(A_BUTTON))
    {
      if (currentAction > 0)
      {
        currentAction--;
        return 1;
      }
    }

    if (Arduboy2Base::justPressed(B_BUTTON))
    {
      if (currentAction == 2)
      {
        return useTool(utils, stats);
      }
      else if (currentAction == 1)
      {
        currentAction++;
      }
      else if (currentAction < 1)
      {
        currentToolSelected = 0;
        currentAction++;
        return 1;
      }
    }

    if (currentAction == 1)
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
          return move(utils, stats, 1, 0);
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
          return move(utils, stats, -1, 0);
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
          return move(utils, stats, 0, 1);
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
          return move(utils, stats, 0, -1);
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

    return 0;
  }

  void reset()
  {
    justPressedLock = true;

    clearMap();
    clearPlayerPosition();
  }

  void moveOthers(uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    if (map[i][j] == VOID_NUMBER)
    {
      map[i][j] = map[x][y] + 1;
      map[x][y] = VOID_NUMBER;
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

  void environmentChange(Utils *utils)
  {
    sheepChange(utils);
  }

  void displayTime(Utils *utils, Stats *stats)
  {
    if (currentAction > 0)
    {
      switch (currentToolSelected)
      {
      case 0:
        Arduboy2Base::drawBitmap(106, 2, Mini::plant_tool, 20, 20, WHITE);
        break;
      case 1:
        Arduboy2Base::drawBitmap(106, 2, Mini::sheers_tool, 20, 20, WHITE);
        break;
      case 2:
        Arduboy2Base::drawBitmap(106, 2, Mini::sword_tool, 20, 20, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(106, 2, Mini::items_tool, 20, 20, WHITE);
        break;
      }
    }
    else
    {
      Arduboy2Base::drawBitmap(107, 2, Mini::clock, 18, 19, WHITE);

      if (!(stats->getEnergy() < 2) && !(stats->getEnergy() == 9))
      {
        Arduboy2Base::drawBitmap(113, 1, Mini::clock_empty, 6, 7, BLACK);
      }

      if (!(stats->getEnergy() == 2))
      {
        Arduboy2Base::drawBitmap(106, 1, Mini::clock_empty, 7, 7, BLACK);
      }

      if (!(stats->getEnergy() == 3))
      {
        Arduboy2Base::drawBitmap(106, 8, Mini::clock_empty, 7, 7, BLACK);
      }

      if (!(stats->getEnergy() == 4))
      {
        Arduboy2Base::drawBitmap(106, 15, Mini::clock_empty, 7, 7, BLACK);
      }

      if (!(stats->getEnergy() == 5))
      {
        Arduboy2Base::drawBitmap(113, 15, Mini::clock_empty, 6, 7, BLACK);
      }

      if (!(stats->getEnergy() == 6))
      {
        Arduboy2Base::drawBitmap(119, 15, Mini::clock_empty, 7, 7, BLACK);
      }

      if (!(stats->getEnergy() == 7))
      {
        Arduboy2Base::drawBitmap(119, 8, Mini::clock_empty, 7, 7, BLACK);
      }

      if (!(stats->getEnergy() == 8))
      {
        Arduboy2Base::drawBitmap(119, 1, Mini::clock_empty, 7, 7, BLACK);
      }
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

  void display(Utils *utils, Stats *stats)
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

    displayTime(utils, stats);
    displayToolAction(utils);
    displayPlayerPointer(utils);
    displayBuilderSelector(utils);
    displayCardOption(utils);
    displayStats(stats);

    for (uint8_t x = mapOffsetX, i = 0; x < SQUARE_AMOUNT_WEIGHT + mapOffsetX - 1; x++, i++)
    {
      for (uint8_t y = mapOffsetY, j = 0; y < SQUARE_AMOUNT_HEIGHT + mapOffsetY - 1; y++, j++)
      {
        displayMaze(utils, x, y, i, j);
      }
    }

    if (plusAnimation > 0)
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + 1), SQUARE_SIZE * (playerYPosition - 1), Common::plus_animation_0, 8, 8, BLACK);
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + 1), SQUARE_SIZE * (playerYPosition - 1), Common::plus_animation_1, 8, 8, WHITE);
      plusAnimation--;
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

  void clearMap()
  {
    uint8_t cell[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT];
    memcpy_P(&cell, &Map::map_0, sizeof(cell));

    for (uint8_t i = 0; i < REAL_MAP_WEIGHT; i++)
    {
      for (uint8_t j = 0; j < REAL_MAP_HEIGHT; j++)
      {
        map[i][j] = cell[i][j];
        if (cell[i][j] == 0)
        {
          map[i][j] = rand() % 3;
        }
        else if (cell[i][j] == 1)
        {
          map[i][j] = VOID_NUMBER;
        }
      }
    }
  }

  void clearPlayerPosition()
  {
    mapOffsetX = 0;
    mapOffsetY = 0;
    playerOrientation = 1;
    playerXOrientation = true;
    playerXPosition = 3;
    playerYPosition = 2;
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
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, Common::player_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, Common::player_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayPlayerLeft(Utils *utils)
  {
    if (utils->halfCycleCheck())
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, Common::player_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * playerXPosition, SQUARE_SIZE * playerYPosition, Common::player_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  void displayBuilderSelector(Utils *utils)
  {
    if (currentAction == 0)
    {
      if (utils->halfCycleCheck())
      {
        Arduboy2Base::drawBitmap(104, 28, Cards::a_1, 24, 8, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(104, 28, Cards::a_2, 24, 8, WHITE);
      }
    }
    else
    {
      if (utils->halfCycleCheck())
      {
        switch (currentToolSelected)
        {
        case 0:
          Arduboy2Base::drawBitmap(104, 28, Cards::plant_0, 24, 8, WHITE);
          break;
        case 1:
          Arduboy2Base::drawBitmap(104, 28, Cards::sheers_0, 24, 8, WHITE);
          break;
        case 2:
          Arduboy2Base::drawBitmap(104, 28, Cards::sword_0, 24, 8, WHITE);
          break;
        case 3:
          Arduboy2Base::drawBitmap(104, 28, Cards::items_0, 24, 8, WHITE);
          break;
        }
      }
      else
      {
        switch (currentToolSelected)
        {
        case 0:
          Arduboy2Base::drawBitmap(104, 28, Cards::plant_1, 24, 8, WHITE);
          break;
        case 1:
          Arduboy2Base::drawBitmap(104, 28, Cards::sheers_1, 24, 8, WHITE);
          break;
        case 2:
          Arduboy2Base::drawBitmap(104, 28, Cards::sword_1, 24, 8, WHITE);
          break;
        case 3:
          Arduboy2Base::drawBitmap(104, 28, Cards::items_1, 24, 8, WHITE);
          break;
        }
      }
    }
  }

  void displayCardOption(Utils *utils)
  {
    switch (currentAction)
    {
    case 1:
      if (utils->halfCycleCheck())
      {
        Arduboy2Base::drawBitmap(104, 21, Cards::change_1, 24, 8, WHITE);
      }
      else
      {
        Arduboy2Base::drawBitmap(104, 21, Cards::change_2, 24, 8, WHITE);
      }
      break;
    case 2:
      Arduboy2Base::drawBitmap(104, 21, Cards::use_0, 24, 8, WHITE);
      break;
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

  bool check(uint8_t x, uint8_t y, bool check)
  {
    return (check) ? map[x][y] == EMPTY_NUMBER : map[x][y] < SEED_1_NUMBER;
  }

  bool mazeOccupancy(uint8_t x, uint8_t y, bool left, bool right, bool up, bool down)
  {
    uint8_t checks = 0;
    if (check(x - 1, y, left))
    {
      checks++;
    }
    if (check(x + 1, y, right))
    {
      checks++;
    }
    if (check(x, y - 1, up))
    {
      checks++;
    }
    if (check(x, y + 1, down))
    {
      checks++;
    }
    return checks == 4;
  }

  void displayMaze(Utils *utils, uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
    if (x > 0 && y < SQUARE_AMOUNT_WEIGHT - 1 && map[x][y] < SEED_1_NUMBER && currentAction > 1 && currentToolSelected == 0)
    {
      if (mazeOccupancy(x, y, false, false, true, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, true, false, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, false, false, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, false, false, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, false, true, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, true, true, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, true, false, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, false, false, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, false, true, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_bottom_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, true, true, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_bottom_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, true, false, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_bottom_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, true, true, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, false, false, true, true))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_top_bottom, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
      else if (mazeOccupancy(x, y, true, true, false, false))
      {
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::map_left_right, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      }
    }

    if (!(i == playerXPosition && j == playerYPosition))
    {
      switch (map[x][y])
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
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 4:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 5:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 6:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 7:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_4, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 8:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::home_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 9:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 10:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 11:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 12:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 13:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_4, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 14:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::ranch_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
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
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::natural_hay_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::natural_hay_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 21:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 23:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_3, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 25:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_4, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_5, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 27:
        if (utils->halfCycleCheck())
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_6, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Mini::sheep_7, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
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
      }
    }
  }

  uint8_t move(Utils *utils, Stats *stats, const int extX, const int extY)
  {
    if (playerXPosition + extX >= 0 && playerYPosition + extY >= 0 && playerXPosition + extX < SQUARE_AMOUNT_WEIGHT - 1 && playerYPosition + extY < SQUARE_AMOUNT_HEIGHT - 1)
    {
      uint8_t value = map[playerXPosition + mapOffsetX + extX][playerYPosition + mapOffsetY + extY];

      if (value == SEED_1_NUMBER + 10)
      {
        stats->plusSeedOne(utils);
        plusAnimation = 5;
        map[playerXPosition + mapOffsetX + extX][playerYPosition + mapOffsetY + extY] = EMPTY_NUMBER;
      }
      if (value == SEED_2_NUMBER + 10)
      {
        stats->plusSeedTwo(utils);
        plusAnimation = 5;
        map[playerXPosition + mapOffsetX + extX][playerYPosition + mapOffsetY + extY] = EMPTY_NUMBER;
      }
      if (value == SEED_3_NUMBER + 10)
      {
        stats->plusSeedThree(utils);
        plusAnimation = 5;
        map[playerXPosition + mapOffsetX + extX][playerYPosition + mapOffsetY + extY] = EMPTY_NUMBER;
      }

      if (value == 17)
      {
        // to right map
        return 2;
      }
      else if (value > 16)
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

  uint8_t useTool(Utils *utils, Stats *stats)
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

    if (stats->getEnergy() > 0)
    {
      uint8_t value = map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)];
      switch (currentToolSelected)
      {
      case 0:
        if (canPlace())
        {
          map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = (SEED_1_NUMBER + rand() % 3);
          stats->decEnergy(1);
          return 1;
        }
        break;
      case 1:
        if (value == 21 || value == 25)
        {
          map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = value + 2;
          stats->plusWool(utils);
          plusAnimation = 5;
          return 1;
        }
        break;
      case 2:
        if (attackEnemy(value))
        {
          map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = VOID_NUMBER;
          utils->subtleOkBeep();
        }
        break;
      case 3:
        if (stats->potionsAmount > 0 && stats->getHP() < MAX_CAPACITY)
        {
          utils->okBeep();
          stats->usePotion();
        }
        break;
      }
    }
    return 0;
  }

  void displayToolAction(Utils *utils)
  {
    if (currentAction == 2)
    {
      if (canPlace() && currentToolSelected == 0)
      {
        displayPlaceIcon(utils);
      }
    }
  }

  bool canPlace()
  {
    switch (playerOrientation)
    {
    case 0:
      if (playerYPosition + mapOffsetY > 0 && map[playerXPosition + mapOffsetX][playerYPosition + mapOffsetY - 1] == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 1:
      if (playerXPosition + mapOffsetX < REAL_MAP_WEIGHT - 1 && map[playerXPosition + mapOffsetX + 1][playerYPosition + mapOffsetY] == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 2:
      if (playerYPosition + mapOffsetY < REAL_MAP_HEIGHT - 1 && map[playerXPosition + mapOffsetX][playerYPosition + mapOffsetY + 1] == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    case 3:
      if (playerXPosition + mapOffsetX > 0 && map[playerXPosition + mapOffsetX - 1][playerYPosition + mapOffsetY] == EMPTY_NUMBER)
      {
        return true;
      }
      break;
    }

    return false;
  }
};
