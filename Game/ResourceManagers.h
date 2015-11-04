#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <vector>


class ResourceManagers {
public:
  ResourceManagers();
  void loadFont(const std::string& name, const std::string& filename);
  sf::Font& getFont(const std::string& name);
  void loadTileSet(const std::string& imgName, uint16_t firstgid, uint16_t tilecont);
  sf::Texture& getTileTexture(uint16_t id);
  sf::IntRect& getTileRectangle(uint16_t id);
  void clear();
  ~ResourceManagers();
private:
  std::map<std::string, sf::Font> fonts;
  std::map<uint16_t, uint16_t> idToTexture;
  std::vector<sf::Texture> tile_textures;
  std::map<uint16_t, sf::IntRect> tile_rects;

};

