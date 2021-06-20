#pragma once

struct Stats
{
  uint16_t hp;
  uint16_t money;
  uint16_t energy;

  void init()
  {
    hp = MAX_CAPACITY;
    money = 2;
    energy = MAX_CAPACITY;
  }

  void incHP(uint8_t val)
  {
    hp = min(hp + val, MAX_CAPACITY);
  }

  void decHP(uint8_t val)
  {
    hp = max(hp - val, 0);
  }

  void incMoney(uint8_t val)
  {
    money = min(money + val, REAL_MAX_CAPACITY);
  }

  void decMoney(uint8_t val)
  {
    money = max(money - val, 0);
  }

  void incEnergy(uint8_t val)
  {
    energy = min(energy + val, MAX_CAPACITY);
  }

  void decEnergy(uint8_t val)
  {
    energy = max(energy - val, 0);
  }

  uint8_t getHP()
  {
    return min(hp, MAX_CAPACITY);
  }

  uint8_t getMoney()
  {
    return min(money, MAX_CAPACITY);
  }

  uint8_t getRealMoney()
  {
    return min(money, REAL_MAX_CAPACITY);
  }

  uint8_t getEnergy()
  {
    return min(energy, MAX_CAPACITY);
  }
};
