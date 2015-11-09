#pragma once
#include "Common.h"

namespace Engine {
struct AccessabilityMap {
  AccessabilityMap();
  ~AccessabilityMap();
  AccessabilityMap(const AccessabilityMap& that) = delete;

  void createMap(uint16_t height, uint16_t width);
  void clear();

  void setFree(Engine::Common::Point point);
  void setOccupied(Engine::Common::Point point);
  void setDeadly(Engine::Common::Point point);

  bool isFree(Engine::Common::Point point);
  bool isOccupied(Engine::Common::Point point);
  bool isDeadly(Engine::Common::Point point);


private:
  uint8_t* data_;
  uint8_t** map_;
  uint16_t height;
  uint16_t width;
};
}
