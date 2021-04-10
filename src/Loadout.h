#pragma once

#include <string>

#include "BMCodeReader.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

using namespace std;

typedef shared_ptr<GameWrapper> Game;
typedef shared_ptr<CVarManagerWrapper> CVarManager;

struct LoadoutItem {
  int productId;
  uint64_t instanceId;
  uint8_t paintId;
  uint8_t teamId;
  string itemString;

  void clear();
  void fromItem(uint64_t id, bool isOnline, Game gw);
  void fromBMItem(Item item, Game gw);
  void addTeamId(uint8_t teamId, Game gw);
  string toString();
  void handleAttributes(ArrayWrapper<ProductAttributeWrapper> attrs, Game gw);
};

struct PaintItem {
  int paintId;
  unsigned long paint;

  string itemString;

  void clear();
  void fromPaintId(int paintId, bool isPrimary);
  void fromBMPaint(unsigned long paint);
  string toString(bool isPrimary);
};

class Loadout {
 public:
  void clear();
  void load(int teamNum, CVarManager cv, Game gw);
  void assignItemToSlot(uint64_t id, bool isOnline, CVarManager cv, Game gw);

  void loadVanilla(int teamNum, CVarManager cv, Game gw);
  void loadBakkes(int teamNum, CVarManager cv, Game gw);

  string toBMCode();
  string toString();

 private:
  PaintItem primaryPaint;
  PaintItem accentPaint;
  LoadoutItem body;
  LoadoutItem decal;
  LoadoutItem primaryFinish;
  LoadoutItem accentFinish;
  LoadoutItem wheels;
  LoadoutItem boost;
  LoadoutItem topper;
  LoadoutItem antenna;
  LoadoutItem explosion;
  LoadoutItem trail;
  LoadoutItem engine;
  LoadoutItem banner;
  LoadoutItem anthem;
};