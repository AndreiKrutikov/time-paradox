#pragma once

#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {
struct IMotorialCallback {
  virtual void onPositionChanged(Engine::Common::Direction direction) { }
};

struct Motorial : Component<Motorial> {
  Motorial(Engine::Common::Point velocity, Engine::Common::Point start, Engine::Common::Point finish,
           Engine::Common::Direction dir, IMotorialCallback* callback) : velocity(velocity), 
           startPosition (start), endPosition (finish), direction(dir), callback(callback) { }

  IMotorialCallback* callback;
  bool isActive;
  Engine::Common::Point velocity, startPosition, endPosition;
  Engine::Common::Direction direction;
};
} //end of Engine namespace