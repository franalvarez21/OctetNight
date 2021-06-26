#pragma once

#include <Arduboy2.h>

#include "const/Map.h"
#include "const/Common.h"
#include "const/Mini.h"
#include "const/Lines.h"
#include "const/Title.h"
#include "const/Cards.h"
#include "const/Seeds.h"
#include "const/Hub.h"
#include "const/Digits.h"

struct Utils
{
  Arduboy2Base *arduboy;

  uint8_t cycle;

  void init(Arduboy2Base *arduboy)
  {
    this->arduboy = arduboy;
    cycle = CYCLE_TIME;
  }

  void tick()
  {
    cycle--;
    if (cycle < 1)
    {
      cycle = CYCLE_TIME;
    }
  }

  bool halfCycleCheck()
  {
    return cycle <= CYCLE_TIME / 2;
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};
