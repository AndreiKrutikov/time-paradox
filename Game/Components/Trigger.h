#pragma once

#include <unordered_set>
#include <EntityComponentSystem\Entity.hpp>
#include <EntityComponentSystem/Component.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Trigger : Component<Trigger> {
  bool isSet = false;
};

}
