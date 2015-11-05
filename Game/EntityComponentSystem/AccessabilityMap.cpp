#include "AccessabilityMap.h"

namespace EntityComponentSystem {

AccessabilityMap::AccessabilityMap():map_(nullptr), data_(nullptr) {}

void AccessabilityMap::createMap(uint16_t height, uint16_t width) {
  this->height = height;
  this->width = width;
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
  if (point.y < 0 || point.x < 0 || point.y >= height || point.x >= width) return false;
  return (map_[point.y][point.x] == 0);
}

bool AccessabilityMap::isOccupied(Engine::Common::Point point) {
  return !isFree(point);
}

bool AccessabilityMap::isDeadly(Engine::Common::Point point) {
  return (map_[point.y][point.x] == 2);
}

uint8_t AccessabilityMap::setType(Engine::Common::Point point, uint8_t newType) {
  uint8_t old = map_[point.y][point.x];
  map_[point.y][point.x] = newType;
  return old;
}

AccessabilityMap::~AccessabilityMap() {
  clear();
}

}