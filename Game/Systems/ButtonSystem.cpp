#include "ButtonSystem.h"
#include <cassert>
#include <EntityComponentSystem/World.hpp>
#include "../Components/Button.h"
#include "../Components/Region.h"

Engine::ButtonSystem::ButtonSystem(): System(EntityComponentSystem::ComponentFilter().requiresOneOf<Button>()) {
}

void Engine::ButtonSystem::update() {
  auto& entities = getEntities();

  for (auto button : entities) {
    assert(button.hasComponent<Region>());
    auto& reg = button.getComponent<Region>();
    if (reg.entitiesInRegion.size() > 0) {
      button.getComponent<Button>().pressed = true;
    } else {
      button.getComponent<Button>().pressed = false;
    }
  }
}
