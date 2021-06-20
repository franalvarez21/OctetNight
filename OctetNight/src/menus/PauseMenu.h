#pragma once

class PauseMenu : public Menu
{
public:
  PauseMenu() : Menu(2){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 2)
      {
        utils->okBeep();
        return 2;
      }
      else if (option == 1)
      {
        utils->changesoundFlag();
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

  void eventDisplay(Utils *utils)
  {
    Arduboy2Base::drawBitmap(48, 8, Lines::options, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(54, 20, Lines::back, 34, 4, WHITE);
    if (utils->soundFlag)
    {
      Arduboy2Base::drawBitmap(54, 28, Lines::sOn, 34, 4, WHITE);
    }
    else
    {
      Arduboy2Base::drawBitmap(54, 28, Lines::sOff, 34, 4, WHITE);
    }
    Arduboy2Base::drawBitmap(54, 36, Lines::mMenu, 34, 4, WHITE);

    displayMenuCursor(48, 20);
  }
};
