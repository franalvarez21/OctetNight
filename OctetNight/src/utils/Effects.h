#pragma once

#include <Bistercian.h>

struct Effects
{
  Bistercian bistercian;
  uint8_t plusAn;
  uint8_t sleepAn;

  void refresh() // 261
  {
    plusAn = 0;
    sleepAn = 0;
  }

  void playerAnimationTick(uint8_t x, uint8_t y)
  {
    if (plusAn > 0)
    {
      Arduboy2Base::drawBitmap(x, y, Common::plus_animation_0, SQUARE_SIZE, SQUARE_SIZE, BLACK);
      Arduboy2Base::drawBitmap(x, y, Common::plus_animation_1, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      plusAn--;
    }

    if (sleepAn > 0)
    {
      Arduboy2Base::drawBitmap(x, y, Common::plus_animation_0, SQUARE_SIZE, SQUARE_SIZE, BLACK);
      Arduboy2Base::drawBitmap(x, y, Common::sleep_animation_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
      sleepAn--;
    }
  }

  void plusAnimation()
  {
    plusAn = 5;
  }

  void sleepAnimation()
  {
    sleepAn = 5;
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

  static void displayErrorLine(int16_t x, int16_t y, int16_t size)
  {
    if (rand() % 10 == 0)
    {
      Arduboy2Base::drawFastHLine(x, rand() % y, size, BLACK);
    }
  }
};
