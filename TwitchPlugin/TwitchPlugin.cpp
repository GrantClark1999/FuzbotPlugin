#include "TwitchPlugin.h"

#include <fstream>
#include <ostream>

#include "RLCustomization.h"
#include "bakkesmod/wrappers/gamewrapper.h"

BAKKESMOD_PLUGIN(TwitchPlugin, "Twitch Plugin", "0.0.1", PLUGINTYPE_FREEPLAY)

void TwitchPlugin::onLoad() {
  std::string itemCode = cvarManager->getCvar("cl_itemmod_code").getStringValue();

  cvarManager->registerNotifier(
      "print_bm_loadout",
      [this, itemCode](std::vector<std::string> commands) {
        BMLoadout loadout = load(itemCode);
        for (auto body : loadout.body.blue_loadout) {
          std::ostringstream oss;
          oss << "Slot: " << unsigned(body.first) << ", ID: " << body.second.product_id
              << ", Paint: " << unsigned(body.second.paint_index);
          cvarManager->log(oss.str());
        }
        if (loadout.body.blueColor.should_override) {
          std::ostringstream oss;
          oss << "Color Primary (" << unsigned(loadout.body.blueColor.primary_colors.r) << ", "
              << unsigned(loadout.body.blueColor.primary_colors.g) << ", "
              << unsigned(loadout.body.blueColor.primary_colors.b) << ")";
          oss << " Secondary (" << unsigned(loadout.body.blueColor.secondary_colors.r) << ", "
              << unsigned(loadout.body.blueColor.secondary_colors.g) << ", "
              << unsigned(loadout.body.blueColor.secondary_colors.b) << ")";
          cvarManager->log(oss.str());
        }
      },
      "Print BakkesMod Loadout", PERMISSION_ALL);
};
void TwitchPlugin::onUnload() {}
void TwitchPlugin::onCarUpdate() {}