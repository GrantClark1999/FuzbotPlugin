#pragma once

#include <array>
#include <string>

#include "BMCodeReader.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

using namespace std;

typedef shared_ptr<GameWrapper> Game;
typedef shared_ptr<CVarManagerWrapper> CVarManager;

struct Item {
  // Vanilla
  int id = 0;
  string name = "";
  string cert = "";
  string edition = "";
  bool isPainted = false;
  unsigned long paint = 0;

  // BakkesMod
  int id_override = 0;
  string name_override = "";
  unsigned long paint_override = 0;

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