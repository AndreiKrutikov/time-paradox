#pragma once

#include "Components\Interactible.h"
#include <chrono>

namespace Game {

class TimeManager : public Engine::Interactible {
public:
  TimeManager(EntityComponentSystem::Entity e) : timeSpeed(1), e(e), outatime(false) {
    e.addComponent<Engine::Interactible>(static_cast<Interactible*>(this));
    e.activate();
  }
  
  void checkPoint() {
    realtimeOrigin = std::chrono::high_resolution_clock::now();
  }

  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override {
    if (pressed) {
      if (ev.code == sf::Keyboard::Space) {
        if (timeSpeed != 0) {
          outatime = true;
          gameTimeOrigin = getGameTime();
          checkPoint();
          timeSpeed = 0;
        } else {
          outatime = false;
          checkPoint();
          timeSpeed = 1;
        }
      }

      if (ev.code == sf::Keyboard::Subtract || ev.code == sf::Keyboard::Dash) {
        if (outatime) {
          gameTimeOrigin = getGameTime();
          checkPoint();
          timeSpeed--;
        }
      }

      if (ev.code == sf::Keyboard::Add) {
        if (outatime) {
          gameTimeOrigin = getGameTime();
          checkPoint();
          timeSpeed++;
        }
      }
    }
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> getGameTime() {
    return gameTimeOrigin + (std::chrono::high_resolution_clock::now() - realtimeOrigin) * timeSpeed;
  }

  int64_t getTimeMultiplier() const {
    return timeSpeed;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> gameTimeOrigin;
  std::chrono::time_point<std::chrono::high_resolution_clock> realtimeOrigin;
  int64_t timeSpeed;
  bool outatime;
  EntityComponentSystem::Entity e;
  sf::Text text;
};

}
