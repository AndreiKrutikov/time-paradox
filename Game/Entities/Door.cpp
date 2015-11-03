#include "Door.h"
using namespace EntityComponentSystem;
namespace Entities{

Door::Door(Entity e) : e(e), isOpened(false) {
  e.addComponent<Engine::Trigerable>(static_cast<Engine::Trigerable*>(this));
}
void Door::onTrigger(bool pressed) {
  isOpened = pressed;
  //todo - add accesability checker
}
};

