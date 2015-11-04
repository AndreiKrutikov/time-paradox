#include "Interactible.h"

Engine::Interactible::Interactible(IInteractible * receiver) : receiver(receiver) {
}

void Engine::Interactible::onEvent(sf::Event ev) {
  if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
    receiver->onKeyEvent(ev.key, ev.type == sf::Event::KeyPressed);
  }

  if (ev.type == sf::Event::MouseWheelScrolled) {
    receiver->onMouseWheel(ev.mouseWheelScroll);
  }
}
