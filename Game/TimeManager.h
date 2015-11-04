#pragma once

#include "Components\Interactible.h"
#include <SFML\Graphics\Text.hpp>
#include "Act.h"
#include "EntityComponentSystem\AccessabilityMap.h"
#include <chrono>
#include <memory>
#include <list>

namespace Game {

struct Player;

class TimeManager : public Engine::IInteractible {
public:
  TimeManager(EntityComponentSystem::Entity e);  
  void checkPoint();
  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override;
  std::chrono::time_point<std::chrono::high_resolution_clock> getGameTime();
  int64_t getTimeMultiplier() const;
  void addAndExecuteAct(std::unique_ptr<Act> act);
  bool update(); 
  bool isOutatime() {
    return outatime;
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> gameTimeOrigin;
  std::chrono::time_point<std::chrono::high_resolution_clock> realtimeOrigin;
  int64_t timeSpeed;
  bool outatime;
  bool disappeared;
  EntityComponentSystem::Entity e;
  sf::Text text;
  std::list<std::unique_ptr<Act>> timeline;
  std::list<std::unique_ptr<Act>>::iterator firstUnexecutedAct;
  //std::list<std::unique_ptr<Act>>::reverse_iterator lastExecutedAct;
};

}
