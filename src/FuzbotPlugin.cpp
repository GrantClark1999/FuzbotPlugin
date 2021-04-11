#include "FuzbotPlugin.h"

BAKKESMOD_PLUGIN(FuzbotPlugin, "Fuzbot Plugin", "0.0.1", PLUGINTYPE_FREEPLAY)

TeamLoadouts::TeamLoadouts(bool isOrange, BM::Teams teams,
                           CvarManager cvarManager, Game game) {
  vanilla = new Loadout(isOrange, cvarManager, game);
  bakkes = new Loadout(isOrange, teams, cvarManager, game);
};

FuzbotPlugin::FuzbotPlugin() {
  if (!cvarManager->getCvar("cl_itemmod_enabled").getBoolValue()) return;
  std::string itemCode =
      cvarManager->getCvar("cl_itemmod_code").getStringValue();
  BM::Teams teams = BMCodeReader::Read(itemCode);

  blue = new TeamLoadouts(0, teams, cvarManager, gameWrapper);
  orange = new TeamLoadouts(1, teams, cvarManager, gameWrapper);
};

void FuzbotPlugin::onLoad() {
  std::string itemCode =
      cvarManager->getCvar("cl_itemmod_code").getStringValue();

  cvarManager->registerNotifier(
      "print_vanilla_loadout",
      [this](std::vector<std::string> params) {
        Loadout vanillaLoadout(0, cvarManager, gameWrapper);
      },
      "Print Vanilla Loadout", PERMISSION_ALL);
};

void FuzbotPlugin::onUnload() {
  cvarManager->removeNotifier("print_vanilla_loadout");
}