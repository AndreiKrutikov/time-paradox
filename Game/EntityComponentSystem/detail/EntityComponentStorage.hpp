#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

#include <EntityComponentSystem/detail/ClassTypeId.hpp>
#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/TypeLists.hpp>

namespace EntityComponentSystem {
namespace detail {

class EntityComponentStorage {
public:
  EntityComponentStorage(std::size_t entityAmount);

  EntityComponentStorage(const EntityComponentStorage&) = delete;
  EntityComponentStorage(EntityComponentStorage&&) = delete;
  EntityComponentStorage& operator=(const EntityComponentStorage&) = delete;
  EntityComponentStorage& operator=(EntityComponentStorage&&) = delete;

  void addEntity(const Entity& entity);
  void addComponent(Entity& entity, BaseComponent* component, TypeId componentTypeId);
  void removeComponent(Entity& entity, TypeId componentTypeId);
  void removeAllComponents(Entity& entity);
  BaseComponent& getComponent(const Entity& entity, TypeId componentTypeId) const;
  ComponentTypeList getComponentTypeList(const Entity& entity) const;
  ComponentArray getComponents(const Entity& entity) const;
  bool hasComponent(const Entity& entity, TypeId componentTypeId) const;
  void clear();

private:
  typedef std::unordered_map<TypeId, std::unique_ptr<BaseComponent> > ImplComponentArray;

  struct EntityComponents {
    EntityComponents() = default;
    //EntityComponents(EntityComponents&& e)
    //  : components(std::move(e.components)),
    //  componentTypeList(std::move(e.componentTypeList)) { }

    ImplComponentArray components;
    ComponentTypeList componentTypeList;
  };

  std::vector<EntityComponents> componentEntries;

  ImplComponentArray& getComponentsImpl(const Entity& e);
  const ImplComponentArray& getComponentsImpl(const Entity& e) const;
};

}
}
