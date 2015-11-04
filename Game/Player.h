#pragma once
#include "Components\Interactible.h"
#include "Components\Movable.h"
#include "Acts.h"
#include "TimeManager.h"
#include <EntityComponentSystem\Entity.hpp>


using namespace EntityComponentSystem;
using namespace Engine;

namespace Game {

struct Player : public Interactible {
  Player(Entity e, TimeManager& tm) : e(e), tm(tm)  {
    e.addComponent<Interactible>(static_cast<Interactible*>(this));
    e.addComponent<Movable>(Common::Point{ 1, 1 });
  }

  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override {
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
      tm.addAndExecuteAct(std::move(act));
    }
  }

  Entity e;
  TimeManager& tm;
};

}
