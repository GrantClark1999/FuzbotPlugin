#pragma once

#include <array>
#include <optional>
#include <string>

#include "BMCodeReader.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

using namespace std;

typedef shared_ptr<GameWrapper> Game;
typedef shared_ptr<CVarManagerWrapper> CVarManager;

const array<string, 28> SLOT = {"BODY",
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

const array<string, 10> QUALITY = {
    "COMMON", "UNCOMMON",     "RARE",    "VERY_RARE", "IMPORT",
    "EXOTIC", "BLACK_MARKET", "PREMIUM", "LIMITED",   "LEGACY"};

const array<string, 19> PAINT = {
    "NONE",      "CRIMSON",      "LIME",           "BLACK",   "SKY_BLUE",
    "COBALT",    "BURNT_SIENNA", "FOREST_GREEN",   "PURPLE",  "PINK",
    "ORANGE",    "GREY",         "TITANIUM_WHITE", "SAFFRON", "GOLD",
    "ROSE_GOLD", "WHITE_GOLD",   "ONYX",           "PLATINUM"};

struct Item {
  // Vanilla
  int id = 0;
  string name = "";
  string certified = "";
  string special_edition = "";
  string team_edition = "";
  bool isPainted = false;
  unsigned long paint = 0;

  // BakkesMod
  int bm_id = 0;
  string bm_name = "";
  string bm_special_edition = "";
  string bm_team_edition = "";
  unsigned long bm_paint = 0;

  Item(uint64_t id, bool isOnline, Game gw);
};

class Loadout {
 public:
  void load(int teamNum, CVarManager cv, Game gw);
  void loadVanilla(int teamNum, CVarManager cv, Game gw);
  void loadBakkes(int teamNum, CVarManager cv, Game gw);

  // void clear() { items.clear(); };
  string toString();

 private:
  // map<string, Item> items;
};