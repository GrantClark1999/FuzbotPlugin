#include "Loadout.h"

void Loadout::load(int teamNum, CVarManager cv, Game gw) {}

void Loadout::loadVanilla(int teamNum, CVarManager cv, Game gw) {
  ItemsWrapper iw = gw->GetItemsWrapper();
  if (iw.IsNull()) return cv->log("Unable to load Rocket League Loadout");

  LoadoutWrapper lw = iw.GetCurrentLoadout(teamNum);
  // TODO: Remove below when BakkesMod updates
  lw = LoadoutWrapper(*reinterpret_cast<uintptr_t*>(lw.memory_address));
  ArrayWrapper<uint64_t> items = lw.GetOnlineLoadout();

  bool foundPrimary = false;

  for (uint64_t id : items) {
    if (id == 0) continue;  // 0 indicates no data for that slot

    OnlineProductWrapper onlineProduct = iw.GetOnlineProduct(id);

    // If the id does not match an online product, cast unsigned long long
    // (uint64) -> int to check as a productId.
    bool isValidInt = id - INT_MIN <= (uint64_t)INT_MAX - INT_MIN;
    if (!onlineProduct && !isValidInt) {
      cv->log("Missing Online ID: " + to_string(id));
      continue;
    }

    ProductWrapper product =
        onlineProduct ? onlineProduct.GetProduct() : iw.GetProduct((int)id);

    if (!product) {
      cv->log("ERROR: Product is null!");
      continue;
    }

    ProductSlotWrapper productSlot = product.GetSlot();
    if (productSlot.IsNull()) {
      cv->log("ERROR: Slot is null!");
      continue;
    }

    int slotIdx = productSlot.GetSlotIndex();

    // Assign second "finish" slot to accent/secondary finish
    if (slotIdx == 7) {
      if (foundPrimary) {
        slotIdx = 12;
      } else {
        foundPrimary = true;
      }
    }

    if (slotIdx < 0 || slotIdx >= SLOT.size()) {
      cv->log("Invalid Slot Index: " + to_string(slotIdx));
      continue;
    }

    stringstream ss;
    string slot = SLOT[slotIdx];
    string prodName = product.GetLongLabel().ToString();
    string rarity = QUALITY[product.GetQuality()];

    ss << SLOT[slotIdx] << ": " << prodName << " (";

    if (onlineProduct) {
      for (ProductAttributeWrapper attr : onlineProduct.GetAttributes()) {
        string type = attr.GetTypename();
        if (type == "Certified") {
          string statName =
              gw->GetItemsWrapper().GetCertifiedStatDB().GetStatName(
                  ProductAttribute_CertifiedWrapper(attr.memory_address)
                      .GetStatId());
          ss << " Certified=" << statName << " ";
        } else if (type == "Painted") {
          string paint =
              PAINT[ProductAttribute_PaintedWrapper(attr.memory_address)
                        .GetPaintID()];
          ss << " Painted=" << paint << " ";
        } else if (type == "SpecialEdition") {
          string edition =
              gw->GetItemsWrapper().GetSpecialEditionDB().GetSpecialEditionName(
                  ProductAttribute_SpecialEditionWrapper(attr.memory_address)
                      .GetEditionID());
          edition = edition.substr(edition.find("_") + 1);
          ss << " SpecialEdition=" << edition << " ";
        } else if (type == "TeamEdition") {
          string team = gw->GetItemsWrapper().GetEsportTeamDB().GetName(
              ProductAttribute_TeamEditionWrapper(attr.memory_address).GetId());
          ss << " TeamEdition=" << team << " ";
        }
      }
    }
    ss << ")";
    cv->log(ss.str());
  }
}

void Loadout::loadBakkes(int teamNum, CVarManager cv, Game gw) {
  if (!cv->getCvar("cl_itemmod_enabled").getBoolValue()) return;
  string itemCode = cv->getCvar("cl_itemmod_code").getStringValue();
  // BMCodeReader reader(itemCode);
}

ProductWrapper getProduct() {}