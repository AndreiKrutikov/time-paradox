#pragma once
#include <list>
#include <vector>
#include <EntityComponentSystem/World.hpp>
#include "AccessabilityMap.h"
#include "Entities/Door.h"
#include "Entities/MovingPlatform.h"
#include "Entities/Switch.h"
#include "Utils/JsonValue.h"
#include "ResourceManager.h"

namespace Game {

namespace Entities {
  struct Door;
  struct Switch;
}

struct LevelManager {
  LevelManager();
  
  void loadLevel(const std::string path,const std::string& levelfile, EntityComponentSystem::World& w);
  void initLevel();

  void clear();

  ~LevelManager();

  Engine::AccessabilityMap accessMap;
  Engine::ResourceManager ResourceManager;
  uint16_t width, height;

  Engine::Common::Point start, finish;
private:
  std::list<Entities::Door> doors;
  std::list<Entities::Switch> buttons;
  std::list<Entities::MovingPlatform> platforms;
  std::vector<EntityComponentSystem::Entity> entities;  

  void loadTileSet(Engine::Common::JsonValue& tilesetArray, const std::string& path);
  void loadTileLayer(Engine::Common::JsonValue& layer, uint16_t width, EntityComponentSystem::World& w);
};

}

