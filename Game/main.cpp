#include <SFML/Graphics.hpp>
#include "Systems\Graphics.h"
#include <EntityComponentSystem\World.hpp>
#include "LevelManager.h"
#include "Components\Interactible.h"
#include "Systems\EventDispatcher.h"
#include "TimeManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>


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
  sf::Font font;
  bool f = font.loadFromFile("unispace rg.ttf");
  
  sf::Text text;
  text.setFont(font); 
  text.setString("12:34.567");
  text.setCharacterSize(18); 
  text.setColor(sf::Color::Red);


  sf::Texture t;
  sf::RenderWindow window(sf::VideoMode(960, 512), "SFML works!");
  sf::Image im;
  bool s = im.loadFromFile("maps\\denis\\robot.png");
  s = t.loadFromImage(im);
  std::cout << s;
  World w;
  LevelManager levelManager;
  levelManager.loadLevel("maps\\denis\\1.json", w);
  Player p(w.createEntity());
  p.e.addComponent<GamePosition>(Common::Point{ 1, 1 });
  p.e.addComponent<Drawable>(t, sf::IntRect(0,0,32,32));
  p.e.activate();

  Graphics graphicsSystem(window);
  EventDispatcher ed(window);
  w.addSystem(graphicsSystem);
  w.addSystem(ed);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  Game::TimeManager tm(w.createEntity());

  w.refresh();
  tm.checkPoint();
  while (window.isOpen()) {
    
    


    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tm.getGameTime().time_since_epoch()).count();
    std::cout << ms << std::endl;
    auto minute = ms/60000;
    ms %= 60000;
    auto sec = ms / 1000;
    ms %= 1000;
    std::stringstream ss;
    ss << minute << ":" << std::setw(2) << std::setfill('0')<< sec << "." << ms << " x" << tm.getTimeMultiplier();
    text.setString(ss.str());
    graphicsSystem.addText(text);
    graphicsSystem.update();
    ed.update();



  }

  return 0;
}
