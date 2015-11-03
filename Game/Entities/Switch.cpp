#include "Switch.h"
using namespace EntityComponentSystem;
using namespace Engine;
namespace Entities {
  Switch::Switch(EntityComponentSystem::Entity e, const Common::Point & leftupCorner, int16_t height_, int16_t width_):Region(leftupCorner, height_, width_), e(e) {}
}