#include "tact/DefaultActor.h"

namespace tact {
  class ActiveState : public DefaultActor::State {
    void Activate(DefaultActor& actor) override {
    }

    void Deactivate(DefaultActor& actor) override {
      actor.SetState(DefaultActor::kInactive);
      actor.DeactivateItself();
    }

    void Execute(DefaultActor& actor) override {
      actor.ScheduleTask();
    }
  } activeState;

  DefaultActor::State& DefaultActor::kActive = activeState;
}