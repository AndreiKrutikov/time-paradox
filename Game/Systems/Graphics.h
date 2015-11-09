#pragma once
#include <SFML/Graphics.hpp>
#include <EntityComponentSystem/System.hpp>
#include "../Components/Drawable.h"
#include "../Components/GamePosition.h"
#include "../Components/Interactible.h"

namespace Game {
  class TimeManager;
}

namespace Engine {

class Graphics : public EntityComponentSystem::System<Graphics>, public IInteractible{
public:
  Graphics(sf::RenderWindow& window); 
  virtual void initialize() override;
  void update();
  static const float TILESIZE;

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;
  void addText(const sf::Text& t);

private:
  virtual void onMouseWheel(sf::Event::MouseWheelScrollEvent ev) override {
    camera.zoom(exp(ev.delta*0.1f));
  };

  virtual void onMouseMove(sf::Event::MouseMoveEvent ev) override;

  void updateCam();

  sf::View camera;
  EntityComponentSystem::Entity e;
  sf::Texture winImg;
  sf::Texture failImg;

  sf::RenderTexture rt;
  sf::Sprite ppSprite; 
  sf::Shader ppShader;
  sf::RenderWindow& window;
  std::vector<std::reference_wrapper<const sf::Text>> texts;
};

}

