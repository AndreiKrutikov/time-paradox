#include "Door.h"
#include "Components\Drawable.h"
using namespace EntityComponentSystem;
namespace Entities{

Door::Door(Entity e, AccessabilityMap& map, bool initialState, sf::Sprite alternativeSprite) : e(e), map(map), isOpened(initialState), alternativeSprite(alternativeSprite) {
  e.addComponent<Engine::Triggerable>(static_cast<Engine::Triggerable*>(this));
  if (!isOpened) {
    map.setOccupied(e.getComponent<Engine::GamePosition>().point);
  }
}
void Door::onTrigger(bool pressed) {
  isOpened = !isOpened;
  std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
  auto& p = e.getComponent<Engine::GamePosition>().point;
  if (isOpened) {
    map.setFree(p);
  } else {
    map.setOccupied(p);
  }
}
};

