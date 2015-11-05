#pragma once

#include <unordered_set>
#include <EntityComponentSystem\Entity.hpp>
#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Region : Component<Region> {
  Region(Common::Point topLeftCorner, int16_t height, int16_t width) :
    topLeftCorner(topLeftCorner), height(height), width(width) {  }

  Common::Point topLeftCorner;
  size_t height, width;
  std::unordered_set<EntityComponentSystem::Entity> entitiesInRegion; 
};

}
