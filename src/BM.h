#include <stdint.h>

#include <array>
#include <string>
#include <vector>

// Namespace for BakkesMod raw data.
// Includes decoded BM code types and int -> string mappings for missing SDK
// databases.

namespace BM {

struct Header {
  uint8_t version = 0;
  uint16_t code_size = 0;
  uint8_t crc = 0;
};

struct Teams {
  bool blue_is_orange = true;
  std::vector<BM::Item> blueItems;
  BM::Color blueColor;
  std::vector<BM::Item> orangeItems;
  BM::Color orangeColor;
};

struct Item {
  uint8_t slotIdx = 0;
  uint16_t productId = 0;
  uint8_t paintId = 0;
};

struct Color {
  bool override;
  std::string primary = "#000000";
  std::string accent = "#000000";
};

// All slots used by BakkesMod. Numbered slots are unknown or unused by
// BakkesMod.
const std::array<std::string, 28> SLOT = {"BODY",
                                          "DECAL",
                                          "WHEELS",
                                          "BOOST",
                                          "ANTENNA",
                                          "TOPPER",
                                          "6",
                                          "PRIMARY_FINISH",
                                          "BOT",
                                          "LOGO",
                                          "10",
                                          "PREMIUM_INVENTORY",
                                          "ACCENT_FINISH",
                                          "ENGINE",
                                          "TRAIL",
                                          "EXPLOSION",
                                          "BANNER",
                                          "17",
                                          "ANTHEM",
                                          "19",
                                          "AVATAR_BORDER",
                                          "TITLE",
                                          "ESPORTS_TEAM",
                                          "23",
                                          "BLUEPRINT",
                                          "SHOP_ITEM",
                                          "CURRENCY",
                                          "27"};

const std::array<std::string, 10> QUALITY = {
    "COMMON", "UNCOMMON",     "RARE",    "VERY_RARE", "IMPORT",
    "EXOTIC", "BLACK_MARKET", "PREMIUM", "LIMITED",   "LEGACY"};
}  // namespace BM