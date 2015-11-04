#include "MotorialSystem.h"
#include "../EntityComponentSystem/World.hpp"
Engine::MotorialSystem::MotorialSystem() : System(EntityComponentSystem::ComponentFilter().requires <Movable, Motorial>()) { } 

void Engine::MotorialSystem::update() {
  auto& entities = getEntities();
  for (auto& e : entities) {
    auto& motorial = e.getComponent<Motorial>();
    if (motorial.isActive == true) {
      motorial.callback->onPositionChanged(motorial.direction);
      auto& position = e.getComponent<Movable>().position;
      if ((position.x == motorial.endPosition.x && position.y == motorial.endPosition.y) ||
        (position.x == motorial.startPosition.x && position.y == motorial.startPosition.x ) )
        switch (motorial.direction) {
        case Common::Direction::Up :
          motorial.direction = Common::Direction::Down;
          break;
        case Common::Direction::Down :
          motorial.direction = Common::Direction::Up;
          break;
        case Common::Direction::Left :
          motorial.direction = Common::Direction::Right;
          break;
        case Common::Direction::Right :
          motorial.direction = Common::Direction::Left;
          break;
        }

      //check if we returned back and should stop now
      if (position.x == motorial.startPosition.x && position.y == motorial.startPosition.y)
        motorial.isActive = false;
    }
  }//end of loop over entities
}
