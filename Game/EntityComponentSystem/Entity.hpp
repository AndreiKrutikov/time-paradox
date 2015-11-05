#pragma once
#include <type_traits>
#include <cstdint>
#include <EntityComponentSystem/detail/ClassTypeId.hpp>
#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/TypeLists.hpp>

namespace EntityComponentSystem {

class World;

class Entity {
public:
  typedef uint64_t Id;

  Entity();
  Entity(World& world, Id id);

  Entity(const Entity&) = default;
  Entity(Entity&&) = default;
  Entity& operator=(const Entity&) = default;
  Entity& operator=(Entity&&) = default;

  bool isValid() const;

  const Id& getId() const;
  World& getWorld() const;
  bool isActivated() const;
  void activate();
  void deactivate();
  void kill();

  template <typename T>
  T& addComponent(T* component);

  template <typename T, typename... Args>
  T& addComponent(Args&&... args);

  template <typename T>
  void removeComponent();

  void removeAllComponents();

  template <typename T>
  T& getComponent() const;

  template <typename T>
  bool hasComponent() const;

  ComponentArray getComponents() const;
  ComponentTypeList getComponentTypeList() const;

  bool operator==(const Entity& entity) const;
  bool operator!=(const Entity& entity) const {
    return !operator==(entity);
  }

private:
  void addComponent(BaseComponent* component, detail::TypeId componentTypeId);
  void removeComponent(detail::TypeId componentTypeId);
  BaseComponent& getComponent(detail::TypeId componentTypeId) const;
  bool hasComponent(detail::TypeId componentTypeId) const;

  Id id;
  World* world;
};

template <typename T>
T& Entity::addComponent(T* component) {
  static_assert(std::is_base_of<BaseComponent, T>::value, "T is not a component, cannot add T to entity");
  addComponent(component, T::GetTypeId());
  return *component;
}

template <typename T, typename... Args>
T& Entity::addComponent(Args&&... args) {
  return addComponent<T>(new T{ std::forward<Args>(args)... });
}

template <typename T>
void Entity::removeComponent() {
  static_assert(std::is_base_of<BaseComponent, T>::value, "T is not a component, cannot remove T from entity");
  removeComponent(T::GetTypeId());
}

template <typename T>
T& Entity::getComponent() const {
  static_assert(std::is_base_of<BaseComponent, T>::value, "T is not a component, cannot retrieve T from entity");
  return static_cast<T&>(getComponent(T::GetTypeId()));
}

template <typename T>
bool Entity::hasComponent() const {
  static_assert(std::is_base_of<BaseComponent, T>::value, "T is not a component, cannot determine if entity has T");
  return hasComponent(T::GetTypeId());
}

}

namespace std {
template <> struct hash<EntityComponentSystem::Entity> {
  size_t operator()(const EntityComponentSystem::Entity & e) const {
    return e.getId();
  }
};
}

