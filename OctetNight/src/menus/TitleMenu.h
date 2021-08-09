#pragma once

class TitleMenu : public Menu
{
public:
  TitleMenu() : Menu(1){};

  uint8_t action(bool saveFlag)
  {
    maxOption = saveFlag ? 1 : 0;

    upDownMovement();

    if (okMovement())
    {
      switch (option)
      {
      case 0:
        return 1;
      case 1:
        return 2;
      }
    }

    return 0;
  }

  void eventDisplay(Cycle *cycle, bool saveFlag)
  {
    Arduboy2Base::drawBitmap(73, 0, Title::title_2, 52, 24, WHITE);
    Arduboy2Base::drawBitmap(20, 18, cycle->halfCycleCheck() ? Title::title_0 : Title::title_1, 23, 23, WHITE);
    Arduboy2Base::drawBitmap(65, 30, cycle->halfCycleCheck() ? Title::title_3 : Title::title_4, 12, 12, WHITE);
    Arduboy2Base::drawBitmap(20, 41, Title::title_5, 60, 8, WHITE);

    if (saveFlag)
    {
      Arduboy2Base::drawBitmap(104, 52, Lines::start, 24, 4, WHITE);
      Arduboy2Base::drawBitmap(109, 60, Lines::load, 24, 4, WHITE);
      displayMenuCursor(98, 52);
    }
    else
    {
      Arduboy2Base::drawBitmap(104, 60, Lines::start, 24, 4, WHITE);
      displayMenuCursor(98, 60);
    }

    Arduboy2Base::drawBitmap(0, 56, Title::g_rating, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(10, 61, Lines::mark, 35, 3, WHITE);
    Arduboy2Base::drawBitmap(112, 25, Lines::version, 16, 4, WHITE);
  }
};
