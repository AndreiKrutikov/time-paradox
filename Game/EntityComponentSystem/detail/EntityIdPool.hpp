#pragma once
#include <vector>
#include <unordered_set>
#include <EntityComponentSystem/Entity.hpp>

namespace EntityComponentSystem {
namespace detail {

class EntityIdPool {
public:
  EntityIdPool(std::size_t poolSize);

  EntityIdPool(const EntityIdPool&) = delete;
  EntityIdPool(EntityIdPool&&) = delete;
  EntityIdPool& operator=(const EntityIdPool&) = delete;
  EntityIdPool& operator=(EntityIdPool&&) = delete;

  Entity::Id create();
  void remove(Entity::Id id);
  bool isValid(Entity::Id id) const;
  void clear();

private:
  std::size_t defaultPoolSize;
  std::size_t nextId;
  std::vector<Entity::Id> freeList;
  std::unordered_set<Entity::Id> entities;
};
}
}
