#include "FuzbotPlugin.h"

#include <bitset>
#include <iomanip>

BAKKESMOD_PLUGIN(FuzbotPlugin, "Fuzbot Plugin", "0.0.1", PLUGINTYPE_FREEPLAY)

CvarManager g_cvarManager = nullptr;

void LOG(std::string text) {
  if (g_cvarManager != nullptr) g_cvarManager->log(text);
}
void LOG(std::wstring text) {
  if (g_cvarManager != nullptr) g_cvarManager->log(text);
}

Team::Team(bool isOrange, BM::Teams bmTeams, CvarManager cvarManager,
           Game game) {
  loadouts["vanilla"] = Loadout(isOrange, cvarManager, game);
  loadouts["bakkes"] = Loadout(isOrange, bmTeams, cvarManager, game);
};

void FuzbotPlugin::onLoad() {
  g_cvarManager = cvarManager;

  cvarManager->registerNotifier(
      "print_loadout",
      [this](std::vector<std::string> params) {
        BM::Teams bmTeams;
        if (cvarManager->getCvar("cl_itemmod_enabled").getBoolValue()) {
          std::string itemCode =
              cvarManager->getCvar("cl_itemmod_code").getStringValue();
          LOG(itemCode);
          bmTeams = BMCodeReader::Read(itemCode);
          auto decoded = base64_decode_bytearr(itemCode);
        }

        teams["blue"] = Team(false, bmTeams, cvarManager, gameWrapper);
        teams["orange"] = Team(true, bmTeams, cvarManager, gameWrapper);

        std::ofstream file(
            "C:\\Users\\Grant\\Desktop\\Projects\\FuzbotPlugin\\output.json");
        file << std::setw(2) << teams << std::endl;
      },
      "Print Vanilla Loadout", PERMISSION_ALL);
};

void FuzbotPlugin::onUnload() { cvarManager->removeNotifier("print_loadout"); }

// JSON conversions

void to_json(json& j, const Team& team) { j = team.loadouts; }