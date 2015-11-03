#include "EventDispatcher.h"

Engine::EventDispatcher::EventDispatcher(sf::Window & window) : System(EntityComponentSystem::ComponentFilter().requires<Interactible>()), window(window) {
}

void Engine::EventDispatcher::update() {
  auto& entities = getEntities();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
      for (auto e : entities) {
        auto& interactible = e.getComponent<Interactible>();
        interactible.onKeyEvent(event.key, event.type == sf::Event::KeyPressed);
      }
    }
  }
}
