#include "Loadout.h"

void Loadout::load(int teamNum, CVarManager cv, Game gw) {}

void Loadout::loadVanilla(int teamNum, CVarManager cv, Game gw) {
  auto iw = gw->GetItemsWrapper();
  if (iw.IsNull()) {
    cv->log("Unable to load Rocket League Loadout");
    return;
  }

  auto lw = iw.GetCurrentLoadout(teamNum);
  // TODO: Remove below once BM updates
  lw = LoadoutWrapper(*reinterpret_cast<uintptr_t*>(lw.memory_address));

  for (int id : lw.GetLoadout()) {
    assignItemToSlot(id, false, cv, gw);
  }

  for (uint64_t id : lw.GetOnlineLoadout()) {
    assignItemToSlot(id, true, cv, gw);
  }

  primaryPaint.itemString = "Unknown";
  accentPaint.itemString = "Unknown";
}

void Loadout::loadBakkes(int teamNum, CVarManager cv, Game gw) {
  if (!cv->getCvar("cl_itemmod_enabled").getBoolValue()) return;
  string itemCode = cv->getCvar("cl_itemmod_code").getStringValue();
  BMCodeReader reader(itemCode);
}