#include "Common.h"

using namespace Engine;
using namespace Engine::Common;

Direction Engine::Common::getOpposite(Direction d) {
  switch (d) {
  case Direction::Up:
    return Direction::Down;
  case Direction::Down:
    return Direction::Up;
  case Direction::Left:
    return Direction::Right;
  case Direction::Right:
    return Direction::Left;
  }
}
