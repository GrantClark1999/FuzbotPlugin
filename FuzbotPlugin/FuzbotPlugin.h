#pragma once
#pragma comment(lib, "pluginsdk.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"

class TwitchPlugin : public BakkesMod::Plugin::BakkesModPlugin {
 public:
  virtual void onLoad();
  virtual void onUnload();
  void onCarUpdate();
};