#pragma once
#include <chrono>

namespace Game {

struct Act {
  virtual bool execute() = 0;
  virtual void unexecute() = 0;

  EntityComponentSystem::Entity entity;
  std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
};


}
