#pragma once

struct Cycle
{
  uint8_t cycle;

  void init()
  {
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
};
