#pragma once

#include <EntityComponentSystem/Component.hpp>
#include "Common.h"
#include <chrono>

using EntityComponentSystem::Component;

namespace Engine {

struct IMotorialCallback {
  virtual void onPositionChanged(Engine::Common::Point lastPosition, Engine::Common::Point newPosition) { }
};

struct Motorial : Component<Motorial> {
  Motorial(float velocity, Engine::Common::Point start, Engine::Common::Point finish,
           Engine::Common::Direction dir, IMotorialCallback* callback) : velocity(velocity), 
           startPosition (start), endPosition (finish), direction(dir), callback(callback), isActive(false) { }

  IMotorialCallback* callback;
  bool isActive;
  float velocity;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastShiftTime;
  Engine::Common::Point startPosition, currentPosition, endPosition;
  Engine::Common::Direction direction;
};
} //end of Engine namespace