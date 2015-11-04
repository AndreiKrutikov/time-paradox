#pragma once

#include "Components\Interactible.h"
#include "Act.h"
#include <chrono>
#include <memory>

namespace Game {

class TimeManager : public Engine::Interactible {
public:
  TimeManager(EntityComponentSystem::Entity e) : timeSpeed(1), e(e), outatime(false) {
    e.addComponent<Engine::Interactible>(static_cast<Interactible*>(this));
    e.activate();
    firstUnexecutedAct = timeline.begin();
  }
  
  void checkPoint() {
    realtimeOrigin = std::chrono::high_resolution_clock::now();
  }

  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override {
    if (pressed) {
      bool wasOuttatime = outatime;
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

      if (ev.code == sf::Keyboard::Add || ev.code == sf::Keyboard::Equal) {
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

  void addAndExecuteAct(std::unique_ptr<Act> act) {
    if (!outatime) {
      if (act->execute()) {
        act->timestamp = getGameTime();
        firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(act));
        firstUnexecutedAct++;
      }
    }
  }

  bool update() {
    auto currentTime = getGameTime();
    if (timeSpeed > 0) {
      while (firstUnexecutedAct != timeline.end() && firstUnexecutedAct->get()->timestamp <= currentTime) {
        bool success = firstUnexecutedAct->get()->execute();
        if (!success) return false; //TimeParadox
        firstUnexecutedAct++; 
      }
    }

    if (timeSpeed < 0) {
      for (;;) {
        if (firstUnexecutedAct == timeline.begin()) break;
        firstUnexecutedAct--;
        if (firstUnexecutedAct->get()->timestamp >= currentTime) {
          firstUnexecutedAct->get()->unexecute();
        } else {
          firstUnexecutedAct++;
          break;
        }
      }
    }
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> gameTimeOrigin;
  std::chrono::time_point<std::chrono::high_resolution_clock> realtimeOrigin;
  int64_t timeSpeed;
  bool outatime;
  EntityComponentSystem::Entity e;
  sf::Text text;
  std::list<std::unique_ptr<Act>> timeline;
  std::list<std::unique_ptr<Act>>::iterator firstUnexecutedAct;
  //std::list<std::unique_ptr<Act>>::reverse_iterator lastExecutedAct;
};

}
