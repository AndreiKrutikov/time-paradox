#include "ResourceManagers.h"

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

void ResourceManagers::loadTileSet(const std::string & imgName, uint16_t firstgid, uint16_t tilecont) {
  sf::Texture texture;
  texture.loadFromFile(imgName);
  tile_textures.push_back(texture);
  
  //т.к нумерация с нуля
  uint16_t tileXSide = 32;
  uint16_t tileYSide = 32;
  
  //tileset params
  uint16_t n = texture.getSize().y / tileYSide;
  uint16_t m = texture.getSize().x / tileXSide;

  //-1 - count from 0
  for (uint16_t i = 0; i < tilecont; i++) {
    sf::IntRect tmp;
    tmp.left = tileXSide*(i%m);
    tmp.top = tileYSide*(i / m);
    tmp.height = tileYSide;
    tmp.width = tileXSide;

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

ResourceManagers::~ResourceManagers() {
}
