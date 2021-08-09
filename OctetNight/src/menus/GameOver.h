#pragma once

class GameOver
{
private:
  uint8_t timeout;

public:
  void refresh()
  {
    timeout = 50;
  }

  bool action()
  {
    Arduboy2Base::drawBitmap(25, 25, Lines::game_over, 78, 8, WHITE);
    if (timeout > 0)
    {
      timeout--;
      return false;
    }
    return true;
  }
};
