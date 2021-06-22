#pragma once

namespace Common
{
  const uint8_t PROGMEM bar[] = {
      0x01, 0x01, 0x01, 0x01,
  };

  const uint8_t PROGMEM player_0[] = {
      0x07, 0x05, 0x04, 0x6a, 0x56, 0xae, 0x40, 0x00, 
  };

  const uint8_t PROGMEM player_1[] = {
      0x07, 0x05, 0x04, 0xea, 0x56, 0x2e, 0x40, 0x00, 
  };

  const uint8_t PROGMEM player_2[] = {
      0x00, 0x40, 0xae, 0x56, 0x6a, 0x04, 0x05, 0x07, 
  };

  const uint8_t PROGMEM player_3[] = {
      0x00, 0x40, 0x2e, 0x56, 0xea, 0x04, 0x05, 0x07, 
  };

  const uint8_t PROGMEM available_spot_1[] = {
      0x00, 0x54, 0x2a, 0x54, 0x2a, 0x54, 0x2a, 0x00,
  };

  const uint8_t PROGMEM available_spot_2[] = {
      0x00, 0x2a, 0x54, 0x2a, 0x54, 0x2a, 0x54, 0x00,
  };

  const uint8_t PROGMEM plus_animation_0[] = {
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  };

  const uint8_t PROGMEM plus_animation_1[] = {
      0x30, 0x30, 0xfc, 0xfc, 0x30, 0x30, 0x00, 0x00, 
  };

  const uint8_t PROGMEM swing_animation_0[] = {
      0x00, 0x00, 0x00, 0xc1, 0xb1, 0xc3, 0x76, 0x3c, 
  };

  const uint8_t PROGMEM swing_animation_1[] = {
      0x3c, 0x76, 0xc3, 0xb1, 0xc1, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM swing_animation_2[] = {
      0x1c, 0x06, 0x03, 0x01, 0x0b, 0x0b, 0x16, 0x1c, 
  };

  const uint8_t PROGMEM swing_animation_3[] = {
      0x38, 0x68, 0xd0, 0xd0, 0x80, 0xc0, 0x60, 0x38, 
  };
}
