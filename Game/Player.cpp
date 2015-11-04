#include "Player.h"
#include "Components\Movable.h"
#include "Components\Drawable.h"
#include "Acts.h"
#include "TimeManager.h"
#include "Game.h"
#include <EntityComponentSystem\World.hpp>

using namespace EntityComponentSystem;
using namespace Engine;

Game::Player::Player(Entity e) : e(e) {
  e.addComponent<Interactible>(this);
  e.addComponent<Movable>(Common::Point{ 1, 1 });
}

void Game::Player::onKeyEvent(sf::Event::KeyEvent ev, bool pressed) {
  if (pressed) {
    Common::Direction d;
    switch (ev.code) {
    case sf::Keyboard::Right:
      d = Common::Direction::Right;
      break;
    case sf::Keyboard::Left:
      d = Common::Direction::Left;
      break;
    case sf::Keyboard::Up:
      d = Common::Direction::Up;
      break;
    case sf::Keyboard::Down:
      d = Common::Direction::Down;
      break;
    default:
      return;
    }

    auto ptr = new MoveAct;
    ptr->entity = e;
    ptr->direction = d;
    std::unique_ptr<Act> act(ptr);
    Game::getGameInstance()->timeManager->addAndExecuteAct(std::move(act));
  }
}

#include <iostream>

Entity Game::Player::createClone() {
  auto old = e;
  std::cout << "old " << old.getId();
  old.removeComponent<Interactible>();
  e = e.getWorld().createEntity();
  std::cout << " new " << e.getId() << std::endl;
  e.addComponent<Movable>(old.getComponent<Movable>().position);
  e.addComponent<Drawable>(&old.getComponent<Drawable>());
  e.activate();
  old.activate();
  return old;
}


