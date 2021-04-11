#include "FuzbotPlugin.h"

BAKKESMOD_PLUGIN(FuzbotPlugin, "Fuzbot Plugin", "0.0.1", PLUGINTYPE_FREEPLAY)

void FuzbotPlugin::onLoad() {
  string itemCode = cvarManager->getCvar("cl_itemmod_code").getStringValue();

  cvarManager->registerNotifier(
      "print_vanilla_loadout",
      [this](vector<string> params) {
        Loadout loadout;
        loadout.loadVanilla(0, cvarManager, gameWrapper);
      },
      "Print Vanilla Loadout", PERMISSION_ALL);

  // cvarManager->registerNotifier(
  //     "print_bm_loadout",
  //     [this, itemCode](vector<string> commands) {
  //       BMLoadout loadout = load(itemCode);
  //       for (auto body : loadout.body.blue_loadout) {
  //         ostringstream oss;
  //         oss << "Slot: " << unsigned(body.first) << ", ID: " <<
  //         body.second.product_id
  //             << ", Paint: " << unsigned(body.second.paint_index);
  //         cvarManager->log(oss.str());
  //       }
  //       if (loadout.body.blueColor.should_override) {
  //         ostringstream oss;
  //         oss << "Color Primary (" <<
  //         unsigned(loadout.body.blueColor.primary_colors.r) << ", "
  //             << unsigned(loadout.body.blueColor.primary_colors.g) << ", "
  //             << unsigned(loadout.body.blueColor.primary_colors.b) << ")";
  //         oss << " Secondary (" <<
  //         unsigned(loadout.body.blueColor.secondary_colors.r) << ", "
  //             << unsigned(loadout.body.blueColor.secondary_colors.g) << ", "
  //             << unsigned(loadout.body.blueColor.secondary_colors.b) << ")";
  //         cvarManager->log(oss.str());
  //       }
  //     },
  //     "Print BakkesMod Loadout", PERMISSION_ALL);
};
void FuzbotPlugin::onUnload() {}
void FuzbotPlugin::onCarUpdate() {}