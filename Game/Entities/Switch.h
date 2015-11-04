#pragma once

#include "Common.h"
#include <EntityComponentSystem\World.hpp>
#include "Components\Triggerable.h"
#include "Components\Region.h"

namespace Entities {
struct Switch: public Engine::Region {
  Switch(EntityComponentSystem::Entity e, const Engine::Common::Point & leftupCorner, int16_t height_, int16_t width_);
  void bind(EntityComponentSystem::Entity e);
  void onObjectEntered(EntityComponentSystem::Entity e);
  void onObjectLeave(EntityComponentSystem::Entity e);
  EntityComponentSystem::Entity e;
private:
  std::vector<EntityComponentSystem::Entity> triggerObjects;
};


}
