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
using namespace Game;
using namespace Engine::Common;

LevelManager::LevelManager() {
}

void LevelManager::loadLevel(const std::string path, const std::string& levelfile, EntityComponentSystem::World& w){
  clear();
  std::ifstream t(path+levelfile);
  std::string jsonString((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
  auto& jsonData = JsonValue::fromString(jsonString);

  uint16_t height = (uint16_t)(jsonData("layers").getArray()[0])("height").getInteger();
  uint16_t width = (uint16_t)(jsonData("layers").getArray()[0])("width").getInteger();

  accessMap.createMap(height, width);

  //load tile sets

  loadTileSet(jsonData("tilesets"), path);

  //first element of layers section;
  for (auto& layer : jsonData("layers").getArray()) {
    std::string s = layer("type").getString();
    if (s == "tilelayer") {
      loadTileLayer(layer, width, w);
    } else {
      //process objects
      for (auto& x : layer("objects").getArray()) {
        std::string s = x("name").toString();
        if (s == "enter") {

        } else if (s == "exit") {

        }
      }
    }
   
  }
}

void LevelManager::loadTileLayer(JsonValue& layer, uint16_t width, EntityComponentSystem::World& w) {
  auto& data = layer("data").getArray();
  //load entities
  auto& tiles = w.createEntities(data.size());

  //check if we can walk on this thile
  for (uint16_t i = 0; i < (uint16_t)data.size(); i++) {
    tiles[i].addComponent<Engine::GamePosition>(Point{ i % width, i / width });
    tiles[i].addComponent<Engine::Drawable>(resourceManagers.getTileTexture(data[i].getInteger()), resourceManagers.getTileRectangle(data[i].getInteger()));
    tiles[i].activate();

    if (resourceManagers.isWallType(data[i].getInteger())) {
      accessMap.setOccupied(Point{ i % width, i / width });
    }
  }
}

void LevelManager::loadTileSet(JsonValue& tilesetArray, const std::string& path) {
  for (auto& tileset : tilesetArray.getArray()) {
    std::string imagefile = path + tileset("image").getString();
    uint16_t firstgid = (uint16_t)tileset("firstgid").getInteger();
    uint16_t tilecount = (uint16_t)tileset("tilecount").getInteger();

    uint16_t tileXside = (uint16_t)tileset("tileheight").getInteger();
    uint16_t tileYside = (uint16_t)tileset("tilewidth").getInteger();

    uint16_t  imgWidth = (uint16_t)tileset("imagewidth").getInteger();
    resourceManagers.loadTileSet(imagefile, firstgid, tilecount, imgWidth, tileXside, tileYside);

    if (tileset.contains("tileproperties")) {
      auto& props = tileset("tileproperties").getObject();
      for(auto& property : props) {
        if (property.second.contains("get_through") && property.second("get_through").getString() == "0") {
          resourceManagers.setTypeToWall(firstgid + std::stoi(property.first));
        }
      }
    }
  }
}



void LevelManager::clear() {
  accessMap.clear();
}

LevelManager::~LevelManager() {
}