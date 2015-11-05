#pragma once
#include <EntityComponentSystem\World.hpp>
#include "EntityComponentSystem\AccessabilityMap.h"
#include "Components\Triggerable.h"
#include "Components\GamePosition.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace Game { namespace Entities {

struct Door : public Engine::ITriggerable {
  Door(EntityComponentSystem::Entity e, bool initialState, sf::Sprite alternativeSprite);
  Door(Door&&) = delete;
  Door(const Door&) = delete;
  
  void onTrigger(bool value) override;
  void init();

  EntityComponentSystem::Entity e;
  bool isOpened;
  sf::Sprite alternativeSprite;
};

} } //Entities
