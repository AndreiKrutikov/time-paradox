#pragma once
#include "Components\Motorial.h"
#include "Components\Region.h"
#include "../Components/Triggerable.h"
#include "EntityComponentSystem\Entity.hpp"
#include <set>

namespace Game {
namespace Entities {

struct MovingPlatform : Engine::IMotorialCallback, Engine::IRegionCallback, Engine::ITriggerable {
  MovingPlatform(EntityComponentSystem::Entity platform) : platformEntity(platform) {
  }

  void onObjectEntered(EntityComponentSystem::Entity newEntity) override;
  void onObjectLeave(EntityComponentSystem::Entity newEntity) override;
  void onPositionChanged(Engine::Common::Direction direction) override;
  void onTrigger(bool value) override;

  void init();

  EntityComponentSystem::Entity platformEntity;
  std::set <uint64_t> myEntities;
};

}
}
