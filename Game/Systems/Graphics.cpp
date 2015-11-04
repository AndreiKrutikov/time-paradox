#include "Graphics.h"
#include <EntityComponentSystem/World.hpp>
#include "EventDispatcher.h"
#include "../Components/Movable.h"
#include "../TimeManager.h"
#include "../Game.h"

const float Engine::Graphics::TILESIZE = 32;

Engine::Graphics::Graphics(sf::RenderWindow & window) : System(EntityComponentSystem::ComponentFilter().requires<Drawable>().requiresOneOf<GamePosition,Movable>()), window(window) {
}

void Engine::Graphics::initialize() {
  camera.view.setCenter({ window.getSize().x / 2.f, window.getSize().y / 2.f });
  camera.view.setSize({ window.getSize().x * 1.f, window.getSize().y* 1.f });
  window.setView(camera.view);
  camera.view.zoom(0.5f);
  camera.view.setCenter({ window.getSize().x / 4.f, window.getSize().y / 4.f });
  camera.e = getWorld().createEntity();
  camera.e.addComponent<Interactible>(&camera);
  camera.e.activate();
  auto size = window.getSize();
  rt.create(size.x, size.y);
  ppSprite.setTexture(rt.getTexture());
  ppShader.loadFromFile("glow.frag", sf::Shader::Fragment);
  ppShader.setParameter("texture", sf::Shader::CurrentTexture);
}

void Engine::Graphics::update() {
  rt.clear();
  rt.setView(camera.view);

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
    drawable.sprite.setPosition(sf::Vector2f{ point.x * TILESIZE, point.y * TILESIZE });
    rt.draw(drawable.sprite);
  }

  rt.display();

  auto tmngr = Game::Game::getGameInstance()->timeManager;

  if (tmngr->isOutatime()) {
    auto color = sf::Color::Black;
    if (tmngr->getTimeMultiplier() > 0) {
      color = sf::Color(0x0000FF00);
    }

    if (tmngr->getTimeMultiplier() < 0) {
      color = sf::Color(0x00FF0000);
    }

    float intensity = std::abs(tmngr->getTimeMultiplier()) * 0.35f;

    ppShader.setParameter("glowColor", color);
    ppShader.setParameter("intensity", intensity);
    window.draw(ppSprite, &ppShader);
  } else {

    window.draw(ppSprite);
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
