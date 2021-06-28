#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(4){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action()
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
        return 4;
      }
      else if (option == 2)
      {
        return 5;
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

  void eventDisplay(Stats *stats)
  {
    // Stats
    Arduboy2Base::drawBitmap(5, 20, Lines::stats, 34, 36, WHITE);
    Numbers::print(37, 28, stats->getRealMoney());
    Numbers::print(37, 34, stats->potionsAmount);
    Numbers::print(37, 40, stats->woolAmount);
    Numbers::print(37, 46, stats->getTotalCropAmount());
    Numbers::print(37, 52, stats->getTotalSeedAmount());

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
  }
};
