#pragma once

#include "Common.h"
#include <EntityComponentSystem/Component.hpp>
#include <SFML\Window\Event.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct PlayerControlable : Component<PlayerControlable> {
  PlayerControlable(){}
};

}
