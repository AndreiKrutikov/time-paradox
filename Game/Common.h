#pragma once
#include <cstdint>

namespace Engine { namespace Common {

enum class Direction {
  Up, Down, Left, Right
};

Direction getOpposite(Direction d); 

struct Point {
  int16_t x;
  int16_t y;

  Point operator+(Direction d) {
    Point p{ x, y };
    switch (d) {
    case Direction::Up:
      p.y--;
      break;
    case Direction::Down:
      p.y++;
      break;
    case Direction::Left:
      p.x--;
      break;
    case Direction::Right:
      p.x++;
      break;
    }

    return p;
  }

  bool operator==(Point p) const {
    return x == p.x && y == p.y;
  }
};

} }
