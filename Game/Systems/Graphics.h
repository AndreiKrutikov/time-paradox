#pragma once
#include <EntityComponentSystem/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Drawable.h"
#include "../Components/GamePosition.h"
#include "../Components/Interactible.h"
#include <iostream>

namespace Engine {

class Graphics : public EntityComponentSystem::System<Graphics> {
public:
  Graphics(sf::RenderWindow& window); 
  virtual void initialize() override;
  void update();
  static const float TILESIZE;

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;

private:
  struct Camera : public Interactible {
    virtual void onMouseWheel(sf::Event::MouseWheelScrollEvent ev) override {
      std::cout << exp(ev.delta) << " ";
      view.zoom(exp(ev.delta*0.1));
      window->setView(view);
    };

    sf::View view;
    sf::RenderWindow* window;
    EntityComponentSystem::Entity e;
  } camera;

  sf::RenderWindow& window;
};

}
