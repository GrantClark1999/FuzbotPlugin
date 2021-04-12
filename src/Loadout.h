#pragma once

#include <array>
#include <string>

#include "BM.h"
#include "BMCodeReader.h"
#include "BitReader.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

typedef std::shared_ptr<GameWrapper> Game;
typedef std::shared_ptr<CVarManagerWrapper> CvarManager;

class Item {
 public:
  Item(BM::Item item, ItemsWrapper iw);
  Item(ProductWrapper prod, OnlineProductWrapper o_prod, Game game);
  void setAttribute(ProductAttributeWrapper attr, Game game);

  json data;

 private:
  void setCertified(uintptr_t mem_addr, ItemsWrapper iw);
  void setPainted(uintptr_t mem_addr, ItemsWrapper iw);
  void setSpecialEdition(uintptr_t mem_addr, ItemsWrapper iw);
  void setTeamEdition(uintptr_t mem_addr, ItemsWrapper iw);
};

class Loadout {
 public:
  // Vanilla
  Loadout(bool isOrange, CvarManager cvarManager, Game game);
  // BakkesMod
  Loadout(bool isOrange, BM::Teams teams, CvarManager cvarManager, Game game);

  json items;

 private:
  CvarManager cvarManager;
  Game game;
};

void to_json(json& j, const Item& item);
void to_json(json& j, const Loadout& loadout);