#pragma once
#include <cstddef>

namespace EntityComponentSystem {
namespace detail {

typedef std::size_t TypeId;

template <typename TBase>
class ClassTypeId {
public:
  template <typename T>
  static TypeId GetTypeId() {
    static const TypeId id = nextTypeId++;
    return id;
  }

private:
  static TypeId nextTypeId;
};

template <typename TBase>
TypeId ClassTypeId<TBase>::nextTypeId = 0;

}
}
