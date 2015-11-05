#pragma once
#include <chrono>
#include <unordered_set>
#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Platform : Component<Platform> {
  Platform(float velocity, Engine::Common::Point start, Engine::Common::Point finish, Engine::Common::Point current,
           Engine::Common::Direction dir) : velocity(velocity),
    startPosition(start), endPosition(finish), currentPosition(current), direction(dir), isActive(false), isAccesible(true) {
  }

  bool isActive;
  bool isAccesible;
  float velocity;
  std::chrono::time_point<std::chrono::high_resolution_clock> lastShiftTime;
  Engine::Common::Point startPosition, currentPosition, endPosition;
  Engine::Common::Direction direction;
  std::unordered_set<EntityComponentSystem::Entity> dependencies;
};

}
