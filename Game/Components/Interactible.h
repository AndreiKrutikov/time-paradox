#pragma once

#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Interactible : Component<Interactible> {
  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) { };
  virtual void onMouseWheel(sf::Event::MouseWheelScrollEvent ev) { };
};

}
