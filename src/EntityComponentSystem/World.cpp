#include <EntityComponentSystem/World.hpp>
#include <algorithm>
#include <cassert>

using namespace EntityComponentSystem;

void World::SystemDeleter::operator() (BaseSystem* system) const {
  system->world = nullptr;
  system->entities.clear();
}

World::World() :
  World(DEFAULT_ENTITY_POOL_SIZE) { }

World::World(std::size_t entityPoolSize) :
  entityIdPool(entityPoolSize),
  entityAttributes(entityPoolSize),
  componentStorage(entityPoolSize) { }

void World::removeAllSystems() {
  systems.clear();
}

Entity World::createEntity() {
  entityCache.alive.emplace_back(*this, entityIdPool.create());
  auto& entity = entityCache.alive.back();
  entityAttributes.addEntity(entity);
  componentStorage.addEntity(entity);
  return entity;
}

std::vector<Entity> World::createEntities(std::size_t amount) {
  std::vector<Entity> temp;
  temp.reserve(amount);
  for (decltype(amount) i = 0; i < amount; ++i) {
    temp.push_back(createEntity());
  }

  return temp;
}

void World::killEntity(Entity& entity) {
  deactivateEntity(entity);
  entityCache.killed.push_back(entity);
}

void World::killEntities(std::vector<Entity>& entities) {
  for (auto& i : entities) {
    killEntity(i);
  }
}

void World::activateEntity(Entity& entity) {
  assert(isValid(entity));
  entityCache.activated.push_back(entity);
}

void World::deactivateEntity(Entity& entity) {
  assert(isValid(entity));
  entityCache.deactivated.push_back(entity);
}

bool World::isActivated(const Entity& entity) const {
  assert(isValid(entity));
  return entityAttributes.attributes[entity.getId()].activated;
}

bool World::isValid(const EntityComponentSystem::Entity &entity) const {
  return entityIdPool.isValid(entity.getId());
}

void World::refresh() {
  for (auto& entity : entityCache.activated) {
    auto& attribute = entityAttributes.attributes[entity.getId()];
    attribute.activated = true;
    for (auto& pair : systems) {
      auto systemIndex = pair.first;
      if (pair.second->getComponentFilter().doesPassFilter(componentStorage.getComponentTypeList(entity))) {
        if (!attribute.systems[systemIndex]) {
          pair.second->add(entity);
          assert(systemIndex < MAX_SYSTEMS_COUNT);
          attribute.systems[systemIndex] = true;
        }
      } else if (attribute.systems[systemIndex]) {
        pair.second->remove(entity);
        attribute.systems[systemIndex] = false;
      }
    }
  }
  
  for (auto& entity : entityCache.deactivated) {
    auto& attribute = entityAttributes.attributes[entity.getId()];
    attribute.activated = false;
    for (auto& pair : systems) {
      auto systemIndex = pair.first;
      if (attribute.systems[systemIndex]) {
        pair.second->remove(entity);
        attribute.systems[systemIndex] = false;
      }
    }
  }

  for (auto& entity : entityCache.killed) {
    entityCache.alive.erase(std::remove(entityCache.alive.begin(), entityCache.alive.end(), entity), entityCache.alive.end());
    componentStorage.removeAllComponents(entity);
    entityAttributes.removeEntity(entity);
    entityIdPool.remove(entity.getId());
  }

  entityCache.clearTemp();
}

void World::clear() {
  removeAllSystems(); 
  componentStorage.clear();
  entityAttributes.clear();
  entityCache.clear();
  entityIdPool.clear();
}

std::size_t World::getEntityCount() const {
  return entityCache.alive.size();
}

const World::EntityArray& World::getEntities() const {
  return entityCache.alive;
}

void World::addSystem(BaseSystem& system, detail::TypeId systemTypeId) {
  assert(!system.world && "System is already contained within a World");
  systems[systemTypeId].reset(&system);
  system.world = this;
  system.initialize();
}

void World::removeSystem(detail::TypeId systemTypeId) {
  assert(doesSystemExist(systemTypeId) && "System does not exist in world");
  systems.erase(systemTypeId);
}

bool World::doesSystemExist(detail::TypeId systemTypeId) const {
  return systems.find(systemTypeId) != systems.end();
}

Entity World::getEntity(Entity::Id id) {
  return Entity{ *this, id };
}
