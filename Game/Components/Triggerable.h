#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>
#include <unordered_set>

using EntityComponentSystem::Component;

namespace Engine {

class ITriggerable {
public:
  virtual void onTrigger(bool value) { }
  virtual ~ITriggerable() { }
};

struct Triggerable : Component<Triggerable> {
  Triggerable(ITriggerable* callback) : receiver(callback), triggered(false) {
  }

  ITriggerable* receiver;
  bool triggered;
  std::unordered_set<EntityComponentSystem::Entity> dependecies;
};

}
