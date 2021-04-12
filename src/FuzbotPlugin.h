#pragma once
#pragma comment(lib, "pluginsdk.lib")

#include <fstream>
#include <ostream>

#include "Loadout.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/gamewrapper.h"

void LOG(std::string text);
void LOG(std::wstring text);

struct Team {
  Team(bool isOrange, BM::Teams teams, CvarManager cvarManager, Game game);
  json loadouts;
};

void to_json(json& j, const Team& team);

class FuzbotPlugin : public BakkesMod::Plugin::BakkesModPlugin {
 public:
  virtual void onLoad();
  virtual void onUnload();

 private:
  json teams;
};
