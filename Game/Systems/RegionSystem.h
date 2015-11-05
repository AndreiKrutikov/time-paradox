#pragma once
#include <EntityComponentSystem/System.hpp>
#include "../Components/Movable.h"
#include "../Components/Region.h"
#include <map>
#include <unordered_set>

namespace Engine {

class RegionSystem : public EntityComponentSystem::System<RegionSystem> {
public:
  RegionSystem();
  void update();

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;
  virtual void onEntityRemoved(EntityComponentSystem::Entity& entity)override;

private:
  bool isInRegion(EntityComponentSystem::Entity movableEntity, EntityComponentSystem::Entity regionEntity) const;

  std::vector<std::pair<EntityComponentSystem::Entity, EntityComponentSystem::Entity>> movableToRegion;
  std::unordered_set<EntityComponentSystem::Entity> regions;
  std::unordered_set<EntityComponentSystem::Entity> movables;
};

}
