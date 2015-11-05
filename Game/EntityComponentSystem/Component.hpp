#pragma once
#include <cstddef>
#include <vector>
#include <functional>

#include <EntityComponentSystem/detail/ClassTypeId.hpp>


#include <iostream>
#include <typeinfo>


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
  
  virtual ~Component() {
    std::cerr << "~ " << typeid(T).name() << std::endl;
  }

};

typedef std::vector<std::reference_wrapper<BaseComponent>> ComponentArray;

}
