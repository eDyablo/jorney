#include "tact/DefaultActor.h"

namespace tact {
  class InactiveState : public DefaultActor::State {
    void Activate(DefaultActor& actor) override {
      actor.SetState(DefaultActor::kActive);
      actor.ActivateItself();
    }

    void Deactivate(DefaultActor& actor) override {
    }

    void Execute(DefaultActor& actor) override {
    }
  } inactiveState;

  DefaultActor::State& DefaultActor::kInactive = inactiveState;
}