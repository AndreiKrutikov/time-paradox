#include "Acts.h"
#include "Components\Movable.h"
#include "Components\PlayerControlable.h"
#include <EntityComponentSystem\Entity.hpp>
#include "EntityComponentSystem\AccessabilityMap.h"
#include "Game.h"
using namespace EntityComponentSystem;

#include <iostream>

bool Game::MoveAct::execute() {
  using namespace Engine::Common;
  auto& movable = entity.getComponent<Engine::Movable>();
  Point newPosition = movable.position;
  auto map = Game::getGameInstance()->accessabilityMap;
  map->setFree(newPosition);

  switch (direction) {
  case Direction::Up :
    newPosition.y--;
    break;
  case Direction::Down :
    newPosition.y++;
    break;
  case Direction::Left :
    newPosition.x--;
    break;
  case Direction::Right :
    newPosition.x++;
    break;
  }

  if (!map->isOccupied(newPosition)) {
    movable.position = newPosition;
    map->setOccupied(newPosition);
    return true;
  } else {
    if (entity.hasComponent<Engine::PlayerControlable>())
      return true;
    else
      return false;
  }
}

void Game::MoveAct::unexecute() {
  using namespace Engine::Common;
  Point newPosition = entity.getComponent<Engine::Movable>().position;
  Game::getGameInstance()->accessabilityMap->setFree(newPosition);

  switch (direction) {
  case Direction::Up:
    newPosition.y++;
    break;
  case Direction::Down:
    newPosition.y--;
    break;
  case Direction::Left:
    newPosition.x++;
    break;
  case Direction::Right:
    newPosition.x--;
    break;
  }

  if (Game::getGameInstance()->accessabilityMap->isOccupied(newPosition))
    std::cout << "Bad" << std::endl;
  else
    Game::getGameInstance()->accessabilityMap->setOccupied(newPosition);
  entity.getComponent<Engine::Movable>().position = newPosition;
}


bool Game::UnconditionalMoveAct::execute() {
  using namespace Engine::Common;
  auto& movable = entity.getComponent<Engine::Movable>();
  Point newPosition = movable.position;
  auto map = Game::getGameInstance()->accessabilityMap;

  switch (direction) {
  case Direction::Up:
    newPosition.y--;
    break;
  case Direction::Down:
    newPosition.y++;
    break;
  case Direction::Left:
    newPosition.x--;
    break;
  case Direction::Right:
    newPosition.x++;
    break;
  }

  movable.position = newPosition;
  return true;
}

void Game::UnconditionalMoveAct::unexecute() {
  using namespace Engine::Common;
  Point newPosition = entity.getComponent<Engine::Movable>().position;

  switch (direction) {
  case Direction::Up:
    newPosition.y++;
    break;
  case Direction::Down:
    newPosition.y--;
    break;
  case Direction::Left:
    newPosition.x++;
    break;
  case Direction::Right:
    newPosition.x--;
    break;
  }

  entity.getComponent<Engine::Movable>().position = newPosition;
}

bool Game::SpawnAct::execute() {
  std::cout << "Game::SpawnAct::execute() " << entity.getId() << std::endl;
  auto map = Game::getGameInstance()->accessabilityMap;

  if (!map->isFree(position)) {
    return false;
  }

  entity.activate();
  return true;
}

void Game::SpawnAct::unexecute() {
  std::cout << "Game::SpawnAct::unexecute() " << entity.getId() << std::endl;
  
  entity.deactivate();
}

bool Game::DisappearAct::execute() {
  std::cout << "Game::DisappearAct::execute() " << entity.getId() << std::endl;
  auto& map = Game::getGameInstance()->accessabilityMap;
  map->setFree(entity.getComponent<Engine::Movable>().position);
  entity.deactivate();
  return true;
}

void Game::DisappearAct::unexecute() {
  std::cout << "Game::DisappearAct::unexecute() " << entity.getId() << std::endl;
  entity.activate();
}