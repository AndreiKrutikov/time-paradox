#include "MovingPlatform.h"
#include "Components\Movable.h"
#include "EntityComponentSystem\World.hpp"

void Game::MovingPlatform::onObjectEntered(EntityComponentSystem::Entity newEntity) {
  myEntities.insert(newEntity.getId());
}

void Game::MovingPlatform::onObjectLeave(EntityComponentSystem::Entity newEntity) {
  myEntities.erase(newEntity.getId());
}

void Game::MovingPlatform::onPositionChanged(Engine::Common::Direction direction) {
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

  for (auto entityId : myEntities) {
    auto& positionOfCurEntity = platformEntity.getWorld().getEntity(entityId).getComponent<Engine::Movable>().position;
    positionOfCurEntity.x += shift.x;
    positionOfCurEntity.y += shift.y;
  }

  auto& position = platformEntity.getComponent<Engine::Movable>().position;
  position.x += shift.x;
  position.y += shift.y;
}