#include "Acts.h"
#include "Components\Movable.h"
#include <EntityComponentSystem\Entity.hpp>

using namespace EntityComponentSystem;

#include <iostream>

bool Game::MoveAct::execute() {
  using namespace Engine::Common;
  auto& movable = entity.getComponent<Engine::Movable>();
  Point newPosition = movable.position;
 
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

  if (/*map.isFree(newPosition)*/ true) {
    movable.position = newPosition;
    return true;
  } else
    return false;
}

void Game::MoveAct::unexecute() {
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

  if (/*map.isFree(position) == false || map.isDeadly(position) == true*/ false)
    return false;
  entity.activate();
  return true;
}

void Game::SpawnAct::unexecute() {
  std::cout << "Game::SpawnAct::unexecute() " << entity.getId() << std::endl;
  entity.deactivate();
}

bool Game::DisappearAct::execute() {
  std::cout << "Game::DisappearAct::execute() " << entity.getId() << std::endl;
  entity.deactivate();
  return true;
}

void Game::DisappearAct::unexecute() {
  std::cout << "Game::DisappearAct::unexecute() " << entity.getId() << std::endl;
  entity.activate();
}