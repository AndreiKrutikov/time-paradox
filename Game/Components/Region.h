#pragma once

#include "Common.h"
#include "EntityComponentSystem\Entity.hpp"
#include <EntityComponentSystem/Component.hpp>

using EntityComponentSystem::Component;

namespace Engine {
struct IRegionCallback {
  virtual void onObjectEntered(EntityComponentSystem::Entity e) {   }
  virtual void onObjectLeave(EntityComponentSystem::Entity e) {  }
};

struct Region : Component<Region> {
  Region(const Common::Point & leftupCorner, int16_t height, int16_t width, IRegionCallback* callback) :
  corner(leftupCorner), height(height), width(width), callback(callback) {  }

  IRegionCallback* callback;
  Common::Point corner;
  size_t height, width;

};

}
