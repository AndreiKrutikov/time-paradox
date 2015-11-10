#include <EntityComponentSystem/System.hpp>
#include <algorithm>

using namespace EntityComponentSystem;

BaseSystem::BaseSystem() :
  world(nullptr) { }

BaseSystem::BaseSystem(const ComponentFilter& componentFilter) :
  componentFilter(componentFilter),
  world(nullptr) { }

BaseSystem::~BaseSystem() { }

const ComponentFilter& BaseSystem::getComponentFilter() const {
  return componentFilter;
}

World& BaseSystem::getWorld() const {
  return *world;
}

const std::vector<Entity>& BaseSystem::getEntities() const {
  return entities;
}

void BaseSystem::add(EntityComponentSystem::Entity &entity) {
  entities.push_back(entity);
  onEntityAdded(entity);
}

void BaseSystem::remove(EntityComponentSystem::Entity &entity) {
  entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());

  onEntityRemoved(entity);
}

void BaseSystem::setWorld(EntityComponentSystem::World &newWorld) {
  world = &newWorld;
  initialize();
}

