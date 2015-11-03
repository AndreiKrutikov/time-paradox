#pragma once
#include "../Common.h"
#include <EntityComponentSystem/Component.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct GamePosition : Component<GamePosition> {
  GamePosition(Common::Point p) : point(p) {
  }

  Common::Point point;
};

}
