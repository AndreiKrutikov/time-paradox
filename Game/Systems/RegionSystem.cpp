#include "RegionSystem.h"
#include "..\Game.h"
#include "../Components/PlayerControllable.h"
#include "../TimeManager.h"
#include <map>
#include <vector>
#include <EntityComponentSystem/World.hpp>

Engine::RegionSystem::RegionSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Movable, Region>()) {
}

void Engine::RegionSystem::update() {
  for (auto region : regions) {
    auto& reg = region.getComponent<Region>();
    reg.entitiesInRegion.clear();
    for (auto movable : movables) {
      if (isInRegion(movable, region) && !(movable.hasComponent<PlayerControllable>() && Game::Game::getGameInstance()->timeManager->isOutatime())) {
        reg.entitiesInRegion.insert(movable);
      }
    }
  }
}

void Engine::RegionSystem::onEntityAdded(EntityComponentSystem::Entity& entity) {
  if (entity.hasComponent<Movable>()) movables.insert(entity);
  if (entity.hasComponent<Region>()) regions.insert(entity);
}

void Engine::RegionSystem::onEntityRemoved(EntityComponentSystem::Entity & entity) {
  movables.erase(entity);
  regions.erase(entity);
}

bool Engine::RegionSystem::isInRegion(EntityComponentSystem::Entity movableEntity, EntityComponentSystem::Entity regionEntity) const {
  auto& mov = movableEntity.getComponent<Movable>();
  auto& reg = regionEntity.getComponent<Region>();

  return mov.position.x >= reg.topLeftCorner.x && mov.position.x < reg.topLeftCorner.x + reg.width
    && mov.position.y >= reg.topLeftCorner.y && mov.position.y < reg.topLeftCorner.y + reg.height;
}
