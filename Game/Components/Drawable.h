#pragma once
#include <EntityComponentSystem/Component.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
using EntityComponentSystem::Component;

namespace Engine {

struct Drawable : Component<Drawable> {
  Drawable(const sf::Texture& t, sf::IntRect subrect) : sprite(t, subrect) {
  }

  Drawable(const sf::Sprite& s): sprite(*s.getTexture(), s.getTextureRect()) {
  }

  sf::Sprite sprite;
};

}
