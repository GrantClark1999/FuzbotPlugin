#include <string>

#include "RLCustomization.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

struct LoadoutItem {
  // ItemType type = NONE;
  int productId;
  unsigned long long instanceId;
  uint8_t paintId;
  uint8_t teamId;
  std::string itemString;

  void clear();
  void fromItem(unsigned long long id, bool isOnline, std::shared_ptr<GameWrapper> gw);
  void fromBMItem(Item item, std::shared_ptr<GameWrapper> gw);
  void fromAlphaConsolePlugin(std::shared_ptr<CVarManagerWrapper> cvarManager, int teamNum, std::string itemType);
  void addTeamId(uint8_t teamId, std::shared_ptr<GameWrapper> gw);
  std::string toString();
  void handleAttributes(ArrayWrapper<ProductAttributeWrapper> attrs, std::shared_ptr<GameWrapper> gw);
};

struct PaintItem {
  // ItemType type = NONE;
  int paintId;
  uint8_t r;
  uint8_t g;
  uint8_t b;

  bool reverse;
  float saturation;
  float speed;
  float value;

  std::string itemString;

  void clear();
  // void fromPaintId(int paintId, bool isPrimary);
  void fromBMPaint(RGB paint);
  // void fromRainbowPlugin(std::shared_ptr<CVarManagerWrapper> cvarManager, bool isPrimary);
  std::string toString(bool isPrimary);
};

class Loadout {
 public:
  void clear();
  void load(int teamNum, std::shared_ptr<CVarManagerWrapper> cv, std::shared_ptr<GameWrapper> gw);
  void assignItemToSlot(unsigned long long id, bool isOnline, std::shared_ptr<CVarManagerWrapper> cv,
                        std::shared_ptr<GameWrapper> gw);

  void fromLoadoutWrapper(int teamNum, std::shared_ptr<CVarManagerWrapper> cv, std::shared_ptr<GameWrapper> gw);
  void fromBakkesMod(int teamNum, std::shared_ptr<CVarManagerWrapper> cv, std::shared_ptr<GameWrapper> gw);
  void fromPlugins(int teamNum, std::shared_ptr<CVarManagerWrapper> cv, std::shared_ptr<GameWrapper> gw);

  std::string toBMCode();
  std::string toString();
  std::string getItemString(std::string itemType, std::string outputSeparator, bool showSlotName, bool showBMCode);

 private:
  PaintItem primaryPaint;
  PaintItem accentPaint;
  LoadoutItem body;
  LoadoutItem decal;
  LoadoutItem wheels;
  LoadoutItem boost;
  LoadoutItem antenna;
  LoadoutItem topper;
  LoadoutItem primaryFinish;
  LoadoutItem accentFinish;
  LoadoutItem engineAudio;
  LoadoutItem trail;
  LoadoutItem goalExplosion;
};