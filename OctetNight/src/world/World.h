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

public:
  void refresh()
  {
    speedTick = 0;
    mapOffsetX = 0;
    mapOffsetY = 0;
    currentAction = 0;
    currentToolSelected = 0;
    playerOrientation = 1;
    playerXOrientation = true;
    reset();
  }

  bool inAction()
  {
    return (currentAction > 0);
  }

  bool action(Utils *utils, Stats *stats)
  {
    if (Arduboy2Base::justPressed(A_BUTTON))
    {
      if (currentAction > 0)
      {
        currentAction--;
        return true;
      }
    }

    if (Arduboy2Base::justPressed(B_BUTTON))
    {
      if (currentAction == 2)
      {
        return useTool(stats);
      }
      else if (currentAction == 1)
      {
        currentAction++;
      }
      else if (currentAction < 1)
      {
        currentToolSelected = 0;
        currentAction++;
        return true;
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
          return move(1, 0);
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
          return move(-1, 0);
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
          return move(0, 1);
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
          return move(0, -1);
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

    return false;
  }

  void reset()
  {
    justPressedLock = true;

    clearMap();
    clearPlayerPosition();
  }

  void displayTime(Utils *utils, Stats *stats)
  {

    // Display Items to use
    if (currentAction > 0)
    {
      switch (currentToolSelected)
      {
      case 0:
        Arduboy2Base::drawBitmap(106, 2, Mini::plant_tool, 20, 20, WHITE);
        break;
      case 1:
        Arduboy2Base::drawBitmap(106, 2, Mini::water_tool, 20, 20, WHITE);
        break;
      case 2:
        Arduboy2Base::drawBitmap(106, 2, Mini::sheers_tool, 20, 20, WHITE);
        break;
      case 3:
        Arduboy2Base::drawBitmap(106, 2, Mini::sword_tool, 20, 20, WHITE);
        break;
      case 4:
        Arduboy2Base::drawBitmap(106, 2, Mini::items_tool, 20, 20, WHITE);
        break;
      }
    }
    else
    // Display Clock
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

      // use empty clock to cover the corners depending on the stamina left, time will depend on the stamina only,
      // and will not be possible to access the TOP with less than 2 stamina.
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
          map[i][j] = rand() % 3 + 18;
        }
      }
    }
  }

  void clearPlayerPosition()
  {
    playerXPosition = 3;
    playerYPosition = 3;
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
    if (utils->cycle <= 5)
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
    if (utils->cycle <= 5)
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
      if (utils->cycle <= 5)
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
      if (utils->cycle <= 5)
      {
        switch (currentToolSelected)
        {
        case 0:
          Arduboy2Base::drawBitmap(104, 28, Cards::plant_0, 24, 8, WHITE);
          break;
        case 1:
          Arduboy2Base::drawBitmap(104, 28, Cards::water_0, 24, 8, WHITE);
          break;
        case 2:
          Arduboy2Base::drawBitmap(104, 28, Cards::sheers_0, 24, 8, WHITE);
          break;
        case 3:
          Arduboy2Base::drawBitmap(104, 28, Cards::sword_0, 24, 8, WHITE);
          break;
        case 4:
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
          Arduboy2Base::drawBitmap(104, 28, Cards::water_1, 24, 8, WHITE);
          break;
        case 2:
          Arduboy2Base::drawBitmap(104, 28, Cards::sheers_1, 24, 8, WHITE);
          break;
        case 3:
          Arduboy2Base::drawBitmap(104, 28, Cards::sword_1, 24, 8, WHITE);
          break;
        case 4:
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
    case 0:
      Arduboy2Base::drawBitmap(104, 21, Cards::use_0, 24, 8, WHITE);
      break;
    case 1:
      if (utils->cycle <= 5)
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

  void displayMaze(Utils *utils, uint8_t x, uint8_t y, uint8_t i, uint8_t j)
  {
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
        if (utils->cycle <= 5)
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_right_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 17:
        if (utils->cycle <= 5)
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::exit_top_arrow, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 18:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::floor_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 19:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::floor_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 20:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::floor_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      case 21:
        if (utils->cycle <= 5)
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::natural_hay_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        else
        {
          Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::natural_hay_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        }
        break;
      case 22:
        Arduboy2Base::drawBitmap(SQUARE_SIZE * i, SQUARE_SIZE * j, Map::door_0, SQUARE_SIZE, SQUARE_SIZE, WHITE);
        break;
      }
    }
  }

  bool move(const int extX, const int extY)
  {
    if (playerXPosition + extX >= 0 && playerYPosition + extY >= 0 && playerXPosition + extX < SQUARE_AMOUNT_WEIGHT - 1 && playerYPosition + extY < SQUARE_AMOUNT_HEIGHT - 1)
    {
      uint8_t value = map[playerXPosition + mapOffsetX + extX][playerYPosition + mapOffsetY + extY];
      if (value > 15)
      {
        playerXPosition += extX;
        playerYPosition += extY;
        return true;
      }
    }
    return false;
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

    if (utils->cycle <= 5)
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + (-1 + x)), SQUARE_SIZE * (playerYPosition + (-1 + y)), Common::available_spot_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(SQUARE_SIZE * (playerXPosition + (-1 + x)), SQUARE_SIZE * (playerYPosition + (-1 + y)), Common::available_spot_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    }
  }

  bool useTool(Stats *stats)
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

    if (stats->getEnergy() > 0 && canPlace())
    {
      switch (currentToolSelected)
      {
      case 0:
        map[playerXPosition + mapOffsetX + (-1 + x)][playerYPosition + mapOffsetY + (-1 + y)] = 21;
        stats->decEnergy(1);
        return true;
      case 1:
        return true;
      case 2:
        return true;
      case 3:
        return true;
      case 4:
        return true;
      }
    }
    return false;
  }

  void displayToolAction(Utils *utils)
  {
    if (currentAction == 2)
    {
      if (canPlace())
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
