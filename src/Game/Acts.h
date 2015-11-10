#pragma once

#include "Act.h"
#include "Common.h"
#include "Components\Triggerable.h"

namespace Game {

struct MoveAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;

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

  Engine::Common::Point position;
};

struct DisappearAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;
};

struct TriggerAct : Act {
  virtual bool execute() override;
  virtual void unexecute() override;
};

}
