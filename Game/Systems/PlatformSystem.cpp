#include "PlatformSystem.h"
#include <cassert>
#include <chrono>
#include <utility>
#include "../Acts.h"
#include "../Components/Button.h"
#include "../Components/Drawable.h"
#include "../Components/Movable.h"
#include "../Components/Platform.h"
#include "../Components/PlayerControllable.h"
#include "../Components/Region.h"
#include "../Game.h"
#include "../EntityComponentSystem/AccessabilityMap.h"
#include "../TimeManager.h"

Engine::PlatformSystem::PlatformSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Platform>()) {
}

void Engine::PlatformSystem::update() {
  auto& entities = getEntities();
  auto now = Game::Game::getGameInstance()->timeManager->getGameTime();
  for (auto platform : entities) {
    auto& platformComp = platform.getComponent<Platform>();
    if (platformComp.futureUndefinedSince > now) continue;
    Game::Game::getGameInstance()->accessabilityMap->setFree(platformComp.currentPosition);
    if (!platformComp.isActive) {
      bool shouldBeTriggered = true;
      for (auto button : platformComp.dependencies) {
        assert(button.hasComponent<Button>());
        if (!button.getComponent<Button>().pressed) {
          shouldBeTriggered = false;
          break;
        }
      }

      platformComp.isActive = shouldBeTriggered;
      platformComp.lastShiftTime = Game::Game::getGameInstance()->timeManager->getGameTime();
    }

    if (platformComp.isActive) {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now - platformComp.lastShiftTime).count() < platformComp.velocity) continue;
      platformComp.lastShiftTime = now;
      platformComp.futureUndefinedSince = now;

      auto makeForwardTileAccesible = new Game::AccessabilityChangeAct;
      makeForwardTileAccesible->after = 0;
      makeForwardTileAccesible->point = platformComp.currentPosition + platformComp.direction;
      Game::Game::getGameInstance()->timeManager->addAndExecuteAct(std::unique_ptr<Game::Act>(makeForwardTileAccesible));


      auto newPosition = platformComp.currentPosition + platformComp.direction;

      //move everethin on platform
      platformComp.currentPosition = newPosition;
      auto& region = platform.getComponent<Engine::Region>();
      for (auto passenger : region.entitiesInRegion) {
        if (passenger.hasComponent<PlayerControllable>()) {
          passenger.getComponent<Movable>().position = newPosition;
        }
      }

      region.topLeftCorner = newPosition;

      if (newPosition == platformComp.endPosition) {
        platformComp.direction = Common::getOpposite(platformComp.direction);
      }

      if (newPosition == platformComp.startPosition) {
        platformComp.direction = Common::getOpposite(platformComp.direction);
        platformComp.isActive = false;
      }
    }
  }
}
