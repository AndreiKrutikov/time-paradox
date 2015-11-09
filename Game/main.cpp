#include <SFML/Graphics.hpp>
#include "Systems\Graphics.h"
#include <EntityComponentSystem\World.hpp>
#include "LevelManager.h"
#include "Components\Interactible.h"
#include "Components\Movable.h"
#include "Game.h"
#include "Systems\EventDispatcher.h"
#include "Systems\RegionSystem.h"
#include "Systems\ButtonSystem.h"
#include "Systems\DoorSystem.h"
#include "Systems\PlatformSystem.h"
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
  sf::RenderWindow window(sf::VideoMode(960, 512), "Wait, OH SHI~~~");
  sf::Image im;
  bool s = im.loadFromFile("maps\\denis\\robot.png");
  s = t.loadFromImage(im);
  std::cout << s;

  World w;
  game.world = &w;
  Game::LevelManager levelManager;
  game.levelManager = &levelManager;
  game.resourceManager = &levelManager.resourceManagers;

  RegionSystem regSys;
  w.addSystem(regSys);

  game.resourceManager->loadFont("cam_font", "unispace rg.ttf");
  levelManager.loadLevel("maps\\denis\\", "5.json", w);
  
  game.accessabilityMap = &levelManager.accessMap;
  levelManager.initLevel();

  Graphics graphicsSystem(window);
  game.graphics = &graphicsSystem;
  EventDispatcher ed(window);
  Engine::DoorSystem doorSystem;
  Engine::ButtonSystem buttonSystem;
  Engine::PlatformSystem platformSystem;
  

  w.addSystem(graphicsSystem);
  w.addSystem(ed);
  w.addSystem(doorSystem);
  w.addSystem(buttonSystem);
  w.addSystem(platformSystem);

  Game::Player p(w.createEntity());
  game.player = &p;
  p.e.getComponent<Movable>().position = levelManager.start;
  p.e.addComponent<Drawable>(t, sf::IntRect(0, 0, 32, 32));
 

  Game::TimeManager tm_(w.createEntity());
  game.timeManager = &tm_;
  w.refresh();
  tm_.checkPoint();
  while (window.isOpen()) {    
    tm_.update();
    w.refresh();
    regSys.update();
    buttonSystem.update();
    doorSystem.update();
    platformSystem.update();
    ed.update();
    graphicsSystem.update();
  }

  return 0;
}

