#pragma once
#include <EntityComponentSystem/Component.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct PlayerControlable : Component<PlayerControlable> {
  PlayerControlable(){}
};

}
