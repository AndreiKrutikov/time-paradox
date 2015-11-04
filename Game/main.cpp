#include <SFML/Graphics.hpp>
#include "Systems\Graphics.h"
#include <EntityComponentSystem\World.hpp>
#include "LevelManager.h"
#include "Components\Interactible.h"
#include "Systems\EventDispatcher.h"
#include "TimeManager.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>


using namespace EntityComponentSystem;
using namespace Engine;

int main() {
  sf::Font font;
  bool f = font.loadFromFile("unispace rg.ttf");
  
  sf::Text text;
  text.setFont(font); 
  text.setString("12:34.567");
  text.setCharacterSize(18); 
  text.setColor(sf::Color::Red);


  sf::Texture t;
  sf::RenderWindow window(sf::VideoMode(960, 512), "Wait, OH SHI~~~");
  sf::Image im;
  bool s = im.loadFromFile("maps\\denis\\robot.png");
  s = t.loadFromImage(im);
  std::cout << s;
  World w;
  Game::LevelManager levelManager;
  levelManager.loadLevel("maps\\denis\\", "4.json", w);
  Player p(w.createEntity(),levelManager.accessMap);
  p.e.addComponent<GamePosition>(Common::Point{ 1, 4 });
  p.e.addComponent<Drawable>(t, sf::IntRect(0,0,32,32));
  p.e.activate();

  Graphics graphicsSystem(window);
  EventDispatcher ed(window);
  w.addSystem(graphicsSystem);
  w.addSystem(ed);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  Game::Player p(w.createEntity());
  p.e.addComponent<Drawable>(t);
  Game::TimeManager tm_(w.createEntity(), p);
  p.setTimeManager(&tm_);
  graphicsSystem.setTimeManager(&tm_);

  w.refresh();
  tm_.checkPoint();
  while (window.isOpen()) {
    
    tm_.update();
    w.refresh();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tm_.getGameTime().time_since_epoch()).count();
    auto minute = ms/60000;
    ms %= 60000;
    auto sec = ms / 1000;
    ms %= 1000;
    std::stringstream ss;
    ss << minute << ":" << std::setw(2) << std::setfill('0')<< sec << "." << std::setw(3) << std::setfill('0') << ms << " x" << tm_.getTimeMultiplier();
    text.setString(ss.str());
    graphicsSystem.addText(text);
    graphicsSystem.update();
    ed.update();
  }

  return 0;
}
