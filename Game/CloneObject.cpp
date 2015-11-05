#include "CloneObject.h"
#include "Game.h"
#include "EntityComponentSystem\AccessabilityMap.h"
using namespace Engine;
void Game::Clone::killClone() {
  e.deactivate();
}

Game::Clone::Clone(EntityComponentSystem::Entity e, Engine::Common::Point position, sf::Texture t) {
//  e.addComponent<Engine::Drawable>(t);
  e.addComponent<Engine::Movable>(position);
}

void Game::Clone::spawnClone() {
  e.activate();
}

void Game::Clone::moveClone(Common::Direction dir) {
  using namespace Common;
  auto& movComp = e.getComponent<Movable>();
  switch (dir) {
  case Direction::Up:
    movComp.position.y--;
    break;
  case Direction::Down:
    movComp.position.y++;
    break;
  case Direction::Left:
    movComp.position.x--;
    break;
  case Direction::Right:
    movComp.position.x++;
    break;
  }

}