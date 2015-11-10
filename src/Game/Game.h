#pragma once

namespace EntityComponentSystem {

class World;

}

namespace Engine {

class Graphics;
class ResourceManager;
struct AccessabilityMap;

}

namespace Game {

struct Player;
class TimeManager;
struct LevelManager;

struct Game {
  Player* player;
  TimeManager* timeManager;
  LevelManager* levelManager;
  Engine::Graphics* graphics;
  Engine::AccessabilityMap* accessabilityMap;
  EntityComponentSystem::World* world;
  Engine::ResourceManager* resourceManager;

  static Game* getGameInstance();

  enum State {
    running,
    failed,
    win
  } state;
};

}
