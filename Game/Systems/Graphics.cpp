#include "Graphics.h"
#include <EntityComponentSystem/World.hpp>
#include "EventDispatcher.h"
#include "../Components/Movable.h"

const float Engine::Graphics::TILESIZE = 64;

Engine::Graphics::Graphics(sf::RenderWindow & window) : System(EntityComponentSystem::ComponentFilter().requires<Drawable>().requiresOneOf<GamePosition,Movable>()), window(window) {
}

void Engine::Graphics::initialize() {
  camera.view.setCenter({ window.getSize().x / 2.f, window.getSize().y / 2.f });
  camera.view.setSize({ window.getSize().x * 1.f, window.getSize().y* 1.f });
  window.setView(camera.view);
  camera.e = getWorld().createEntity();
  camera.e.addComponent<Interactible>(static_cast<Interactible*>(&camera));
  camera.e.activate();
  camera.window = &window;
}

void Engine::Graphics::update() {
  window.clear();
  auto& entities = getEntities();
  for (auto e : entities) {
    Common::Point point;
    if (e.hasComponent<GamePosition>()) {
      auto& pos = e.getComponent<GamePosition>(); 
      point = pos.point;
    }

    if (e.hasComponent<Movable>()) {
      auto& pos = e.getComponent<Movable>();
      point = pos.position;
    }

    auto& drawable = e.getComponent<Drawable>();
    drawable.sprite.setPosition(sf::Vector2f{point.x * TILESIZE, point.y * TILESIZE });
    window.draw(drawable.sprite);
  }

  for (auto& t : texts) {
    window.draw(t);
  }

  texts.clear();

  window.display();
}

void Engine::Graphics::onEntityAdded(EntityComponentSystem::Entity & entity) {
  auto& drawable = entity.getComponent<Drawable>();
}

void Engine::Graphics::addText(const sf::Text & t) {
  texts.push_back(t);
}
