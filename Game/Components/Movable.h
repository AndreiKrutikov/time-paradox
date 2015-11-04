#pragma once

#include "Common.h"
#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Movable : Component<Movable> {
  Movable(Common::Point p) : position(p) { }

  Common::Point position;
};

}
