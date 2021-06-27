#pragma once

class LevelProgression
{
public:
  uint8_t keyZoneA;

  void reset()
  {
    keyZoneA = 0;
  }

  void addKeyZoneA()
  {
    keyZoneA++;
  }

  bool canAccessZoneA(uint8_t number)
  {
    return number < keyZoneA;
  }
};
