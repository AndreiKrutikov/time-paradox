#include "Switch.h"
using namespace EntityComponentSystem;
using namespace Engine;

namespace Entities {
  Switch::Switch(EntityComponentSystem::Entity e, const Common::Point & leftupCorner, int16_t height_, int16_t width_): e(e) {
    e.addComponent<Region>(leftupCorner, height_, width_, this);
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
}