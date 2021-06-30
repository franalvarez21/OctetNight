#pragma once

struct Dialogs
{
  bool subject;
  uint8_t displayDialog;
  uint8_t displayCooldown;

  uint8_t (*dialogList[9])[sizeof(Hub::text_dialog_0)] = {
    &Hub::text_dialog_0,
    &Hub::text_dialog_1,
    &Hub::text_dialog_2,
    &Hub::text_dialog_3,
    &Hub::text_dialog_4,
    &Hub::text_dialog_5,
    &Hub::text_dialog_6,
    &Hub::text_dialog_7,
    &Hub::text_dialog_8
  };

  void init()
  {
    subject = false;
    displayDialog = 0;
    displayCooldown = DIALOG_COOLDOWN;
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
    Arduboy2Base::drawBitmap(44, 51, *dialogList[displayDialog], 43, 13, WHITE);
    Arduboy2Base::drawBitmap(3, 35, Hub::portrait_player_0, 31, 32, BLACK);
    Arduboy2Base::drawBitmap(4, 36, Hub::portrait_player_1, 29, 30, WHITE);
  }
};
