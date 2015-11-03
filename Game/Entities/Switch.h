#pragma once

#include "Common.h"
#include <EntityComponentSystem\World.hpp>
#include "Components\Trigerable.h"
#include "Components\Region.h"

namespace Entities {
struct Switch: public Engine::Region {
  Switch(EntityComponentSystem::Entity e, const Engine::Common::Point & leftupCorner, int16_t height_, int16_t width_);

  EntityComponentSystem::Entity e;
};


}
