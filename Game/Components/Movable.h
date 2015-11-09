#pragma once
#include <SFML/Window/Event.hpp>
#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Movable : Component<Movable> {
  Movable(Common::Point p) : position(p) { }

  Common::Point position;
};

}
