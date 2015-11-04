#pragma once
#include <cassert>
#include <memory>
#include <vector>
#include <unordered_map>
#include <type_traits>

#include <EntityComponentSystem/detail/EntityIdPool.hpp>
#include <EntityComponentSystem/detail/EntityComponentStorage.hpp>
#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/System.hpp>

namespace EntityComponentSystem {

const size_t DEFAULT_ENTITY_POOL_SIZE = 1000;

class World {
public:
  typedef std::vector<Entity> EntityArray;

  World();
  World(std::size_t entityPoolSize);

  World(const World& world) = delete;
  World(World&& world) = delete;
  World& operator=(const World&) = delete;
  World& operator=(World&&) = delete;

  template <typename TSystem>
  void addSystem(TSystem& system);

  template <typename TSystem>
  void removeSystem();

  template <typename TSystem>
  bool doesSystemExist() const;

  template <typename TSystem>
  bool doesSystemExist(const TSystem& system) const;

  void removeAllSystems();
  Entity createEntity();
  EntityArray createEntities(std::size_t amount);
  void killEntity(Entity& entity);
  void killEntities(std::vector<Entity>& entities);
  void activateEntity(Entity& entity);
  void deactivateEntity(Entity& entity);
  bool isActivated(const Entity& entity) const;
  bool isValid(const Entity& entity) const;
  void refresh();
  void clear();
  std::size_t getEntityCount() const;
  const EntityArray& getEntities() const;
  Entity getEntity(Entity::Id id);

private:
  struct SystemDeleter {
    void operator() (BaseSystem* system) const;
  };

  struct Attribute {
    bool activated;
    SystemTypeList systems;
  };
  
  struct EntityAttributesStorage { 
    EntityAttributesStorage(size_t size) : attributes(size) { }

    void addEntity(const Entity& entity) { 
      auto index = entity.getId();
      assert(attributes.size() >= index); //sic!
      if (index == attributes.size()) {
        attributes.emplace_back();
      }

      assert(attributes.at(index).systems.none());
      assert(!attributes.at(index).activated);
    }

    void removeEntity(Entity& entity) { 
      auto index = entity.getId();
      assert(attributes.size() > index);
      
      attributes.at(index).systems.reset();
      attributes.at(index).activated = false;
    }

    void clear() { 
      attributes.clear();
    }

    std::vector<Attribute> attributes;
  };

  struct EntityCache {
    EntityArray alive;
    EntityArray killed;
    EntityArray activated;
    EntityArray deactivated;
    EntityArray componentsChanged;

    void clearTemp() {
      killed.clear();
      activated.clear();
      deactivated.clear();
      componentsChanged.clear();
    }

    void clear() {
      alive.clear();
      clearTemp();
    }
  };

  typedef std::unordered_map<detail::TypeId, std::unique_ptr<BaseSystem, SystemDeleter>> SystemArray;

  SystemArray systems;
  detail::EntityIdPool entityIdPool;
  detail::EntityComponentStorage componentStorage;
  EntityAttributesStorage entityAttributes;
  EntityCache entityCache;

  //void checkForResize(std::size_t amountOfEntitiesToBeAllocated);
  //void resize(std::size_t amount);

  void addSystem(BaseSystem& system, detail::TypeId systemTypeId);
  void removeSystem(detail::TypeId systemTypeId);
  bool doesSystemExist(detail::TypeId systemTypeId) const;

  friend class Entity;
};

template <typename TSystem>
void World::addSystem(TSystem& system) {
  static_assert(std::is_base_of<BaseSystem, TSystem>::value, "Template argument does not inherit from BaseSystem");
  addSystem(system, TSystem::GetTypeId());
}

template <typename TSystem>
void World::removeSystem() {
  static_assert(std::is_base_of<BaseSystem, TSystem>::value, "Template argument does not inherit from BaseSystem");
  removeSystem(TSystem::GetTypeId());
}

template <typename TSystem>
bool World::doesSystemExist() const {
  static_assert(std::is_base_of<BaseSystem, TSystem>::value, "Template argument does not inherit from BaseSystem");
  return doesSystemExist(TSystem::GetTypeId());
}

template <typename TSystem>
bool World::doesSystemExist(const TSystem& system) const {
  static_assert(std::is_base_of<BaseSystem, TSystem>::value, "Template argument does not inherit from BaseSystem");
  return system.world == this && doesSystemExist<TSystem>();
}

}
