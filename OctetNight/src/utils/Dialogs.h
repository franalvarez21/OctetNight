#pragma once

struct Dialogs
{
  bool subject;
  uint8_t displayDialog;
  uint8_t displayCooldown;

  void init()
  {
    subject = false;
    displayDialog = 0;
    displayCooldown = DIALOG_COOLDOWN + 10;
  }

  void tick()
  {
    if (displayCooldown > 0)
    {
      display();
      displayCooldown--;
    }
    else
    {
      displayDialog = 0;
    }
  }

  void displayDialogs(uint8_t number, bool side = false)
  {
    subject = side;
    displayDialog = number;
    displayCooldown = side ? 2 : DIALOG_COOLDOWN;
  }

  void display()
  {
    Arduboy2Base::drawBitmap(87, 53, Hub::text_dialog_bubble_right_1, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(34, 53, Hub::text_dialog_bubble_left_1, 10, 10, BLACK);
    Arduboy2Base::drawBitmap(39, 48, Hub::text_dialog_bubble_1, 53, 15, BLACK);
    Arduboy2Base::drawBitmap(40, 49, Hub::text_dialog_bubble, 51, 13, WHITE);
    Arduboy2Base::drawBitmap(88, 54, subject ? Hub::text_dialog_bubble_right : Hub::text_dialog_bubble_right_2, SQUARE_SIZE, SQUARE_SIZE, WHITE);
    Arduboy2Base::drawBitmap(35, 54, subject ? Hub::text_dialog_bubble_left_2 : Hub::text_dialog_bubble_left, SQUARE_SIZE, SQUARE_SIZE, WHITE);

    switch (displayDialog)
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
