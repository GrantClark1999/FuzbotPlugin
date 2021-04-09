#include "FuzbotPlugin.h"

#include <fstream>
#include <ostream>

#include "RLCustomization.h"
#include "bakkesmod/wrappers/gamewrapper.h"

using namespace std;

BAKKESMOD_PLUGIN(FuzbotPlugin, "Fuzbot Plugin", "0.0.1", PLUGINTYPE_FREEPLAY)

void TwitchPlugin::onLoad() {
  string itemCode = cvarManager->getCvar("cl_itemmod_code").getStringValue();

  cvarManager->registerNotifier(
      "print_bm_loadout",
      [this](vector<string> params) {
        auto iw = gameWrapper->GetItemsWrapper();
        if (iw.IsNull()) {
          cvarManager->log("ItemsWrapper is null");
          return;
        }

        for (ProductWrapper product : iw.GetAllProducts()) {
          cvarManager->log(product.GetLabel().ToString());
        }

        LoadoutWrapper lw = LoadoutWrapper(*reinterpret_cast<uintptr_t*>(iw.GetCurrentLoadout(0).memory_address));
        ArrayWrapper<int> loadout = lw.GetLoadout();
        cvarManager->log("Total items: " + to_string(loadout.Count()));
        for (int i = 0; i < loadout.Count(); i++) {
          int productId = loadout.Get(i);
          if (productId > 0) {
            cvarManager->log(iw.GetProduct(productId).GetLabel().ToString());
          }
        }
      },
      "", PERMISSION_ALL);

  // cvarManager->registerNotifier(
  //     "print_bm_loadout",
  //     [this, itemCode](vector<string> commands) {
  //       BMLoadout loadout = load(itemCode);
  //       for (auto body : loadout.body.blue_loadout) {
  //         ostringstream oss;
  //         oss << "Slot: " << unsigned(body.first) << ", ID: " << body.second.product_id
  //             << ", Paint: " << unsigned(body.second.paint_index);
  //         cvarManager->log(oss.str());
  //       }
  //       if (loadout.body.blueColor.should_override) {
  //         ostringstream oss;
  //         oss << "Color Primary (" << unsigned(loadout.body.blueColor.primary_colors.r) << ", "
  //             << unsigned(loadout.body.blueColor.primary_colors.g) << ", "
  //             << unsigned(loadout.body.blueColor.primary_colors.b) << ")";
  //         oss << " Secondary (" << unsigned(loadout.body.blueColor.secondary_colors.r) << ", "
  //             << unsigned(loadout.body.blueColor.secondary_colors.g) << ", "
  //             << unsigned(loadout.body.blueColor.secondary_colors.b) << ")";
  //         cvarManager->log(oss.str());
  //       }
  //     },
  //     "Print BakkesMod Loadout", PERMISSION_ALL);
};
void TwitchPlugin::onUnload() {}
void TwitchPlugin::onCarUpdate() {}