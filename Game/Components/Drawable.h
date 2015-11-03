#pragma once
#include <EntityComponentSystem/Component.hpp>
#include <SFML\Graphics\Texture.hpp>

using EntityComponentSystem::Component;

namespace Engine {

struct Drawable : Component<Drawable> {
  Drawable(sf::Texture& t) : sprite(t) {
  }

  sf::Sprite sprite;
};

}
