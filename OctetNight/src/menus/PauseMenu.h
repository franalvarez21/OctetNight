#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(5){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 5)
      {
        utils->okBeep();
        return 3;
      }
      else if (option == 4)
      {
        utils->okBeep();
        // Load Game message
      }
      else if (option == 3)
      {
        utils->okBeep();
        // Save Game message
      }
      else if (option == 2)
      {
        utils->changesoundFlag();
      }
      else if (option == 1)
      {
        utils->okBeep();
        return 2;
      }
      else if (option == 0)
      {
        return 1;
      }
    }

    if (koMovement())
    {
      return 1;
    }

    return 0;
  }

  void eventDisplay(Utils *utils, Stats *stats, Numbers *numbers)
  {
    // Stats
    Arduboy2Base::drawBitmap(5, 4, Lines::stats, 33, 22, WHITE);
    printBigNumber(numbers, 26, 10, stats->getRealMoney());
    numbers->print(26, 16, stats->potionsAmount);
    numbers->print(26, 22, stats->woolAmount);

    Arduboy2Base::drawBitmap(5, 34, Lines::crops, 51, 22, WHITE); // crops
    numbers->print(10, 40, stats->seedSixAmount);
    numbers->print(10, 46, stats->seedFiveAmount);
    numbers->print(10, 52, stats->seedFourAmount);
    numbers->print(43, 40, stats->seedThreeAmount);
    numbers->print(43, 46, stats->seedTwoAmount);
    numbers->print(43, 52, stats->seedOneAmount);

    // Menu
    Arduboy2Base::drawBitmap(74, 4, Lines::options, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 22, Lines::back, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 28, Lines::nDay, 34, 4, WHITE);
    if (utils->soundFlag)
    {
      Arduboy2Base::drawBitmap(82, 34, Lines::sOn, 34, 4, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(82, 34, Lines::sOff, 34, 4, WHITE);
    }
    Arduboy2Base::drawBitmap(82, 40, Lines::save, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 46, Lines::load, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 52, Lines::mMenu, 34, 4, WHITE);
    displayMenuCursor(76, 22, 6);

    // Hub
    Arduboy2Base::drawBitmap(110, 2, Hub::hub_0, 16, 60, WHITE);
    Arduboy2Base::drawBitmap(12, 59, Hub::hub_1, 100, 2, WHITE);
    if (stats->getHP() < 3)
    {
      Arduboy2Base::drawBitmap(115, 6, Hub::smile_2, 6, 6, BLACK);
    }
    else if (stats->getHP() < 6)
    {
      Arduboy2Base::drawBitmap(115, 6, Hub::smile_1, 6, 6, BLACK);
    }
    else
    {
      Arduboy2Base::drawBitmap(115, 6, Hub::smile_0, 6, 6, BLACK);
    }
  }
};
