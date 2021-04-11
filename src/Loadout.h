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
  void json();

 private:
  int id = 0;
  std::string name = "";
  std::string quality = "";
  std::string certified = "";  // Vanilla only
  std::string painted = "";
  std::string special_edition = "";
  std::string team_edition = "";

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

  void clear() { items.clear(); }
  void json();

 private:
  CvarManager cvarManager;
  Game game;
  std::map<std::string, Item> items;
  BM::Color color;
};