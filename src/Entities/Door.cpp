#include "Door.h"
#include "Components/Drawable.h"
#include "Game/Game.h"

using namespace EntityComponentSystem;
using namespace Game::Entities;

Door::Door(Entity e, bool initialState, sf::Sprite alternativeSprite) : e(e), isOpened(initialState), alternativeSprite(alternativeSprite) {
  e.addComponent<Engine::Triggerable>(this);
}

void Door::onTrigger(bool pressed) {
  isOpened = !isOpened;
  std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
  auto& p = e.getComponent<Engine::GamePosition>().point;
  if (isOpened) {
    Game::getGameInstance()->accessabilityMap->setFree(p);
  } else {
    Game::getGameInstance()->accessabilityMap->setOccupied(p);
  }
}

void Game::Entities::Door::init() {
  if (!isOpened) {
    Game::getGameInstance()->accessabilityMap->setOccupied(e.getComponent<Engine::GamePosition>().point);
  }
}
