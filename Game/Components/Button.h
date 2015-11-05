#pragma once
#include <unordered_set>
#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Button : Component<Button> {
  Button() : pressed(false) { }
  bool pressed;
};

}
