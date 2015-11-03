#pragma once
#include <cstddef>
#include <vector>
#include <functional>

#include <EntityComponentSystem/detail/ClassTypeId.hpp>

namespace EntityComponentSystem {

class BaseComponent {
public:
  virtual ~BaseComponent() { }
};

template <typename T>
class Component : public BaseComponent {
public:
  static detail::TypeId GetTypeId() {
    return detail::ClassTypeId<BaseComponent>::GetTypeId<T>();
  }
};

typedef std::vector<std::reference_wrapper<BaseComponent>> ComponentArray;

}
