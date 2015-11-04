#include "EventDispatcher.h"
#include <iostream>

Engine::EventDispatcher::EventDispatcher(sf::Window & window) : System(EntityComponentSystem::ComponentFilter().requires<Interactible>()), window(window) {
}

void Engine::EventDispatcher::update() {
  auto& entities = getEntities();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();

    for (auto e : entities) {
      if (e.hasComponent<Interactible>()) {
        e.getComponent<Interactible>().onEvent(event);
      }
    }
  }
}
