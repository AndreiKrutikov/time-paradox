#pragma once
#include "EntityComponentSystem\Entity.hpp"
#include "Components\Drawable.h"
#include "Components\Movable.h"
#include "Components\GamePosition.h"
#include <SFML\Graphics\Texture.hpp>
namespace Game {

struct Clone {
  
  Clone(EntityComponentSystem::Entity e, Engine::Common::Point position, sf::Texture t);

  void spawnClone();
  void killClone();
  void moveClone(Engine::Common::Direction dir);
private:
  EntityComponentSystem::Entity e;
};

}
