#pragma once
#include <cstdint>

namespace Engine { namespace Common {

struct Point {
  int16_t x;
  int16_t y;
};

enum class Direction {
  Up, Down, Left, Right
};

} }
