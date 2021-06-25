#pragma once

class StoreMenu : public Menu
{
public:
  StoreMenu() : Menu(6){};

  void refresh()
  {
    option = 0;
  }

  uint8_t action(Utils *utils, Stats *stats)
  {
    upDownMovement();

    if (okMovement())
    {
      switch (option)
      {
      case 0:
        stats->sellAll();
        utils->okBeep();
        break;
      case 1:
        if (stats->getRealMoney() > POTION_PRICE - 1)
        {
          stats->addPotion();
          stats->decMoney(POTION_PRICE);
          utils->okBeep();
        }
        break;
      case 2:
        if (stats->getRealMoney() > BASIC_SEED_PACK_PRICE - 1)
        {
          stats->incSeedOne(2 * rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedTwo(2 * rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedThree(1 * rand() % RANDOM_PACK_BENEFITS);
          stats->decMoney(BASIC_SEED_PACK_PRICE);
          utils->okBeep();
        }
        break;
      case 3:
        if (stats->getRealMoney() > MEDIUM_SEED_PACK_PRICE - 1)
        {
          stats->incSeedFour(2 * rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedFive(2 * rand() % RANDOM_PACK_BENEFITS);
          stats->incSeedSix(2 * rand() % RANDOM_PACK_BENEFITS);
          stats->decMoney(MEDIUM_SEED_PACK_PRICE);
          utils->okBeep();
        }
        break;
      case 4:
        if (stats->getRealMoney() > SHEEP_PRICE - 1 && stats->sheepAmount < SHEEP_MAX_AMOUNT)
        {
          stats->decMoney(SHEEP_PRICE);
          stats->buySheep();
          utils->okBeep();
        }
        break;
      case 5:
        stats->buySword();
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

    return 0;
  }

  void eventDisplay(Stats *stats, Numbers *numbers)
  {
    Arduboy2Base::drawBitmap(4, 6, Lines::buy, 38, 4, WHITE);

    Arduboy2Base::drawBitmap(49, 6, Lines::sAll, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 14, Lines::bPotion, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 22, Lines::bBasicSeedsPack, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 30, Lines::bMediumSeedsPack, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 38, Lines::bBuySheep, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 46, Lines::bBuySword, 38, 4, WHITE);
    Arduboy2Base::drawBitmap(49, 54, Lines::bBack, 38, 4, WHITE);
    displayMenuCursor(43, 6);

    printBigNumber(numbers, 95, 6, stats->getRealMoney());

    Arduboy2Base::drawBitmap(3, 35, Hub::portrait_player_0, 31, 32, BLACK);
    Arduboy2Base::drawBitmap(4, 36, Hub::portrait_player_1, 29, 30, WHITE);

    Arduboy2Base::drawBitmap(96, 35, Hub::portrait_shop_0, 29, 32, BLACK);
    Arduboy2Base::drawBitmap(97, 36, Hub::portrait_shop_1, 27, 30, WHITE);
  }
};
