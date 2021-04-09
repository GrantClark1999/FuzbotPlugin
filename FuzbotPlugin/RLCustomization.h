// https://github.com/bakkesmodorg/BakkesModLoadoutLib/blob/master/BakkesModLoadoutLib
#pragma once

#include <stdint.h>

#include <map>
#include <string>

#include "BitBinaryReader.h"

#define CURRENT_LOADOUT_VERSION 2

using namespace std;

struct Header {
  uint8_t version = 0;
  uint16_t code_size = 0;
  uint8_t crc = 0;
};

struct Item {
  uint8_t slot_index = 0;
  uint16_t product_id = 0;
  uint8_t paint_index = 0;
};

struct RGB {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

struct OverrideColor {
  bool should_override = false;
  RGB primary_colors;
  RGB secondary_colors;
};

struct Body {
  bool blue_is_orange = true;
  map<uint8_t, Item> blue_loadout;
  OverrideColor blueColor;
  map<uint8_t, Item> orange_loadout;
  OverrideColor orangeColor;
};

struct BMLoadout {
  Header header;
  Body body;
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

map<uint8_t, Item> read_items_from_buffer(BitBinaryReader<unsigned char>& reader) {
  map<uint8_t, Item> items;
  int itemsSize = reader.ReadBits<int>(4);
  for (int i = 0; i < itemsSize; i++) {
    Item option;
    int slotIndex = reader.ReadBits<int>(5);
    int productId = reader.ReadBits<int>(13);
    bool isPaintable = reader.ReadBool();

    if (isPaintable) {
      int paintID = reader.ReadBits<int>(6);
      option.paint_index = paintID;
    }
    option.product_id = productId;
    option.slot_index = slotIndex;
    items.insert_or_assign(slotIndex, option);
  }
  return items;
}

RGB read_colors_from_buffer(BitBinaryReader<unsigned char>& reader) {
  RGB col;
  col.r = reader.ReadBits<uint8_t>(8);
  col.g = reader.ReadBits<uint8_t>(8);
  col.b = reader.ReadBits<uint8_t>(8);
  return col;
}

BMLoadout load(std::string loadoutString) {
  BitBinaryReader<unsigned char> reader(loadoutString);
  BMLoadout loadout;

  loadout.header.version = reader.ReadBits<uint8_t>(6);
  loadout.header.code_size = reader.ReadBits<uint16_t>(10);
  loadout.header.crc = reader.ReadBits<uint8_t>(8);

  loadout.body.blue_is_orange = reader.ReadBool();
  loadout.body.blue_loadout = read_items_from_buffer(reader);

  loadout.body.blueColor.should_override = reader.ReadBool();
  if (loadout.body.blueColor.should_override) {
    loadout.body.blueColor.primary_colors = read_colors_from_buffer(reader);
    loadout.body.blueColor.secondary_colors = read_colors_from_buffer(reader);
  }

  if (loadout.body.blue_is_orange) {
    loadout.body.orange_loadout = loadout.body.blue_loadout;
  } else {
    loadout.body.orange_loadout = read_items_from_buffer(reader);
    loadout.body.orangeColor.should_override = reader.ReadBool();
    if (loadout.body.blueColor.should_override) {
      loadout.body.orangeColor.primary_colors = read_colors_from_buffer(reader);
      loadout.body.orangeColor.secondary_colors = read_colors_from_buffer(reader);
    }
  }

  return loadout;
}