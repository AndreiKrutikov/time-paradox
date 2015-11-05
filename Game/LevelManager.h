#pragma once
#include "EntityComponentSystem\AccessabilityMap.h"
#include "ResourceManagers.h"
#include "EntityComponentSystem\World.hpp"
#include "Utils\JsonValue.h"
#include "Entities\MovingPlatform.h"
#include <string>
#include <map>
#include <vector>

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

  EntityComponentSystem::AccessabilityMap accessMap;
  Engine::ResourceManagers resourceManagers;
  uint16_t width, height;

  Engine::Common::Point start, finish;
private:
  //std::list<Entities::Door> doors;
  //std::list<Entities::Switch> buttons;
//  std::list<Entities::MovingPlatform> platforms;
  std::vector<EntityComponentSystem::Entity> entities;
  

  void loadTileSet(Engine::Common::JsonValue& tilesetArray, const std::string& path);
  void loadTileLayer(Engine::Common::JsonValue& layer, uint16_t width, EntityComponentSystem::World& w);

};

}

