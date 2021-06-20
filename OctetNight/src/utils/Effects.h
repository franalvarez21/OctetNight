#pragma once

#include <Bistercian.h>

struct Effects
{
  Bistercian bistercian;

  void displayErrorLine(int16_t x, int16_t y, int16_t size)
  {
    if (rand() % 10 == 0)
    {
      Arduboy2Base::drawFastHLine(x, rand() % y, size, BLACK);
    }
  }

  void displayBistercian(int16_t x, int16_t y, int32_t number)
  {
    bistercian.setCursor(x, y);
    bistercian.print(number);
  }

  void displayBistercianColumn(int16_t x, int16_t y, int8_t size)
  {
    for (uint8_t i = 0; i < size; i++)
    {
      displayBistercian(x, y + i * 6, rand() % 10000);
    }
  }

  void displayBistercianBar(int16_t x, int16_t y, int8_t size)
  {
    for (uint8_t i = 0; i < size; i++)
    {
      displayBistercian(x + i * 6, y, rand() % 10000);
    }
  }
};
