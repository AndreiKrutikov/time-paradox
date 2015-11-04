#include "ResourceManagers.h"
using namespace Engine;
ResourceManagers::ResourceManagers() {
}

void ResourceManagers::loadFont(const std::string& name, const std::string& filename) {
  sf::Font newFont;
  newFont.loadFromFile(filename);
  fonts[name] = newFont;
}

sf::Font & ResourceManagers::getFont(const std::string & name) {
  return fonts[name];
}

void ResourceManagers::loadTileSet(const std::string & imgName, uint16_t firstgid, uint16_t tilecont, uint16_t imgwidth, uint16_t tileXside, uint16_t tileYside) {
  sf::Texture texture;
  texture.loadFromFile(imgName);
  tile_textures.push_back(texture);
  
  //tileset params
  uint16_t m = imgwidth / tileXside;

  //-1 - count from 0
  for (uint16_t i = 0; i < tilecont; i++) {
    sf::IntRect tmp;
    tmp.left = tileXside*(i%m);
    tmp.top = tileYside*(i / m);
    tmp.height = tileYside;
    tmp.width = tileXside;

    tile_rects[firstgid + i] = tmp;
    idToTexture[firstgid + i] = (uint16_t)tile_textures.size()-1;
  }
}

sf::Texture& ResourceManagers::getTileTexture(uint16_t id) {
  return tile_textures[idToTexture[id]];
}

sf::IntRect & ResourceManagers::getTileRectangle(uint16_t id) {
  return tile_rects[id];
}

void ResourceManagers::clear() {
  tile_rects.clear();
  tile_textures.clear();
  fonts.clear();
}

void Engine::ResourceManagers::setTypeToWall(uint16_t tileType) {
  flags[tileType] |= 0x0001;
}

bool Engine::ResourceManagers::isWallType(uint16_t tileType) {
  return flags[tileType] & 0x0001;
}

ResourceManagers::~ResourceManagers() {
}
