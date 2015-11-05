#include "Door.h"
#include "Components\Drawable.h"
#include "Components\Triggerable.h"
#include "..\Game.h"
#include "..\TimeManager.h"
#include "../Acts.h"

using namespace EntityComponentSystem;
using namespace Game::Entities;
using namespace Engine;

Door::Door(Entity e, sf::Sprite alternativeSprite, bool type) : e(e), alternativeSprite(alternativeSprite), closed(type) {
}

void Door::onTrigger(bool newState) {
  auto& p = e.getComponent<Engine::GamePosition>().point;
  if (e.getComponent<Triggerable>().triggered && !newState) { //cond fail
    auto functorialAct = new FunctorialAct();
    functorialAct->exec = [this] {
      std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
      return true;
    };

    functorialAct->unexec = [this] {
      std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
    };

    Game::getGameInstance()->timeManager->addAndExecuteAct(std::unique_ptr<Act>(functorialAct));
    auto accessabilityChangeAct = new AccessabilityChangeAct;
    accessabilityChangeAct->after = closed? 1: 0;
    accessabilityChangeAct->point = p;
    Game::getGameInstance()->timeManager->addAndExecuteAct(std::unique_ptr<Act>(accessabilityChangeAct));
  }

  if (!e.getComponent<Triggerable>().triggered && newState) { // cond success
    auto functorialAct = new FunctorialAct();
    functorialAct->exec = [this] {
      std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
      return true;
    };

    functorialAct->unexec = [this] {
      std::swap(e.getComponent<Engine::Drawable>().sprite, alternativeSprite);
    };

    Game::getGameInstance()->timeManager->addAndExecuteAct(std::unique_ptr<Act>(functorialAct));
    auto accessabilityChangeAct = new AccessabilityChangeAct;
    accessabilityChangeAct->after = closed ? 0 : 1;
    accessabilityChangeAct->point = p;
    Game::getGameInstance()->timeManager->addAndExecuteAct(std::unique_ptr<Act>(accessabilityChangeAct));
  }
}

void Game::Entities::Door::init() {
  if (e.getComponent<Triggerable>().triggered) {
    Game::getGameInstance()->accessabilityMap->setOccupied(e.getComponent<Engine::GamePosition>().point);
  }
}
