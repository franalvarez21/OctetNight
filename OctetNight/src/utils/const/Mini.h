#pragma once

namespace Mini
{
  const uint8_t PROGMEM clock[] = {
      0xc0, 0xd8, 0x9c, 0x1e, 0x3e, 0x30, 0x03, 0x87, 0x4f, 0xcf, 0x87, 0x03, 0x30, 0x3e, 0x1e, 0x9c, 0xd8, 0xc0, 0x1f, 0xdf, 0xcf, 0xc7, 0xe0, 0x60, 0x07, 0x0c, 0x9f, 0x97, 0x09, 0x07, 0x60, 0xe0, 0xc7, 0xcf, 0xdf, 0x1f, 0x00, 0x00, 0x01, 0x03, 0x03, 0x00, 0x06, 0x07, 0x07, 0x07, 0x07, 0x06, 0x00, 0x03, 0x03, 0x01, 0x00, 0x00, 
  };

  const uint8_t PROGMEM clock_empty[] = {
      0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
  };

  const uint8_t PROGMEM plant_tool[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x70, 0x38, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0c, 0x43, 0x40, 0x20, 0xa1, 0x92, 0x45, 0x4b, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM sheers_tool[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x90, 0x48, 0x28, 0x18, 0x88, 0x40, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x24, 0x14, 0x8c, 0x48, 0x37, 0xe9, 0x08, 0x0c, 0x0a, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM sword_tool[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x90, 0x48, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x64, 0x5c, 0x38, 0x34, 0x6a, 0x09, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM items_tool[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x90, 0x38, 0x38, 0x38, 0x28, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x04, 0x13, 0x00, 0x00, 0x43, 0x24, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM sheep_0[] = {
      0x38, 0xfc, 0x7e, 0x7e, 0x7c, 0x7e, 0x36, 0x1c, 
  };

  const uint8_t PROGMEM sheep_1[] = {
      0x38, 0x7c, 0x7e, 0x7e, 0x7c, 0xfe, 0x36, 0x1c, 
  };

  const uint8_t PROGMEM sheep_2[] = {
      0x20, 0xf0, 0x70, 0x70, 0x70, 0x7c, 0x34, 0x1c, 
  };

  const uint8_t PROGMEM sheep_3[] = {
      0x20, 0x70, 0x70, 0x70, 0x70, 0xfc, 0x34, 0x1c, 
  };

  const uint8_t PROGMEM sheep_4[] = {
      0x1c, 0x36, 0x7e, 0x7c, 0x7e, 0x7e, 0xfc, 0x38, 
  };

  const uint8_t PROGMEM sheep_5[] = {
      0x1c, 0x36, 0xfe, 0x7c, 0x7e, 0x7e, 0x7c, 0x38, 
  };

  const uint8_t PROGMEM sheep_6[] = {
      0x1c, 0x34, 0x7c, 0x70, 0x70, 0x70, 0xf0, 0x20, 
  };

  const uint8_t PROGMEM sheep_7[] = {
      0x1c, 0x34, 0xfc, 0x70, 0x70, 0x70, 0x70, 0x20, 
  };
}
