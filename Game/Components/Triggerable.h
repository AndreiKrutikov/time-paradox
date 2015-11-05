#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

class ITriggerable {
public:
  virtual void onTrigger(bool value) { }
  virtual ~ITriggerable() { }
};

struct Triggerable : Component<Triggerable> {
  Triggerable(ITriggerable* callback) : receiver(callback) {
  }

  void onTrigger(bool value) {
    receiver->onTrigger(value);
  }

  ITriggerable* receiver;
};

}
