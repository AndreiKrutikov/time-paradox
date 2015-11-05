#pragma once
#include <EntityComponentSystem\World.hpp>
#include "EntityComponentSystem\AccessabilityMap.h"
#include "Components\Triggerable.h"
#include "Components\GamePosition.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace Entities {
struct Door : public Engine::Triggerable{
  Door(EntityComponentSystem::Entity e, EntityComponentSystem::AccessabilityMap& map, bool initialState, sf::Sprite alternativeSprite);
  void onTrigger(bool pressed);

  EntityComponentSystem::Entity e;
  EntityComponentSystem::AccessabilityMap& map;
  bool isOpened;
private:
  sf::Sprite alternativeSprite;
};

}//end of namespace Entities

