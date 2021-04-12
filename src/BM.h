#pragma once

#include <stdint.h>

#include <array>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;

// Namespace for BakkesMod raw data.
// Includes decoded BM code types and int -> string mappings for missing SDK
// databases.

namespace BM {

struct Header {
  uint8_t version = 0;
  uint16_t code_size = 0;
  uint8_t crc = 0;
};

struct Item {
  uint8_t slotIdx = 0;
  uint16_t productId = 0;
  uint8_t paintId = 0;
};

struct Teams {
  bool blue_is_orange = true;
  std::vector<Item> blueItems;
  json blueColor;
  std::vector<Item> orangeItems;
  json orangeColor;
};

// All slots used by BakkesMod. Unknown slots are empty strings.
const std::array<std::string, 28> SLOT = {
    "body",
    "decal",
    "wheels",
    "boost",
    "antenna",
    "toper",
    "",
    "primary_finish",
    "bot",
    "logo",
    "",
    "premium_inventory",
    "accent_finish",
    "engine",
    "trail",
    "explosion",
    "banner",
    "",
    "anthem",
    "",
    "avatar_border",
    "title",
    "esports_team",
    "",
    "blueprints",
    "shop_item",
    "currency",
    "",
};

const std::array<std::string, 10> QUALITY = {
    "common", "uncommon",     "rare",    "very_rare", "import",
    "exotic", "black_market", "premium", "limited",   "legacy",
};
}  // namespace BM