#pragma once
#include <EntityComponentSystem\World.hpp>
#include "EntityComponentSystem\AccessabilityMap.h"
#include "Components\Triggerable.h"
#include "Components\GamePosition.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace Game { namespace Entities {

struct Door : public Engine::ITriggerable {
  Door(EntityComponentSystem::Entity e, sf::Sprite alternativeSprite, bool type);
  Door(Door&&) = delete;
  Door(const Door&) = delete;
  
  void onTrigger(bool value) override;
  void init();

  bool closed;
  EntityComponentSystem::Entity e;
  sf::Sprite alternativeSprite;
};

} } //Entities
