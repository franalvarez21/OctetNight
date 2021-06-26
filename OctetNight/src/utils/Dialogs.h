#pragma once

struct Dialogs
{
  void displayDialogs(uint8_t number, bool subject = false)
  {
    Arduboy2Base::drawBitmap(87, 53, Hub::text_dialog_bubble_right_1, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(34, 53, Hub::text_dialog_bubble_left_1, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(39, 48, Hub::text_dialog_bubble_1, 53, 15, BLACK);
    Arduboy2Base::drawBitmap(40, 49, Hub::text_dialog_bubble, 51, 13, WHITE);
    Arduboy2Base::drawBitmap(88, 54, subject ? Hub::text_dialog_bubble_right : Hub::text_dialog_bubble_right_2, 8, 8, WHITE);
    Arduboy2Base::drawBitmap(35, 54, subject ? Hub::text_dialog_bubble_left_2 : Hub::text_dialog_bubble_left, 8, 8, WHITE);

    switch (number)
    {
    case 0:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_0, 43, 13, WHITE);
      break;
    case 1:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_1, 43, 13, WHITE);
      break;
    case 2:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_2, 43, 13, WHITE);
      break;
    case 3:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_3, 43, 13, WHITE);
      break;
    case 4:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_4, 43, 13, WHITE);
      break;
    case 5:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_5, 43, 13, WHITE);
      break;
    case 6:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_6, 43, 13, WHITE);
      break;
    case 7:
      Arduboy2Base::drawBitmap(44, 51, Hub::text_dialog_7, 43, 13, WHITE);
      break;
    }

    Arduboy2Base::drawBitmap(3, 35, Hub::portrait_player_0, 31, 32, BLACK);
    Arduboy2Base::drawBitmap(4, 36, Hub::portrait_player_1, 29, 30, WHITE);
  }
};
