#pragma once
#include <EntityComponentSystem\World.hpp>
#include "EntityComponentSystem\WorldMap.h"
#include "Components\Triggerable.h"
#include "Components\GamePosition.h"


namespace Entities {
struct Door : public Engine::Triggerable{
  Door(EntityComponentSystem::Entity e, EntityComponentSystem::WorldMap& map);
  void onTrigger(bool pressed);

  EntityComponentSystem::Entity e;
  EntityComponentSystem::WorldMap& map;
  bool isOpened;
};

}//end of namespace Entities

