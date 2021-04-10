// https://github.com/bakkesmodorg/BakkesModLoadoutLib/blob/master/BakkesModLoadoutLib
#pragma once

#include <stdint.h>

#include <map>
#include <string>

#include "BitReader.h"

#define CURRENT_LOADOUT_VERSION 2

using namespace std;

struct BMLoadout {
  Header header;
  Body body;
};

struct Header {
  uint8_t version = 0;
  uint16_t code_size = 0;
  uint8_t crc = 0;
};

struct Body {
  bool blue_is_orange = true;
  OverrideLoadout blueLoadout;
  OverrideColor blueColor;
  OverrideLoadout orangeLoadout;
  OverrideColor orangeColor;
};

typedef map<uint8_t, Item> OverrideLoadout;

struct Item {
  uint8_t slot_index = 0;
  uint16_t product_id = 0;
  uint8_t paint_index = 0;
};

struct OverrideColor {
  bool override = false;
  unsigned long primary = 0;
  unsigned long accent = 0;
};

enum EQUIPSLOT {
  SLOT_BODY = 0,
  SLOT_SKIN = 1,
  SLOT_WHEELS = 2,
  SLOT_BOOST = 3,
  SLOT_ANTENNA = 4,
  SLOT_HAT = 5,

  SLOT_PAINTFINISH = 7,
  SLOT_PAINTFINISH_SECONDARY = 12,

  SLOT_ENGINE_AUDIO = 13,
  SLOT_SUPERSONIC_TRAIL = 14,
  SLOT_GOALEXPLOSION = 15
};

enum ITEMPAINT {
  PAINT_NONE = 0,
  PAINT_CRIMSON = 1,
  PAINT_LIME = 2,
  PAINT_BLACK = 3,
  PAINT_SKYBLUE = 4,
  PAINT_COBALT = 5,
  PAINT_BURNTSIENNA = 6,
  PAINT_FORESTGREEN = 7,
  PAINT_PURPLE = 8,
  PAINT_PINK = 9,
  PAINT_ORANGE = 10,
  PAINT_GREY = 11,
  PAINT_TITANIUMWHITE = 12,
  PAINT_SAFFRON = 13,
  PAINT_GOLD = 14,
  PAINT_ROSEGOLD = 15,
  PAINT_WHITEGOLD = 16,
  PAINT_ONYX = 17,
  PAINT_PLATINUM = 18
};

class BMCodeReader : public BitReader<uint8_t> {
 public:
  BMLoadout Read() {
    Header header = ReadHeader();
    Body body = ReadBody();
    return {header, body};
  }

  Header ReadHeader() {
    uint8_t version = ReadBits<uint8_t>(6);
    uint8_t code_size = ReadBits<uint8_t>(10);
    uint8_t crc = ReadBits<uint8_t>(8);
    return {version, code_size, crc};
  }

  Body ReadBody() {
    bool blue_is_orange = ReadBool();
    OverrideLoadout blueLoadout = ReadLoadout();
    OverrideColor blueColor = ReadColor();
    OverrideLoadout orangeLoadout =
        blue_is_orange ? blueLoadout : ReadLoadout();
    OverrideColor orangeColor = blue_is_orange ? blueColor : ReadColor();
    return {blue_is_orange, blueLoadout, blueColor, orangeLoadout, orangeColor};
  }

  OverrideLoadout ReadLoadout() {
    OverrideLoadout items;
    int numItems = ReadBits<int>(4);
    for (int i = 0; i < numItems; i++) {
      Item item = ReadItem();
      items.insert_or_assign(item.slot_index, item);
    }
    return items;
  }

  Item ReadItem() {
    int slot_index = ReadBits<int>(5);
    int product_id = ReadBits<int>(13);
    Item item{slot_index, product_id};

    bool isPaintable = ReadBool();
    if (isPaintable) item.paint_index = ReadBits<int>(6);

    return item;
  }

  unsigned long ReadRGB() {
    uint8_t r = ReadBits<uint8_t>(8);
    uint8_t g = ReadBits<uint8_t>(8);
    uint8_t b = ReadBits<uint8_t>(8);
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
  }

  OverrideColor ReadColor() {
    bool override = ReadBool();
    if (!override) return {override};

    unsigned long primary = ReadRGB();
    unsigned long accent = ReadRGB();
    return {override, primary, accent};
  }
};