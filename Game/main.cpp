#include <SFML/Graphics.hpp>
#include "Systems\Graphics.h"
#include <EntityComponentSystem\World.hpp>
#include "LevelManager.h"
#include "Components\Interactible.h"
#include "Components\Movable.h"
#include "Game.h"
#include "Systems\EventDispatcher.h"
#include "Systems\RegionSystem.h"
#include "Systems\MotorialSystem.h"
#include "TimeManager.h"
#include "Player.h"
#include <iostream>



using namespace EntityComponentSystem;
using namespace Engine;

extern Game::Game* gameInstance;

int main() {
  Game::Game game;
  gameInstance = &game;
  


  sf::Texture t;
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Wait, OH SHI~~~");
  sf::Image im;
  bool s = im.loadFromFile("maps//denis//robot.png");
  s = t.loadFromImage(im);

  sf::Texture t2;
  t2.loadFromFile("kuzrobot.png");
  std::cout << s;

  World w;
  game.world = &w;
  Game::LevelManager levelManager;
  game.levelManager = &levelManager;
  game.resourceManager = &levelManager.resourceManagers;

  RegionSystem regSys;
  w.addSystem(regSys);

  game.resourceManager->loadFont("cam_font", "unispace rg.ttf");
  levelManager.loadLevel("maps\\denis\\", "1.json", w);
  
  game.accessabilityMap = &levelManager.accessMap;
  levelManager.initLevel();

  Graphics graphicsSystem(window);
  game.graphics = &graphicsSystem;
  EventDispatcher ed(window);
  

  w.addSystem(graphicsSystem);
  w.addSystem(ed);

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  Engine::MotorialSystem ms;
  w.addSystem(ms);

  Game::Player p(w.createEntity());
  game.player = &p;
  p.e.getComponent<Movable>().position = levelManager.start;
  p.e.addComponent<Drawable>(t, sf::IntRect(0, 0, 32, 32));
  Game::TimeManager tm_(w.createEntity());
  game.timeManager = &tm_;
  w.refresh();
  tm_.checkPoint();
  while (window.isOpen()) {    
    if (!tm_.update())
      Game::Game::getGameInstance()->state = Game::Game::failed;
    w.refresh();
    ms.update();
    graphicsSystem.update();
    ed.update();
    regSys.update(tm_.isOutatime());

    auto plpos = p.e.getComponent<Movable>().position;
    if (plpos.x == levelManager.finish.x && plpos.y == levelManager.finish.y) {
      game.state = Game::Game::win;
      p.e.removeComponent<Drawable>();
      p.e.addComponent<Drawable>(t2, sf::IntRect(0, 0, 32, 32));
      p.e.activate();
    }


  }

  return 0;
}
