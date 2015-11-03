#pragma once
#include <bitset>

namespace EntityComponentSystem {

const size_t MAX_COMPONENTS_COUNT = 64;
const size_t MAX_SYSTEMS_COUNT = 64;
typedef std::bitset<MAX_COMPONENTS_COUNT> ComponentTypeList;
typedef std::bitset<MAX_SYSTEMS_COUNT> SystemTypeList;

}
