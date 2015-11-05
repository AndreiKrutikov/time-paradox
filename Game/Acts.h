#pragma once

#include "Act.h"
#include "Common.h"
#include <functional>

namespace Game {

struct AccessabilityChangeAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  uint8_t before;
  uint8_t after;
  Engine::Common::Point point;
};

struct FunctorialAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  std::function<bool(void)> exec;
  std::function<void(void)> unexec;
};


struct MoveAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  EntityComponentSystem::Entity entity;
  Engine::Common::Direction direction;
};

struct UnconditionalMoveAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  Engine::Common::Direction direction;
};

struct SpawnAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  EntityComponentSystem::Entity entity;
  Engine::Common::Point position;
};

struct DisappearAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

  EntityComponentSystem::Entity entity;
};


}
