#pragma once

class StoreMenu : public Menu
{
private:
  bool sell;

public:
  StoreMenu() : Menu(5){};

  void refresh()
  {
    option = 0;
    sell = false;
  }

  uint8_t action(Stats *stats)
  {
    upDownMovement();

    if (okMovement())
    {
      switch (option)
      {
      case 0:
        stats->sellAll();
        break;
      case 1:
        if (stats->getRealMoney() > POTION_PRICE - 1)
        {
          stats->addPotion();
          stats->decMoney(POTION_PRICE);
          sell = true;
        }
        break;
      case 2:
        if (stats->getRealMoney() > BASIC_SEED_PACK_PRICE - 1)
        {
          stats->incSeedOne(2 + rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedTwo(2 + rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedThree(1 + rand() % RANDOM_PACK_BENEFITS);
          stats->decMoney(BASIC_SEED_PACK_PRICE);
          sell = true;
        }
        break;
      case 3:
        if (stats->getRealMoney() > MEDIUM_SEED_PACK_PRICE - 1)
        {
          stats->incSeedFour(2 + rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedFive(2 + rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedSix(2 + rand() % RANDOM_PACK_BENEFITS);
          stats->decMoney(MEDIUM_SEED_PACK_PRICE);
          sell = true;
        }
        break;
      case 4:
        if (stats->getRealMoney() > SHEEP_PRICE - 1 && stats->sheepAmount < SHEEP_MAX_AMOUNT)
        {
          stats->decMoney(SHEEP_PRICE);
          stats->buySheep();
          sell = true;
        }
        break;
      default:
        return 1;
        break;
      }
    }

    if (koMovement())
    {
      return 1;
    }

    return sell ? 3 : 2;
  }

  void eventDisplay(Stats *stats)
  {
    Arduboy2Base::drawBitmap(45, 6, Lines::shop, 66, 34, WHITE);
    displayMenuCursor(40, 6, 6);

    Numbers::print(10, 6, stats->getRealMoney());

    if (option > 0 && option < 5)
    {
      Arduboy2Base::drawBitmap(8, 14, Common::bar, 4, 1, WHITE);
    }

    switch (option)
    {
    case 1:
      Numbers::print(10, 12, POTION_PRICE);
      break;
    case 2:
      Numbers::print(10, 12, BASIC_SEED_PACK_PRICE);
      break;
    case 3:
      Numbers::print(10, 12, MEDIUM_SEED_PACK_PRICE);
      break;
    case 4:
      Numbers::print(10, 12, SHEEP_PRICE);
      break;
    }

    Arduboy2Base::drawBitmap(96, 35, Hub::portrait_shop_0, 29, 32, BLACK);
    Arduboy2Base::drawBitmap(97, 36, Hub::portrait_shop_1, 27, 30, WHITE);
  }
};
