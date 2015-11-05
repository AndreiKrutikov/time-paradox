#pragma once
#include <EntityComponentSystem/System.hpp>

namespace Engine {

class PlatformSystem : public EntityComponentSystem::System<PlatformSystem> {
public:
  PlatformSystem();
  void update();
};

}
