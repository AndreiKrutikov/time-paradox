#pragma once
#include <EntityComponentSystem/System.hpp>

namespace Engine {

class ButtonSystem : public EntityComponentSystem::System<ButtonSystem> {
public:
  ButtonSystem();
  void update();
};

}
