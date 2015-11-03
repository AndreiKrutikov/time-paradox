#include <SFML/Graphics.hpp>
#include "Systems\Graphics.h"
#include <EntityComponentSystem\World.hpp>
#include "Components\Interactible.h"
#include "Systems\EventDispatcher.h"
#include <iostream>

using namespace EntityComponentSystem;
using namespace Engine;

struct Player : public Interactible {
  Player(Entity e) : e(e) {
    e.addComponent<Interactible>(static_cast<Interactible*>(this));
  }

  virtual void onKeyEvent(sf::Event::KeyEvent ev, bool pressed) override {
    if (pressed) {
      auto& pos = e.getComponent<GamePosition>();
      switch (ev.code) {
      case sf::Keyboard::Right:
        pos.point.x++;
        break;

      case sf::Keyboard::Left:
        pos.point.x--;
        break;

      case sf::Keyboard::Up:
        pos.point.y--;
        break;

      case sf::Keyboard::Down:
        pos.point.y++;
        break;
      }

      std::cout << pos.point.x;
    }
  }

  Entity e;
};


int main() {

  sf::Texture t;
  sf::RenderWindow window(sf::VideoMode(960, 512), "SFML works!");
  sf::Image im;
  bool s = im.loadFromFile("test.png");
  s = t.loadFromImage(im);
  std::cout << s;
  World w;
  Player p(w.createEntity());
  p.e.addComponent<GamePosition>(Common::Point{ 1, 1 });
  p.e.addComponent<Drawable>(t);
  p.e.activate();

  Graphics graphicsSystem(window);
  EventDispatcher ed(window);
  w.addSystem(graphicsSystem);
  w.addSystem(ed);
  w.refresh();

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()) {
    graphicsSystem.update();
    ed.update();
  }

  return 0;
}
