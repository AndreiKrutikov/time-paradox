#pragma once
#include <EntityComponentSystem\World.hpp>
#include "EntityComponentSystem\AccessabilityMap.h"
#include "Components\Triggerable.h"
#include "Components\GamePosition.h"


namespace Entities {
struct Door : public Engine::Triggerable{
  Door(EntityComponentSystem::Entity e, EntityComponentSystem::AccessabilityMap& map);
  void onTrigger(bool pressed);

  EntityComponentSystem::Entity e;
  EntityComponentSystem::AccessabilityMap& map;
  bool isOpened;
};

}//end of namespace Entities

