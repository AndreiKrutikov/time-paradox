#include "MovingPlatform.h"
#include "Components\Movable.h"
#include "EntityComponentSystem\World.hpp"
#include "..\Game.h"
#include "../TimeManager.h"
#include "../Acts.h"

using namespace Game::Entities;
using namespace Engine;

void MovingPlatform::onObjectEntered(EntityComponentSystem::Entity newEntity) {
  if (Game::Game::getGameInstance()->timeManager->isOutatime()) return;
  if (!newEntity.hasComponent<Motorial>()) {
    myEntities.insert(newEntity.getId());
  }
}

void MovingPlatform::onObjectLeave(EntityComponentSystem::Entity newEntity) {
  if (Game::Game::getGameInstance()->timeManager->isOutatime()) return;
  if (!newEntity.hasComponent<Motorial>()) {
    myEntities.erase(newEntity.getId());
  }
}

void MovingPlatform::onPositionChanged(Engine::Common::Direction direction) {
  using namespace Engine::Common;
  Point shift;
  switch (direction) {
  case Direction::Up :
    shift.x = 0;
    shift.y = -1;
    break;
  case Direction::Down :
    shift.x = 0;
    shift.y = 1;
    break;
  case Direction::Left :
    shift.x = -1;
    shift.y = 0;
    break;
  case Direction::Right :
    shift.x = 1;
    shift.y = 0;
    break;
  }


  auto position = platformEntity.getComponent<Engine::Movable>().position;
  position.x += shift.x;
  position.y += shift.y;
  Game::getGameInstance()->accessabilityMap->setFree(position);

  auto ptr = new UnconditionalMoveAct;
  ptr->entity = platformEntity;
  ptr->direction = direction;
  std::unique_ptr<Act> act(ptr);
  Game::getGameInstance()->timeManager->addAndExecuteAct(std::move(act));


  for (auto entityId : myEntities) {
    if (entityId == platformEntity.getId()) continue;
    auto ptr = new UnconditionalMoveAct;
    ptr->entity = platformEntity.getWorld().getEntity(entityId);
    ptr->direction = direction;
    std::unique_ptr<Act> act(ptr);
    Game::getGameInstance()->timeManager->addAndExecuteAct(std::move(act));
  }

  position.x -= shift.x;
  position.y -= shift.y;
  Game::getGameInstance()->accessabilityMap->setOccupied(position);



  auto& region = platformEntity.getComponent<Engine::Region>();
  region.corner = position;
}

void Game::Entities::MovingPlatform::onTrigger(bool value) {
  if (value) {
    auto& motorial = platformEntity.getComponent<Motorial>();
    if (!motorial.isActive && !Game::getGameInstance()->timeManager->isOutatime()) {
      motorial.isActive = true;
      motorial.lastShiftTime = Game::Game::getGameInstance()->timeManager->getGameTime();
    }
  }
}

void Game::Entities::MovingPlatform::init() {
}
