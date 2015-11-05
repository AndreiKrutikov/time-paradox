#pragma once
#include <EntityComponentSystem/System.hpp>

namespace Engine {

class DoorSystem : public EntityComponentSystem::System<DoorSystem> {
public:
  DoorSystem();
  void update();
};

}
