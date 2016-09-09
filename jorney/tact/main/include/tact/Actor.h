#pragma once

#include <memory>

namespace tact {
  class Task;
  
  class Actor {
  public:
    virtual bool HasPendingTasks() const = 0;

    virtual void AddTask(std::shared_ptr<Task> task) = 0;

    virtual void Activate() = 0;

    virtual void Deactivate() = 0;

    virtual ~Actor() {}
  };
}