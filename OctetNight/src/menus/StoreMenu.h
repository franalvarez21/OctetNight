#pragma once

class StoreMenu : public Menu
{
public:
  StoreMenu() : Menu(1){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils)
  {
    upDownMovement();

    if (okMovement())
    {
      if (option == 1)
      {
        return 1;
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

  void eventDisplay()
  {
    Arduboy2Base::drawBitmap(48, 8, Lines::options, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(54, 20, Lines::back, 34, 4, WHITE);
    Arduboy2Base::drawBitmap(54, 28, Lines::back, 34, 4, WHITE);
    displayMenuCursor(48, 20);
  }
};
