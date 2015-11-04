#pragma once

namespace EntityComponentSystem {

struct AccessabilityMap;
class World;

}

namespace Engine {

class Graphics;
class ResourceManagers;

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
  EntityComponentSystem::AccessabilityMap* accessabilityMap;
  EntityComponentSystem::World* world;
  Engine::ResourceManagers* resourceManager;

  static Game* getGameInstance();
};

}
