#pragma once

#include "../Game.h"

class Menu
{
protected:
  uint8_t option;
  uint8_t maxOption;

public:
  Menu(uint8_t value = 4) : maxOption(value), option(0){};

  void upDownMovement()
  {
    if (Arduboy2Base::justPressed(UP_BUTTON))
    {
      if (option > 0)
      {
        option--;
      }
    }

    if (Arduboy2Base::justPressed(DOWN_BUTTON))
    {
      if (option < maxOption)
      {
        option++;
      }
    }
  }

  bool okMovement()
  {
    return Arduboy2Base::justPressed(B_BUTTON) || Arduboy2Base::justPressed(RIGHT_BUTTON);
  }

  bool koMovement()
  {
    return Arduboy2Base::justPressed(A_BUTTON) || Arduboy2Base::justPressed(LEFT_BUTTON);
  }

  void displayMenuCursor(uint8_t x, uint8_t y, uint8_t jumps = SQUARE_SIZE)
  {
    Arduboy2Base::drawBitmap(x, y - 1 + (jumps * option), Common::cursor, 4, 5, WHITE);
  }

  void printBigNumber(Numbers *numbers, uint8_t x, uint8_t y, uint16_t value)
  {
    if (value < 100)
    {
      numbers->print(x, y, value, 2);
    }
    else if (value < 1000)
    {
      numbers->print(x + 5, y, value, 4);
    }
    else
    {
      numbers->print(x + 10, y, value, 4);
    }
  }
};
