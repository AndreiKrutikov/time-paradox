#include <EntityComponentSystem/ComponentFilter.hpp>

using namespace EntityComponentSystem;

void ComponentFilter::clear() {
  requiredComponentsList.reset();
  requiresOneOfComponentsList.reset();
  excludeComponentsList.reset();
}

bool ComponentFilter::doesPassFilter(const ComponentTypeList &componentTypeList) const {
  if ((requiredComponentsList & componentTypeList) != requiredComponentsList) {
    return false;
  }

  if (requiresOneOfComponentsList.any() && (requiresOneOfComponentsList & componentTypeList).none()) {
    return false;
  }

  if (excludeComponentsList.any() && (excludeComponentsList & componentTypeList).any()) {
    return false;
  }

  return true;
}

