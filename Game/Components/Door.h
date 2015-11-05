#pragma once
#include <unordered_set>
#include <SFML/Graphics/Sprite.hpp>
#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include "Common.h"

using EntityComponentSystem::Component;

namespace Engine {

struct Door : Component<Door> {
  Door(bool triggeredMeanClosed, sf::Sprite alternativeSprite) : alternativeSprite(alternativeSprite), triggeredMeanClosed(triggeredMeanClosed), triggered(false) {
  }

  sf::Sprite alternativeSprite;
  bool triggeredMeanClosed;
  bool triggered;
  std::unordered_set<EntityComponentSystem::Entity> dependencies;
};

}
