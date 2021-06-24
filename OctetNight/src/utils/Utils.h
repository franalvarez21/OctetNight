#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <Arduboy2.h>
#include <ArduboyTones.h>

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

  bool soundFlag;
  uint8_t music;
  uint8_t cycle;

  void init(Arduboy2Base *arduboy)
  {
    this->arduboy = arduboy;
    cycle = CYCLE_TIME;

    soundFlag = false;
    Arduboy2Base::audio.off();
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

  void changesoundFlag()
  {
    if (soundFlag)
    {
      soundFlag = false;
      Arduboy2Base::audio.off();
    }
    else
    {
      soundFlag = true;
      Arduboy2Base::audio.on();
      okBeep();
    }
  }

  void koBeep()
  {
    ArduboyTones::tone(250, 50);
  }

  void okBeep()
  {
    ArduboyTones::tone(700, 50);
  }

  void subtleKoBeep()
  {
    ArduboyTones::tone(200, 40);
  }

  void subtleOkBeep()
  {
    ArduboyTones::tone(600, 40);
  }

  uint8_t sizeTypeAbs(uint8_t a, uint8_t b)
  {
    return a < b ? b - a : a - b;
  }
};
