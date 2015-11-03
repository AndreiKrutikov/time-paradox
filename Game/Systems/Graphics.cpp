#include "Graphics.h"
#include <EntityComponentSystem/World.hpp>
#include "EventDispatcher.h"

const float Engine::Graphics::TILESIZE = 64;

Engine::Graphics::Graphics(sf::RenderWindow & window) : System(EntityComponentSystem::ComponentFilter().requires<GamePosition, Drawable>()), window(window) {
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
    auto& pos = e.getComponent<GamePosition>();
    auto& drawable = e.getComponent<Drawable>();
    drawable.sprite.setPosition(sf::Vector2f{pos.point.x * TILESIZE, pos.point.y * TILESIZE });
    window.draw(drawable.sprite);
  }

  window.display();
}

void Engine::Graphics::onEntityAdded(EntityComponentSystem::Entity & entity) {
  auto& drawable = entity.getComponent<Drawable>();
}