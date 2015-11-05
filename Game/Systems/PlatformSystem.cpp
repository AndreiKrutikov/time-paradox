#include "PlatformSystem.h"
#include <cassert>
#include <chrono>
#include <utility>
#include "../Components/Button.h"
#include "../Components/Drawable.h"
#include "../Components/Movable.h"
#include "../Components/Platform.h"
#include "../Game.h"
#include "../EntityComponentSystem/AccessabilityMap.h"
#include "../TimeManager.h"

Engine::PlatformSystem::PlatformSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Platform>()) {
}

void Engine::PlatformSystem::update() {
  auto& entities = getEntities();
  for (auto platform : entities) {
    auto& platformComp = platform.getComponent<Platform>();
    if (platformComp.isAccesible) {
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
        if (std::chrono::duration_cast<std::chrono::milliseconds>(Game::Game::getGameInstance()->timeManager->getGameTime() - platformComp.lastShiftTime).count() < platformComp.velocity) continue;
        auto newPosition = platformComp.currentPosition + platformComp.direction;

        //move

        if (newPosition == platformComp.endPosition) {
          platformComp.direction = Common::getOpposite(platformComp.direction);
        }
      }
    }
  }
}
