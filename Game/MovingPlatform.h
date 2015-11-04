#pragma once
#include "Components\Motorial.h"
#include "Components\Region.h"
#include "EntityComponentSystem\Entity.hpp"
#include <set>
namespace Game {

struct MovingPlatform : Engine::IMotorialCallback, Engine::IRegionCallback  {
  MovingPlatform(EntityComponentSystem::Entity platform) : platformEntity(platform) {  }
  void onObjectEntered(EntityComponentSystem::Entity newEntity) override;
  void onObjectLeave(EntityComponentSystem::Entity newEntity) override;
  void onPositionChanged(Engine::Common::Direction direction) override;
  EntityComponentSystem::Entity platformEntity;
  std::set <uint64_t> myEntities;
};
}