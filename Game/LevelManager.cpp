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
#include "Game.h"
#include "Components\Motorial.h"
#include "Components\Region.h"
#include "Components\Movable.h"

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

  height = (uint16_t)(jsonData("layers").getArray()[0])("height").getInteger();
  width = (uint16_t)(jsonData("layers").getArray()[0])("width").getInteger();

  accessMap.createMap(height, width);

  //load tile sets

  loadTileSet(jsonData("tilesets"), path);

  //first load tiles;
  JsonValue data;
  for (auto& layer : jsonData("layers").getArray()) {
    std::string s = layer("type").getString();
    if (s == "tilelayer") {
      loadTileLayer(layer, width, w);
      data = layer("data");
      break;
    } 
  }

  //then load objects

  //we need to create switched after all other objects 
  std::vector<JsonValue> switches;
  std::map<size_t, Entity> triggerables;

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
          //uint16_t alternativeTextureId = static_cast<uint16_t>(data.getArray()[altidx].getInteger());

          sf::Sprite alterSprite(resourceManagers.getTileTexture(altidx), resourceManagers.getTileRectangle(altidx));
          
          doors.emplace_back(entities[idx], !isClosed, alterSprite);
          triggerables[std::stoul((x("properties"))("triggerable_id").getString())] = entities[idx];
        } else if (s == "platform") {
          entities.push_back(Game::getGameInstance()->world->createEntity());
          platforms.emplace_back(entities.back());
          entities.back().addComponent<Engine::Movable>(pos);
          uint16_t tileId = static_cast<uint16_t>(std::stoi((x("properties"))("tile_id").getString()));
          entities.back().addComponent<Engine::Drawable>(resourceManagers.getTileTexture(tileId), resourceManagers.getTileRectangle(tileId));
          entities.back().addComponent<Engine::Triggerable>(&platforms.back());
          entities.back().addComponent<Engine::Region>(pos, int16_t(0), int16_t(0), &platforms.back());
          auto str = x("properties")("bounds").getString();
          auto jv = JsonValue::fromString(str);
          auto arr = (jv).getArray();
          Engine::Common::Direction d;
          str = x("properties")("direction").getString();
          if (str == "left") d = Engine::Common::Direction::Left;
          if (str == "up") d = Engine::Common::Direction::Up;
          if (str == "down") d = Engine::Common::Direction::Down;
          if (str == "right") d = Engine::Common::Direction::Right;

          entities.back().addComponent<Engine::Motorial>(
            250.f,
            Engine::Common::Point{ static_cast<int16_t>(arr[0].getInteger()), static_cast<int16_t>(arr[1].getInteger()) },
            Engine::Common::Point{ static_cast<int16_t>(arr[2].getInteger()), static_cast<int16_t>(arr[3].getInteger()) },
            d,
            &platforms.back());
          triggerables[std::stoul((x("properties"))("triggerable_id").getString())] = entities.back();
          accessMap.setFree(pos);
        }
      }
    }
  }

  for (auto& x : switches) {
    uint16_t idx = std::stoi((x("properties"))("arr_pos").getString());
    Point pos = Point{ idx % width, idx / width };
    buttons.emplace_back(entities[idx], pos, 0, 0);
    auto str = x("properties")("switches").getString();
    auto jv = JsonValue::fromString(str);
    for (auto& dependency : (jv).getArray()) {
      buttons.back().bind(triggerables[dependency.getInteger()]);
    }
  }
}

void LevelManager::initLevel() {
  for (auto& d : doors) {
    d.init();
  }

  for (auto& p : platforms) {
    p.init();
  }

  for (auto e : entities) {
    e.activate();
  }
}

void LevelManager::loadTileLayer(JsonValue& layer, uint16_t width, EntityComponentSystem::World& w) {
  auto& data = layer("data").getArray();
  //load entities
  entities = w.createEntities(data.size());

  //check if we can walk on this thile
  for (uint16_t i = 0; i < data.size(); i++) {
    entities[i].addComponent<Engine::GamePosition>(Point{ i % width, i / width });
    uint16_t tileTypeId = static_cast<uint16_t>(data[i].getInteger());
    entities[i].addComponent<Engine::Drawable>(resourceManagers.getTileTexture(tileTypeId), resourceManagers.getTileRectangle(tileTypeId));
    entities[i].activate();

    if (resourceManagers.isWallType(tileTypeId)) {
      accessMap.setOccupied(Point{ i % width, i / width });
    }
  }
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
