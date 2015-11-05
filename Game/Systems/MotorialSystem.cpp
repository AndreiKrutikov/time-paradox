#include "MotorialSystem.h"
#include "../EntityComponentSystem/World.hpp"
#include "..\Game.h"
#include "../TimeManager.h"
Engine::MotorialSystem::MotorialSystem() : System(EntityComponentSystem::ComponentFilter().requires <Movable, Motorial>()) { } 

#include <iostream>

void Engine::MotorialSystem::update() {
  if (Game::Game::getGameInstance()->timeManager->isOutatime()) return;
  auto& entities = getEntities();
  for (auto& e : entities) {
    auto& motorial = e.getComponent<Motorial>();
    if (motorial.isActive == true) {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(Game::Game::getGameInstance()->timeManager->getGameTime() - motorial.lastShiftTime).count() < motorial.velocity) continue;
      motorial.callback->onPositionChanged(motorial.direction);

      auto& position = e.getComponent<Movable>().position;
      motorial.lastShiftTime = Game::Game::getGameInstance()->timeManager->getGameTime();

      if ((position.x == motorial.endPosition.x && position.y == motorial.endPosition.y) ) {
      switch (motorial.direction) {
        case Common::Direction::Up:
          motorial.direction = Common::Direction::Down;
          break;
        case Common::Direction::Down:
          motorial.direction = Common::Direction::Up;
          break;
        case Common::Direction::Left:
          motorial.direction = Common::Direction::Right;
          break;
        case Common::Direction::Right:
          motorial.direction = Common::Direction::Left;
          break;
        }
      }

     // motorial.isActive = false;
      //check if we returned back and should stop now
      if (position.x == motorial.startPosition.x && position.y == motorial.startPosition.y) {
        std::cout << "WTF1 " << e.getId() << " " << position.x << " " << position.y << " " << std::endl;
        std::cout << "WTF2 " << e.getId() << " " << motorial.endPosition.x << " " << motorial.endPosition.y << " " << std::endl;
        std::cout << "WTF3 " << e.getId() << " " << motorial.startPosition.x << " " << motorial.startPosition.y << " " << std::endl;
        std::cout << std::endl;


        motorial.isActive = false;
        switch (motorial.direction) {
        case Common::Direction::Up:
          motorial.direction = Common::Direction::Down;
          break;
        case Common::Direction::Down:
          motorial.direction = Common::Direction::Up;
          break;
        case Common::Direction::Left:
          motorial.direction = Common::Direction::Right;
          break;
        case Common::Direction::Right:
          motorial.direction = Common::Direction::Left;
          break;
        }
      }
    }
  }//end of loop over entities
}
