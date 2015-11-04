#include "AccessabilityMap.h"

namespace EntityComponentSystem {

AccessabilityMap::AccessabilityMap():map_(nullptr), data_(nullptr) {}

void AccessabilityMap::createMap(uint16_t height, uint16_t width) {
  clear();
  data_ = new uint8_t[height*width];
  map_ = new uint8_t*[height];
  for (uint16_t i = 0; i < height; i++) {
    map_[i] = data_ + width*i;
  }
  for (uint16_t i = 0; i < height; i++) {
    for (uint16_t j = 0; j < width; j++) {
      map_[i][j] = 0;
    }
  }
}

void AccessabilityMap::clear() {
  delete[] map_;
  delete[] data_;
}

void AccessabilityMap::setFree(Engine::Common::Point point) {
  map_[point.y][point.x] = 0;
}

void AccessabilityMap::setOccupied(Engine::Common::Point point) {
  map_[point.y][point.x] = 1;
}

void AccessabilityMap::setDeadly(Engine::Common::Point point) {
  map_[point.y][point.x] = 2;
}

bool AccessabilityMap::isFree(Engine::Common::Point point) {
  return (map_[point.y][point.x] == 0);
}

bool AccessabilityMap::isOccupied(Engine::Common::Point point) {
  return !isFree(point);
}

bool AccessabilityMap::isDeadly(Engine::Common::Point point) {
  return (map_[point.y][point.x] == 2);
}

AccessabilityMap::~AccessabilityMap() {
  clear();
}

}