#include <cassert>
#include <EntityComponentSystem/Entity.hpp>
#include <EntityComponentSystem/World.hpp>

using namespace EntityComponentSystem;

Entity::Entity() :
  world(nullptr) {
}

Entity::Entity(World& world, Entity::Id id) :
  id(id),
  world(&world) {
}

World& Entity::getWorld() const {
  assert(world != nullptr);

  return *world;
}

const Entity::Id& Entity::getId() const {
  return id;
}

bool Entity::isValid() const {
  //Allows an empty Entity handle to be checked.
  if (world == nullptr)
    return false;

  return getWorld().isValid(*this);
}

bool Entity::isActivated() const {
  return getWorld().isActivated(*this);
}

void Entity::activate() {
  getWorld().activateEntity(*this);
}

void Entity::deactivate() {
  getWorld().deactivateEntity(*this);
}

void Entity::kill() {
  getWorld().killEntity(*this);
}

void Entity::removeAllComponents() {
  getWorld().componentStorage.removeAllComponents(*this);
}

ComponentArray Entity::getComponents() const {
  return getWorld().componentStorage.getComponents(*this);
}

ComponentTypeList Entity::getComponentTypeList() const {
  return getWorld().componentStorage.getComponentTypeList(*this);
}

bool Entity::operator==(const EntityComponentSystem::Entity &entity) const {
  return id == entity.id && entity.world == world;
}

void Entity::addComponent(BaseComponent* component, detail::TypeId componentTypeId) {
  getWorld().componentStorage.addComponent(*this, component, componentTypeId);
}

void Entity::removeComponent(detail::TypeId componentTypeId) {
  getWorld().componentStorage.removeComponent(*this, componentTypeId);
}

BaseComponent& Entity::getComponent(detail::TypeId componentTypeId) const {
  return getWorld().componentStorage.getComponent(*this, componentTypeId);
}

bool Entity::hasComponent(detail::TypeId componentTypeId) const {
  return getWorld().componentStorage.hasComponent(*this, componentTypeId);
}


