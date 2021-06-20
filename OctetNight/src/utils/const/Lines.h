#pragma once

namespace Lines
{
  // 34 4
  const uint8_t PROGMEM options[] = {
      0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x05, 0x05, 0x07, 0x00, 0x01, 0x0f, 0x01, 0x01, 0x00, 0x09, 0x0f, 0x09, 0x00, 0x00, 0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x02, 0x04, 0x0f, 0x00, 0x0b, 0x0b, 0x0d, 0x0d, 
  };

  const uint8_t PROGMEM back[] = {
      0x0f, 0x0b, 0x0b, 0x0e, 0x00, 0x0f, 0x05, 0x05, 0x0f, 0x00, 0x0f, 0x09, 0x09, 0x09, 0x00, 0x0f, 0x02, 0x05, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM sOn[] = {
      0x0b, 0x0b, 0x0d, 0x0d, 0x00, 0x08, 0x00, 0x00, 0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x02, 0x04, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM sOff[] = {
      0x0b, 0x0b, 0x0d, 0x0d, 0x00, 0x08, 0x00, 0x00, 0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x05, 0x05, 0x01, 0x00, 0x0f, 0x05, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM mMenu[] = {
      0x0f, 0x01, 0x03, 0x0f, 0x00, 0x08, 0x00, 0x00, 0x0f, 0x01, 0x03, 0x0f, 0x00, 0x0f, 0x0b, 0x0b, 0x09, 0x00, 0x0f, 0x02, 0x04, 0x0f, 0x00, 0x0f, 0x08, 0x08, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  const uint8_t PROGMEM version[] = {
      0x07, 0x08, 0x08, 0x07, 0x00, 0x0f, 0x09, 0x0b, 0x0f, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x09, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  };

  // 24 4
  const uint8_t PROGMEM start[] = {
      0x0b, 0x0b, 0x0d, 0x0d, 0x00, 0x01, 0x0f, 0x01, 0x01, 0x00, 0x0f, 0x05, 0x05, 0x0f, 0x00, 0x0f, 0x05, 0x0d, 0x07, 0x00, 0x01, 0x0f, 0x01, 0x01, 
  };

  const uint8_t PROGMEM sound[] = {
      0x0b, 0x0b, 0x0d, 0x0d, 0x00, 0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x08, 0x08, 0x0f, 0x00, 0x0f, 0x02, 0x04, 0x0f, 0x00, 0x0f, 0x09, 0x09, 0x06, 
  };

  // 14 4
  const uint8_t PROGMEM on[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x02, 0x04, 0x0f, 
  };

  const uint8_t PROGMEM off[] = {
      0x0f, 0x09, 0x09, 0x0f, 0x00, 0x0f, 0x05, 0x05, 0x01, 0x00, 0x0f, 0x05, 0x05, 0x01, 
  };

  // 4 4
  const uint8_t PROGMEM x[] = {
      0x04, 0x0f, 0x04, 0x05, 
  };
}
