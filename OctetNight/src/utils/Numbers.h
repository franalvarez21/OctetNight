#pragma once

class Numbers
{
public:
  static void print(uint8_t x, uint8_t y, int16_t number)
  {
    number = abs(number);
    uint16_t multiplier = 10;
    for (uint8_t i = 0; i < 4; i++)
    {
      printDigit(x, y, (number % multiplier) == 0 ? 0 : (number % multiplier) / (multiplier / 10), i);
      multiplier *= 10;
    }
  }

  static void printDigit(uint8_t x, uint8_t y, uint8_t number, uint8_t sector)
  {
    switch (number)
    {
    case 0:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::zero, 4, 4, WHITE);
      break;
    case 1:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::one, 4, 4, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::two, 4, 4, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::three, 4, 4, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::four, 4, 4, WHITE);
      break;
    case 5:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::five, 4, 4, WHITE);
      break;
    case 6:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::six, 4, 4, WHITE);
      break;
    case 7:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::seven, 4, 4, WHITE);
      break;
    case 8:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::eight, 4, 4, WHITE);
      break;
    case 9:
      Arduboy2Base::drawBitmap(x + (20 - 5 * sector), y, Digits::nine, 4, 4, WHITE);
      break;
    }
  }
};
