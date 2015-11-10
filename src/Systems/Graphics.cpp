#include "Graphics.h"
#include <EntityComponentSystem/World.hpp>
#include "EventDispatcher.h"
#include "Game/Game.h"
#include "Components/Movable.h"
#include "Game/LevelManager.h"
#include "Game/Player.h"
#include "Game/TimeManager.h"

const float Engine::Graphics::TILESIZE = 32;

Engine::Graphics::Graphics(sf::RenderWindow & window) : System(EntityComponentSystem::ComponentFilter().requires<Drawable>().requiresOneOf<GamePosition,Movable>()), window(window) {
}

void Engine::Graphics::initialize() {
  camera.setCenter({ window.getSize().x / 2.f, window.getSize().y / 2.f });
  camera.setSize({ window.getSize().x * 1.f, window.getSize().y* 1.f });
  window.setView(camera);
  camera.zoom(0.5f);
  camera.setCenter({ window.getSize().x / 4.f, window.getSize().y / 4.f });
  e = getWorld().createEntity();
  e.addComponent<Interactible>(this);
  e.activate();
  auto size = window.getSize();
  rt.create(size.x, size.y);
  ppSprite.setTexture(rt.getTexture());
  ppShader.loadFromFile("glow.frag", sf::Shader::Fragment);
  ppShader.setParameter("texture", sf::Shader::CurrentTexture);

  winImg.loadFromFile("win.png");
  failImg.loadFromFile("fail.png");

}

void Engine::Graphics::update() {
  rt.clear();
  updateCam();
  rt.setView(camera);

  auto& entities = getEntities();
  for (auto e : entities) {
    Common::Point point{ 0, 0 };
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
    int i = 1;
    rt.draw(drawable.sprite);
  }


  if (Game::Game::getGameInstance()->state == Game::Game::failed) {
    sf::Sprite failImg_(failImg);

    failImg_.setPosition(camera.getCenter());
    rt.draw(failImg_);
  }
  

  if (Game::Game::getGameInstance()->state == Game::Game::win) {
    sf::Sprite winImg_(winImg);

    winImg_.setPosition(camera.getCenter());
    rt.draw(winImg_);
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

void Engine::Graphics::onMouseMove(sf::Event::MouseMoveEvent ev) {}

void Engine::Graphics::updateCam() {
  auto player = Game::Game::getGameInstance()->player;
  auto position = player->e.getComponent<Movable>().position;
  auto mousePos = sf::Mouse::getPosition();
  auto wSize = window.getSize();
  
  auto x = position.x*TILESIZE + (mousePos.x - wSize.x*1.f) / 2.f;
  auto y = position.y*TILESIZE + (mousePos.y - wSize.y*1.f) / 2.f;

  
  auto camSize = camera.getSize();
  
  auto heigth = Game::Game::getGameInstance()->levelManager->height * TILESIZE;
  if (y > heigth - camSize.y / 2) y = heigth - camSize.y / 2;
  auto width = Game::Game::getGameInstance()->levelManager->width * TILESIZE;
  if (x > width - camSize.x / 2) x = width - camSize.x / 2;


  if (x < camSize.x / 2) x = camSize.x / 2;
  if (y < camSize.y / 2) y = camSize.y / 2;

  camera.setCenter(x, y);
}
