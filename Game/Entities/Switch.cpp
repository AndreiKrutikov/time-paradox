#include "Switch.h"
#include "../Components/PlayerControllable.h"
#include "../Components/Trigger.h"
#include <iostream>

using namespace EntityComponentSystem;
using namespace Engine;
using namespace Game::Entities;

Game::Entities::Switch::Switch(EntityComponentSystem::Entity e) : e(e){
}

void Game::Entities::Switch::onEntityEnter(EntityComponentSystem::Entity reason) {
  if (reason.hasComponent<PlayerControllable>()) {
    e.getComponent<Trigger>().isSet = true;
  }
}

void Game::Entities::Switch::onEntityLeave(EntityComponentSystem::Entity reason) {
  if (reason.hasComponent<PlayerControllable>()) {
    e.getComponent<Trigger>().isSet = false;
  }
}
