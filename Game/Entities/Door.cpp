#include "Door.h"
using namespace EntityComponentSystem;
namespace Entities{

Door::Door(Entity e, AccessabilityMap& map, bool initialState) : e(e), map(map), isOpened(initialState) {
  e.addComponent<Engine::Triggerable>(static_cast<Engine::Triggerable*>(this));
  if (!isOpened) {
    map.setOccupied(e.getComponent<Engine::GamePosition>().point);
  }
}
void Door::onTrigger(bool pressed) {
  isOpened = !isOpened;
  auto& p = e.getComponent<Engine::GamePosition>().point;
  if (isOpened) {
    map.setFree(p);
  } else {
    map.setOccupied(p);
  }
}
};

