#pragma once
#include <EntityComponentSystem/System.hpp>
#include <SFML/Window.hpp>
#include "../Components/Interactible.h"

namespace Engine {

class EventDispatcher : public EntityComponentSystem::System<EventDispatcher> {
public:
  EventDispatcher(sf::Window& window);
  void update();

private:
  sf::Window& window;
};

}
