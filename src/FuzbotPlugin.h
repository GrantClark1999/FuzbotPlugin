#pragma once
#pragma comment(lib, "pluginsdk.lib")

#include <fstream>
#include <ostream>

#include "Loadout.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/gamewrapper.h"

using namespace std;

class FuzbotPlugin : public BakkesMod::Plugin::BakkesModPlugin {
 public:
  virtual void onLoad();
  virtual void onUnload();

 private:
  void onCarUpdate();
};