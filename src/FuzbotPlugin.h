#pragma once
#pragma comment(lib, "pluginsdk.lib")

#include <fstream>
#include <ostream>

#include "Loadout.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/gamewrapper.h"

class TeamLoadouts {
 public:
  TeamLoadouts(bool isOrange, BM::Teams teams, CvarManager cvarManager,
               Game game);
  ~TeamLoadouts() {
    delete vanilla;
    delete bakkes;
  };

 private:
  Loadout* vanilla;
  Loadout* bakkes;
};

class FuzbotPlugin : public BakkesMod::Plugin::BakkesModPlugin {
 public:
  FuzbotPlugin();
  ~FuzbotPlugin() {
    delete blue;
    delete orange;
  };

  virtual void onLoad();
  virtual void onUnload();

 private:
  TeamLoadouts* blue;
  TeamLoadouts* orange;
};