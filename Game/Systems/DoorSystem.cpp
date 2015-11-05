#include "DoorSystem.h"
#include <cassert>
#include <utility>
#include "../Components/Button.h"
#include "../Components/Door.h"
#include "../Components/Drawable.h"
#include "../Components/GamePosition.h"
#include "../Game.h"
#include "../EntityComponentSystem/AccessabilityMap.h"

Engine::DoorSystem::DoorSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Door>()) {
}

void Engine::DoorSystem::update() {
  auto& entities = getEntities();
  for (auto door : entities) {
    auto& doorComp = door.getComponent<Door>();
    bool shouldBeTriggered = true;
    for (auto button : doorComp.dependencies) {
      assert(button.hasComponent<Button>());
      if (!button.getComponent<Button>().pressed) {
        shouldBeTriggered = false;
        break;
      }
    }

    if (shouldBeTriggered != doorComp.triggered) {
      std::swap(doorComp.alternativeSprite, door.getComponent<Drawable>().sprite);
      doorComp.triggered = shouldBeTriggered;
      if (doorComp.triggered == doorComp.triggeredMeanClosed) {
        Game::Game::getGameInstance()->accessabilityMap->setOccupied(door.getComponent<GamePosition>().point);
      } else {
        Game::Game::getGameInstance()->accessabilityMap->setFree(door.getComponent<GamePosition>().point);
      }
    }
  }
}
