#include "CloneObject.h"

void Engine::Clone::killClone() {
  e.deactivate();
}

void Engine::Clone::spawnClone() {
  e.activate();
}

void Engine::Clone::moveClone(Direction dir) {
  auto& movComp = e.getComponent<Movable>();
  switch (dir) {
  case Up:
    movComp.position.y--;
    break;
  case Down:
    movComp.position.y++;
    break;
  case Left:
    movComp.position.x--;
    break;
  case Right:
    movComp.position.x++;
    break;
  }
}