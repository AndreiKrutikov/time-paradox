#pragma once
#include <type_traits>
#include <cassert>

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/TypeLists.hpp>
#include <EntityComponentSystem/detail/EntityIdPool.hpp>

namespace EntityComponentSystem {

class ComponentFilter {
public:
  ComponentFilter() { }
  ComponentFilter(const ComponentFilter&) = default;
  ComponentFilter(ComponentFilter&&) = default;
  ComponentFilter& operator=(const ComponentFilter&) = default;
  ComponentFilter& operator=(ComponentFilter&&) = default;

  template <typename C1>
  ComponentFilter& requires() {
    static_assert(std::is_base_of<BaseComponent, C1>::value, "C1 does not inherit from Component");

    assert(C1::GetTypeId() < MAX_COMPONENTS_COUNT);
    requiredComponentsList[C1::GetTypeId()] = true;
    return *this;
  }

  template <typename C1>
  ComponentFilter& requiresOneOf() {
    static_assert(std::is_base_of<BaseComponent, C1>::value, "C1 does not inherit from Component");

    assert(C1::GetTypeId() < MAX_COMPONENTS_COUNT);
    requiresOneOfComponentsList[C1::GetTypeId()] = true;
    return *this;
  }

  template <typename C1>
  ComponentFilter& excludes() {
    static_assert(std::is_base_of<BaseComponent, C1>::value, "C1 does not inherit from Component");

    assert(C1::GetTypeId() < MAX_COMPONENTS_COUNT);
    excludeComponentsList[C1::GetTypeId()] = true;
    return *this;
  }

  template <typename C1, typename C2, typename... Components>
  ComponentFilter& requires() {
    requires<C1>();
    requires<C2, Components...>();
    return *this;
  }

  template <typename C1, typename C2, typename... Components>
  ComponentFilter& requiresOneOf() {
    requiresOneOf<C1>();
    requiresOneOf<C2, Components...>();
    return *this;
  }

  template <typename C1, typename C2, typename... Components>
  ComponentFilter& excludes() {
    excludes<C1>();
    excludes<C2, Components...>();
    return *this;
  }

  bool doesPassFilter(const ComponentTypeList& componentTypeList) const;
  void clear();

private:
  ComponentTypeList requiredComponentsList;
  ComponentTypeList requiresOneOfComponentsList;
  ComponentTypeList excludeComponentsList;
};

}
