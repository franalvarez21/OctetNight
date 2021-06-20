#pragma once

namespace Map
{
  const PROGMEM uint8_t map_0[REAL_MAP_WEIGHT][REAL_MAP_HEIGHT] = {
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 3, 6, 22, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 4, 7, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 5, 8, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 1, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 15, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 15, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 15, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 15, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 1, 1, 1, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, EMPTY_NUMBER, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 9, 12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 10, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 11, 14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
      { 0, 1, 1, 1, 16, 16, 1, 1, 1, 1, 1, 1, 1, 0, },
  };

  const uint8_t PROGMEM tree_0[] = {
      0x00, 0x04, 0x08, 0x72, 0x6d, 0x10, 0x08, 0x00,
  };

  const uint8_t PROGMEM tree_1[] = {
      0x00, 0x04, 0x28, 0x72, 0x6c, 0x12, 0x09, 0x00,
  };

  const uint8_t PROGMEM tree_2[] = {
      0x00, 0x12, 0x24, 0x79, 0x6e, 0x34, 0x12, 0x00,
  };

  const uint8_t PROGMEM home_0[] = {
      0xc0, 0xa0, 0x90, 0x90, 0x88, 0x84, 0xa4, 0x92, 
  };

  const uint8_t PROGMEM home_1[] = {
      0x82, 0xfd, 0xd5, 0xfd, 0xd5, 0xd5, 0xfd, 0x82, 
  };

  const uint8_t PROGMEM home_2[] = {
      0x92, 0xa4, 0x84, 0x88, 0x90, 0x90, 0xa0, 0xc0, 
  };

  const uint8_t PROGMEM home_3[] = {
      0x7e, 0x83, 0x7c, 0x92, 0x82, 0x82, 0x82, 0x7c, 
  };

  const uint8_t PROGMEM home_4[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
  };

  const uint8_t PROGMEM home_5[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x7c, 0x83, 0x7e, 
  };

  const uint8_t PROGMEM ranch_0[] = {
      0xe0, 0x90, 0xd0, 0xa8, 0xa8, 0x94, 0x54, 0x4a, 
  };

  const uint8_t PROGMEM ranch_1[] = {
      0x0a, 0x65, 0x93, 0x91, 0x91, 0x93, 0x65, 0x0a, 
  };

  const uint8_t PROGMEM ranch_2[] = {
      0x4a, 0x54, 0x94, 0xa8, 0xa8, 0xd0, 0x90, 0xe0, 
  };

  const uint8_t PROGMEM ranch_3[] = {
      0x7e, 0xab, 0x80, 0xfc, 0x8a, 0x8e, 0x8a, 0x8a, 
  };

  const uint8_t PROGMEM ranch_4[] = {
      0x8a, 0x8a, 0x8a, 0x8e, 0x8e, 0x8a, 0x8a, 0x8a, 
  };

  const uint8_t PROGMEM ranch_5[] = {
      0x8a, 0x8a, 0x8e, 0x8a, 0xfc, 0x80, 0xab, 0x7e, 
  };

  const uint8_t PROGMEM exit_right_arrow[] = {
      0x3c, 0x3c, 0x3c, 0x3c, 0xff, 0x7e, 0x3c, 0x18, 
  };

  const uint8_t PROGMEM exit_top_arrow[] = {
      0x08, 0x0c, 0xfe, 0xff, 0xff, 0xfe, 0x0c, 0x08, 
  };

  const uint8_t PROGMEM floor_0[] = {
      0x00, 0x04, 0x40, 0x00, 0x00, 0x10, 0x00, 0x00, 
  };

  const uint8_t PROGMEM floor_1[] = {
      0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM floor_2[] = {
      0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 
  };

  const uint8_t PROGMEM home_hay[] = {
      0x7e, 0x95, 0xbf, 0x95, 0xbf, 0x95, 0x7e, 0x00, 
  };

  const uint8_t PROGMEM natural_hay_0[] = {
      0x04, 0x08, 0x30, 0x00, 0x00, 0x60, 0x10, 0x00, 
  };

  const uint8_t PROGMEM natural_hay_1[] = {
      0x00, 0x00, 0x30, 0x08, 0x14, 0x60, 0x00, 0x00, 
  };

  const uint8_t PROGMEM door_0[] = {
      0x00, 0x00, 0x00, 0x2a, 0x2a, 0x2a, 0x2a, 0x00, 
  };

  const uint8_t PROGMEM map_top[] = {
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  };

  const uint8_t PROGMEM map_right[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  };

  const uint8_t PROGMEM map_left[] = {
      0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  const uint8_t PROGMEM map_bottom[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  };

  const uint8_t PROGMEM map_top_left[] = {
      0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  };

  const uint8_t PROGMEM map_top_right[] = {
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff,
  };

  const uint8_t PROGMEM map_bottom_right[] = {
      0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
  };

  const uint8_t PROGMEM map_bottom_left[] = {
      0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  };
}
