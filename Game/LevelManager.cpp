#include "LevelManager.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "Utils\JsonValue.h"
#include <iostream>
#include "Common.h"
#include "Components\GamePosition.h"
#include "Components\Drawable.h"
using namespace EntityComponentSystem;
using namespace Engine::Common;
LevelManager::LevelManager() {
}

LevelManager::LevelManager(const std::string& filename, World& w) {
  loadLevel(filename, w);
}

void LevelManager::loadLevel(const std::string& filename, World& w) {
  accessMap.clear();
  std::ifstream t(filename);
  std::string jsonString((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  auto& jsonData = JsonValue::fromString(jsonString);
  
  //first element of layers section;
  auto& data = (jsonData("layers").getArray()[0])("data").getArray();

  uint16_t height = (uint16_t)(jsonData("layers").getArray()[0])("height").getInteger();
  uint16_t width = (uint16_t)(jsonData("layers").getArray()[0])("width").getInteger();
  accessMap.createMap(height, width);

  //basic path. RODO - remove

  std::string s = "maps\\denis\\";

  for (auto& tileset : jsonData("tilesets").getArray()) {
    resourceManagers.loadTileSet(s+tileset("image").getString(), (uint16_t)tileset("firstgid").getInteger(), (uint16_t)tileset("tilecount").getInteger());
  }

  auto& tiles = w.createEntities(data.size());
  for (uint16_t i = 0; i < (uint16_t)data.size(); i++) {
    tiles[i].addComponent<Engine::GamePosition>(Point{ i % width, i / width });

    tiles[i].addComponent<Engine::Drawable>(resourceManagers.getTileTexture(data[i].getInteger()), resourceManagers.getTileRectangle(data[i].getInteger()));
    
    tiles[i].activate();
  }
}

LevelManager::~LevelManager() {
}