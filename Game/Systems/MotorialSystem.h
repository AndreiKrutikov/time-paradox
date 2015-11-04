#pragma once

#include <EntityComponentSystem/System.hpp>
#include "../Components/Movable.h"
#include "../Components/Motorial.h"
namespace Engine {

class MotorialSystem : public EntityComponentSystem::System<MotorialSystem> {
public:
  MotorialSystem();
  void update();
};

}
