#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Triggerable : Component<Triggerable> {
  virtual void onTrigger(bool pressed) {
  };
};

}
