#pragma once
#include <cstddef>
#include <vector>

#include <EntityComponentSystem/detail/ClassTypeId.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/ComponentFilter.hpp>

namespace EntityComponentSystem {

class World;

class BaseSystem {
public:
  BaseSystem();
  BaseSystem(const ComponentFilter& componentFilter);
  virtual ~BaseSystem() = 0;
  const ComponentFilter& getComponentFilter() const;
  World& getWorld() const;
  const std::vector<Entity>& getEntities() const;

private:
  virtual void initialize() { }
  virtual void onEntityAdded(Entity& entity) { }
  virtual void onEntityRemoved(Entity& entity) { }

  void add(Entity& entity);
  void remove(Entity& entity);
  void setWorld(World& world);

  ComponentFilter componentFilter;
  std::vector<Entity> entities;
  World* world;

  friend class World;
};

template <typename T>
class System : public BaseSystem {
public:
  typedef System<T> Base;

  System() { }
  System(const ComponentFilter& componentFilter) : BaseSystem(componentFilter) { }
  
  static detail::TypeId GetTypeId() {
    return detail::ClassTypeId<BaseSystem>::GetTypeId<T>();
  }  
};

}
