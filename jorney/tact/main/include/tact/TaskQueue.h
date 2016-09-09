#pragma once

#include <memory>

namespace tact {
  class Task;

  class TaskQueue {
  public:
    virtual void AddTask(std::shared_ptr<Task> task) = 0;

    virtual std::shared_ptr<Task> GetNextTask() const = 0;

    virtual void Pop() = 0;

    virtual ~TaskQueue() {}

    bool IsEmpty() const {
      return GetNextTask() == nullptr;
    }
  };
}