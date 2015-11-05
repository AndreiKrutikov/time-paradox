#pragma once

#include "Common.h"
#include <EntityComponentSystem\World.hpp>
#include "Components\Triggerable.h"
#include "Components\Region.h"

namespace Game { namespace Entities {

struct Switch : Engine::IEnterableCallback {
  Switch(EntityComponentSystem::Entity e);
  Switch(Switch&&) = delete;
  Switch(const Switch&) = delete;

  virtual void onEntityEnter(EntityComponentSystem::Entity e) override;
  virtual void onEntityLeave(EntityComponentSystem::Entity e) override;
  EntityComponentSystem::Entity e;
};

} }
