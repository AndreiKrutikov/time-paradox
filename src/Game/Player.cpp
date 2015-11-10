#include "Player.h"
#include <EntityComponentSystem/World.hpp>
#include "Acts.h"
#include "Components/Movable.h"
#include "Components/Drawable.h"
#include "Components/PlayerControlable.h"
#include "Game.h"
#include "TimeManager.h"

using namespace EntityComponentSystem;
using namespace Engine;

Game::Player::Player(Entity e) : e(e) {
  e.addComponent<Interactible>(this);
  e.addComponent<Movable>(Common::Point{ 1, 1 });
  e.addComponent <PlayerControlable>();
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

Entity Game::Player::createClone() {
  auto old = e;
  old.removeComponent<Interactible>();
  old.removeComponent<PlayerControlable>();
  e = e.getWorld().createEntity();
  e.addComponent<Movable>(old.getComponent<Movable>().position);
  e.addComponent<Drawable>(old.getComponent<Drawable>().sprite);
  e.addComponent<PlayerControlable>();
  e.activate();
  old.activate();
  return old;
}

