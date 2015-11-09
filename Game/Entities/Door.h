#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <EntityComponentSystem/World.hpp>
#include "AccessabilityMap.h"
#include "Components/GamePosition.h"
#include "Components/Triggerable.h"

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
