#pragma once

struct Stats
{
  uint8_t hp;
  uint16_t money;
  uint8_t energy;

  uint16_t seedOne;
  uint16_t seedTwo;
  uint16_t seedThree;
  uint16_t seedFour;
  uint16_t seedFive;
  uint16_t seedSix;

  uint8_t sheepAmount;
  uint16_t potionsAmount;
  uint16_t seedOneAmount;
  uint16_t seedTwoAmount;
  uint16_t seedThreeAmount;
  uint16_t seedFourAmount;
  uint16_t seedFiveAmount;
  uint16_t seedSixAmount;
  uint16_t woolAmount;

  void init()
  {
    seedOne = 20;
    seedTwo = 0;
    seedThree = 0;
    seedFour = 0;
    seedFive = 0;
    seedSix = 0;

    sheepAmount = 1;
    seedOneAmount = 0;
    seedTwoAmount = 0;
    seedThreeAmount = 0;
    seedFourAmount = 0;
    seedFiveAmount = 0;
    seedSixAmount = 0;
    potionsAmount = 99;
    woolAmount = 0;

    money = 200;
    rest();
  }

  void rest()
  {
    hp = MAX_CAPACITY;
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

  void incSeedOne(uint8_t val)
  {
    seedOne = min(seedOne + val, REAL_MAX_CAPACITY);
  }

  void decSeedOne(uint8_t val)
  {
    seedOne = max(seedOne - val, 0);
  }

  void incSeedTwo(uint8_t val)
  {
    seedTwo = min(seedTwo + val, REAL_MAX_CAPACITY);
  }

  void decSeedTwo(uint8_t val)
  {
    seedTwo = max(seedTwo - val, 0);
  }

  void incSeedThree(uint8_t val)
  {
    seedThree = min(seedThree + val, REAL_MAX_CAPACITY);
  }

  void decSeedThree(uint8_t val)
  {
    seedThree = max(seedThree - val, 0);
  }

  void incSeedFour(uint8_t val)
  {
    seedFour = min(seedFour + val, REAL_MAX_CAPACITY);
  }

  void decSeedFour(uint8_t val)
  {
    seedFour = max(seedFour - val, 0);
  }

  void incSeedFive(uint8_t val)
  {
    seedFive = min(seedFive + val, REAL_MAX_CAPACITY);
  }

  void decSeedFive(uint8_t val)
  {
    seedFive = max(seedFive - val, 0);
  }

  void incSeedSix(uint8_t val)
  {
    seedSix = min(seedSix + val, REAL_MAX_CAPACITY);
  }

  void decSeedSix(uint8_t val)
  {
    seedSix = max(seedSix - val, 0);
  }

  void plusSeedOne()
  {
    seedOneAmount = min(seedOneAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusSeedTwo()
  {
    seedTwoAmount = min(seedTwoAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusSeedThree()
  {
    seedThreeAmount = min(seedThreeAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusSeedFour()
  {
    seedFourAmount = min(seedFourAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusSeedFive()
  {
    seedFiveAmount = min(seedFiveAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusSeedSix()
  {
    seedSixAmount = min(seedSixAmount + 1, REAL_MAX_CAPACITY);
  }

  void plusWool()
  {
    woolAmount = min(woolAmount + 1, REAL_MAX_CAPACITY);
  }

  void addPotion()
  {
    potionsAmount = min(potionsAmount + 1, REAL_MAX_CAPACITY);
  }

  void usePotion()
  {
    potionsAmount = max(potionsAmount - 1, 0);
    incHP(1);
  }

  void buySheep()
  {
    sheepAmount = min(sheepAmount + 1, SHEEP_MAX_AMOUNT);
  }

  void sellAll()
  {
    incMoney(seedOneAmount * 40);
    incMoney(seedTwoAmount * 45);
    incMoney(seedThreeAmount * 60);
    incMoney(seedFourAmount * 80);
    incMoney(seedFiveAmount * 85);
    incMoney(seedSixAmount * 100);
    incMoney(woolAmount * 200);

    seedOneAmount = 0;
    seedTwoAmount = 0;
    seedThreeAmount = 0;
    seedFourAmount = 0;
    seedFiveAmount = 0;
    seedSixAmount = 0;
    woolAmount = 0;
  }

  uint16_t getTotalSeedAmount()
  {
    return seedOne + seedTwo + seedThree + seedFour + seedFive + seedSix;
  }

  uint16_t getTotalCropAmount()
  {
    return seedOneAmount + seedTwoAmount + seedThreeAmount + seedFourAmount + seedFiveAmount + seedSixAmount;
  }

  uint8_t getHP()
  {
    return min(hp, MAX_CAPACITY);
  }

  uint8_t getMoney()
  {
    switch (money)
    {
    case 0 ... 10:
      return 1;
    case 11 ... 100:
      return 2;
    case 101 ... 500:
      return 3;
    case 501 ... 1000:
      return 4;
    case 1001 ... 2500:
      return 5;
    case 2501 ... 5000:
      return 6;
    case 5001 ... 7500:
      return 7;
    case 7501 ... 9000:
      return 8;
    default:
      return 9;
    }
  }

  uint16_t getRealMoney()
  {
    return min(money, REAL_MAX_CAPACITY);
  }

  uint8_t getEnergy()
  {
    return min(energy, MAX_CAPACITY);
  }
};
