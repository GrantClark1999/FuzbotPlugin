// #pragma once

// #include <stdint.h>

// #include <map>
// #include <string>

// using namespace std;

// struct BMLoadout {
//   Header header;
//   Body body;
// };

// struct Header {
//   uint8_t version = 0;
//   uint16_t code_size = 0;
//   uint8_t crc = 0;
// };

// struct Body {
//   bool blue_is_orange = true;
//   OverrideLoadout blueLoadout;
//   OverrideColor blueColor;
//   OverrideLoadout orangeLoadout;
//   OverrideColor orangeColor;
// };

// typedef map<uint8_t, Item> OverrideLoadout;

// struct Item {
//   uint8_t slot_index = 0;
//   uint16_t product_id = 0;
//   uint8_t paint_index = 0;
// };

// struct OverrideColor {
//   bool override = false;
//   unsigned long primary = 0;
//   unsigned long accent = 0;
// };