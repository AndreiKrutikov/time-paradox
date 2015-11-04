#pragma once
#include <EntityComponentSystem/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Drawable.h"
#include "../Components/GamePosition.h"
#include "../Components/Interactible.h"
#include <iostream>

namespace Game {
  class TimeManager;
}

namespace Engine {

class Graphics : public EntityComponentSystem::System<Graphics> {
public:
  Graphics(sf::RenderWindow& window); 
  virtual void initialize() override;
  void update();
  static const float TILESIZE;

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;
  void addText(const sf::Text& t);

private:
  struct Camera : public IInteractible {
    virtual void onMouseWheel(sf::Event::MouseWheelScrollEvent ev) override {
      view.zoom(exp(ev.delta*0.1f));
    };

    sf::View view;
    EntityComponentSystem::Entity e;
  } camera;

  sf::RenderTexture rt;
  sf::Sprite ppSprite; 
  sf::Shader ppShader;
  sf::RenderWindow& window;
  std::vector<std::reference_wrapper<const sf::Text>> texts;
};

}
