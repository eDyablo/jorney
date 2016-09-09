#pragma once

#include "tact/ActorPool.h"
#include <vector>

namespace tact {
  class TaskQueue;

  class DefaultActorPool : public ActorPool {
  public:
    DefaultActorPool(std::shared_ptr<TaskQueue> queue);

    bool IsEmpty() const override;

    std::shared_ptr<Actor> AddActor() override ;

  private:
    std::vector<std::shared_ptr<Actor>> m_Actors;
    std::shared_ptr<TaskQueue> m_Tasks;
  };
}