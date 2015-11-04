#pragma once
#include "EntityComponentSystem\AccessabilityMap.h"
#include "ResourceManagers.h"
#include "EntityComponentSystem\World.hpp"
#include "Utils\JsonValue.h"
#include <string>
#include <map>
namespace Game {

struct LevelManager {
  LevelManager();
  
  void loadLevel(const std::string path,const std::string& levelfile, EntityComponentSystem::World& w);

  void clear();

  ~LevelManager();

  EntityComponentSystem::AccessabilityMap accessMap;
  Engine::ResourceManagers resourceManagers;
private:
  Engine::Common::Point start, finish;
  
  void loadTileSet(Engine::Common::JsonValue& tilesetArray, const std::string& path);
  void loadTileLayer(Engine::Common::JsonValue& layer, uint16_t width, EntityComponentSystem::World& w);

};

}

