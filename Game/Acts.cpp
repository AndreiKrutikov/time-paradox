#include "Acts.h"
#include "Components\Movable.h"

bool Game::MoveAct::execute() {
  using namespace Engine::Common;
  Point newPosition = entity.getComponent<Engine::Movable>().position;
 
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

  if (map.isFree(newPosition)) {
    entity.getComponent<Engine::Movable>().position = newPosition;
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
  if (map.isFree(position) == false || map.isDeadly(position) == true)
    return false;
  entity.activate();
  return true;
}

void Game::SpawnAct::unexecute() {
  entity.deactivate();
}

bool Game::DisappearAct::execute() {
  entity.deactivate();
  return true;
}

void Game::DisappearAct::unexecute() {
  entity.activate();
}