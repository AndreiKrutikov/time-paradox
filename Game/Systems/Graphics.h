#pragma once
#include <EntityComponentSystem/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Drawable.h"
#include "../Components/GamePosition.h"

namespace Engine {

class Graphics : public EntityComponentSystem::System<Graphics> {
public:
  Graphics(sf::RenderWindow& window); 
  void update();
  static const float TILESIZE;

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;

private:
  sf::RenderWindow& window;
};

}
