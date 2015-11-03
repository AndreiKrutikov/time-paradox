#pragma once
#include <EntityComponentSystem\World.hpp>
#include "Components\Trigerable.h"

namespace Entities {
struct Door : public Engine::Trigerable{
  Door(EntityComponentSystem::Entity e);
  void onTrigger(bool pressed);

  EntityComponentSystem::Entity e;
  bool isOpened;
};

}//end of namespace Entities

