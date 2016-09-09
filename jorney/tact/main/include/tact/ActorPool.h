#pragma once

#include <memory>

namespace tact {
  class Actor;

  class ActorPool {
  public:
    virtual bool IsEmpty() const = 0;

    virtual std::shared_ptr<Actor> AddActor() = 0;

    virtual ~ActorPool() {}
  };
}