#include <cassert>
#include <EntityComponentSystem/detail/EntityComponentStorage.hpp>

using namespace EntityComponentSystem;
using namespace detail;

EntityComponentStorage::EntityComponentStorage(std::size_t entityAmount) :
  componentEntries(entityAmount) { }

void EntityComponentSystem::detail::EntityComponentStorage::addEntity(const Entity & entity) { 
  auto index = entity.getId();
  assert(componentEntries.size() >= index); //sic!
  if (index == componentEntries.size()) {
    componentEntries.emplace_back();
  }

  assert(componentEntries.at(index).componentTypeList.none());
  assert(componentEntries.at(index).components.empty());
}

void EntityComponentStorage::addComponent(Entity& entity, BaseComponent* component, TypeId componentTypeId) {
  assert(entity.isValid());
  auto index = entity.getId();
  assert(componentEntries.size() > index);
  auto& componentDataForEntity = componentEntries[index];
  componentDataForEntity.components[componentTypeId].reset(component);
  assert(componentTypeId < MAX_COMPONENTS_COUNT);
  componentDataForEntity.componentTypeList[componentTypeId] = true;
}

void EntityComponentStorage::removeComponent(Entity& entity, TypeId componentTypeId) {
  assert(entity.isValid());
  auto index = entity.getId();
  auto& componentDataForEntity = componentEntries[index];
  componentDataForEntity.components[componentTypeId].reset();
  componentDataForEntity.componentTypeList[componentTypeId] = false;
}

void EntityComponentStorage::removeAllComponents(Entity &entity) {
  auto index = entity.getId();
  auto& componentDataForEntity = componentEntries[index];
  componentDataForEntity.components.clear();
  componentDataForEntity.componentTypeList.reset();
}

BaseComponent& EntityComponentStorage::getComponent(const Entity& entity, TypeId componentTypeId) const {
  assert(entity.isValid() && hasComponent(entity, componentTypeId) && "Entity is not valid or does not contain component");
  return *getComponentsImpl(entity).at(componentTypeId);
}

ComponentTypeList EntityComponentStorage::getComponentTypeList(const Entity& entity) const {
  assert(entity.isValid());
  return componentEntries[entity.getId()].componentTypeList;
}

ComponentArray EntityComponentStorage::getComponents(const Entity& entity) const {
  assert(entity.isValid());
  auto& componentsToConvert = getComponentsImpl(entity);
  std::vector<std::reference_wrapper<BaseComponent>> temp;
  temp.reserve(componentsToConvert.size());
  for (auto& pair : componentsToConvert) {
    temp.push_back(*pair.second);
  }

  return temp;
}

bool EntityComponentStorage::hasComponent(const Entity& entity, TypeId componentTypeId) const {
  assert(entity.isValid());
  auto& components = getComponentsImpl(entity);
  return components.count(componentTypeId) > 0 && components.at(componentTypeId) != nullptr;
}

void EntityComponentStorage::clear() {
  componentEntries.clear();
}

EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e) {
  return componentEntries[e.getId()].components;
}

const EntityComponentStorage::ImplComponentArray& EntityComponentStorage::getComponentsImpl(const Entity &e) const {
  return componentEntries[e.getId()].components;
}
