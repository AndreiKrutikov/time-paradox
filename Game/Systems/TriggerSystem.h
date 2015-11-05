#pragma once
#include <EntityComponentSystem/System.hpp>
#include "../Components/Trigger.h"
#include "../Components/Triggerable.h"
#include <map>
#include <unordered_set>

namespace Engine {

class TriggerSystem : public EntityComponentSystem::System<TriggerSystem> {
public:
  TriggerSystem();
  void update();

  virtual void onEntityAdded(EntityComponentSystem::Entity& entity) override;
  virtual void onEntityRemoved(EntityComponentSystem::Entity& entity)override;

private:
  std::unordered_set<EntityComponentSystem::Entity> triggerables;
};

}
