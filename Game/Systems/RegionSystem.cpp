#include "RegionSystem.h"
#include <map>
#include <vector>
#include <EntityComponentSystem/World.hpp>

Engine::RegionSystem::RegionSystem() : System(EntityComponentSystem::ComponentFilter().requiresOneOf <Movable, Region>()) {
}

int32_t Engine::RegionSystem::findInMap(std::pair <uint64_t, uint64_t> p) {
  //we can try to optimise something here if needed
  std::vector <uint64_t> res;
  for (size_t t = 0; t < movableToRegion.size(); ++t)
    if (movableToRegion[t] == p)
      return t;
  return -1;
}

void Engine::RegionSystem::update() {
  auto& entities = getEntities();
  std::vector < std::pair <uint64_t, uint64_t> > newMap;
  for (size_t i = 0; i < entities.size(); ++i) {
    auto& e = entities[i];
    if (e.hasComponent<Movable>()) {
      for (auto& r : entities) {
        if (r.hasComponent<Region>())
          if (isInRegion(e, r))
            newMap.push_back(std::make_pair(e.getId(), r.getId()));
      }
    }
  }
  
  for (auto p : newMap) {
    auto foundInd = findInMap(p);
    if (foundInd == -1) {
      auto& mov = getWorld().getEntity(p.first);
      auto& reg = getWorld().getEntity(p.second).getComponent<Region>();
      reg.callback->onObjectEntered(mov);
    } else {
      movableToRegion[foundInd] = std::make_pair(-1ULL, -1ULL);
    }
  }

  for (auto p : movableToRegion) {
    if (p !=  std::make_pair(-1ULL, -1ULL)) {
      auto& mov = getWorld().getEntity(p.first);
      auto& reg = getWorld().getEntity(p.second).getComponent<Region>();
      reg.callback->onObjectLeave(mov);
    }
  }

  movableToRegion = newMap;
}

bool Engine::RegionSystem::isInRegion(EntityComponentSystem::Entity const & movableEntity, EntityComponentSystem::Entity const & regionEntity) const {
  auto& mov = movableEntity.getComponent<Movable>();
  auto& reg = regionEntity.getComponent<Region>();

  return mov.position.x >= reg.corner.x && mov.position.x <= reg.corner.x + reg.width
    && mov.position.y >= reg.corner.y && mov.position.y <= reg.corner.y + reg.height;
}
