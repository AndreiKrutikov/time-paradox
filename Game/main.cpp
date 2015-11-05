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
#include <fstream>


using namespace EntityComponentSystem;
using namespace Engine;

extern Game::Game* gameInstance;

int main() {
  Game::Game game;
  gameInstance = &game;
  

  sf::Font font;
  bool f = font.loadFromFile("unispace rg.ttf");


  sf::Texture t;
  sf::RenderWindow window(sf::VideoMode(1024, 768), "Wait, OH SHI~~~");
  sf::Image im;
  bool s = im.loadFromFile("maps//robot.png");
  s = t.loadFromImage(im);

  sf::Texture t2;
  t2.loadFromFile("kuzrobot.png");
  
  std::vector<sf::Text> levels;
  std::ifstream file("Levels.config");
  uint16_t margin = 10;
  std::string str;
  while (std::getline(file, str)) {
    //text.move(0, (text.getCharacterSize() + margin)*levels.size());

    levels.emplace_back();

    levels.back().setColor(sf::Color(200, 200, 200)); 
    levels.back().setString(str);
    levels.back().setFont(font);
    levels.back().move(0, (levels.size() - 1) * (levels.back().getLocalBounds().height + margin));
  }
  levels[0].setStyle(sf::Text::Style::Bold || sf::Text::Style::Underlined);
  levels[0].setColor(sf::Color::White);
  while (window.isOpen()) {


    sf::Event event;
    int16_t levelidx = 0;
    while (window.isOpen()) {
      bool endCycle = false;
      while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyReleased:
          switch (event.key.code) {
          case sf::Keyboard::Space:
            endCycle = true;
            break;
          case sf::Keyboard::Up:
            levels[levelidx].setStyle(sf::Text::Style::Regular);
            levels[levelidx].setColor(sf::Color(200, 200, 200));
            levelidx--;
            if (levelidx < 0) {
              levelidx = levels.size() - 1;
            }
            levels[levelidx].setStyle(sf::Text::Style::Bold);
            levels[levelidx].setColor(sf::Color::White);
            break;
          case sf::Keyboard::Down:
            levels[levelidx].setStyle(sf::Text::Style::Regular);
            levels[levelidx].setColor(sf::Color(200, 200, 200));
            levelidx++;
            if (levelidx == levels.size()) {
              levelidx = 0;
            }
            levels[levelidx].setStyle(sf::Text::Style::Bold);
            levels[levelidx].setColor(sf::Color::White);
            break;
          default:
            break;
          }
          break;
        default:
          break;
        }
      }

      if (endCycle) {
        break;
      }
      window.clear();
      for (auto text : levels) {
        window.draw(text);
      }
      window.display();
    }
    std::string  curlevel = levels[levelidx].getString() + ".json";
    World w;
    game.world = &w;
    Game::LevelManager levelManager;
    game.levelManager = &levelManager;
    game.resourceManager = &levelManager.resourceManagers;

    RegionSystem regSys;
    w.addSystem(regSys);

    game.resourceManager->loadFont("cam_font", "unispace rg.ttf");
    levelManager.loadLevel("maps\\", curlevel, w);

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

      if (Game::Game::getGameInstance()->state == Game::Game::win || Game::Game::getGameInstance()->state == Game::Game::failed) {
        while (window.isOpen()) {
          bool tobreak = false;
          sf::Event event;
          while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
              tobreak = true;
              break;
            }
          }
          if (tobreak) {
            break;
          }
        }
        w.clear();
        break;
      }


      auto plpos = p.e.getComponent<Movable>().position;
      if (plpos.x == levelManager.finish.x && plpos.y == levelManager.finish.y) {
        game.state = Game::Game::win;
        p.e.removeComponent<Drawable>();
        p.e.addComponent<Drawable>(t2, sf::IntRect(0, 0, 32, 32));
        p.e.activate();
      }

    }
  }
  return 0;
}
