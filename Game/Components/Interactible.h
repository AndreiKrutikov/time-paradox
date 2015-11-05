#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

class IInteractible{
public:
  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) { };
  virtual void onMouseWheel(sf::Event::MouseWheelScrollEvent ev) { };
  virtual void onMouseMove(sf::Event::MouseMoveEvent ev) { };

  virtual ~IInteractible() {
  }
};

struct Interactible : Component<Interactible> {
  Interactible(IInteractible* receiver);
  void onEvent(sf::Event ev);

  IInteractible* receiver;
};

}
