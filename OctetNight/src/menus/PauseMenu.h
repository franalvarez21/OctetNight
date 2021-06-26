#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(4){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 4)
      {
        return 3;
      }
      else if (option == 3)
      {
        // Load Game message
      }
      else if (option == 2)
      {
        // Save Game message
      }
      else if (option == 1)
      {
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
    Arduboy2Base::drawBitmap(5, 20, Lines::stats, 34, 36, WHITE);
    numbers->print(37, 28, stats->getRealMoney(), 4);
    numbers->print(37, 34, stats->potionsAmount);
    numbers->print(37, 40, stats->woolAmount);
    numbers->print(37, 46, stats->getTotalCropAmount());
    numbers->print(37, 52, stats->getTotalSeedAmount());

    // Menu
    Arduboy2Base::drawBitmap(74, 4, Lines::options, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 28, Lines::back, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 34, Lines::nDay, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 40, Lines::save, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 46, Lines::load, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(82, 52, Lines::mMenu, 34, 4, WHITE);
    displayMenuCursor(76, 28, 6);

    // Hub
    Arduboy2Base::drawBitmap(110, 2, Hub::hub_0, 16, 60, WHITE);
    Arduboy2Base::drawBitmap(5, 59, Hub::hub_1, 107, 2, WHITE);
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
