#include "RegionSystem.h"
#include <map>
#include <vector>
#include <EntityComponentSystem/World.hpp>

Engine::RegionSystem::RegionSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf<Movable, Region>()) {
}

void Engine::RegionSystem::update() {
  for (auto region : regions) {
    auto& reg = region.getComponent<Region>();
    for (auto movable : movables) {
      if (reg.entitiesInRegion.count(movable) > 0 && !isInRegion(movable, region)) {
          reg.entitiesInRegion.erase(movable);
          reg.callback->onEntityLeave(movable);        
      }

      if (reg.entitiesInRegion.count(movable) == 0 && isInRegion(movable, region)) {
        reg.entitiesInRegion.insert(movable);
        reg.callback->onEntityEnter(movable);
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
