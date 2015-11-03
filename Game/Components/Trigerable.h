#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Trigerable : Component<Trigerable> {
  virtual void onTrigger(bool pressed) {
  };
};

}
