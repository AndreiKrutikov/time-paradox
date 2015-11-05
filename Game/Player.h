#pragma once
#include <EntityComponentSystem\Entity.hpp>
#include "Components\Interactible.h"

namespace Game {

class TimeManager;

struct Player : public Engine::IInteractible {
public:
  Player(EntityComponentSystem::Entity e);
  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override;
  EntityComponentSystem::Entity createClone();

  EntityComponentSystem::Entity e;

  ~Player() {
    e.kill();
    e.~Entity();
  }
};

}
