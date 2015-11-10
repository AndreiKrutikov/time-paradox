#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <EntityComponentSystem/Component.hpp>

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
