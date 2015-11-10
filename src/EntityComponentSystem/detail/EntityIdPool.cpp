#include <EntityComponentSystem/detail/EntityIdPool.hpp>

using namespace EntityComponentSystem;
using namespace detail;

EntityIdPool::EntityIdPool(std::size_t poolSize) :
  defaultPoolSize(poolSize),
  nextId(0),
  entities(poolSize) { }

Entity::Id EntityIdPool::create() {
  Entity::Id id;

  if (!freeList.empty()) {
    id = freeList.back();
    freeList.pop_back();
  } else {
    id = nextId++;
    entities.insert(id);
  }

  return id;
}

void EntityIdPool::remove(Entity::Id id) {
  freeList.emplace_back(id);
}

bool EntityIdPool::isValid(Entity::Id id) const {
  return entities.count(id) > 0;
}

void EntityIdPool::clear() {
  entities.clear();
  freeList.clear();
  nextId = 0;

  entities.reserve(defaultPoolSize);
}
