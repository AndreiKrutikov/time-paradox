#pragma once

#include <unordered_set>
#include <EntityComponentSystem\Entity.hpp>
#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

class IEnterableCallback {
public:
  virtual void onEntityEnter(EntityComponentSystem::Entity e) { }
  virtual void onEntityLeave(EntityComponentSystem::Entity e) { }
};

struct Region : Component<Region> {
  Region(Common::Point topLeftCorner, int16_t height, int16_t width, IEnterableCallback* cb) :
    topLeftCorner(topLeftCorner), height(height), width(width), callback(cb) {  }

  Common::Point topLeftCorner;
  size_t height, width;
  std::unordered_set<EntityComponentSystem::Entity> entitiesInRegion; 
  IEnterableCallback* callback;
};

}
