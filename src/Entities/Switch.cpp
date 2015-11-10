#include "Switch.h"

using namespace EntityComponentSystem;
using namespace Engine;
using namespace Game::Entities;

Switch::Switch(EntityComponentSystem::Entity e, Common::Point leftupCorner, int16_t height, int16_t width) : e(e) {
  e.addComponent<Region>(leftupCorner, height, width, this);
}

void Switch::bind(EntityComponentSystem::Entity entity) {
  triggerObjects.push_back(entity);
}

void Switch::onObjectEntered(EntityComponentSystem::Entity e) {
  for (auto& entity : triggerObjects) {
    entity.getComponent<Triggerable>().onTrigger(true);
  }
}

void Switch::onObjectLeave(EntityComponentSystem::Entity e) {
  for (auto& entity : triggerObjects) {
    entity.getComponent<Triggerable>().onTrigger(false);
  }
}
