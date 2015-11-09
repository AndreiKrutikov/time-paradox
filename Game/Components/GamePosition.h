#pragma once
#include <EntityComponentSystem/Component.hpp>
#include "../Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct GamePosition : Component<GamePosition> {
  GamePosition(Common::Point p) : point(p) {
  }

  Common::Point point;
};

}
