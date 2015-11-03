#pragma once

#include "Common.h"
#include "EntityComponentSystem\Entity.hpp"
#include <EntityComponentSystem/Component.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Region : Component<Region> {
  Region(const Common::Point & leftupCorner, int16_t height_, int16_t width_) {
    height = height_;
    width = width_;
    corner = leftupCorner;
  }

  Common::Point corner;
  size_t height, width;

  virtual void onObjectEntered(EntityComponentSystem::Entity e) {  }
  virtual void onObjectLeave(EntityComponentSystem::Entity e) {  }
};

}
