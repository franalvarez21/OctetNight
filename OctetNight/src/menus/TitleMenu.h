#pragma once

class TitleMenu : public Menu
{
public:
  TitleMenu() : Menu(1){};

  bool action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 1)
      {
        utils->changesoundFlag();
      }
      else if (option == 0)
      {
        utils->okBeep();
        return false;
      }
    }

    return true;
  }

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(65, 0, Title::title_2, 60, 25, WHITE);
    if (utils->halfCycleCheck())
    {
      Arduboy2Base::drawBitmap(15, 27, Title::title_0, 23, 23, WHITE);
      Arduboy2Base::drawBitmap(60, 39, Title::title_3, 12, 12, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(15, 27, Title::title_1, 23, 23, WHITE);
      Arduboy2Base::drawBitmap(60, 39, Title::title_4, 12, 12, WHITE);
    }

    Arduboy2Base::drawBitmap(98, 52, Lines::start, 24, 4, WHITE);
    Arduboy2Base::drawBitmap(98, 60, Lines::sound, 24, 4, WHITE);
    if (utils->soundFlag)
    {
      Arduboy2Base::drawBitmap(76, 60, Lines::on, 14, 4, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(76, 60, Lines::off, 14, 4, WHITE);
    }

    displayMenuCursor(92, 52);

    Arduboy2Base::drawBitmap(0, 60, Lines::version, 34, 4, WHITE);
  }
};
