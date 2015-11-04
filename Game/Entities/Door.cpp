#include "Door.h"
using namespace EntityComponentSystem;
namespace Entities{

Door::Door(Entity e, WorldMap& map) : e(e), map(map), isOpened(false) {
  e.addComponent<Engine::Triggerable>(static_cast<Engine::Triggerable*>(this));
}
void Door::onTrigger(bool pressed) {
  isOpened = pressed;
  auto& p = e.getComponent<Engine::GamePosition>().point;
  if (isOpened) {
    map.setFree(p);
  } else {
    map.setOccupied(p);
  }
}
};

