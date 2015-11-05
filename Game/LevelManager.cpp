#include "LevelManager.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <map>
#include "Utils\JsonValue.h"
#include <iostream>
#include "Common.h"
#include "Components\GamePosition.h"
#include "Components\Drawable.h"
#include "Entities\Door.h"
#include "Entities\Switch.h"

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

  //first load tiles;
  JsonValue data;
  EntityComponentSystem::World::EntityArray entities;
  for (auto& layer : jsonData("layers").getArray()) {
    std::string s = layer("type").getString();
    if (s == "tilelayer") {
      entities = loadTileLayer(layer, width, w);
      data = layer("data");
      break;
    } 
  }

  //then load objects

  //we need to create switched after all other objects 
  std::vector<JsonValue> switches;
  std::map<std::string, Entity> triggerables;

  for (auto& layer : jsonData("layers").getArray()) {
    std::string s = layer("type").getString();
    if (s == "objectgroup") {
      //process objects
      for (auto& x : layer("objects").getArray()) {
        std::string s = x("type").getString();
        uint16_t idx = std::stoi((x("properties"))("arr_pos").getString());
        Point pos = Point{ idx % width, idx / width };
        if (s == "enter") {
          start = pos;
        } else if (s == "exit") {
          finish = pos;
        } else if (s == "button") {
          switches.push_back(x);
        } else if (s == "door") {
          
          bool isClosed = (x("properties"))("is_locked").getString() == "1";
          uint16_t altidx = static_cast<uint16_t>(std::stoi((x("properties"))("paired_tile").getString()));
          uint16_t textureId = static_cast<uint16_t>(data.getArray()[idx].getInteger());
          uint16_t alternativeTextureId = static_cast<uint16_t>(data.getArray()[altidx].getInteger());

          sf::Sprite alterSprite(resourceManagers.getTileTexture(alternativeTextureId), resourceManagers.getTileRectangle(alternativeTextureId));
          
          Entities::Door d(entities[idx], accessMap, !isClosed, alterSprite);
          triggerables[x("name").getString()] = d.e;
        } else if (s == "platform") {
          //todo
        }
      }
    }
  }

  for (auto& x : switches) {
    uint16_t idx = std::stoi((x("properties"))("arr_pos").getString());
    Point pos = Point{ idx % width, idx / width };
    Entities::Switch s(entities[idx], pos, 1, 1);
    for (auto& dependency : (x("properties")("switches")).getArray()) {
      s.bind(triggerables[dependency.getString()]);
    }
  }
}

EntityComponentSystem::World::EntityArray LevelManager::loadTileLayer(JsonValue& layer, uint16_t width, EntityComponentSystem::World& w) {
  auto& data = layer("data").getArray();
  //load entities
  auto& tiles = w.createEntities(data.size());

  //check if we can walk on this thile
  for (uint16_t i = 0; i < data.size(); i++) {
    tiles[i].addComponent<Engine::GamePosition>(Point{ i % width, i / width });
    uint16_t pos = static_cast<uint16_t>(data[i].getInteger());
    tiles[i].addComponent<Engine::Drawable>(resourceManagers.getTileTexture(pos), resourceManagers.getTileRectangle(pos));
    tiles[i].activate();

    if (resourceManagers.isWallType(pos)) {
      accessMap.setOccupied(Point{ i % width, i / width });
    }
  }
  return tiles;
}

void LevelManager::loadTileSet(JsonValue& tilesetArray, const std::string& path) {
  for (auto& tileset : tilesetArray.getArray()) {
    std::string imagefile = path + tileset("image").getString();
    uint16_t firstgid =  static_cast<uint16_t>(tileset("firstgid").getInteger());
    uint16_t tilecount = static_cast<uint16_t>(tileset("tilecount").getInteger());

    uint16_t tileXside = static_cast<uint16_t>(tileset("tileheight").getInteger());
    uint16_t tileYside = static_cast<uint16_t>(tileset("tilewidth").getInteger());

    uint16_t  imgWidth = static_cast<uint16_t>(tileset("imagewidth").getInteger());
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