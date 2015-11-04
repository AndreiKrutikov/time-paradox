#pragma once
#include "EntityComponentSystem\Entity.hpp"
#include "Components\Drawable.h"
#include "Components\Movable.h"
#include "Components\GamePosition.h"
#include <SFML\Graphics\Texture.hpp>
namespace Engine {

struct Clone {
  
  Clone(EntityComponentSystem::Entity e, Common::Point position, sf::Texture t) {
    e.addComponent<Drawable>(t);
    e.addComponent<Movable>(position);
  }

  enum Direction {
    Up, Down, Left, Right
  };

  void spawnClone();
  void killClone();
  void moveClone(Direction dir);
private:
  EntityComponentSystem::Entity e;
};

}
