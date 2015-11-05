#include "TriggerSystem.h"
#include <map>
#include <vector>
#include <EntityComponentSystem/World.hpp>

Engine::TriggerSystem::TriggerSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Triggerable>()) {
}

void Engine::TriggerSystem::update() {
  for (auto triggerable : triggerables) {
    auto& trig = triggerable.getComponent<Triggerable>();
    for (auto dependency : trig.dependecies) {
      if (trig.triggered && !dependency.getComponent<Trigger>().isSet) {
        trig.receiver->onTrigger(false);
        trig.triggered = false;
      }

      if (!trig.triggered && dependency.getComponent<Trigger>().isSet) {
        trig.receiver->onTrigger(true);
        trig.triggered = true;
      }
    }
  }
}

void Engine::TriggerSystem::onEntityAdded(EntityComponentSystem::Entity& entity) {
  triggerables.insert(entity);
}

void Engine::TriggerSystem::onEntityRemoved(EntityComponentSystem::Entity & entity) {
  triggerables.erase(entity);
}
